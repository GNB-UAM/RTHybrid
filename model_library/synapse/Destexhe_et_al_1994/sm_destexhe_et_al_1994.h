/**
 * @file sm_destexhe_et_al_1994.h
 * @brief Header file for the Destexhe_et_al_1994 synapse model functions.
 */


#ifdef __cplusplus
extern "C" {
#endif

#ifndef SM_DESTEXHE_ET_AL_1994_H
#define SM_DESTEXHE_ET_AL_1994_H

#include <math.h>
#include "../../../clamp/includes/types_clamp.h"
#include "../../integration_methods.h"



#define SYN_MODEL_TO_LIVE 0
#define SYN_LIVE_TO_MODEL 1

#define SYN_SCALE 0
#define SYN_OFFSET 1
#define SYN_CALIBRATE 2

#define SYN_CALIB_PRE 0
#define SYN_CALIB_POST 1

/** @name Destexhe_et_al_1994
 *  Destexhe_et_al_1994 synapse model. 
 */
///@{

#define SM_DESTEXHE_ET_AL_1994_N_G 1
#define SM_DESTEXHE_ET_AL_1994_G 0

// Vars
#define SM_DESTEXHE_ET_AL_1994_R 0

// Params
#define SM_DESTEXHE_ET_AL_1994_ALPHA 0
#define SM_DESTEXHE_ET_AL_1994_BETA 1
#define SM_DESTEXHE_ET_AL_1994_T 2
#define SM_DESTEXHE_ET_AL_1994_PULSE_DURATION 3
#define SM_DESTEXHE_ET_AL_1994_TMAX 4

/**
 * @brief Structure that stores the arguments specified by the user.
 *
 * It is specific for the destexhe_et_al_1994 synapse and will be used as argument in #init_synapse_model.
 */	
typedef struct {
    double g[SM_DESTEXHE_ET_AL_1994_N_G]; /**< Conductances array with length #SM_DESTEXHE_ET_AL_1994_N_G*/
    double alpha;
	double beta;
	double e_syn_per;
	unsigned int pulse_duration;
	double tmax;
} sm_destexhe_et_al_1994_args;


/**
 * @brief Structure that stores the parameters of the destexhe_et_al_1994 synapse model.
 *
 * It is initialized in #init_synapse_model and is part of #synapse_model.
 */ 
typedef struct {
	double alpha;
	double beta;
	double old_vpre;
	double r;
	double e_syn_per;
	double min;
	double max;
	unsigned int t;
	unsigned int pulse_duration;
	double tmax;
} sm_destexhe_et_al_1994_params;



void sm_destexhe_et_al_1994_init (synapse_model * sm, void * syn_args);

void sm_destexhe_et_al_1994 (double v_post, double v_pre, synapse_model * sm, double * ret);


///@}

#endif // SM_DESTEXHE_ET_AL_1994_H


#ifdef __cplusplus
}
#endif
