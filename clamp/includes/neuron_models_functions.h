#ifdef __cplusplus
extern "C" {
#endif

#ifndef NEURON_MODELS_FUNCTIONS_H
#define NEURON_MODELS_FUNCTIONS_H

#include <math.h>
#include "types_clamp.h"

/* General functions */

void init_neuron_model (neuron_model * nm, int model);

void free_neuron_model (neuron_model * nm);


/* Models functions */

/* IZHIKEVICH */

void izh_f (double * vars, double * ret, double * params, double syn);

void izhikevich (neuron_model nm, double syn);

void iz_set_pts_burst (double pts_live, double * pts_model);


/* HINDMARSH-ROSE */

void hr_f (double * vars, double * ret, double * params, double syn);

void hindmarsh_rose (neuron_model nm, double syn);

void hr_set_pts_burst (double pts_live, double * pts_model);


/* RULKOV MAP */

void rlk_f (double * vars, double * ret, double * params, double syn);

void rulkov_map (neuron_model nm, double syn);

void rlk_set_pts_burst (double pts_live, double * pts_model);


#endif // NEURON_MODELS_FUNCTIONS_H


#ifdef __cplusplus
}
#endif