/**
 * @file nm_hindmarsh_rose_1986.h
 * @brief Header file for the Hindmarsh_Rose_1986 model functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NM_HINDMARSH_ROSE_1986_H__
#define NM_HINDMARSH_ROSE_1986_H__

#include <math.h>
#include "../../../clamp/includes/types_clamp.h"

/** @name Hindmarsh_Rose_1986
 * Hindmarsh_Rose_1986 neuron model.
 */
///@{

#define NM_HINDMARSH_ROSE_1986_N_VARS 3
// Variables
#define NM_HINDMARSH_ROSE_1986_V 0
#define NM_HINDMARSH_ROSE_1986_Y 1
#define NM_HINDMARSH_ROSE_1986_Z 2


#define NM_HINDMARSH_ROSE_1986_N_PARAMS 10
// Parameters
#define NM_HINDMARSH_ROSE_1986_DT 0
#define NM_HINDMARSH_ROSE_1986_B 1
#define NM_HINDMARSH_ROSE_1986_A 2
#define NM_HINDMARSH_ROSE_1986_I 3
#define NM_HINDMARSH_ROSE_1986_SYN 4
#define NM_HINDMARSH_ROSE_1986_C 5
#define NM_HINDMARSH_ROSE_1986_D 6
#define NM_HINDMARSH_ROSE_1986_R 7
#define NM_HINDMARSH_ROSE_1986_S 8
#define NM_HINDMARSH_ROSE_1986_XR 9

void nm_hindmarsh_rose_1986_init (neuron_model * nm, double * vars, double * params);
void nm_hindmarsh_rose_1986_ (neuron_model nm, double syn);
double nm_hindmarsh_rose_1986_set_pts_burst (double pts_live, neuron_model * nm);

///@}

#endif // NM_HINDMARSH_ROSE_1986_H__

#ifdef __cplusplus
}
#endif