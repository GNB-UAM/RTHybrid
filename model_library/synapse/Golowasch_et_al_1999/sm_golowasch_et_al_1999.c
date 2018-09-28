#include "sm_golowasch_et_al_1999.h"

/**
 * @file sm_golowasch_et_al_1999.c
 * @brief Source file with the Electrical synapse model functions.
 */ 


/** @name Golowasch
 *  Graded chemical synapse model from (Golowasch et al, 1999). 
 */
///@{


/**
 * @brief Initializes graded chemical synapse model from (Golowasch et al, 1999).
 * @param[in/out] sm Pointer to synapse neuron model
 * @param[in] syn_args Synapse model parameters entered as input arguments
 */

void sm_golowasch_et_al_1999_init (synapse_model * sm, void * syn_args) {
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
    aux_gl_params->s_fast = aux_syn_args->s_fast/100.0;
    aux_gl_params->s_slow = aux_syn_args->s_slow/100.0;

    sm->g = (double *) malloc (sizeof(GL_N_G));
    copy_1d_array(aux_syn_args->g, sm->g, GL_N_G);

    sm->func = &sm_golowasch_et_al_1999;
    sm->set_online_parameters = &gl_set_online_params;
}


/**
 * @brief Sets the amplitude mininum, maximum, scale and offset parameters of the (Golowasch et al, 1999) synapse model according to the living neuron signal.
 * @param[in] sm Pointer to synapse neuron model
 * @param[in] scale Amplitude scale of the living neuron signal regarding to the neuron model
 * @param[in] offset Amplitude offset of the living neuron signal regarding to the neuron model
 * @param[in] min Minimum value of the living neuron signal voltage
 * @param[in] max Maximum value of the living neuron signal voltage
 */

void gl_set_online_params (synapse_model * sm, double scale, double offset, double min, double max) {
    syn_gl_params * aux_gl_params = sm->type_params;

    sm->scale = scale;
    sm->offset = offset;
    aux_gl_params->min = min;
    aux_gl_params->max = max;

    return;
}


/**
 * @brief Golowasch m_slow differential equation.
 * @param[in] vars Synapse model variables
 * @param[out] ret Return values array
 * @param[in] params Synapse model parameters
 * @param[in] v_pre Pre-synaptic neuron membrane potential
 */

void gl_ms_f (double * vars, double * ret, double * params, double v_pre) {
    double p1, p2, p3;

    p1 = params[GL_MS_K1] * (1.0 - vars[0]);
    p2 = 1.0 + exp(params[GL_MS_SS] * (params[GL_MS_VS] - v_pre));
    p3 = params[GL_MS_K2] * vars[0];
    
    ret[0] = (p1 / p2) - p3;

    return;
}
    

/**
 * @brief Golowasch fast synapse equation.
 * @param[in] v_post Post-synaptic neuron membrane potential
 * @param[in] v_pre Pre-synaptic neuron membrane potential
 * @param[in] g Conductance
 * @param[in] params Structure with the synapse auxiliary parameters
 * @return Synaptic current
 */

double gl_fast (double v_post, double v_pre, double g, syn_gl_params * params) {
    double e_syn;
    double v_f;
    double s_f;

    double v_range = params->max - params->min;

    e_syn = params->min - v_range * 0.153846;
    v_f = params->min + v_range * params->v_fast;

    s_f = 1.0 / (v_range * params->s_fast);

    return (g * (v_post - e_syn)) / (1.0 + exp(s_f * (v_f - v_pre)));
}


/**
 * @brief Golowasch slow synapse equation.
 * @param[in] v_post Post-synaptic neuron membrane potential
 * @param[in] v_pre Pre-synaptic neuron membrane potential
 * @param[in] g Conductance
 * @param[in] params Structure with the synapse auxiliary parameters
 * @return Synaptic current
 */

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
    params_ms[GL_MS_SS] = 1.0 / (v_range * params->s_slow);

    ret = g * params->ms_old * (v_post - e_syn);

    runge_kutta_65(&gl_ms_f, 1, params->dt, vars, params_ms, v_pre);
    params->ms_old = vars[0];

    return ret;
}


/**
 * @brief Golowasch synapse model function.
 *
 * It computes a graded chemical synapse model as detailed in (Golowasch et al, 1999).
 * @param[in] v_post Post-synaptic neuron membrane potential
 * @param[in] v_pre Pre-synaptic neuron membrane potential
 * @param[in] sm Pointer to synapse neuron model
 * @param[out] ret Pointer to the return value
 */

void sm_golowasch_et_al_1999 (double v_post, double v_pre, synapse_model * sm, double * ret) {
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

    aux_gl_params->min = min;
    aux_gl_params->max = max;

    return;
}