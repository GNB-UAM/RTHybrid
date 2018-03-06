#ifdef __cplusplus
extern "C" {
#endif

#ifndef NEURON_MODELS_FUNCTIONS_H
#define NEURON_MODELS_FUNCTIONS_H

#include <math.h>
#include "types_clamp.h"

/* Macros */

#define IZ 0
#define HR 1
#define RLK 2

#define X 0
#define Y 1
#define Z 2

/* IZHIKEVICH */
#define IZ_I 0
#define IZ_DT 1
#define IZ_A 2
#define IZ_B 3
#define IZ_C 4
#define IZ_D 5


/* HINDMARSH-ROSE */
#define HR_I 0
#define HR_DT 1
#define HR_R 2
#define HR_S 3


/* RULKOV MAP */
#define RLK_I 0
#define RLK_ALPHA 1
#define RLK_MU 2
#define RLK_SIGMA 3
#define RLK_J 4
#define RLK_OLD 5
#define RLK_PTS 6
#define RLK_INTER 7

/* General functions */

void init_neuron_model (neuron_model * nm, int model, double * vars, double * params);

void free_neuron_model (neuron_model * nm);


/* Models functions */

/* IZHIKEVICH */

void izh_f (double * vars, double * ret, double * params, double syn);

void izhikevich (neuron_model nm, double syn);

void iz_set_pts_burst (double pts_live, neuron_model nm);


/* HINDMARSH-ROSE */

void hr_f (double * vars, double * ret, double * params, double syn);

void hindmarsh_rose (neuron_model nm, double syn);

void hr_set_pts_burst (double pts_live, neuron_model nm);


/* RULKOV MAP */

void rlk_f (double * vars, double * ret, double * params, double syn);

void rulkov_map (neuron_model nm, double syn);

void rlk_set_pts_burst (double pts_live, neuron_model nm);


#endif // NEURON_MODELS_FUNCTIONS_H


#ifdef __cplusplus
}
#endif