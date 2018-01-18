#include "../includes/model_library.h"

#include <syslog.h>


double exp2(double x) {
  x = 1.0 + x / 1024;
  x *= x; x *= x; x *= x; x *= x;
  x *= x; x *= x; x *= x; x *= x;
  x *= x; x *= x;
  return x;
}



/* INTEGRATION FUNCTIONS */

void runge_kutta_6 (void (*f) (double *, double *, double *, double), int dim, double dt, double * vars, double * params, double syn) {
    double apoyo[dim], retorno[dim];
    double k[6][dim];
    int j;

    (*f)(vars, retorno, params, syn);
    for(j = 0; j < dim; ++j) {
        k[0][j] = dt * retorno[j];
        apoyo[j] = vars[j] + k[0][j] * 0.2;
    }

    (*f)(apoyo, retorno, params, syn);
    for(j = 0; j < dim; ++j) {
        k[1][j] = dt * retorno[j];
        apoyo[j] = vars[j] + k[0][j] * 0.075 + k[1][j] * 0.225;
    }

    (*f)(apoyo, retorno, params, syn);
    for(j = 0; j < dim; ++j) {
        k[2][j] = dt * retorno[j];
        apoyo[j] = vars[j] + k[0][j] * 0.3 - k[1][j] * 0.9 + k[2][j] * 1.2;
    }

    (*f)(apoyo, retorno, params, syn);
    for(j = 0; j < dim; ++j) {
        k[3][j] = dt * retorno[j];
        apoyo[j] = vars[j] + k[0][j] * 0.075 + k[1][j] * 0.675 - k[2][j] * 0.6 + k[2][j] * 0.75;
    }

    (*f)(apoyo, retorno, params, syn);
    for(j = 0; j < dim; ++j) {
        k[4][j] = dt * retorno[j];
        apoyo[j] = vars[j] 
                + k[0][j] * 0.660493827160493
                + k[1][j] * 2.5
                - k[2][j] * 5.185185185185185
                + k[3][j] * 3.888888888888889
                - k[4][j] * 0.864197530864197;
    }

    (*f)(apoyo, retorno, params, syn);
    for(j = 0; j < dim; ++j) {
        k[5][j] = dt * retorno[j];
        apoyo[j] = vars[j] 
                + k[0][j]*0.1049382716049382
                + k[2][j]*0.3703703703703703
                + k[3][j]*0.2777777777777777
                + k[4][j]*0.2469135802469135;
    }


    for(j = 0; j < dim; ++j) {
        vars[j] += k[0][j]*0.098765432098765+
                   k[2][j]*0.396825396825396+
                   k[3][j]*0.231481481481481+
                   k[4][j]*0.308641975308641-
                   k[5][j]*0.035714285714285;
    }


    //printf("rk %f\n", vars[0]);

    return;
}


/* SYNAPSES
 
 * Synapses are calculated and sign change is NOT applied. 
 * The neuron model function performs a substraction with this current.
 * The synaptic current is sent to the external neuron after changing its sign.
 * Synaptic currents sent to the queue have their sign changed.
 * Antiphase is applied to both synaptic currents.

 */


 /* ELECTRICAL */

 void ini_elec (double ** params, double scale, double offset, void * syn_args) {
     syn_elec_args * aux_syn_args = (syn_elec_args *) syn_args;

    *params = (double *) malloc (sizeof(double) * 4);
    (*params)[SYN_SCALE] = scale;
    (*params)[SYN_OFFSET] = offset;
    (*params)[SYN_CALIBRATE] = SYN_CALIB_PRE;
    (*params)[ELEC_ANTI] = aux_syn_args->anti;
 }

void elec_syn (double v_post, double v_pre, double * g, double * ret, double * aux) {
	if (aux[SYN_CALIBRATE] == SYN_CALIB_PRE) {
		v_pre = v_pre * aux[SYN_SCALE] + aux[SYN_OFFSET];
	} else if (aux[SYN_CALIBRATE] == SYN_CALIB_POST) {
        v_post = (v_post - aux[SYN_OFFSET]) / aux[SYN_SCALE];
	}

    *ret = aux[ELEC_ANTI] * (g[ELEC_G] * (v_post - v_pre));
    return;
}


