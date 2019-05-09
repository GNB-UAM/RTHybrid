#include "sm_empty.h"

/**
 * @file sm_empty.c
 * @brief Source file with the empty synapse model functions.
 */ 



/** @name Empty
 *  Empty synapse model. 
 */
///@{



/**
 * @brief Sets the amplitude scale and offset parameters of the empty synapse model according to the living neuron signal.
 * @param[in] sm Pointer to synapse neuron model
 * @param[in] scale Amplitude scale of the living neuron signal regarding to the neuron model
 * @param[in] offset Amplitude offset of the living neuron signal regarding to the neuron model
 * @param[in] min Minimum value of the living neuron signal voltage
 * @param[in] max Maximum value of the living neuron signal voltage
 * @param[in] dt Integration step of the neuron model (-1 if it is not a differential model)
 */

void sm_empty_set_online_params (synapse_model * sm, double scale, double offset, double min, double max, double dt) {
    return;
}



/**
 * @brief Empty synapse model function. 
 * 
 * Always returns 0.
 * @param[in] v_post Post-synaptic neuron membrane potential
 * @param[in] v_pre Pre-synaptic neuron membrane potential
 * @param[in] sm Pointer to synapse neuron model
 * @param[out] ret Pointer to the return value
 */

void sm_empty (double v_post, double v_pre, synapse_model * sm, double * ret) {
    *ret = 0.0;
    return;
}


/**
 * @brief Initializes the empty synapse model.
 * @param[in/out] sm Pointer to synapse neuron model
 * @param[in] syn_args Synapse model parameters entered as input arguments
 */

void sm_empty_init (synapse_model * sm, void * syn_args) {
	sm->type_params = NULL;
    sm->g = NULL;

    sm->func = &sm_empty;
    sm->set_online_parameters = &sm_empty_set_online_params;
}

///@} 
