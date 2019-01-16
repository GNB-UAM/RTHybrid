#include "nm_hindmarsh_rose_1986.h"
#include <math.h>
#include "../../integration_methods.h"
#include "../neuron_models_aux_functions.h"

/**
 * @file nm_hindmarsh_rose_1986.c
 * @brief Source file with the Hindmarsh and Rose model functions.
 */



/** @name Hindmarsh-Rose
 *  Hindmarsh-Rose neuron model from (Hindmarsh and Rose, 1984). 
 */
///@{


/**
 * @brief Initializes Hindmarsh-Rose neuron model.
 *
 * @param[in/out] nm Pointer to the neuron model structure
 * @param[in] vars Neuron model variables entered as input arguments
 * @param[in] params Neuron model parameters entered as input arguments
 */

void nm_hindmarsh_rose_1986_init (neuron_model * nm, double * vars, double * params) {
    nm->dim = 3;
    nm->vars = (double *) malloc (sizeof(double) * nm->dim);
    copy_1d_array(vars, nm->vars, nm->dim);

    nm->n_params = 4;
    nm->params = (double *) malloc (sizeof(double) * nm->n_params);
    copy_1d_array(params, nm->params, nm->n_params);

    nm->max = 1.797032;
    nm->min = -1.608734;
    nm->pts_burst = -1.0;

    nm->func = &nm_hindmarsh_rose_1986;
    nm->set_pts_burst = &nm_hindmarsh_rose_1986_set_pts_burst;
    nm->method = integration_method_selector(params[HR_DT]);

    return;
}


/**
 * @brief Hindmarsh-Rose neuron model differential equations.
 * @param[in] vars Neuron model variables
 * @param[out] ret Return values array
 * @param[in] params Neuron models parameters
 * @param[in] syn Synapse input current value
 */

void nm_hindmarsh_rose_1986_f (double * vars, double * ret, double * params, double syn) {
    ret[HR_X] = vars[HR_Y] + 3.0 * (vars[HR_X]*vars[HR_X]) - (vars[HR_X]*vars[HR_X]*vars[HR_X]) - vars[HR_Z] + params[HR_I] - syn;
    ret[HR_Y] = 1.0 - 5.0 * (vars[HR_X]*vars[HR_X]) - vars[HR_Y];
    ret[HR_Z] = (-vars[HR_Z] + params[HR_S] * (vars[HR_X] + 1.6)) * params[HR_R];

    return;
}


/**
 * @brief Hindmarsh-Rose neuron model.
 *
 * This model calculates a three-dimensional differential equation using order 6 Runge-Kutta integration method.
 * @param[in] nm Neuron model structure
 * @param[in] syn Synapse input current value
 */

void nm_hindmarsh_rose_1986 (neuron_model nm, double syn) {
    nm.method(nm_hindmarsh_rose_1986_f, nm.dim, nm.params[HR_DT], nm.vars, nm.params, syn);

    return;
}


/**
 * @brief Sets Hindmarsh-Rose model number of points per burst and integration step.
 *
 * If not previously specified by the user, the number of points per burst of the model and its integration step is set according to the living neuron number of points per burst.
 * @param[in] pts_live Number of points in a living neuron burst
 * @param[in] nm Pointer to the neuron model structure
 */

