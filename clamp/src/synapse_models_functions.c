#include "../includes/synapse_models_functions.h"

/* General functions */

void init_synapse_model (synapse_model * sm, int model, void * syn_args) {
    sm->type = model;

    switch (model) {
        case EMPTY_SYN:
        {
            sm->type_params = NULL;
            sm->g = NULL;

            sm->func = &empty_syn;

            break;
        }
        case ELECTRIC:
        {
            syn_elec_args * aux_syn_args = (syn_elec_args *) syn_args;
            sm->type_params = (syn_elec_params *) malloc (sizeof(syn_elec_params));
            syn_elec_params * aux_elec_params = sm->type_params;

            sm->calibrate = SYN_CALIB_PRE;
            aux_elec_params->anti = aux_syn_args->anti;

            sm->g = (double *) malloc (sizeof(ELEC_N_G));
            copy_1d_array(aux_syn_args->g, sm->g, ELEC_N_G);

            sm->func = &elec_syn;

            break;
        }
        case GOLOWASCH:
        {
            syn_gl_args * aux_syn_args = (syn_gl_args *) syn_args;
            sm->type_params = (syn_gl_params *) malloc (sizeof(syn_gl_params));
            syn_gl_params * aux_gl_params = sm->type_params;

            sm->calibrate = SYN_CALIB_PRE;
            aux_gl_params->dt = 0.001;
            aux_gl_params->k1 = aux_syn_args->k1;
            aux_gl_params->k2 = aux_syn_args->k2;
            aux_gl_params->v_fast = aux_syn_args->v_fast/100.0;
            aux_gl_params->v_slow = aux_syn_args->v_slow/100.0;
            aux_gl_params->ms_old = 0.0;

            sm->g = (double *) malloc (sizeof(GL_N_G));
            copy_1d_array(aux_syn_args->g, sm->g, GL_N_G);

            sm->func = &golowasch_syn;

            break;
        }
        default:
            return;
    }

    return;
}


void free_synapse_model (synapse_model * sm) {
    free_pointers(2, &sm->g, &sm->type_params);
    return;
}


 /* EMPTY */

void empty_syn (double v_post, double v_pre, synapse_model * sm, double * ret) {
    *ret = 0.0;
    return;
}



 /* ELECTRICAL */

void elec_set_online_params (synapse_model * sm, double scale, double offset) {
    sm->scale = scale;
    sm->offset = offset;

    return;
}

void elec_syn (double v_post, double v_pre, synapse_model * sm, double * ret) {
    syn_elec_params * aux_elec_params = sm->type_params;

    if (sm->calibrate == SYN_CALIB_PRE) {
        v_pre = v_pre * sm->scale + sm->offset;
    } else if (sm->calibrate == SYN_CALIB_POST) {
        v_post = (v_post - sm->offset) / sm->scale;
    }

    *ret = aux_elec_params->anti * (sm->g[ELEC_G] * (v_post - v_pre));
    return;
}


/* GOLOWASCH */

void gl_set_online_params (synapse_model * sm, double scale, double offset, double min, double max) {
    syn_gl_params * aux_gl_params = sm->type_params;

    sm->scale = scale;
    sm->offset = offset;
    aux_gl_params->min = min;
    aux_gl_params->max = max;

    return;
}

void gl_ms_f (double * vars, double * ret, double * params, double v_pre) {
    double p1, p2, p3;

    //printf("vpre %f ms %f k1 %f k2 %f vs %f ss %f ", v_pre, vars[0], params[MS_K1], params[MS_K2], params[MS_VS], params[MS_SS]);

    p1 = params[GL_MS_K1] * (1.0 - vars[0]);
    p2 = 1.0 + exp(params[GL_MS_SS] * (params[GL_MS_VS] - v_pre));
    p3 = params[GL_MS_K2] * vars[0];
    
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
    params_ms[GL_MS_VS] = params->min + v_range * params->v_slow;

    params_ms[GL_MS_K1] = params->k1;
    params_ms[GL_MS_K2] = params->k2;
    params_ms[GL_MS_SS] = 1.0 / (v_range * 0.01);

    //printf("vpre %f ms %f k1 %f k2 %f ss %f vs %f dt %f\n", v_pre, aux[GL_MS_OLD], params[MS_K1], params[MS_K2], params[MS_SS], params[MS_VS], aux[GL_DT]);

    ret = g * params->ms_old * (v_post - e_syn);

    runge_kutta_6(&gl_ms_f, 1, params->dt, vars, params_ms, v_pre);
    params->ms_old = vars[0];
    //printf("%f\n\n", aux[GL_MS_OLD]);

    //printf("\nv_post %f esyn %f old %f\n", v_post, e_syn, aux[GL_MS_OLD]);



    return ret;
}

void golowasch_syn (double v_post, double v_pre, synapse_model * sm, double * ret) {
    double min, max;
    syn_gl_params * aux_gl_params = sm->type_params;

    min = aux_gl_params->min;
    max = aux_gl_params->max;
    *ret = 0.0;

    if (sm->calibrate == SYN_CALIB_PRE) {
        v_pre = v_pre * sm->scale + sm->offset;
        aux_gl_params->min = aux_gl_params->min * sm->scale + sm->offset;
        aux_gl_params->max = aux_gl_params->max * sm->scale + sm->offset;
    } else if (sm->calibrate == SYN_CALIB_POST) {
        v_post = (v_post - sm->offset) / sm->scale;
    }

    if (sm->g[GL_G_FAST] != 0.0) {
        *ret += gl_fast(v_post, v_pre, sm->g[GL_G_FAST], aux_gl_params);
    }

    if (sm->g[GL_G_SLOW] != 0.0) {
        *ret += gl_slow(v_post, v_pre, sm->g[GL_G_SLOW], aux_gl_params);
    }

    //printf("g_f = %f // g_s = %f\n", g[G_FAST], g[G_SLOW]);
    //printf("v_fast %f\n", chem_fast(v_post, v_pre, &(g[G_FAST]), aux));
    //printf("v_slow %f\n", chem_slow(v_post, &(g[G_SLOW]), aux));

    aux_gl_params->min = min;
    aux_gl_params->max = max;

    return;
}