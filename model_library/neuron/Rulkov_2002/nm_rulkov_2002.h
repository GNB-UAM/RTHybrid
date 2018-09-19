/**
 * @file nm_rulkov_2002.h
 * @brief Header file for the Rulkov model functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NM_RULKOV_2002_H
#define NM_RULKOV_2002_H

#include <math.h>
#include "../../../clamp/includes/types_clamp.h"


/** @name Rulkov map
 *  Rulkov neuron model from (Rulkov, 2001). 
 */
///@{

//Params
#define RLK_I 0
#define RLK_ALPHA 1
#define RLK_MU 2
#define RLK_SIGMA 3
#define RLK_J 4
#define RLK_OLD 5
#define RLK_PTS 6
#define RLK_INTER 7

//Vars
#define RLK_X 0
#define RLK_Y 1

void rlk_init (neuron_model * nm, double * vars, double * params);

void rulkov_2002 (neuron_model nm, double syn);

void rlk_set_pts_burst (double pts_live, neuron_model * nm);

///@}


#endif // NM_RULKOV_2002_H


#ifdef __cplusplus
}
#endif
 
