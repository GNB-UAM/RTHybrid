 /**
 * @file nm_ghigliazza_holmes_2004.h
 * @brief Header file for the Ghigliazza and Holmes model functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NM_GHIGLIAZZA_HOLMES_2004_H
#define NM_GHIGLIAZZA_HOLMES_2004_H

#include <math.h>
#include "../../../clamp/includes/types_clamp.h"
#include "../../integration_methods.h"


/** @name Ghigliazza-Holmes
 *  Ghigliazza and Holmes neuron model from (Ghigliazza and Holmes, 2004). 
 */
///@{

//Params
#define GH_I 0
#define GH_DT 1
#define GH_G_CA 2
#define GH_G_K 3
#define GH_G_L 4
#define GH_G_KS 5
#define GH_CM 6
#define GH_E_CA 7
#define GH_E_K 8
#define GH_E_L 9
#define GH_EPSILON 10
#define GH_DELTA 11
#define GH_K_CA 12
#define GH_K_K 13
#define GH_K_KS 14
#define GH_VTH_CA 15
#define GH_VTH_K 16
#define GH_VTH_KS 17

//Vars
#define GH_V 0
#define GH_M 1
#define GH_C 2


void gh_init (neuron_model * nm, double * vars, double * params);

double ghigliazza_holmes_inf (double v, double vth, double k);

void ghigliazza_holmes_2004 (neuron_model nm, double syn);

void ghigliazza_holmes_set_pts_burst (double pts_live, neuron_model * nm);

///@}


#endif // NM_GHIGLIAZZA_HOLMES_2004_H


#ifdef __cplusplus
}
#endif
