/**
 * @file nm_cpg_model.h
 * @brief Header file for the CPG_Model model functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NM_CPG_MODEL_H__
#define NM_CPG_MODEL_H__

#include <math.h>
#include "../../../clamp/includes/types_clamp.h"

/** @name CPG_Model
 * CPG_Model neuron model.
 */
///@{

void nm_cpg_model (neuron_model nm, double syn);
void nm_cpg_model_init (neuron_model * nm, double * vars, double * params);
double nm_cpg_model_set_pts_burst (double pts_live, neuron_model * nm);

///@}

#endif // NM_CPG_MODEL_H__

#ifdef __cplusplus
}
#endif