/* GOLOWASCH */

void ini_golowasch (double ** params, double scale, double offset, void * syn_args, double dt, double period, double min, double max) {
    syn_gl_args * aux_syn_args = (syn_gl_args *) syn_args;

    *params = (double *) malloc (sizeof(double) * 12);
    (*params)[SYN_SCALE] = scale;
    (*params)[SYN_OFFSET] = offset;
    (*params)[SYN_CALIBRATE] = SYN_CALIB_PRE;
    (*params)[GL_MIN] = min;
    (*params)[GL_MAX] = max;
    (*params)[GL_K1] = aux_syn_args->k1;
    (*params)[GL_K2] = aux_syn_args->k2;
    (*params)[GL_DT] = dt;
    (*params)[GL_VFAST] = aux_syn_args->v_fast/100.0;
    (*params)[GL_VSLOW] = aux_syn_args->v_slow/100.0;
    (*params)[GL_PERIOD] = period;
    (*params)[GL_MS_OLD] = 0.0;

    return;
}

void ms_f (double * vars, double * ret, double * params, double v_pre) {
    double p1, p2, p3;

    //printf("vpre %f ms %f k1 %f k2 %f vs %f ss %f ", v_pre, vars[0], params[MS_K1], params[MS_K2], params[MS_VS], params[MS_SS]);

    p1 = params[MS_K1] * (1.0 - vars[0]);
    p2 = 1.0 + exp(params[MS_SS] * (params[MS_VS] - v_pre));
    p3 = params[MS_K2] * vars[0];
    
    ret[0] = (p1 / p2) - p3;

    //printf("p1 %f p2 %f p3 %f ret %f\n", p1, p2, p3, ret[0]);
    return;
}
    

double golowasch_fast (double v_post, double v_pre, double g, double * aux) {
	double e_syn;
	double v_f;
	double s_f;

    double v_range = aux[GL_MAX] - aux[GL_MIN];

	/*if(aux[SC_MIN] > 0) {
		e_syn = aux[SC_MIN] - v_range * 0.153846;
		v_f = aux[SC_MIN] + v_range * aux[SC_VFAST];
	} else {
		e_syn = aux[SC_MIN] - v_range * 0.153846;
		v_f = aux[SC_MIN] + v_range * aux[SC_VFAST];
	}*/

    e_syn = aux[GL_MIN] - v_range * 0.153846;
    v_f = aux[GL_MIN] + v_range * aux[GL_VFAST];

    s_f = v_range * 0.002;

    //printf("\nesyn %f vf %f sf %f g %f vpre %f vpost %f min %f max %f range %f\n", e_syn, v_f, s_f, g, v_pre, v_post, aux[GL_MIN], aux[GL_MAX], v_range);

    return (g * (v_post - e_syn)) / (1.0 + exp(s_f * (v_f - v_pre)));
}

double golowasch_slow (double v_post, double v_pre, double g, double * aux) {
    double vars[1] = {aux[GL_MS_OLD]};
    double params[4];
    double e_syn;
    double ret;

    double v_range = aux[GL_MAX] - aux[GL_MIN];

	/*if(aux[SC_MIN] > 0) {
		e_syn = aux[SC_MIN] - v_range * 0.153846;
		params[MS_VS] = aux[SC_MIN] + v_range * aux[SC_VSLOW];
	} else {
		e_syn = aux[SC_MIN] + aux[SC_MIN] * 0.153846;
		params[MS_VS] = aux[SC_MIN] + v_range;
	}*/

    e_syn = aux[GL_MIN] - v_range * 0.153846;
    params[MS_VS] = aux[GL_MIN] + v_range * aux[GL_VSLOW];

    params[MS_K1] = aux[GL_K1];//1;
    params[MS_K2] = aux[GL_K2];//0.03;
    params[MS_SS] = v_range * 0.01;

    //printf("vpre %f ms %f k1 %f k2 %f ss %f vs %f dt %f\n", v_pre, aux[GL_MS_OLD], params[MS_K1], params[MS_K2], params[MS_SS], params[MS_VS], aux[GL_DT]);

    ret = g * aux[GL_MS_OLD] * (v_post - e_syn);

    runge_kutta_6(&ms_f, 1, aux[GL_DT], vars, params, v_pre);
    aux[GL_MS_OLD] = vars[0];
    //printf("%f\n\n", aux[GL_MS_OLD]);

    //printf("\nv_post %f esyn %f old %f\n", v_post, e_syn, aux[GL_MS_OLD]);



    return ret;
}

