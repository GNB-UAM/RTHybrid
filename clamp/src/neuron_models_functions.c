/**
 * @file neuron_models_functions.c
 * @brief Source file with the neuron models functions.
 */

#include "../includes/neuron_models_functions.h"

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
        case EMPTY_NEURON:
            nm->dim = 1;
            nm->vars = (double *) malloc (sizeof(double) * nm->dim);
            nm->vars[X] = 0.0;

            nm->n_params = 0;
            nm->params = NULL;

            nm->max = 1.0;
            nm->min = 0.0;

            nm->func = &empty;
            nm->set_pts_burst = &empty_set_pts_burst;

            break;
        case IZ:
            nm->dim = 2;
            nm->vars = (double *) malloc (sizeof(double) * nm->dim);
            copy_1d_array(vars, nm->vars, nm->dim);

            nm->n_params = 6;
            nm->params = (double *) malloc (sizeof(double) * nm->n_params);
            copy_1d_array(params, nm->params, nm->n_params);

            nm->max = 30.240470;
            nm->min = -74.235106;

            nm->func = &izhikevich;
            nm->set_pts_burst = &iz_set_pts_burst;

            break;
        case HR:
            nm->dim = 3;
            nm->vars = (double *) malloc (sizeof(double) * nm->dim);
            copy_1d_array(vars, nm->vars, nm->dim);

            nm->n_params = 4;
            nm->params = (double *) malloc (sizeof(double) * nm->n_params);
            copy_1d_array(params, nm->params, nm->n_params);

            nm->max = 1.797032;
            nm->min = -1.608734;

            nm->func = &hindmarsh_rose;
            nm->set_pts_burst = &hr_set_pts_burst;

            break;
        case RLK:
            nm->dim = 2;
            nm->vars = (double *) malloc (sizeof(double) * nm->dim);
            copy_1d_array(vars, nm->vars, nm->dim);

            nm->n_params = 8;
            nm->params = (double *) malloc (sizeof(double) * nm->n_params);
            copy_1d_array(params, nm->params, nm->n_params);

            nm->max = 2.111;
            nm->min = -1.977;

            nm->func = &rulkov_map;
            nm->set_pts_burst = &rlk_set_pts_burst;

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

/* Models functions */

/** @name Empty
 *  Empty neuron model. 
 */
///@{

/**
 * @brief Empty neuron model function. Does not compute anything.
 * @param[in] nm Neuron model structure
 * @param[in] syn Synapse input current value
 */
void empty (neuron_model nm, double syn) {
    return;
}

/**
 * @brief Sets the empty model number of points per burst.
 * @param[in] pts_live Number of points in a living neuron burst
 * @param[in] nm Pointer to the neuron model structure
 */
void empty_set_pts_burst (double pts_live, neuron_model * nm) {
    nm->pts_burst = pts_live;
    return;
}

///@}


/** @name Izhikevich
 *  Izhikevich neuron model from (Izhikevich, 2003). 
 */
///@{

/**
 * @brief Izhikevich neuron model differential equations.
 * @param[in] vars Neuron model variables
 * @param[out] ret Return values array
 * @param[in] params Neuron models parameters
 * @param[in] syn Synapse input current value
 */

void izh_f (double * vars, double * ret, double * params, double syn) {
	ret[0] = 0.04 * vars[0]*vars[0] + 5*vars[0] + 140 - vars[1] + params[IZ_I] - syn;
	ret[1] = params[IZ_A] * (params[IZ_B] * vars[0] - vars[1]);

	return;
}


/**
 * @brief Izhikevich neuron model.
 * @param[in] nm Neuron model structure
 * @param[in] syn Synapse input current value
 */

void izhikevich (neuron_model nm, double syn) {
	runge_kutta_6 (izh_f, nm.dim, nm.params[IZ_DT], nm.vars, nm.params, syn);

	if (nm.vars[0] >= 30) {
		nm.vars[0] = nm.params[IZ_C];
		nm.vars[1] += nm.params[IZ_D];
	}

	return;
}


