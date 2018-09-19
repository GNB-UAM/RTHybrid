/**
 * @file nm_hindmarsh_rose_1986.h
 * @brief Header file for the Hindmarsh and Rose model functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NM_HINDMARSH_ROSE_1986_H
#define NM_HINDMARSH_ROSE_1986_H

#include <math.h>
#include "../../../clamp/includes/types_clamp.h"
#include "../../integration_methods.h"


/** @name Hindmarsh-Rose
 *  Hindmarsh-Rose neuron model from (Hindmarsh and Rose, 1984). 
 */
///@{

// Params
#define HR_I 0
#define HR_DT 1
#define HR_R 2
#define HR_S 3

//Vars
#define HR_X 0
#define HR_Y 1
#define HR_Z 2


void hr_init (neuron_model * nm, double * vars, double * params);

void hindmarsh_rose_1986 (neuron_model nm, double syn);

void hr_set_pts_burst (double pts_live, neuron_model * nm);

///@}


#endif // NM_HINDMARSH_ROSE_1986_H


#ifdef __cplusplus
}
#endif 