void nm_hindmarsh_rose_1986_set_pts_burst (double pts_live, neuron_model * nm) {
    double dts[] = {0.000300, 0.000400, 0.000500, 0.000600, 0.000700, 0.000800, 0.000900, 0.001000, 0.001100, 0.001200, 0.001300, 0.001400, 0.001500, 0.001600, 0.001700, 0.001800, 0.001900, 0.002000, 0.002100, 0.002200, 0.002300, 0.002400, 0.002500, 0.002600, 0.002700, 0.002800, 0.002900, 0.003000, 0.003100, 0.003200, 0.003300, 0.003400, 0.003500, 0.003600, 0.003700, 0.003800, 0.003900, 0.004000, 0.004100, 0.004200, 0.004300, 0.004400, 0.004500, 0.004600, 0.004700, 0.004800, 0.004900, 0.005000, 0.005100, 0.005200, 0.005300, 0.005400, 0.005500, 0.005600, 0.005700, 0.005800, 0.006000, 0.006100, 0.006200, 0.006400, 0.006500, 0.006700, 0.006900, 0.007000, 0.007200, 0.007400, 0.007600, 0.007800, 0.008000, 0.008300, 0.008500, 0.008800, 0.009100, 0.009400, 0.009700, 0.010100, 0.010400, 0.010800, 0.011300, 0.011700, 0.012300, 0.012800, 0.013400, 0.014100, 0.014800, 0.015700, 0.016600, 0.017600, 0.018800, 0.020200, 0.021700, 0.023500, 0.025700, 0.028300, 0.028500, 0.028800, 0.029100, 0.029400, 0.029700, 0.030100, 0.030400, 0.030700, 0.031100, 0.031400, 0.031800, 0.032100, 0.032500, 0.032900, 0.033300, 0.033600, 0.034100, 0.034500, 0.034900, 0.035300, 0.035800, 0.036200, 0.036700, 0.037200, 0.037700, 0.038200, 0.038700, 0.039300, 0.039800, 0.040400, 0.041000, 0.041600, 0.042200, 0.042800, 0.043500, 0.044200, 0.044900, 0.045600, 0.046400, 0.047100, 0.047900, 0.048800, 0.049600, 0.050500, 0.051400, 0.052400, 0.053400, 0.054400, 0.055500, 0.056600, 0.057700, 0.059000, 0.060200, 0.061500, 0.062900, 0.064300, 0.065900, 0.067400, 0.069100, 0.070800, 0.072600, 0.074500, 0.076600, 0.078700, 0.081000, 0.083400, 0.085900, 0.088600, 0.091500, 0.094600, 0.097900, 0.101400, 0.105300, 0.109400, 0.113800, 0.118700, 0.124000, 0.129800, 0.136200, 0.143300, 0.149900};
    double pts[] = {962728.000000, 715229.500000, 572183.500000, 475095.666667, 406471.750000, 355268.000000, 315793.800000, 284003.500000, 258048.285714, 236544.285714, 218261.750000, 202608.888889, 189054.900000, 177238.900000, 166779.363636, 157487.250000, 149198.416667, 141718.230769, 134953.214286, 128805.266667, 123205.066667, 118060.562500, 113328.882353, 108970.058824, 104926.500000, 101172.526316, 97683.842105, 94422.150000, 91371.428571, 88511.818182, 85829.681818, 83301.608696, 80918.291667, 78670.583333, 76541.520000, 74524.692308, 72611.518519, 70796.222222, 69067.464286, 67421.172414, 65853.241379, 64354.933333, 62923.322581, 61555.451613, 60244.406250, 58988.090909, 57783.117647, 56627.470588, 55516.085714, 54447.527778, 53420.194444, 52430.081081, 51476.000000, 50556.051282, 49669.102564, 48812.050000, 47184.365854, 46410.261905, 45661.162791, 44233.750000, 43552.755556, 42252.239130, 41026.729167, 40440.645833, 39316.580000, 38253.647059, 37246.396226, 36291.111111, 35383.581818, 34103.965517, 33301.338983, 32165.704918, 31104.984127, 30111.969231, 29180.279412, 28024.400000, 27215.791667, 26207.533333, 25047.582278, 24191.060976, 23010.790698, 22111.820225, 21121.531915, 20072.787879, 19123.288462, 18026.954545, 17049.525862, 16080.772358, 15054.318182, 14010.971831, 13042.546053, 12043.660606, 11012.872928, 10001.361809, 9931.205000, 9827.787129, 9726.502439, 9627.289855, 9530.081340, 9403.485849, 9310.728972, 9219.782407, 9101.251142, 9014.339367, 8901.000000, 8817.853982, 8709.379913, 8603.554113, 8500.260684, 8424.406780, 8300.954167, 8204.765432, 8110.788618, 8018.943548, 7907.019841, 7819.709804, 7713.251938, 7609.652672, 7508.807547, 7410.602230, 7314.937500, 7203.357401, 7112.946429, 7007.404930, 6904.955017, 6805.464164, 6708.808081, 6614.863787, 6508.539216, 6405.585209, 6305.841772, 6209.168224, 6102.256881, 6011.695783, 5911.439169, 5802.584302, 5709.146132, 5607.573034, 5509.560773, 5404.615176, 5303.606383, 5206.315927, 5103.352941, 5004.401003, 4909.229064, 4801.341346, 4705.898585, 4606.713626, 4504.496614, 4406.741722, 4300.127155, 4204.787368, 4101.755647, 4003.693387, 3904.888454, 3805.797710, 3702.024119, 3603.817690, 3502.136842, 3402.052811, 3303.789735, 3203.942215, 3103.318818, 3002.646617, 2902.562500, 2803.617978, 2701.223275, 2601.574219, 2502.765664, 2401.532452, 2301.259217, 2201.178414, 2100.969506, 2000.695696, 1916.425695};
    unsigned int length = 175;

    select_dt_neuron_model(dts, pts, length, pts_live, &(nm->params[HR_DT]), &(nm->pts_burst));
    
    return;
}

///@} 
