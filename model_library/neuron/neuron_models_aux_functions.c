#include "neuron_models_aux_functions.h"

/**
 * @brief Selects the best integration step for a neuron model.
 * @param[in] dts Array with the integration steps
 * @param[in] pts Array with the numbers of points needed to complete one burst by the neuron model using the integration steps in dts
 * @param[in] length Length of the dts and pts arrays
 * @param[in] pts_live Number of points of burst from the living neuron
 * @param[out] dt Pointer to store the selected integration step-. If no integration step is found the value will be -1
 * @param[out] dt Pointer to store the number of points per burst from the neuron model with selected integration step. If no integration step is found the value will be -1
 */

void select_dt_neuron_model (double * dts, double * pts, unsigned int length, double pts_live, double * dt, double * pts_burst) {
    double aux = pts_live;
    double factor = 1;
    double intpart, fractpart;
    int flag = 0;
    int i;

    *dt = -1;
    *pts_burst = -1;

    while (aux < pts[0]) {
        aux = pts_live * factor;
        factor += 1;

        for (i = length - 1; i >= 0; i--) {
        	if (pts[i] > aux) {
        		*dt = dts[i];
	            *pts_burst = pts[i];

	            fractpart = modf(*pts_burst / pts_live, &intpart);

	            if (fractpart <= 0.1*intpart) flag = 1;

	            break;
        	}
            
        }

        if (flag == 1) break;
    }

    if (flag == 0) {
        for (i = length - 1; i >= 0; i--) {
        	if (pts[i] > aux) {
        		*dt = dts[i];
	            *pts_burst = pts[i];

	            break;	
        	}
        }
    }

    return;
}