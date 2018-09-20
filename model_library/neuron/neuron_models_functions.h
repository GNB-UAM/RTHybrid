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
#include "../../clamp/includes/types_clamp.h"

#include "Empty/nm_empty.h"
#include "Izhikevich_2003/nm_izhikevich_2003.h"
#include "Hindmarsh_Rose_1986/nm_hindmarsh_rose_1986.h"
#include "Rulkov_2002/nm_rulkov_2002.h"
#include "Ghigliazza_Holmes_2004/nm_ghigliazza_holmes_2004.h"
#include "Wang_1993/nm_wang_1993.h"

/* Macros */

#define EMPTY_NEURON 0
#define IZ 1
#define HR 2
#define RLK 3
#define GH 4
#define WANG 5


/* General functions */

void init_neuron_model (neuron_model * nm, int model, double * vars, double * params);

void free_neuron_model (neuron_model * nm);

#endif // NEURON_MODELS_FUNCTIONS_H


#ifdef __cplusplus
}
#endif