void golowasch_syn (double v_post, double v_pre, double * g, double * ret, double * aux) {
    double min, max;

    min = aux[GL_MIN];
    max = aux[GL_MAX];
    *ret = 0.0;

	if (aux[SYN_CALIBRATE] == SYN_CALIB_PRE) {
		v_pre = v_pre * aux[SYN_SCALE] + aux[SYN_OFFSET];
		aux[GL_MIN] = aux[GL_MIN] * aux[SYN_SCALE] + aux[SYN_OFFSET];
		aux[GL_MAX] = aux[GL_MAX] * aux[SYN_SCALE] + aux[SYN_OFFSET];
	} else if (aux[SYN_CALIBRATE] == SYN_CALIB_POST) {
        v_post = (v_post - aux[SYN_OFFSET]) / aux[SYN_SCALE];
	}

    if (g[GL_G_FAST] != 0.0) {
        *ret += golowasch_fast(v_post, v_pre, g[GL_G_FAST], aux);
    }

    if (g[GL_G_SLOW] != 0.0) {
        *ret += golowasch_slow(v_post, v_pre, g[GL_G_SLOW], aux);
	}

    //printf("g_f = %f // g_s = %f\n", g[G_FAST], g[G_SLOW]);
    //printf("v_fast %f\n", chem_fast(v_post, v_pre, &(g[G_FAST]), aux));
    //printf("v_slow %f\n", chem_slow(v_post, &(g[G_SLOW]), aux));

    aux[GL_MIN] = min;
    aux[GL_MAX] = max;

    return;
}


/* PRINZ */

void ini_prinz (double ** params, double scale, double offset, double k, double vth, double dt, double period, double min, double max) {
    (*params) = (double *) malloc (sizeof(double) * 10);
    (*params)[SYN_SCALE] = scale;
    (*params)[SYN_OFFSET] = offset;
    (*params)[SYN_CALIBRATE] = SYN_CALIB_PRE;
    (*params)[PR_S_OLD] = 0.0;
    (*params)[PR_K] = k;
    (*params)[PR_DT] = dt;
    (*params)[PR_VTH] = vth/100.0;
    (*params)[PR_PERIOD] = period;
    (*params)[PR_MIN] = min;
    (*params)[PR_MAX] = max;

    return;
}

void prinz_syn_f (double * vars, double * ret, double * params, double syn) {
	double tau;
	double s_pre;

	s_pre = 1 / (1 + exp((params[PR_AUX_VTH] - params[PR_AUX_VPRE]) / params[PR_AUX_DELTA]));

	tau = (1 - s_pre) / params[PR_AUX_K];

    ret[0] = (s_pre - vars[0]) / tau;

    //syslog(LOG_INFO, "ret %f vars %f s_pre %f tau %f", ret[0], vars[0], s_pre, tau);
    //if (isnan(ret[0]) == 1) sleep(10);

	return;
}



void prinz_syn (double v_post, double v_pre, double * g, double * ret, double * aux) {
	double vars[1] = {aux[PR_S_OLD]};
    double params[4];
    double v_range;
    double e_syn;

    if (aux[SYN_CALIBRATE] == SYN_CALIB_PRE) {
		v_pre = v_pre * aux[SYN_SCALE] + aux[SYN_OFFSET];
		aux[PR_MIN] = aux[PR_MIN] * aux[SYN_SCALE] + aux[SYN_OFFSET];
		aux[PR_MAX] = aux[PR_MAX] * aux[SYN_SCALE] + aux[SYN_OFFSET];
	} else if (aux[SYN_CALIBRATE] == SYN_CALIB_POST) {
		v_post = v_post / aux[SYN_SCALE] - aux[SYN_OFFSET];
	}

    v_range = aux[PR_MAX] - aux[PR_MIN];
    e_syn = aux[PR_MIN] - v_range * 0.103846;

	params[PR_AUX_VPRE] = v_pre;
	params[PR_AUX_DELTA] = v_range * 0.05;
	params[PR_AUX_VTH] = aux[PR_MIN] + v_range * aux[PR_VTH];
	params[PR_AUX_K] = aux[PR_K];

	/*syslog(LOG_INFO, "min %f max %f range %f esyn %f vpre %f s_old %f delta %f vth %f k %f\n", aux[PR_AUX_MIN], 
		aux[PR_AUX_MAX], v_range, e_syn, params[PR_PARAM_V_PRE], vars[0], params[PR_PARAM_DELTA], 
		params[PR_PARAM_V_TH], params[PR_PARAM_K]);*/

    runge_kutta_6 (&prinz_syn_f, 1, aux[PR_DT], vars, params, 0);
    aux[PR_S_OLD] = vars[0];

    *ret = (*g) * aux[PR_S_OLD] * (v_post - e_syn);

    //syslog(LOG_INFO, "ret %f g %f s %f\n", *ret, *g, aux[PR_AUX_S_OLD]);

    return;
}



