#include "../includes/model_library.h"



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

    return;
}


/* SYNAPSES
 
 * Synapses are calculated and sign change is NOT applied. 
 * The neuron model function performs a substraction with this current.
 * The synaptic current is sent to the external neuron after changing its sign.
 * Synaptic currents sent to the queue have their sign changed.
 * Antiphase is applied to both synaptic currents.

 */

void elec_syn (double v_post, double v_pre, double * g, double * ret, double * aux) {
    *ret = g[0] * (v_post - v_pre);
    return;
}

void ms_f (double * vars, double * ret, double * params, double v_pre) {
    double p1, p2, p3;

    p1 = params[MS_K1] * (1.0 - vars[0]);
    p2 = 1.0 + exp(params[MS_SS] * (params[MS_VS] - v_pre));
    p3 = params[MS_K2] * vars[0];
    
    ret[0] = (p1 / p2) - p3;
    return;
}
    

double chem_fast (double v_post, double v_pre, double * g, double * aux) {
	double e_syn;
	double v_f;
	double s_f;

	if(aux[SC_MIN] > 0) {
		e_syn = aux[SC_MIN] - aux[SC_MIN] * 0.153846;
		v_f = aux[SC_MIN] + aux[SC_MIN] * aux[SC_VFAST];
	} else {
		e_syn = aux[SC_MIN] + aux[SC_MIN] * 0.153846;
		v_f = aux[SC_MIN] - aux[SC_MIN] * aux[SC_VFAST];
	}
	
    s_f = aux[SC_BT] * 0.2;

    //printf("esyn %f vf %f sf %f g %f vpre %f vpost %f", e_syn, v_f, s_f, (*g), v_pre, v_post);

    return ((*g) * (v_post - e_syn)) / (1.0 + exp(s_f * (v_f - v_pre)));
}

double chem_slow (double v_post, double * g, double * aux) {
    double vars[1] = {aux[SC_OLD]};
    double params[4];
    double e_syn;
	
	if(aux[SC_MIN] > 0) {
		e_syn = aux[SC_MIN] - aux[SC_MIN] * 0.153846;
		params[MS_VS] = aux[SC_MIN] + aux[SC_MIN] * aux[SC_VSLOW];
	} else {
		e_syn = aux[SC_MIN] + aux[SC_MIN] * 0.153846;
		params[MS_VS] = aux[SC_MIN] - aux[SC_MIN] * aux[SC_VSLOW];
	}
	
    params[MS_K1] = aux[SC_MS_K1];//1;
    params[MS_K2] = aux[SC_MS_K2];//0.03;
    params[MS_SS] = aux[SC_BT];

    runge_kutta_6(&ms_f, 1, aux[SC_DT], vars, params, 0);
    aux[SC_OLD] = vars[0];

    //printf("v_post %f esyn %f old %f ", v_post, e_syn, aux[SC_OLD]);

    return (*g) * aux[SC_OLD] * (v_post - e_syn);
}

void chem_syn (double v_post, double v_pre, double * g, double * ret, double * aux) {
    *ret = chem_fast(v_post, v_pre, &(g[G_FAST]), aux) + chem_slow(v_post, &(g[G_SLOW]), aux);

    //printf(" v_fast %f\n", chem_fast(v_post, v_pre, &(g[G_FAST]), aux));
    //printf("v_slow %f\n", chem_slow(v_post, &(g[G_SLOW]), aux));
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







