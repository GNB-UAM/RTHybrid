/**
 * @file sm_greenberg_manor_2005.h
 * @brief Header file for the Greenberg_Manor_2005 synapse model functions.
 */


#ifdef __cplusplus
extern "C" {
#endif

#ifndef SM_GREENBERG_MANOR_2005_H
#define SM_GREENBERG_MANOR_2005_H

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

/** @name Greenberg_Manor_2005
 *  Greenberg_Manor_2005 synapse model. 
 */
///@{

#define SM_GREENBERG_MANOR_2005_N_G 1
#define SM_GREENBERG_MANOR_2005_G 0


// Integrate state variables
#define SM_GREENBERG_MANOR_2005_X 0

#define SM_GREENBERG_MANOR_2005_V 0
#define SM_GREENBERG_MANOR_2005_V12 1
#define SM_GREENBERG_MANOR_2005_K 2 
#define SM_GREENBERG_MANOR_2005_TAU_HI 3
#define SM_GREENBERG_MANOR_2005_TAU_LO 4


/**
 * @brief Structure that stores the arguments specified by the user.
 *
 * It is specific for the greenberg_manor_2005 synapse and will be used as argument in #init_synapse_model.
 */	
typedef struct {
    double g[SM_GREENBERG_MANOR_2005_N_G]; /**< Conductances array with length #GREENBERG_MANOR_2005_N_G*/
    double e_syn_per;
    double dt;
    unsigned int method;

    double m;
	double p;
	double v12_m;
	double k_m;
	double tau_hi_m;
	double tau_lo_m;

	double h;
	double q;
	double v12_h;
	double k_h;
	double tau_hi_h;
	double tau_lo_h;
} sm_greenberg_manor_2005_args;


/**
 * @brief Structure that stores the parameters of the greenberg_manor_2005 synapse model.
 *
 * It is initialized in #init_synapse_model and is part of #synapse_model.
 */ 
typedef struct {
	double dt;
	void (*method)
        (void (*f) (double *, double *, double *, double), 
        int dim, double dt, double * vars, 
        double * params, double aux);
	
	double e_syn_per;
	
	double m;
	double p;
	double v12_m;
	double k_m;
	double tau_hi_m;
	double tau_lo_m;

	double h;
	double q;
	double v12_h;
	double k_h;
	double tau_hi_h;
	double tau_lo_h;
} sm_greenberg_manor_2005_params;



void sm_greenberg_manor_2005_init (synapse_model * sm, void * syn_args);

void sm_greenberg_manor_2005 (double v_post, double v_pre, synapse_model * sm, double * ret);


///@}

#endif // SM_GREENBERG_MANOR_2005_H


#ifdef __cplusplus
}
#endif
