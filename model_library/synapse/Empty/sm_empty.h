/**
 * @file sm_empty.h
 * @brief Header file for the empty synapse model functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SM_EMPTY_H
#define SM_EMPTY_H

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

/** @name Empty
 *  Empty synapse model. 
 */
///@{

void empty_init (synapse_model * sm, void * syn_args);

void sm_empty (double v_post, double v_pre, synapse_model * sm, double * ret);

///@}

#endif // SM_EMPTY_H


#ifdef __cplusplus
}
#endif 
 
