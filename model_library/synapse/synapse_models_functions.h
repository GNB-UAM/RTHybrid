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
#include "Destexhe_et_al_1994/sm_destexhe_et_al_1994.h"
#include "Greenberg_Manor_2005/sm_greenberg_manor_2005.h"

/* MACROS */

#define SM_EMPTY 0
#define SM_ELECTRICAL 1
#define SM_GOLOWASCH_ET_AL_1999 2
#define SM_DESTEXHE_ET_AL_1994 3
#define SM_GREENBERG_MANOR_2005 4




/* General */
void init_synapse_model (synapse_model * sm, int model, void * syn_args);

void free_synapse_model (synapse_model * sm);


#endif // SYNAPSE_MODELS_FUNCTIONS_H


#ifdef __cplusplus
}
#endif
