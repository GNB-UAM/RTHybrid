/**
 * @file synapse_models_functions.c
 * @brief Source file with the synapse models functions.
 */


#include "synapse_models_functions.h"

/**
 * @brief Initializates a synapse model.
 *
 * Sets the conductances and parameters to the values introduced by the user.
 * @param[in] sm Pointer to a synapse model structure
 * @param[in] model Type of the synapse model
 * @param[in] syn_args Pointer to an structure with the specific parameters for each kind of model
 */

void init_synapse_model (synapse_model * sm, int model, void * syn_args) {
    sm->type = model;

    switch (model) {
        case SM_EMPTY:
            sm_empty_init(sm, syn_args);
            break;
        case SM_ELECTRICAL:
            sm_electrical_init(sm, syn_args);
            break;
        case SM_GOLOWASCH_ET_AL_1999:
            sm_golowasch_et_al_1999_init(sm, syn_args);
            break;
        case SM_DESTEXHE_ET_AL_1994:
            sm_destexhe_et_al_1994_init(sm, syn_args);
            break;
        case SM_GREENBERG_MANOR_2005:
            sm_greenberg_manor_2005_init(sm, syn_args);
        default:
            return;
    }

    return;
}


/**
 * @brief Frees a synapse model.
 * @param[in] sm Pointer to the syanpse model structure
 */

void free_synapse_model (synapse_model * sm) {
    free_pointers(2, &sm->g, &sm->type_params);
    return;
}
