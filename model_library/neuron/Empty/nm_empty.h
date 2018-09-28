/**
 * @file nm_empty.h
 * @brief Header file for the Empty model functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NM_EMPTY_H
#define NM_EMPTY_H

#include "../../../clamp/includes/types_clamp.h"


/** @name Empty
 *  Empty neuron model. 
 */
///@{

void nm_empty_init (neuron_model * nm, double * vars, double * params);

void nm_empty (neuron_model nm, double syn);

void nm_empty_set_pts_burst (double pts_live, neuron_model * nm);

///@}


#endif // NM_EMPTY_H


#ifdef __cplusplus
}
#endif
 
