/**
 * @file synapse_models_functions.h
 * @brief Header file for the synapse models functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SYNAPSE_MODELS_FUNCTIONS_H
#define SYNAPSE_MODELS_FUNCTIONS_H

#include "Empty/sm_empty.h"
#include "Electrical/sm_electrical.h"
#include "Golowasch_et_al_1999/sm_golowasch_et_al_1999.h"

/* MACROS */

#define EMPTY_SYN 0
#define ELECTRICAL 1
#define GOLOWASCH_ET_AL_1999 2



/* General */
void init_synapse_model (synapse_model * sm, int model, void * syn_args);

void free_synapse_model (synapse_model * sm);


#endif // SYNAPSE_MODELS_FUNCTIONS_H


#ifdef __cplusplus
}
#endif
