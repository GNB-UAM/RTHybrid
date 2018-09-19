#include "nm_izhikevich_2003.h"

/**
 * @file nm_izhikevich_2003.c
 * @brief Source file with the Izhikevich model functions.
 */

/** @name Izhikevich
 *  Izhikevich neuron model from (Izhikevich, 2003). 
 */
///@{


/**
 * @brief Initializes Izhikevich neuron model.
 *
 * @param[in/out] nm Pointer to the neuron model structure
 * @param[in] vars Neuron model variables entered as input arguments
 * @param[in] params Neuron model parameters entered as input arguments
 */

void iz_init (neuron_model * nm, double * vars, double * params) {
    nm->dim = 2;
    nm->vars = (double *) malloc (sizeof(double) * nm->dim);
    copy_1d_array(vars, nm->vars, nm->dim);

    nm->n_params = 6;
    nm->params = (double *) malloc (sizeof(double) * nm->n_params);
    copy_1d_array(params, nm->params, nm->n_params);

    nm->max = 30.240470;
    nm->min = -74.235106;
    nm->pts_burst = -1.0;

    nm->func = &izhikevich_2003;
    nm->set_pts_burst = &iz_set_pts_burst;
    nm->method = integration_method_selector(params[IZ_DT]);

    return;
}


/**
 * @brief Izhikevich neuron model differential equations.
 * @param[in] vars Neuron model variables
 * @param[out] ret Return values array
 * @param[in] params Neuron models parameters
 * @param[in] syn Synapse input current value
 */

void iz_f (double * vars, double * ret, double * params, double syn) {
    ret[IZ_V] = 0.04 * vars[IZ_V]*vars[IZ_V] + 5*vars[IZ_V] + 140 - vars[IZ_U] + params[IZ_I] - syn;
    ret[IZ_U] = params[IZ_A] * (params[IZ_B] * vars[IZ_V] - vars[IZ_U]);

    return;
}


/**
 * @brief Izhikevich neuron model.
 *
 * This model calculates a two-dimensional differential equation using order 6 Runge-Kutta integration method.
 * Additionaly, a non-linear condition is also introduced.
 * @param[in] nm Neuron model structure
 * @param[in] syn Synapse input current value
 */

void izhikevich_2003 (neuron_model nm, double syn) {
    nm.method(iz_f, nm.dim, nm.params[IZ_DT], nm.vars, nm.params, syn);

    if (nm.vars[IZ_V] >= 30) {
        nm.vars[IZ_V] = nm.params[IZ_C];
        nm.vars[IZ_U] += nm.params[IZ_D];
    }

    return;
}


void iz_select_dt (double pts_live, double * dt, double * pts_burst) {
    double dts[] = {0.000100, 0.000200, 0.000300, 0.000400, 0.000500, 0.000600, 0.000700, 0.000800, 0.000900, 0.001000, 0.001100, 0.001200, 0.001300, 0.001400, 0.001500, 0.001600, 0.001700, 0.001800, 0.001900, 0.002000, 0.002100, 0.002200, 0.002300, 0.002400, 0.002500, 0.002600, 0.002700, 0.002800, 0.002900, 0.003000, 0.003100, 0.003200, 0.003300, 0.003400, 0.003500, 0.003600, 0.003700, 0.003800, 0.003900, 0.004000};
    double pts[] = {593119.285714, 296562.000000, 197709.000000, 148283.000000, 118627.000000, 98857.000000, 84736.000000, 74143.500000, 65906.959459, 59318.000000, 53925.000000, 49430.340000, 45630.481481, 42371.000000, 39544.416000, 37075.000000, 34893.661972, 32954.040000, 31222.949686, 29662.000000, 28247.000000, 26965.500000, 25792.994792, 24716.000000, 23729.397129, 22817.000000, 21971.500000, 21187.663830, 20457.333333, 19774.000000, 19137.000000, 18540.600746, 17976.000000, 17447.017544, 16953.000000, 16480.000000, 16034.000000, 15613.495298, 15213.015291, 14831.997024};
    unsigned int length = 40;
    int i;

    for (i = length - 1; i >= 0; i--) {
        if (pts[i] > pts_live) {
            *dt = dts[i];
            *pts_burst = pts[i];
            return;
        }
    }

    return;
}


/**
 * @brief Sets Izhikevich model number of points per burst and integration step.
 *
 * If not previously specified by the user, the number of points per burst of the model and its integration step is set according to the living neuron number of points per burst.
 * @param[in] pts_live Number of points in a living neuron burst
 * @param[in] nm Pointer to the neuron model structure
 */

void iz_set_pts_burst (double pts_live, neuron_model * nm) {
    if (nm->pts_burst == -1.0) {
        iz_select_dt(pts_live, &(nm->params[IZ_DT]), &(nm->pts_burst));
    }

    
    return;
}

///@}
