/**
 * @file nm_wang_1993.h
 * @brief Header file for the Wang model functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NM_WANG_1993_H
#define NM_WANG_1993_H

#include "../../../clamp/includes/types_clamp.h"


/** @name Wang
 *  Wang neuron model from (Wang, 1993). 
 */
///@{

//Params
#define WANG_I 0
#define WANG_DT 1
#define WANG_G_NA 2
#define WANG_G_NAP 3
#define WANG_G_K 4
#define WANG_G_KS 5
#define WANG_G_L 6
#define WANG_CM 7
#define WANG_V_NA 8
#define WANG_V_K 9
#define WANG_V_L 10
#define WANG_SIGMA 11
#define WANG_PHI 12
#define WANG_RHO 13
#define WANG_TAUM 14

//Vars
#define WANG_V 0
#define WANG_H_NA 1
#define WANG_N_K 2
#define WANG_M_KS 3
#define WANG_H1_KS 4
#define WANG_H2_KS 5

void wang_1993 (neuron_model nm, double syn);

double wang_set_pts_burst (double pts_live, neuron_model * nm);

void wang_init (neuron_model * nm, double * vars, double * params);

///@}


#endif // NM_WANG_1993_H


#ifdef __cplusplus
}
#endif
 
