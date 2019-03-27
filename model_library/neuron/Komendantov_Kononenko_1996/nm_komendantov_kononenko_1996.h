/**
 * @file nm_komendantov_kononenko_1996.h
 * @brief Header file for the Komendantov_Kononenko_1996 model functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NM_KOMENDANTOV_KONONENKO_1996_H__
#define NM_KOMENDANTOV_KONONENKO_1996_H__

#include <math.h>
#include "../../../clamp/includes/types_clamp.h"

/** @name Komendantov_Kononenko_1996
 * Komendantov_Kononenko_1996 neuron model.
 */
///@{

#define NM_KOMENDANTOV_KONONENKO_1996_N_VARS 8
// Variables
#define NM_KOMENDANTOV_KONONENKO_1996_V 0
#define NM_KOMENDANTOV_KONONENKO_1996_M_B 1
#define NM_KOMENDANTOV_KONONENKO_1996_H_B 2
#define NM_KOMENDANTOV_KONONENKO_1996_M 3
#define NM_KOMENDANTOV_KONONENKO_1996_H 4
#define NM_KOMENDANTOV_KONONENKO_1996_N 5
#define NM_KOMENDANTOV_KONONENKO_1996_M_CA 6
#define NM_KOMENDANTOV_KONONENKO_1996_CA 7


#define NM_KOMENDANTOV_KONONENKO_1996_N_PARAMS 20
// Parameters
#define NM_KOMENDANTOV_KONONENKO_1996_DT 0
#define NM_KOMENDANTOV_KONONENKO_1996_I 1
#define NM_KOMENDANTOV_KONONENKO_1996_SYN 2
#define NM_KOMENDANTOV_KONONENKO_1996_CM 3
#define NM_KOMENDANTOV_KONONENKO_1996_G_NA_V 4
#define NM_KOMENDANTOV_KONONENKO_1996_V_NA 5
#define NM_KOMENDANTOV_KONONENKO_1996_G_K 6
#define NM_KOMENDANTOV_KONONENKO_1996_V_K 7
#define NM_KOMENDANTOV_KONONENKO_1996_G_NA 8
#define NM_KOMENDANTOV_KONONENKO_1996_G_B 9
#define NM_KOMENDANTOV_KONONENKO_1996_V_B 10
#define NM_KOMENDANTOV_KONONENKO_1996_G_NA_TTX 11
#define NM_KOMENDANTOV_KONONENKO_1996_G_K_TEA 12
#define NM_KOMENDANTOV_KONONENKO_1996_G_CA 13
#define NM_KOMENDANTOV_KONONENKO_1996_V_CA 14
#define NM_KOMENDANTOV_KONONENKO_1996_G_CA_CA 15
#define NM_KOMENDANTOV_KONONENKO_1996_K_BETA 16
#define NM_KOMENDANTOV_KONONENKO_1996_BETA 17
#define NM_KOMENDANTOV_KONONENKO_1996_RHO 18
#define NM_KOMENDANTOV_KONONENKO_1996_K_S 19

void nm_komendantov_kononenko_1996_init (neuron_model * nm, double * vars, double * params);
void nm_komendantov_kononenko_1996_ (neuron_model nm, double syn);
void nm_komendantov_kononenko_1996_set_pts_burst (double pts_live, neuron_model * nm);

///@}

#endif // NM_KOMENDANTOV_KONONENKO_1996_H__

#ifdef __cplusplus
}
#endif