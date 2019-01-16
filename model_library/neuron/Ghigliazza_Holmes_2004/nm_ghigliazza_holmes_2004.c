#include "nm_ghigliazza_holmes_2004.h"
#include <math.h>
#include "../../integration_methods.h"
#include "../neuron_models_aux_functions.h"

/**
 * @file nm_ghigliazza_holmes_2004.c
 * @brief Source file with the Ghigliazza and Holmes model functions.
 */ 

/** @name Ghigliazza and Holmes
 *  Ghigliazza and Holmes neuron model from (Ghigliazza and Holmes, 2004). 
 */
///@{


/**
 * @brief Initializes Ghigliazza-Holmes neuron model.
 *
 * @param[in/out] nm Pointer to the neuron model structure
 * @param[in] vars Neuron model variables entered as input arguments
 * @param[in] params Neuron model parameters entered as input arguments
 */

void nm_ghigliazza_holmes_2004_init (neuron_model * nm, double * vars, double * params) {
    nm->dim = 3;
    nm->vars = (double *) malloc (sizeof(double) * nm->dim);

    copy_1d_array(vars, nm->vars, nm->dim);

    nm->n_params = 18;
    nm->params = (double *) malloc (sizeof(double) * nm->n_params);
    copy_1d_array(params, nm->params, nm->n_params);

    nm->max = 5;
    nm->min = -40;
    nm->pts_burst = -1.0;

    nm->vars[GH_M] = nm_ghigliazza_holmes_2004_inf (nm->vars[0], nm->params[GH_VTH_K], nm->params[GH_K_K]);
    nm->vars[GH_C] = nm_ghigliazza_holmes_2004_inf (nm->vars[0], nm->params[GH_VTH_KS], nm->params[GH_K_KS]);

    nm->func = &nm_ghigliazza_holmes_2004;
    nm->set_pts_burst = &nm_ghigliazza_holmes_2004_set_pts_burst;
    nm->method = integration_method_selector(params[GH_DT]);

    return;
}


double nm_ghigliazza_holmes_2004_inf (double v, double vth, double k) {
    return 1.0 / (1.0 + exp(-k * (v - vth)));
}

void nm_ghigliazza_holmes_2004_ica_f (double * vars, double * params, double * ret) {
    *ret = params[GH_G_CA] * nm_ghigliazza_holmes_2004_inf(vars[GH_V], params[GH_VTH_CA], params[GH_K_CA]) * (vars[GH_V] - params[GH_E_CA]);
    return;
}

void nm_ghigliazza_holmes_2004_il_f (double * vars, double * params, double * ret) {
    *ret = params[GH_G_L] * (vars[GH_V] - params[GH_E_L]);
    return;
}

void nm_ghigliazza_holmes_2004_ik_f (double * vars, double * params, double * ret) {
    *ret = params[GH_G_K] * vars[GH_M] * (vars[GH_V] - params[GH_E_K]);
    return;
}

void nm_ghigliazza_holmes_2004_iks_f (double * vars, double * params, double * ret) {
    *ret = params[GH_G_KS] * vars[GH_C] * (vars[GH_V] - params[GH_E_K]);
    return;
}

/**
 * @brief Ghigliazza and Holmes neuron model differential equations.
 * @param[in] vars Neuron model variables
 * @param[out] ret Return values array
 * @param[in] params Neuron models parameters
 * @param[in] syn Synapse input current value
 */

void nm_ghigliazza_holmes_2004_f (double * vars, double * ret, double * params, double syn) {
    double ica, ik, il, iks;
    nm_ghigliazza_holmes_2004_ica_f(vars, params, &ica);
    nm_ghigliazza_holmes_2004_ik_f(vars, params, &ik);
    nm_ghigliazza_holmes_2004_il_f(vars, params, &il);
    nm_ghigliazza_holmes_2004_iks_f(vars, params, &iks);

    ret[GH_V] = (-(ica + ik + il + iks) + params[GH_I] - syn) / params[GH_CM];
    ret[GH_M] = (params[GH_EPSILON] / 0.8) * (nm_ghigliazza_holmes_2004_inf(vars[GH_V], params[GH_VTH_K], params[GH_K_K]) - vars[GH_M]);
    ret[GH_C] = (params[GH_DELTA] / 0.8) * (nm_ghigliazza_holmes_2004_inf(vars[GH_V], params[GH_VTH_KS], params[GH_K_KS]) - vars[GH_C]);

    return;
}

/**
 * @brief Ghigliazza and Holmes neuron model.
 *
 * This model calculates a three-dimensional differential equation using order 6 Runge-Kutta integration method.
 * @param[in] nm Neuron model structure
 * @param[in] syn Synapse input current value
 */

void nm_ghigliazza_holmes_2004 (neuron_model nm, double syn) {
    nm.method(nm_ghigliazza_holmes_2004_f, nm.dim, nm.params[GH_DT], nm.vars, nm.params, syn);

    return;
}


/**
 * @brief Sets Ghigliazza and Holmes model number of points per burst and integration step.
 *
 * If not previously specified by the user, the number of points per burst of the model and its integration step is set according to the living neuron number of points per burst.
 * @param[in] pts_live Number of points in a living neuron burst
 * @param[in] nm Pointer to the neuron model structure
 */

