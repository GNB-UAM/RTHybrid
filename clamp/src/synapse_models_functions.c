#include "../includes/synapse_models_functions.h"

/* General functions */

void init_neuron_model (neuron_model * nm, int model) {
    nm->type = model;

    switch (model) {
        case IZ:
            nm->dim = 2;
            nm->vars = (double *) malloc (sizeof(double) * nm->dim);
            copy_1d_array(args->vars, nm->vars, nm->dim);

            nm->n_params = 6;
            nm->params = (double *) malloc (sizeof(double) * nm->n_params);
            copy_1d_array(args->params, nm->params, nm->params);

            nm->max = 30.240470;
            nm->min = -74.235106;

            nm->func = &izhikevich;
            nm->set_pts_burst = &iz_set_pts_burst;

            break;
        case HR:
            nm->dim = 3;
            nm->vars = (double *) malloc (sizeof(double) * nm->dim);
            copy_1d_array(args->vars, nm->vars, nm->dim);

            nm->n_params = 4;
            nm->params = (double *) malloc (sizeof(double) * nm->n_params);
            copy_1d_array(args->params, nm->params, nm->params);

            nm->max = 1.797032;
            nm->min = -1.608734;

            nm->func = &hindmarsh_rose;
            nm->set_pts_burst = &hr_set_pts_burst;

            break;
        case RLK:
            nm->dim = 2;
            nm->vars = (double *) malloc (sizeof(double) * nm->dim);
            copy_1d_array(args->vars, nm->vars, nm->dim);

            nm->n_params = 8;
            nm->params = (double *) malloc (sizeof(double) * nm->n_params);
            copy_1d_array(args->params, nm->params, nm->params);

            nm->max = 2.111;
            nm->min = -1.977;

            nm->func = &rulkov_map;
            nm->set_pts_burst = &rlk_set_pts_burst;

            break;
        default:
            return;
    }

    return;
}


void free_synapse (syn_params * params) {
    free_pointers(2, &params->g, &params->type_params);
    return;
}


 /* ELECTRICAL */

 void elec_ini (syn_params * params, double scale, double offset, void * syn_args) {
    syn_elec_args * aux_syn_args = (syn_elec_args *) syn_args;
    params->type_params = (syn_elec_params *) malloc (sizeof(syn_elec_params));
    syn_elec_params * aux_elec_params = params->type_params;

    params->syn_type = ELECTRIC;
    params->scale = scale;
    params->offset = offset;
    params->calibrate = SYN_CALIB_PRE;
    aux_elec_params->anti = aux_syn_args->anti;

    params->g = (double *) malloc (sizeof(ELEC_N_G));
    copy_1d_array(aux_syn_args->g, params->g, ELEC_N_G);

 }

void elec_syn (double v_post, double v_pre, syn_params * params, double * ret) {
    syn_elec_params * aux_elec_params = params->type_params;

    if (params->calibrate == SYN_CALIB_PRE) {
        v_pre = v_pre * params->scale + params->offset;
    } else if (params->calibrate == SYN_CALIB_POST) {
        v_post = (v_post - params->offset) / params->scale;
    }

    *ret = aux_elec_params->anti * (params->g[ELEC_G] * (v_post - v_pre));
    return;
}


/* GOLOWASCH */

void gl_ini (syn_params * params, double scale, double offset, void * syn_args, double dt, double min, double max) {
    syn_gl_args * aux_syn_args = (syn_gl_args *) syn_args;
    params->type_params = (syn_gl_params *) malloc (sizeof(syn_gl_params));
    syn_gl_params * aux_gl_params = params->type_params;

    params->syn_type = GOLOWASCH;
    params->scale = scale;
    params->offset = offset;
    params->calibrate = SYN_CALIB_PRE;
    aux_gl_params->min = min;
    aux_gl_params->max = max;
    aux_gl_params->k1 = aux_syn_args->k1;
    aux_gl_params->k2 = aux_syn_args->k2;
    aux_gl_params->dt = dt;
    aux_gl_params->v_fast = aux_syn_args->v_fast/100.0;
    aux_gl_params->v_slow = aux_syn_args->v_slow/100.0;
    aux_gl_params->ms_old = 0.0;

    params->g = (double *) malloc (sizeof(GL_N_G));
    copy_1d_array(aux_syn_args->g, params->g, GL_N_G);

    return;
}

void gl_ms_f (double * vars, double * ret, double * params, double v_pre) {
    double p1, p2, p3;

    //printf("vpre %f ms %f k1 %f k2 %f vs %f ss %f ", v_pre, vars[0], params[MS_K1], params[MS_K2], params[MS_VS], params[MS_SS]);

    p1 = params[MS_K1] * (1.0 - vars[0]);
    p2 = 1.0 + exp(params[MS_SS] * (params[MS_VS] - v_pre));
    p3 = params[MS_K2] * vars[0];
    
    ret[0] = (p1 / p2) - p3;

    //printf("p1 %f p2 %f p3 %f ret %f\n", p1, p2, p3, ret[0]);
    return;
}
    

