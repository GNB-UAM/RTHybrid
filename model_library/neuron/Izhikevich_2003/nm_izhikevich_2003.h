/**
 * @file nm_izhikevich_2003.h
 * @brief Header file for the Izhikevich model functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NM_IZHIKEVICH_2003_H
#define NM_IZHIKEVICH_2003_H

#include "../../../clamp/includes/types_clamp.h"


/** @name Izhikevich
 *  Izhikevich neuron model from (Izhikevich, 2003). 
 */
///@{

//Params
#define IZ_I 0
#define IZ_DT 1
#define IZ_A 2
#define IZ_B 3
#define IZ_C 4
#define IZ_D 5

//Vars
#define IZ_V 0
#define IZ_U 1


void nm_izhikevich_2003_init (neuron_model * nm, double * vars, double * params);

void nm_izhikevich_2003 (neuron_model nm, double syn);

void nm_izhikevich_2003_set_pts_burst (double pts_live, neuron_model * nm);

///@}


#endif // NM_IZHIKEVICH_2003_H


#ifdef __cplusplus
}
#endif
