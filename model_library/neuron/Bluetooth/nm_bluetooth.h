/**
 * @file nm_bluetooth.h
 * @brief Header file for the Bluetooth model functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NM_BLUETOOTH_H__
#define NM_BLUETOOTH_H__

#include <math.h>
#include "../../../clamp/includes/types_clamp.h"

/** @name Bluetooth
 * Bluetooth neuron model.
 */
///@{

#define NM_BLUETOOTH_N_VARS 2
// Variables
#define NM_BLUETOOTH_N1 0
#define NM_BLUETOOTH_N2 1


#define NM_BLUETOOTH_N_PARAMS 4
// Parameters
#define NM_BLUETOOTH_DT 0
#define NM_BLUETOOTH_COUNTER 1
#define NM_BLUETOOTH_PER 2
#define NM_BLUETOOTH_MAX 3

void nm_bluetooth_init (neuron_model * nm, double * vars, double * params);
void nm_bluetooth (neuron_model nm, double syn);
double nm_bluetooth_set_pts_burst (double pts_live, neuron_model * nm);

///@}

#endif // NM_BLUETOOTH_H__

#ifdef __cplusplus
}
#endif