#include "sm_greenberg_manor_2005.h"

/**
 * @file sm_greenberg_manor_2005.c
 * @brief Source file with the Greenberg_Manor_2005 synapse model functions.
 */ 


/** @name Greenberg_Manor_2005
 *  Greenberg_Manor_2005 synapse model. 
 */

 
///@{

/**
 * @brief Sets the amplitude scale and offset parameters of the greenberg_manor_2005 synapse model according to the living neuron signal.
 * @param[in] sm Pointer to synapse neuron model
 * @param[in] scale Amplitude scale of the living neuron signal regarding to the neuron model
 * @param[in] offset Amplitude offset of the living neuron signal regarding to the neuron model
 */

void sm_greenberg_manor_2005_set_online_params (synapse_model * sm, double scale, double offset, double min, double max) {
    sm->scale = scale;
    sm->offset = offset;
    sm->min = min;
    sm->max = max;

    //printf("min %f max %f scale %f offset %f\n", sm->min, sm->max, sm->scale, sm->offset);
}


double sm_greenberg_manor_2005_tau (double v, double tau_hi, double tau_lo, double v12, double k) {
    double p1 = tau_hi - tau_lo;
    double p2 = (v - v12) / k;
    double p3 = 1.0 + exp(p2);

    return tau_lo + (p1 / p3);
}


double sm_greenberg_manor_2005_inf (double v, double v12, double k) {
    double p2 = (v - v12) / k;
    double p3 = 1.0 + exp(-p2);

    //printf("%f %f ", p2, p3);

    return 1.0 / p3;
}


void sm_greenberg_manor_2005_state_variable (double * vars, double * ret, double * params, double aux) {
    double x_inf, tau_inf;

    x_inf = sm_greenberg_manor_2005_inf (params[SM_GREENBERG_MANOR_2005_V], params[SM_GREENBERG_MANOR_2005_V12], params[SM_GREENBERG_MANOR_2005_K]);
    tau_inf = sm_greenberg_manor_2005_tau (params[SM_GREENBERG_MANOR_2005_V], params[SM_GREENBERG_MANOR_2005_TAU_HI], params[SM_GREENBERG_MANOR_2005_TAU_LO], params[SM_GREENBERG_MANOR_2005_V12], params[SM_GREENBERG_MANOR_2005_K]);

    ret[SM_GREENBERG_MANOR_2005_X] = (x_inf - vars[SM_GREENBERG_MANOR_2005_X]) / tau_inf;

    //printf("%f %f %f ", x_inf, vars[SM_GREENBERG_MANOR_2005_X], tau_inf);
}

double sm_greenberg_manor_2005_m (double v_pre, double v_range, double min, sm_greenberg_manor_2005_params * sm_params) {
    double vars[1], params[5];

    vars[SM_GREENBERG_MANOR_2005_X] = sm_params->m;

    params[SM_GREENBERG_MANOR_2005_V] = v_pre;
    params[SM_GREENBERG_MANOR_2005_V12] = min + v_range * sm_params->v12_m;
    params[SM_GREENBERG_MANOR_2005_K] = v_range * sm_params->k_m;
    params[SM_GREENBERG_MANOR_2005_TAU_HI] = sm_params->tau_hi_m;
    params[SM_GREENBERG_MANOR_2005_TAU_LO] = sm_params->tau_lo_m;

    //printf("M %f: v %f v12 %f k %f tauhi %f taulo %f\n", vars[SM_GREENBERG_MANOR_2005_X], params[SM_GREENBERG_MANOR_2005_V], params[SM_GREENBERG_MANOR_2005_V12], params[SM_GREENBERG_MANOR_2005_K], 
        //params[SM_GREENBERG_MANOR_2005_TAU_HI], params[SM_GREENBERG_MANOR_2005_TAU_LO]);

    sm_params->method(&sm_greenberg_manor_2005_state_variable, 1, sm_params->dt, vars, params, 0);

    //printf("M %f\n", vars[SM_GREENBERG_MANOR_2005_X]);

    //printf("%f %f %f ", params[SM_GREENBERG_MANOR_2005_V], params[SM_GREENBERG_MANOR_2005_V12], params[SM_GREENBERG_MANOR_2005_K]);

    return vars[SM_GREENBERG_MANOR_2005_X];
}


double sm_greenberg_manor_2005_h (double v_pre, double v_range, double min, sm_greenberg_manor_2005_params * sm_params) {
    double vars[1], params[5];

    vars[SM_GREENBERG_MANOR_2005_X] = sm_params->h;

    params[SM_GREENBERG_MANOR_2005_V] = v_pre;
    params[SM_GREENBERG_MANOR_2005_V12] = min + v_range * sm_params->v12_h;
    params[SM_GREENBERG_MANOR_2005_K] = v_range * sm_params->k_h;
    params[SM_GREENBERG_MANOR_2005_TAU_HI] = sm_params->tau_hi_h;
    params[SM_GREENBERG_MANOR_2005_TAU_LO] = sm_params->tau_lo_h;


    //printf("H %f: v %f v12 %f k %f tauhi %f taulo %f\n", vars[SM_GREENBERG_MANOR_2005_X], params[SM_GREENBERG_MANOR_2005_V], params[SM_GREENBERG_MANOR_2005_V12], params[SM_GREENBERG_MANOR_2005_K], 
        //params[SM_GREENBERG_MANOR_2005_TAU_HI], params[SM_GREENBERG_MANOR_2005_TAU_LO]);

    sm_params->method(&sm_greenberg_manor_2005_state_variable, 1, sm_params->dt, vars, params, 0);

    //printf("H %f\n", vars[SM_GREENBERG_MANOR_2005_X]);

    //printf("%f %f ", params[SM_GREENBERG_MANOR_2005_V12], params[SM_GREENBERG_MANOR_2005_K]);

    return vars[SM_GREENBERG_MANOR_2005_X];
}



