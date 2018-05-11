/**
 * @file neuron_models_functions.h
 * @brief Header file for the neuron models functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NEURON_MODELS_FUNCTIONS_H
#define NEURON_MODELS_FUNCTIONS_H

#include <math.h>
#include "types_clamp.h"

/* Macros */

#define EMPTY_NEURON 0
#define IZ 1
#define HR 2
#define RLK 3
#define GH 4

#define X 0
#define Y 1
#define Z 2

/* General functions */

void init_neuron_model (neuron_model * nm, int model, double * vars, double * params);

void free_neuron_model (neuron_model * nm);


/* Models functions */


/** @name Empty
 *  Empty neuron model. 
 */
///@{

void empty (neuron_model nm, double syn);

void empty_set_pts_burst (double pts_live, neuron_model * nm);

///@}


/** @name Izhikevich
 *  Izhikevich neuron model from (Izhikevich, 2003). 
 */
///@{

#define IZ_I 0
#define IZ_DT 1
#define IZ_A 2
#define IZ_B 3
#define IZ_C 4
#define IZ_D 5

void izhikevich (neuron_model nm, double syn);

void iz_set_pts_burst (double pts_live, neuron_model * nm);

///@}


/** @name Hindmarsh-Rose
 *  Hindmarsh-Rose neuron model from (Hindmarsh and Rose, 1984). 
 */
///@{

#define HR_I 0
#define HR_DT 1
#define HR_R 2
#define HR_S 3

void hindmarsh_rose (neuron_model nm, double syn);

void hr_set_pts_burst (double pts_live, neuron_model * nm);

///@}


/** @name Rulkov map
 *  Rulkov neuron model from (Rulkov, 2001). 
 */
///@{

#define RLK_I 0
#define RLK_ALPHA 1
#define RLK_MU 2
#define RLK_SIGMA 3
#define RLK_J 4
#define RLK_OLD 5
#define RLK_PTS 6
#define RLK_INTER 7

void rulkov_map (neuron_model nm, double syn);

void rlk_set_pts_burst (double pts_live, neuron_model * nm);

///@}


/** @name Ghigliazza-Holmes
 *  Ghigliazza and Holmes neuron model from (Ghigliazza and Holmes, 2004). 
 */
///@{

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
 
#define GH_M 1
#define GH_C 2

double ghigliazza_holmes_inf (double v, double vth, double k);

void ghigliazza_holmes (neuron_model nm, double syn);

void ghigliazza_holmes_set_pts_burst (double pts_live, neuron_model * nm);

///@}

#endif // NEURON_MODELS_FUNCTIONS_H


#ifdef __cplusplus
}
#endif