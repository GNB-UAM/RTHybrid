 /**
 * @file sm_golowasch_et_al_1999.h
 * @brief Header file for the Golowasch et al. synapse model functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SM_GOLOWASCH_ET_AL_1999_H
#define SM_GOLOWASCH_ET_AL_1999_H

#include <math.h>
#include "../../../clamp/includes/types_clamp.h"
#include "../../integration_methods.h"


/* General quizas hay que hacer una funcion de syn general, o un types*/
#define SYN_MODEL_TO_LIVE 0
#define SYN_LIVE_TO_MODEL 1

#define SYN_SCALE 0
#define SYN_OFFSET 1
#define SYN_CALIBRATE 2

#define SYN_CALIB_PRE 0
#define SYN_CALIB_POST 1


/** @name Golowasch
 *  Graded chemical synapse model from (Golowasch et al, 1999). 
 */
///@{

#define GL_G_FAST 0
#define GL_G_SLOW 1
#define GL_N_G 2

#define GL_MIN 3
#define GL_MAX 4
#define GL_K1 5
#define GL_K2 6
#define GL_DT 7
#define GL_VFAST 8
#define GL_VSLOW 9
#define GL_PERIOD 10
#define GL_MS_OLD 11

#define GL_MS_K1 0
#define GL_MS_K2 1
#define GL_MS_SS 2
#define GL_MS_VS 3


/**
 * @brief Structure that stores the arguments specified by the user.
 *
 * It is specific for (Golowasch et al, 1999) synapse and will be used as argument in #init_synapse_model.
 */ 	
typedef struct {
    double g[GL_N_G];   /**< Conductances array with length #GL_N_G*/
    double v_fast;      /**< Voltage threshold for the fast synapse*/
    double v_slow;      /**< Voltage threshold for the slow synapse*/
    double s_fast;      /**< Sigmoid scaling for the fast synapse*/
    double s_slow;      /**< Sigmoid scaling for the slow synapse*/
    double k1;          /**< Temporal parameter for the slow conductance*/
    double k2;          /**< Temporal parameter for the slow conductance*/
} syn_gl_args;


/**
 * @brief Structure that stores the parameters of the (Golowasch et al, 1999) synapse model.
 *
 * It is initialized in #init_synapse_model and is part of #synapse_model.
 */ 	
typedef struct {
    double min;     /**< Minimum value of the living neuron signal voltage*/ 
    double max;     /**< Maximum value of the living neuron signal voltage*/
    double k1;      /**< Temporal parameter for the slow conductance*/
    double k2;      /**< Temporal parameter for the slow conductance*/
    double v_fast;  /**< Voltage threshold for the fast synapse*/
    double v_slow;  /**< Voltage threshold for the slow synapse*/
    double s_fast;  /**< Sigmoid scaling for the fast synapse*/
    double s_slow;  /**< Sigmoid scaling for the slow synapse*/
    double ms_old;  /**< Last value of m_slow*/
    double dt;      /**< Integration step*/
} syn_gl_params;


void sm_golowasch_et_al_1999_init (synapse_model * sm, void * syn_args);

void sm_golowasch_et_al_1999 (double v_post, double v_pre, synapse_model * params, double * ret);

///@}



#endif // SM_GOLOWASCH_ET_AL_1999_H


#ifdef __cplusplus
}
#endif 