/* IZHIKEVICH */

void izh_f (double * vars, double * ret, double * params, double syn) {
	ret[0] = 0.04 * vars[0]*vars[0] + 5*vars[0] + 140 - vars[1] + params[I_IZ] - syn;
	ret[1] = params[A_IZ] * (params[B_IZ] * vars[0] - vars[1]);

	return;
}


void izhikevich (int dim, double dt, double * vars, double * params, double syn) {
	runge_kutta_6 (izh_f, dim, dt, vars, params, syn);

	if (vars[0] >= 30) {
		vars[0] = params[C_IZ];
		vars[1] += params[D_IZ];
	}

	return;
}

void ini_iz (double *min, double *minABS, double *max){
    *min=-50.000000;
    *minABS=-74.235106;
    *max=30.240470;
    return;
}


/* HINDMARSH-ROSE */

void hr_f (double * vars, double * ret, double * params, double syn) {
    ret[0] = vars[1] + 3.0 * (vars[0]*vars[0]) - (vars[0]*vars[0]*vars[0]) - vars[2] + params[I_HR] - syn;
    ret[1] = 1.0 - 5.0 * (vars[0]*vars[0]) - vars[1];
    ret[2] = (-vars[2] + params[S_HR] * (vars[0] + 1.6)) * params[R_HR];

    return;
}

void hindmarsh_rose (int dim, double dt, double * vars, double * params, double syn) {
	runge_kutta_6 (hr_f, dim, dt, vars, params, syn);

	return;
}

void ini_hr (double *min, double *minABS, double *max){
    *min=-1.608734;
    *minABS=-1.608734;
    *max=1.797032;
    //rafaga_hr=260166;
    return;
}



/* RULKOV MAP */

void rlk_f (double * vars, double * ret, double * params, double syn) {
    double y_old;

    ret[1] = vars[1] - params[MU_RLK] * (vars[0] + 1) + params[MU_RLK] * params[SIGMA_RLK];
    y_old = vars[1] - syn * params[I_RLK];


    if (vars[0] <= 0) {
        ret[0] = params[ALPHA_RLK] / (1 - vars[0]) + y_old;
    } else if (vars[0] >= params[ALPHA_RLK] + y_old) {
        ret[0] = -1;
    } else {
        ret[0] = params[ALPHA_RLK] + y_old;
    }


    return;
}

void rulkov_map (int dim, double dt, double * vars, double * params, double syn) {
    double ret[2];

    if (params[J_RLK] >= ((params[PTS_RLK] - 400) / 400)) {
        params[OLD_RLK] = vars[0];
        rlk_f(vars, ret, params, syn);
        params[J_RLK] = 0;
        params[INTER_RLK] = ret[0];

        vars[0] = ret[0];
        vars[1] = ret[1];
    }

    ret[0] = params[OLD_RLK] + (params[INTER_RLK] - params[OLD_RLK]) / ((params[PTS_RLK] - 400) / 400) * params[J_RLK];
    ret[1] = vars[1];
    params[J_RLK]++;


    vars[0] = ret[0];
    vars[1] = ret[1];

    return;
}

void ini_rlk (double *min, double *minABS, double *max){
    *min=-1.18;
    *minABS=-1.977;
    *max=2.111;
    return;
}







