/**
 * @file sm_electrical.h
 * @brief Header file for the Electrical synapse model functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SM_ELECTRICAL_H
#define SM_ELECTRICAL_H

#include <math.h>
#include "../../../clamp/includes/types_clamp.h"


/* General quizas hay que hacer una funcion de syn general, o un types*/
#define SYN_MODEL_TO_LIVE 0
#define SYN_LIVE_TO_MODEL 1

#define SYN_SCALE 0
#define SYN_OFFSET 1
#define SYN_CALIBRATE 2

#define SYN_CALIB_PRE 0
#define SYN_CALIB_POST 1

/** @name Electrical
 *  Electrical synapse model. 
 */
///@{

#define ELEC_N_G 1
#define ELEC_G 0


/**
 * @brief Structure that stores the arguments specified by the user.
 *
 * It is specific for the electrical synapse and will be used as argument in #init_synapse_model.
 */	
typedef struct {
    double g[ELEC_N_G]; /**< Conductances array with length #ELEC_N_G*/
    int anti;           /**< Antiphase multiplier value */
} syn_elec_args;


/**
 * @brief Structure that stores the parameters of the electrical synapse model.
 *
 * It is initialized in #init_synapse_model and is part of #synapse_model.
 */ 
typedef struct {
    int anti; /**< Antiphase multiplier value */
} syn_elec_params;



void electrical_init (synapse_model * sm, void * syn_args);

void sm_electrical (double v_post, double v_pre, synapse_model * sm, double * ret);

///@}

#endif // SM_ELECTRICAL_H


#ifdef __cplusplus
}
#endif 
