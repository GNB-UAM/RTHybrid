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
#include "Komendantov_Kononenko_1996/nm_komendantov_kononenko_1996.h"
#include "Bluetooth/nm_bluetooth.h"

/* Macros */

#define NM_EMPTY 0
#define NM_IZHIKEVICH_2003 1
#define NM_HINDMARSH_ROSE_1986 2
#define NM_RULKOV_2002 3
#define NM_GHIGLIAZZA_HOLMES_2004 4
#define NM_WANG_1993 5
#define NM_KOMENDANTOV_KONONENKO_1996 6
#define NM_BLUETOOTH 7


/* General functions */

void init_neuron_model (neuron_model * nm, int model, double * vars, double * params);

void free_neuron_model (neuron_model * nm);

#endif // NEURON_MODELS_FUNCTIONS_H


#ifdef __cplusplus
}
#endif
