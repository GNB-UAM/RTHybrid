/**
 * @file nm_ghigliazza_holmes_2004.h
 * @brief Header file for the Ghigliazza_Holmes_2004 model functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NM_GHIGLIAZZA_HOLMES_2004_H__
#define NM_GHIGLIAZZA_HOLMES_2004_H__

#include <math.h>
#include "../../../clamp/includes/types_clamp.h"

/** @name Ghigliazza_Holmes_2004
 * Ghigliazza_Holmes_2004 neuron model.
 */
///@{

#define NM_GHIGLIAZZA_HOLMES_2004_N_VARS 3
// Variables
#define NM_GHIGLIAZZA_HOLMES_2004_V 0
#define NM_GHIGLIAZZA_HOLMES_2004_M 1
#define NM_GHIGLIAZZA_HOLMES_2004_C 2


#define NM_GHIGLIAZZA_HOLMES_2004_N_PARAMS 19
// Parameters
#define NM_GHIGLIAZZA_HOLMES_2004_DT 0
#define NM_GHIGLIAZZA_HOLMES_2004_I 1
#define NM_GHIGLIAZZA_HOLMES_2004_SYN 2
#define NM_GHIGLIAZZA_HOLMES_2004_CM 3
#define NM_GHIGLIAZZA_HOLMES_2004_EPSILON 4
#define NM_GHIGLIAZZA_HOLMES_2004_DELTA 5
#define NM_GHIGLIAZZA_HOLMES_2004_GCA 6
#define NM_GHIGLIAZZA_HOLMES_2004_ECA 7
#define NM_GHIGLIAZZA_HOLMES_2004_GK 8
#define NM_GHIGLIAZZA_HOLMES_2004_EK 9
#define NM_GHIGLIAZZA_HOLMES_2004_GKS 10
#define NM_GHIGLIAZZA_HOLMES_2004_GL 11
#define NM_GHIGLIAZZA_HOLMES_2004_EL 12
#define NM_GHIGLIAZZA_HOLMES_2004_KK 13
#define NM_GHIGLIAZZA_HOLMES_2004_VTHK 14
#define NM_GHIGLIAZZA_HOLMES_2004_KKS 15
#define NM_GHIGLIAZZA_HOLMES_2004_VTHKS 16
#define NM_GHIGLIAZZA_HOLMES_2004_KCA 17
#define NM_GHIGLIAZZA_HOLMES_2004_VTHCA 18

void nm_ghigliazza_holmes_2004_init (neuron_model * nm, double * vars, double * params);
void nm_ghigliazza_holmes_2004_ (neuron_model nm, double syn);
double nm_ghigliazza_holmes_2004_set_pts_burst (double pts_live, neuron_model * nm);

///@}

#endif // NM_GHIGLIAZZA_HOLMES_2004_H__

#ifdef __cplusplus
}
#endif