/**
 * @brief Greenberg_Manor_2005 synapse model function.
 *
 * @param[in] v_post Post-synaptic neuron membrane potential
 * @param[in] v_pre Pre-synaptic neuron membrane potential
 * @param[in] sm Pointer to synapse neuron model
 * @param[out] ret Pointer to the return value
 */

void sm_greenberg_manor_2005 (double v_post, double v_pre, synapse_model * sm, double * ret) {
	double min, max, v_range, e_syn;
	sm_greenberg_manor_2005_params * aux_params = sm->type_params;

    if (sm->calibrate == SYN_CALIB_PRE) {
        //printf("\n\nPRE scale %f offset %f vpre %f\n", sm->scale, sm->offset, v_pre);
        v_pre = v_pre * sm->scale + sm->offset;
        min = sm->min * sm->scale + sm->offset;
        max = sm->max * sm->scale + sm->offset;
    } else if (sm->calibrate == SYN_CALIB_POST) {
        //printf("\n\nPOST scale %f offset %f vpost %f\n", sm->scale, sm->offset, v_post);
        v_post = (v_post - sm->offset) / sm->scale;
        min = sm->min;
        max = sm->max;

        /**ret = 0.0;
        return;*/
    }

    v_range = max - min;
    e_syn = min + v_range * aux_params->e_syn_per;

    //printf("min %f max %f range %f e_syn_per %f e_syn %f\n", min, max, v_range, aux_params->e_syn_per, e_syn);
    //printf("vpre %f vpost %f v12m %f km %f, v12h %f kh %f\n", v_pre, v_post, aux_params->v12_m, aux_params->k_m, aux_params->v12_h, aux_params->k_h);

    aux_params->m = sm_greenberg_manor_2005_m (v_pre, v_range, min, aux_params);
    aux_params->h = sm_greenberg_manor_2005_h (v_pre, v_range, min, aux_params);

    *ret = sm->g[SM_GREENBERG_MANOR_2005_G] * pow(aux_params->m, aux_params->p) * pow(aux_params->h, aux_params->q) * (v_post - e_syn);

    /*if (sm->calibrate == SYN_CALIB_PRE) {
        printf("%f %f %f %f %f %f %f\n", *ret, min, max, aux_params->m, aux_params->h, e_syn, (v_post - e_syn));
    } else if (sm->calibrate == SYN_CALIB_POST) {
        printf("%f %f %f %f %f %f %f ", *ret, min, max, aux_params->m, aux_params->h, e_syn, (v_post - e_syn));
    }*/

    //printf("ret [%f] = g [%f] * m [%f] ^ p [%f] * h [%f] ^ q [%f] * (vpost [%f] - esyn [%f])\n", *ret, sm->g[SM_GREENBERG_MANOR_2005_G], aux_params->m, aux_params->p, aux_params->h, aux_params->q, v_post, e_syn);
}


/**
 * @brief Initializes the Greenberg_Manor_2005 synapse model.
 * @param[in/out] sm Pointer to synapse neuron model
 * @param[in] syn_args Synapse model parameters entered as input arguments
 */

void sm_greenberg_manor_2005_init (synapse_model * sm, void * syn_args) {
    sm_greenberg_manor_2005_args * aux_syn_args = (sm_greenberg_manor_2005_args *) syn_args;
    sm->type_params = (sm_greenberg_manor_2005_params *) malloc (sizeof(sm_greenberg_manor_2005_params));
    sm_greenberg_manor_2005_params * aux_params = sm->type_params;

    sm->calibrate = SYN_CALIB_PRE;

    sm->g = (double *) malloc (sizeof(SM_GREENBERG_MANOR_2005_N_G));
    copy_1d_array(aux_syn_args->g, sm->g, SM_GREENBERG_MANOR_2005_N_G);

    aux_params->e_syn_per = aux_syn_args->e_syn_per;

    aux_params->p = aux_syn_args->p;
    aux_params->v12_m = aux_syn_args->v12_m;
    aux_params->k_m = aux_syn_args->k_m;
    aux_params->tau_hi_m = aux_syn_args->tau_hi_m;
    aux_params->tau_lo_m = aux_syn_args->tau_lo_m;
    aux_params->m = 0.5;

    aux_params->q = aux_syn_args->q;
    aux_params->v12_h = aux_syn_args->v12_h;
    aux_params->k_h = aux_syn_args->k_h;
    aux_params->tau_hi_h = aux_syn_args->tau_hi_h;
    aux_params->tau_lo_h = aux_syn_args->tau_lo_h;
    aux_params->h = 0.5;

    sm->func = &sm_greenberg_manor_2005;
    sm->set_online_parameters = &sm_greenberg_manor_2005_set_online_params;
    aux_params->method = integration_method_selector(aux_syn_args->method);
    aux_params->dt = aux_syn_args->dt;

    //printf("p %f v12m %f km %f tauhim %f taulom %f\n", aux_params->p, aux_params->v12_m, aux_params->k_m, aux_params->tau_hi_m, aux_params->tau_lo_m);
    //printf("q %f v12h %f kh %f tauhih %f tauloh %f\n", aux_params->q, aux_params->v12_h, aux_params->k_h, aux_params->tau_hi_h, aux_params->tau_lo_h);
}

///@}