double gl_fast (double v_post, double v_pre, double g, syn_gl_params * params) {
    double e_syn;
    double v_f;
    double s_f;

    double v_range = params->max - params->min;

    e_syn = params->min - v_range * 0.153846;
    v_f = params->min + v_range * params->v_fast;

    s_f = 1.0 / (v_range * 0.05);

    //printf("\nesyn %f vf %f sf %f g %f vpre %f vpost %f min %f max %f range %f\n", e_syn, v_f, s_f, g, v_pre, v_post, aux[GL_MIN], aux[GL_MAX], v_range);

    return (g * (v_post - e_syn)) / (1.0 + exp(s_f * (v_f - v_pre)));
}

double gl_slow (double v_post, double v_pre, double g, syn_gl_params * params) {
    double vars[1] = {params->ms_old};
    double params_ms[4];
    double e_syn;
    double ret;

    double v_range = params->max - params->min;

    e_syn = params->min - v_range * 0.153846;
    params_ms[MS_VS] = params->min + v_range * params->v_slow;

    params_ms[MS_K1] = params->k1;
    params_ms[MS_K2] = params->k2;
    params_ms[MS_SS] = 1.0 / (v_range * 0.01);

    //printf("vpre %f ms %f k1 %f k2 %f ss %f vs %f dt %f\n", v_pre, aux[GL_MS_OLD], params[MS_K1], params[MS_K2], params[MS_SS], params[MS_VS], aux[GL_DT]);

    ret = g * params->ms_old * (v_post - e_syn);

    runge_kutta_6(&ms_f, 1, params->dt, vars, params_ms, v_pre);
    params->ms_old = vars[0];
    //printf("%f\n\n", aux[GL_MS_OLD]);

    //printf("\nv_post %f esyn %f old %f\n", v_post, e_syn, aux[GL_MS_OLD]);



    return ret;
}

void golowasch_syn (double v_post, double v_pre, syn_params * params, double * ret) {
    double min, max;
    syn_gl_params * aux_gl_params = params->type_params;

    min = aux_gl_params->min;
    max = aux_gl_params->max;
    *ret = 0.0;

    if (params->calibrate == SYN_CALIB_PRE) {
        v_pre = v_pre * params->scale + params->offset;
        aux_gl_params->min = aux_gl_params->min * params->scale + params->offset;
        aux_gl_params->max = aux_gl_params->max * params->scale + params->offset;
    } else if (params->calibrate == SYN_CALIB_POST) {
        v_post = (v_post - params->offset) / params->scale;
    }

    if (params->g[GL_G_FAST] != 0.0) {
        *ret += golowasch_fast(v_post, v_pre, params->g[GL_G_FAST], aux_gl_params);
    }

    if (params->g[GL_G_SLOW] != 0.0) {
        *ret += golowasch_slow(v_post, v_pre, params->g[GL_G_SLOW], aux_gl_params);
    }

    //printf("g_f = %f // g_s = %f\n", g[G_FAST], g[G_SLOW]);
    //printf("v_fast %f\n", chem_fast(v_post, v_pre, &(g[G_FAST]), aux));
    //printf("v_slow %f\n", chem_slow(v_post, &(g[G_SLOW]), aux));

    aux_gl_params->min = min;
    aux_gl_params->max = max;

    return;
}


/* PRINZ */

void prinz_ini (double ** params, double scale, double offset, double k, double vth, double dt, double period, double min, double max) {
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

void prinz_f (double * vars, double * ret, double * params, double v_pre) {
    double tau;
    double s_pre;

    s_pre = 1 / (1 + exp((params[PR_AUX_VTH] - v_pre) / params[PR_AUX_DELTA]));

    tau = (1 - s_pre) / params[PR_AUX_K];

    ret[0] = (s_pre - vars[0]) / tau;

    //syslog(LOG_INFO, "ret %f vars %f s_pre %f tau %f", ret[0], vars[0], s_pre, tau);
    //if (isnan(ret[0]) == 1) sleep(10);

    return;
}



void prinz_syn (double v_post, double v_pre, syn_params * params, double * ret) {
    /*double vars[1] = {aux[PR_S_OLD]};
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


    runge_kutta_6 (&prinz_syn_f, 1, aux[PR_DT], vars, params, 0);
    aux[PR_S_OLD] = vars[0];

    *ret = (*g) * aux[PR_S_OLD] * (v_post - e_syn);*/

    return;
}