/**
 * @file synapse_models_functions.h
 * @brief Header file for the synapse models functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SYNAPSE_MODELS_FUNCTIONS_H
#define SYNAPSE_MODELS_FUNCTIONS_H

#include <math.h>
#include "types_clamp.h"


/* MACROS */

#define EMPTY_SYN 0
#define ELECTRIC 1
#define GOLOWASCH 2

/* General */
#define SYN_MODEL_TO_LIVE 0
#define SYN_LIVE_TO_MODEL 1

#define SYN_SCALE 0
#define SYN_OFFSET 1
#define SYN_CALIBRATE 2

#define SYN_CALIB_PRE 0
#define SYN_CALIB_POST 1


/* General */
void init_synapse_model (synapse_model * sm, int model, void * syn_args);

void free_synapse_model (synapse_model * sm);


/** @name Empty
 *  Empty synapse model. 
 */
///@{

void empty_syn (double v_post, double v_pre, synapse_model * sm, double * ret);

///@}


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



void elec_set_online_params (synapse_model * sm, double scale, double offset);

void elec_syn (double v_post, double v_pre, synapse_model * sm, double * ret);

///@}


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



void gl_set_online_params (synapse_model * sm, double scale, double offset, double min, double max);

void golowasch_syn (double v_post, double v_pre, synapse_model * params, double * ret);

///@}



#endif // SYNAPSE_MODELS_FUNCTIONS_H


#ifdef __cplusplus
}
#endif