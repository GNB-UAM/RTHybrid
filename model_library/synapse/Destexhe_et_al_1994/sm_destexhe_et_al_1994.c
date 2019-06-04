#include "sm_destexhe_et_al_1994.h"

/**
 * @file sm_destexhe_et_al_1994.c
 * @brief Source file with the Destexhe_et_al_1994 synapse model functions.
 */ 


/** @name Destexhe_et_al_1994
 *  Destexhe_et_al_1994 synapse model. 
 */

 
///@{

/**
 * @brief Sets the amplitude scale and offset parameters of the destexhe_et_al_1994 synapse model according to the living neuron signal.
 * @param[in] sm Pointer to synapse neuron model
 * @param[in] scale Amplitude scale of the living neuron signal regarding to the neuron model
 * @param[in] offset Amplitude offset of the living neuron signal regarding to the neuron model
 * @param[in] min Minimum value of the living neuron signal voltage
 * @param[in] max Maximum value of the living neuron signal voltage
 * @param[in] dt Integration step of the neuron model (-1 if it is not a differential model)
 */

void sm_destexhe_et_al_1994_set_online_params (synapse_model * sm, double scale, double offset, double min, double max, integration_params int_params) {
	sm_destexhe_et_al_1994_params * aux_params = sm->type_params;

    sm->scale = scale;
    sm->offset = offset;
    sm->min = min;
    sm->max = max;
    aux_params->old_vpre = sm->min + (sm->max - sm->min) * 0.5;
    
    if (int_params.method != NULL) {
        aux_params->dt = int_params.dt;
        aux_params->method = int_params.method;
    }

    return;
}


void sm_destexhe_et_al_1994_r_f (double * vars, double * ret, double * params, double aux) {
	
	ret[SM_DESTEXHE_ET_AL_1994_R] = -(params[SM_DESTEXHE_ET_AL_1994_BETA] * vars[SM_DESTEXHE_ET_AL_1994_R]);
	//printf("alpha %f beta %f r %f beta * r %f ", params[SM_DESTEXHE_ET_AL_1994_ALPHA], params[SM_DESTEXHE_ET_AL_1994_BETA], vars[SM_DESTEXHE_ET_AL_1994_R], ret[SM_DESTEXHE_ET_AL_1994_R]);

	if (params[SM_DESTEXHE_ET_AL_1994_T] < params[SM_DESTEXHE_ET_AL_1994_PULSE_DURATION]) {
		ret[SM_DESTEXHE_ET_AL_1994_R] += (params[SM_DESTEXHE_ET_AL_1994_ALPHA] * (1.0 - vars[SM_DESTEXHE_ET_AL_1994_R])) * params[SM_DESTEXHE_ET_AL_1994_TMAX];
		//printf("alpha * (1-r) %f", (params[SM_DESTEXHE_ET_AL_1994_ALPHA] * (1.0 - vars[SM_DESTEXHE_ET_AL_1994_R])));
	}

	//printf("\nret %f\n", ret[SM_DESTEXHE_ET_AL_1994_R]);

	return;
}

/**
 * @brief Destexhe_et_al_1994 synapse model function.
 *
 * @param[in] v_post Post-synaptic neuron membrane potential
 * @param[in] v_pre Pre-synaptic neuron membrane potential
 * @param[in] sm Pointer to synapse neuron model
 * @param[out] ret Pointer to the return value
 */