/**
 * @brief Sets Izhikevich model number of points per burst.
 * @param[in] pts_live Number of points in a living neuron burst
 * @param[in] nm Pointer to the neuron model structure
 */

void iz_set_pts_burst (double pts_live, neuron_model * nm) {
    nm->pts_burst = 59324.0;
    return;
}

///@}


/** @name Hindmarsh-Rose
 *  Hindmarsh-Rose neuron model from (Hindmarsh and Rose, 1984). 
 */
///@{

/**
 * @brief Hindmarsh-Rose neuron model differential equations.
 * @param[in] vars Neuron model variables
 * @param[out] ret Return values array
 * @param[in] params Neuron models parameters
 * @param[in] syn Synapse input current value
 */

void hr_f (double * vars, double * ret, double * params, double syn) {
    ret[0] = vars[1] + 3.0 * (vars[0]*vars[0]) - (vars[0]*vars[0]*vars[0]) - vars[2] + params[HR_I] - syn;
    ret[1] = 1.0 - 5.0 * (vars[0]*vars[0]) - vars[1];
    ret[2] = (-vars[2] + params[HR_S] * (vars[0] + 1.6)) * params[HR_R];

    return;
}


/**
 * @brief Hindmarsh-Rose neuron model.
 * @param[in] nm Neuron model structure
 * @param[in] syn Synapse input current value
 */

void hindmarsh_rose (neuron_model nm, double syn) {
	runge_kutta_6 (hr_f, nm.dim, nm.params[HR_DT], nm.vars, nm.params, syn);

	return;
}


/**
 * @brief Sets Hindmarsh-Rose model number of points per burst.
 * @param[in] pts_live Number of points in a living neuron burst
 * @param[in] nm Pointer to the neuron model structure
 */

void hr_set_pts_burst (double pts_live, neuron_model * nm) {
    nm->pts_burst = 260166.0;
    return;
}

///@}


/** @name Rulkov map
 *  Rulkov neuron model from (Rulkov, 2001). 
 */
///@{

/**
 * @brief Rulkov neuron model equations.
 * @param[in] vars Neuron model variables
 * @param[out] ret Return values array
 * @param[in] params Neuron models parameters
 * @param[in] syn Synapse input current value
 */

void rlk_f (double * vars, double * ret, double * params, double syn) {
    double y_old;

    ret[1] = vars[1] - params[RLK_MU] * (vars[0] + 1) + params[RLK_MU] * params[RLK_SIGMA];
    y_old = vars[1] - syn * params[RLK_I];


    if (vars[0] <= 0) {
        ret[0] = params[RLK_ALPHA] / (1 - vars[0]) + y_old;
    } else if (vars[0] >= params[RLK_ALPHA] + y_old) {
        ret[0] = -1;
    } else {
        ret[0] = params[RLK_ALPHA] + y_old;
    }


    return;
}


/**
 * @brief Rulkov neuron model.
 * @param[in] nm Neuron model structure
 * @param[in] syn Synapse input current value
 */

void rulkov_map (neuron_model nm, double syn) {
    double ret[2];

    if (nm.params[RLK_J] >= ((nm.pts_burst - 400) / 400)) {

        nm.params[RLK_OLD] = nm.vars[0];
        rlk_f(nm.vars, ret, nm.params, syn);
        nm.params[RLK_J] = 0;
        nm.params[RLK_INTER] = ret[0];

    } else {

        ret[0] = nm.params[RLK_OLD] + (nm.params[RLK_INTER] - nm.params[RLK_OLD]) / ((nm.pts_burst - 400) / 400) * nm.params[RLK_J];
        ret[1] = nm.vars[1];
        nm.params[RLK_J]++;

    }

    nm.vars[0] = ret[0];
    nm.vars[1] = ret[1];

    return;
}


/**
 * @brief Sets Rulkov model number of points per burst.
 * @param[in] pts_live Number of points in a living neuron burst
 * @param[in] nm Pointer to the neuron model structure
 */

void rlk_set_pts_burst (double pts_live, neuron_model * nm) {
    nm->pts_burst = pts_live;
    nm->params[RLK_J] = ((nm->pts_burst - 400) / 400) + 1;
    return;
}

///@}