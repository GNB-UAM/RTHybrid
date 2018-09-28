#include "nm_rulkov_2002.h"

/**
 * @file nm_rulkov_2002.h
 * @brief Source file for the Rulkov model functions.
 */

/** @name Rulkov
 *  Rulkov neuron model from (Rulkov, 2002). 
 */
///@{

/**
 * @brief Initializes Rulkov neuron model.
 *
 * @param[in/out] nm Pointer to the neuron model structure
 * @param[in] vars Neuron model variables entered as input arguments
 * @param[in] params Neuron model parameters entered as input arguments
 */

void nm_rulkov_2002_init (neuron_model * nm, double * vars, double * params) {
    nm->dim = 2;
    nm->vars = (double *) malloc (sizeof(double) * nm->dim);
    copy_1d_array(vars, nm->vars, nm->dim);

    nm->n_params = 8;
    nm->params = (double *) malloc (sizeof(double) * nm->n_params);
    copy_1d_array(params, nm->params, nm->n_params);

    nm->max = 2.111;
    nm->min = -1.977;
    nm->pts_burst = -1.0;

    nm->func = &nm_rulkov_2002;
    nm->set_pts_burst = &nm_rulkov_2002_set_pts_burst;
    nm->method = NULL;

    return;
}

/**
 * @brief Rulkov neuron model equations.
 * @param[in] vars Neuron model variables
 * @param[out] ret Return values array
 * @param[in] params Neuron models parameters
 * @param[in] syn Synapse input current value
 */

void nm_rulkov_2002_f (double * vars, double * ret, double * params, double syn) {
    double u;

    ret[RLK_Y] = vars[RLK_Y] - params[RLK_MU] * (vars[RLK_X] + 1) + params[RLK_MU] * params[RLK_SIGMA];
    u = vars[RLK_Y] - syn * params[RLK_I];


    if (vars[RLK_X] <= 0) {
        ret[RLK_X] = params[RLK_ALPHA] / (1 - vars[RLK_X]) + u;
    } else if (vars[RLK_X] >= params[RLK_ALPHA] + u) {
        ret[RLK_X] = -1;
    } else {
        ret[RLK_X] = params[RLK_ALPHA] + u;
    }


    return;
}


/**
 * @brief Rulkov neuron model.
 *
 * This model does not have differential equations and computes a map instead. 
 * Since only around 334 points are needed to build a burst, additional points need to be interpolated.
 * @param[in] nm Neuron model structure
 * @param[in] syn Synapse input current value
 */

void nm_rulkov_2002 (neuron_model nm, double syn) {
    double ret[2];
    double t0, t1, t, x0, x1;
    double inter_pts = (nm.pts_burst - 334) / 334;

    if (nm.params[RLK_J] >= inter_pts) {
        nm.vars[RLK_X] = nm.params[RLK_OLD];
        nm_rulkov_2002_f(nm.vars, ret, nm.params, syn);
        nm.vars[RLK_X] = ret[RLK_X];
        nm.vars[RLK_Y] = ret[RLK_Y];
        nm.params[RLK_OLD] = nm.vars[RLK_X];
        nm.params[RLK_J] = 1;

        /* Next point for interpolation */
        nm_rulkov_2002_f(nm.vars, ret, nm.params, syn);
        nm.params[RLK_INTER] = ret[RLK_X];     
    } else {
        /* Interpolation */
        t0 = 0.0;
        t1 = inter_pts;
        t = nm.params[RLK_J];
        x0 = nm.params[RLK_OLD];
        x1 = nm.params[RLK_INTER];
        ret[RLK_X] = x0 + ((t - t0) * ((x1 - x0) / (t1 - t0)));
        ret[RLK_Y] = nm.vars[RLK_Y];

        nm.params[RLK_J]++;

        nm.vars[RLK_X] = ret[RLK_X];
        nm.vars[RLK_Y] = ret[RLK_Y];
    }

    return;
}


/**
 * @brief Sets Rulkov model number of points per burst.
 *
 * The number of points per burst of the model is equalized to the number of points per burst of the living neuron.
 * @param[in] pts_live Number of points in a living neuron burst
 * @param[in] nm Pointer to the neuron model structure
 */

void nm_rulkov_2002_set_pts_burst (double pts_live, neuron_model * nm) {
    nm->pts_burst = pts_live;
    nm->params[RLK_J] = ((nm->pts_burst - 334) / 334) + 1;
    return;
}

///@} 