void sm_destexhe_et_al_1994 (double v_post, double v_pre, synapse_model * sm, double * ret) {
	double params_r[5];
    double min, max, v_range, threshold, e_syn;
	double new_vpre = v_pre;
    sm_destexhe_et_al_1994_params * aux_params = sm->type_params;
    double vars[1] = {aux_params->r};

    min = sm->min;
    max = sm->max;

    if (sm->calibrate == SYN_CALIB_PRE) {
        v_pre = v_pre * sm->scale + sm->offset;
        sm->min = sm->min * sm->scale + sm->offset;
        sm->max = sm->max * sm->scale + sm->offset;
        aux_params->old_vpre = aux_params->old_vpre * sm->scale + sm->offset;
    } else if (sm->calibrate == SYN_CALIB_POST) {
        v_post = (v_post - sm->offset) / sm->scale;
    }

    v_range = sm->max - sm->min;
    e_syn = sm->min + v_range * aux_params->e_syn_per;
    threshold = sm->max - v_range * 0.15;

    //printf("1threshold %f v_pre %f old %f\n", threshold, v_pre, aux_params->old_vpre);

    if (v_pre > threshold && v_pre > aux_params->old_vpre) {
    	aux_params->t = 0;
    	//printf("2threshold %f v_pre %f old %f\n", threshold, v_pre, aux_params->old_vpre);
    }


	params_r[SM_DESTEXHE_ET_AL_1994_ALPHA] = aux_params->alpha;
	params_r[SM_DESTEXHE_ET_AL_1994_BETA] = aux_params->beta;
	params_r[SM_DESTEXHE_ET_AL_1994_T] = aux_params->t;
	params_r[SM_DESTEXHE_ET_AL_1994_PULSE_DURATION] = aux_params->pulse_duration;
	params_r[SM_DESTEXHE_ET_AL_1994_TMAX] = aux_params->tmax;

    aux_params->method(&sm_destexhe_et_al_1994_r_f, 1, aux_params->dt, vars, params_r, 0);
	aux_params->r = vars[SM_DESTEXHE_ET_AL_1994_R];

    //if (sm->calibrate == SYN_CALIB_POST) printf("post t %d min %f max %f esyn %f threshold %f v_pre %f old %f r %f\n", aux_params->t, sm->min, sm->max, e_syn, threshold, v_pre, aux_params->old_vpre, aux_params->r);
    //if (sm->calibrate == SYN_CALIB_PRE) printf("pre t %d min %f max %f esyn %f threshold %f v_pre %f old %f r %f\n\n", aux_params->t, sm->min, sm->max, e_syn, threshold, v_pre, aux_params->old_vpre, aux_params->r);

	aux_params->t++;

    aux_params->old_vpre = new_vpre;

    *ret = sm->g[SM_DESTEXHE_ET_AL_1994_G] * aux_params->r * (v_post - e_syn);



    //printf("Isyn [%f]= g[%f] * r[%f] * (post[%f] - esyn[%f])\n", *ret ,sm->g[SM_DESTEXHE_ET_AL_1994_G],aux_params->r ,v_post,e_syn);

	sm->min = min;
    sm->max = max;
}


/**
 * @brief Initializes the Destexhe_et_al_1994 synapse model.
 * @param[in/out] sm Pointer to synapse neuron model
 * @param[in] syn_args Synapse model parameters entered as input arguments
 */

void sm_destexhe_et_al_1994_init (synapse_model * sm, void * syn_args) {
    sm_destexhe_et_al_1994_args * aux_syn_args = (sm_destexhe_et_al_1994_args *) syn_args;
    sm->type_params = (sm_destexhe_et_al_1994_params *) malloc (sizeof(sm_destexhe_et_al_1994_params));
    sm_destexhe_et_al_1994_params * aux_params = sm->type_params;

    sm->calibrate = SYN_CALIB_PRE;

    sm->g = (double *) malloc (sizeof(double) * SM_DESTEXHE_ET_AL_1994_N_G);
    copy_1d_array(aux_syn_args->g, sm->g, SM_DESTEXHE_ET_AL_1994_N_G);

    aux_params->alpha = aux_syn_args->alpha;
    aux_params->beta = aux_syn_args->beta;
    aux_params->e_syn_per = aux_syn_args->e_syn_per;
    aux_params->pulse_duration = aux_syn_args->pulse_duration;
    aux_params->tmax = aux_syn_args->tmax;

    //aux_params->r = (aux_params->alpha * aux_params->tmax) / (aux_params->alpha * aux_params->tmax + aux_params->beta); //Steady state
    aux_params->r = 0.0;

    aux_params->dt = 0.001;
    aux_params->method = runge_kutta_65;
    //printf("alpha %f beta %f esyn %f pulse %u tmax %f r %f\n", aux_params->alpha, aux_params->beta, aux_params->e_syn_per, aux_params->pulse_duration, aux_params->tmax, aux_params->r);

    sm->func = &sm_destexhe_et_al_1994;
    sm->set_online_parameters = &sm_destexhe_et_al_1994_set_online_params;
}

///@}
