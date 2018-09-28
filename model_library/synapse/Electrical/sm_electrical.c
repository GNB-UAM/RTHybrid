#include "sm_electrical.h"

/**
 * @file sm_electrical.c
 * @brief Source file with the Electrical synapse model functions.
 */ 


/** @name Electrical
 *  Electrical synapse model. 
 */

 
///@{

/**
 * @brief Sets the amplitude scale and offset parameters of the electrical synapse model according to the living neuron signal.
 * @param[in] sm Pointer to synapse neuron model
 * @param[in] scale Amplitude scale of the living neuron signal regarding to the neuron model
 * @param[in] offset Amplitude offset of the living neuron signal regarding to the neuron model
 */

void sm_electrical_set_online_params (synapse_model * sm, double scale, double offset, double min, double max) {
    sm->scale = scale;
    sm->offset = offset;

    return;
}




/**
 * @brief Electrical synapse model function.
 *
 * It returns the difference of potential between the post and pre synaptic voltages, multiplied to the conductance: g * (v_post - v_pre).
 * @param[in] v_post Post-synaptic neuron membrane potential
 * @param[in] v_pre Pre-synaptic neuron membrane potential
 * @param[in] sm Pointer to synapse neuron model
 * @param[out] ret Pointer to the return value
 */

void sm_electrical (double v_post, double v_pre, synapse_model * sm, double * ret) {
    syn_elec_params * aux_elec_params = sm->type_params;

    if (sm->calibrate == SYN_CALIB_PRE) {
        v_pre = v_pre * sm->scale + sm->offset;
    } else if (sm->calibrate == SYN_CALIB_POST) {
        v_post = (v_post - sm->offset) / sm->scale;
    }

    *ret = aux_elec_params->anti * (sm->g[ELEC_G] * (v_post - v_pre));
    return;
}


/**
 * @brief Initializes the electrical synapse model.
 * @param[in/out] sm Pointer to synapse neuron model
 * @param[in] syn_args Synapse model parameters entered as input arguments
 */

void sm_electrical_init (synapse_model * sm, void * syn_args) {
    syn_elec_args * aux_syn_args = (syn_elec_args *) syn_args;
    sm->type_params = (syn_elec_params *) malloc (sizeof(syn_elec_params));
    syn_elec_params * aux_elec_params = sm->type_params;

    sm->calibrate = SYN_CALIB_PRE;
    aux_elec_params->anti = aux_syn_args->anti;

    sm->g = (double *) malloc (sizeof(ELEC_N_G));
    copy_1d_array(aux_syn_args->g, sm->g, ELEC_N_G);

    sm->func = &sm_electrical;
    sm->set_online_parameters = &sm_electrical_set_online_params;
}

///@}