void nm_ghigliazza_holmes_2004_set_pts_burst (double pts_live, neuron_model * nm) {
    double dts[] = {0.000090, 0.000200, 0.000300, 0.000400, 0.000500, 0.000600, 0.000700, 0.000800, 0.000900, 0.001000, 0.001100, 0.001200, 0.001300, 0.001400, 0.001500, 0.001600, 0.001700, 0.001800, 0.001900, 0.002000, 0.002100, 0.002200, 0.002300, 0.002400, 0.002500, 0.002600, 0.002700, 0.002800, 0.002900, 0.003100, 0.003300, 0.003400, 0.003700, 0.003900, 0.004100, 0.004400, 0.004800, 0.005200, 0.005700, 0.006200, 0.006300, 0.006400, 0.006500, 0.006600, 0.006700, 0.006800, 0.006900, 0.007000, 0.007100, 0.007200, 0.007300, 0.007400, 0.007500, 0.007600, 0.007700, 0.007800, 0.007900, 0.008000, 0.008100, 0.008200, 0.008300, 0.008500, 0.008600, 0.008700, 0.008800, 0.008900, 0.009100, 0.009200, 0.009400, 0.009500, 0.009600, 0.009800, 0.009900, 0.010100, 0.010300, 0.010500, 0.010600, 0.010800, 0.011000, 0.011200, 0.011400, 0.011600, 0.011800, 0.012100, 0.012300, 0.012600, 0.012800, 0.013100, 0.013400, 0.013700, 0.014000, 0.014300, 0.014600, 0.015000, 0.015400, 0.015700, 0.016200, 0.016600, 0.017000, 0.017500, 0.018000, 0.018600, 0.019200, 0.019800, 0.020500, 0.021200, 0.022000, 0.022800, 0.023800, 0.025300, 0.025400, 0.025800, 0.026500, 0.027500, 0.028600, 0.029900, 0.031300, 0.032900, 0.034700, 0.036700, 0.039100, 0.041800, 0.045000, 0.048800, 0.053700, 0.058900, 0.059000, 0.059100, 0.059300, 0.059500, 0.059800, 0.060100, 0.060500, 0.060900, 0.061300, 0.061800, 0.062300, 0.062900, 0.063500, 0.064100, 0.064700, 0.065400, 0.066200, 0.066900, 0.067800, 0.068600, 0.069500, 0.070500, 0.071600, 0.072800, 0.074100, 0.078200, 0.078300, 0.078400, 0.078500, 0.078700, 0.079000, 0.079400, 0.079900, 0.080500, 0.081200, 0.082000, 0.083100, 0.084400, 0.085400, 0.086900, 0.088500, 0.090200, 0.095900, 0.096400, 0.096600, 0.097100, 0.097400, 0.097800, 0.097900, 0.098300, 0.098400, 0.099600, 0.100000};
    double pts[] = {699369.000000, 314716.000000, 209810.666667, 157358.000000, 125886.333333, 104905.375000, 89918.900000, 78678.916667, 69936.923077, 62943.200000, 57221.062500, 52452.647059, 48417.842105, 44959.428571, 41962.181818, 39339.541667, 37025.461538, 34968.518519, 33128.071429, 31471.700000, 29973.062500, 28610.666667, 27366.742857, 26226.513514, 25177.473684, 24209.125000, 23312.536585, 22479.977273, 21704.844444, 20304.604167, 19074.098039, 18513.132075, 17012.210526, 16139.885246, 15352.682540, 14306.088235, 13114.160000, 12105.658537, 11044.144444, 10153.917526, 9992.838384, 9836.790000, 9685.549020, 9538.903846, 9396.628571, 9258.547170, 9124.462963, 8994.227273, 8867.657658, 8744.601770, 8624.921053, 8508.482759, 8395.161017, 8284.816667, 8177.338843, 8072.617886, 7970.556452, 7871.048000, 7774.000000, 7679.325581, 7586.931298, 7408.684211, 7322.674074, 7238.642336, 7156.532374, 7076.264286, 6921.020979, 6845.944444, 6700.585034, 6630.208054, 6561.298013, 6427.714286, 6362.948387, 6237.283019, 6116.500000, 6000.343373, 5943.916168, 5834.205882, 5728.494253, 5626.579545, 5528.255556, 5433.338798, 5341.650538, 5209.836842, 5125.561856, 5004.186869, 4926.450495, 4814.334951, 4707.279621, 4604.953704, 4507.058824, 4413.314159, 4323.469565, 4209.341772, 4101.226337, 4023.817814, 3901.298039, 3808.708812, 3720.588015, 3616.269091, 3517.943463, 3407.229452, 3303.790698, 3207.048387, 3101.971963, 3004.686747, 2902.483965, 2809.636620, 2707.913043, 2677.077957, 2513.696970, 2407.893720, 2310.482599, 2203.452539, 2103.575949, 2000.086172, 1901.386667, 1801.178700, 1701.360068, 1603.536116, 1500.996992, 1401.432584, 1300.979140, 1201.802647, 1101.315673, 1016.018311, 997.329670, 987.000000, 973.000000, 963.000000, 951.173333, 941.427898, 930.189944, 920.261751, 911.211679, 900.810640, 891.132025, 880.305727, 870.144599, 860.541774, 851.415673, 841.295703, 830.347465, 821.253903, 810.175994, 800.870890, 791.000000, 780.702893, 770.243827, 760.000000, 750.166667, 744.650522, 735.289183, 707.761871, 694.811544, 683.270178, 671.600806, 660.991396, 651.112125, 642.758199, 630.231400, 620.509938, 611.988971, 600.000000, 590.823286, 580.347851, 570.189960, 560.583847, 550.453994, 540.418605, 531.053135, 523.058639, 511.223132, 501.296891, 499.694000, 492.422868, 490.999017, 482.209459, 470.684880};
    unsigned int length = 179;

    select_dt_neuron_model(dts, pts, length, pts_live, &(nm->params[GH_DT]), &(nm->pts_burst));
    
    return;
}

///@}