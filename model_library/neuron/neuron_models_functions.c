/**
 * @file neuron_models_functions.c
 * @brief Source file with the neuron models functions.
 */

#include "neuron_models_functions.h"

/* General functions */

/**
 * @brief Initializates a neuron model.
 *
 * Sets the starting values of its variables and parameters to the introduced by the user, as well as its minimum and maximum values.
 * @param[in] nm Pointer to a neuron model structure
 * @param[in] model Type of the neuron model
 * @param[in] vars Array of doubles with the initial values of the variables of the model
 * @param[in] params Array of doubles with the parameters of the model
 */


void init_neuron_model (neuron_model * nm, int model, double * vars, double * params) {
    nm->type = model;

    switch (model) {
        case NM_EMPTY:
            nm_empty_init(nm, vars, params);

            break;
        case NM_IZHIKEVICH_2003:
            nm_izhikevich_2003_init(nm, vars, params);

            break;
        case NM_HINDMARSH_ROSE_1986:
            nm_hindmarsh_rose_1986_init(nm, vars, params);

            break;
        case NM_RULKOV_2002:
            nm_rulkov_2002_init(nm, vars, params);

            break;
        case NM_GHIGLIAZZA_HOLMES_2004:
            nm_ghigliazza_holmes_2004_init(nm, vars, params);

            break;
        case NM_WANG_1993:
            nm_wang_1993_init(nm, vars, params);

            break;
        default:
            return;
    }

    return;
}

/**
 * @brief Frees a neuron model.
 * @param[in] nm Pointer to the neuron model structure
 */

void free_neuron_model (neuron_model * nm) {
    free_pointers(2, &(nm->vars), &(nm->params));
    return;
}
