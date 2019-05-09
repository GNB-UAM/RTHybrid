#include "nm_empty.h"

/**
 * @file nm_empty.c
 * @brief Source file with the empty model functions.
 */

/** @name Empty
 *  Empty neuron model. 
 */
///@{

/**
 * @brief Initializes empty neuron model.
 *
 * @param[in/out] nm Pointer to the neuron model structure
 * @param[in] vars Neuron model variables entered as input arguments
 * @param[in] params Neuron model parameters entered as input arguments
 */

void nm_empty_init (neuron_model * nm, double * vars, double * params) {
    nm->dim = 1;
    nm->vars = (double *) malloc (sizeof(double) * nm->dim);
    nm->vars[0] = 0.0;

    nm->n_params = 0;
    nm->params = NULL;

    nm->max = 1.0;
    nm->min = 0.0;

    nm->func = &nm_empty;
    nm->set_pts_burst = &nm_empty_set_pts_burst;
    nm->method = NULL;

    return;
}

/**
 * @brief Empty neuron model function. Does not compute anything.
 * @param[in] nm Neuron model structure
 * @param[in] syn Synapse input current value
 */
void nm_empty (neuron_model nm, double syn) {
    return;
}

/**
 * @brief Sets the empty model number of points per burst.
 *
 * The number of points per burst of the model is equalized to the number of points per burst of the living neuron.
 * @param[in] pts_live Number of points in a living neuron burst
 * @param[in] nm Pointer to the neuron model structure
 * @return Integration step, default -1
 */
double nm_empty_set_pts_burst (double pts_live, neuron_model * nm) {
    nm->pts_burst = pts_live;
    return -1;
}

///@} 
