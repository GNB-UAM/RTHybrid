/**
 * @file nm_izhikevich_2003.h
 * @brief Header file for the Izhikevich_2003 model functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NM_IZHIKEVICH_2003_H__
#define NM_IZHIKEVICH_2003_H__

#include <math.h>
#include "../../../clamp/includes/types_clamp.h"

/** @name Izhikevich_2003
 * Izhikevich_2003 neuron model.
 */
///@{

#define NM_IZHIKEVICH_2003_N_VARS 2
// Variables
#define NM_IZHIKEVICH_2003_V 0
#define NM_IZHIKEVICH_2003_U 1


#define NM_IZHIKEVICH_2003_N_PARAMS 7
// Parameters
#define NM_IZHIKEVICH_2003_DT 0
#define NM_IZHIKEVICH_2003_I 1
#define NM_IZHIKEVICH_2003_SYN 2
#define NM_IZHIKEVICH_2003_A 3
#define NM_IZHIKEVICH_2003_B 4
#define NM_IZHIKEVICH_2003_D 5
#define NM_IZHIKEVICH_2003_C 6

void nm_izhikevich_2003_init (neuron_model * nm, double * vars, double * params);
void nm_izhikevich_2003_ (neuron_model nm, double syn);
double nm_izhikevich_2003_set_pts_burst (double pts_live, neuron_model * nm);

///@}

#endif // NM_IZHIKEVICH_2003_H__

#ifdef __cplusplus
}
#endif