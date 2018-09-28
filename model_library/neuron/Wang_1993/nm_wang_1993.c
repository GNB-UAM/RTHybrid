#include "nm_wang_1993.h"

/**
 * @file nm_wang_1993.c
 * @brief Source file with the Wang model functions.
 */ 


/** @name Wang
 *  Wang neuron model from (Wang, 1993). 
 */
///@{


double nm_wang_1993_inf_f (double x, double y, double z) {
    return 1.0 / (1.0 + exp(-(x + y) / z));
}


/* INA channel */

double nm_wang_1993_mna (double v, double sigma) {
    double aux1 = -0.1 * (v + 30.0 - sigma);
    double alpha = aux1 / (exp(aux1) - 1.0);
    double beta = 4.0 * exp((-v - 55.0 + sigma) / 18.0);

    return alpha / (alpha + beta);
}

double nm_wang_1993_hna_inf (double v, double sigma) {
    double alpha = 0.07 * exp(-(v + 44.0 - sigma) / 20.0);
    double beta = 1.0 / (exp(-0.1 * (v + 14.0 - sigma)) + 1.0);

    return alpha / (alpha + beta);
}

double nm_wang_1993_hna (double v, double sigma, double phi, double old) {
    double alpha = 0.07 * exp(-(v + 44.0 - sigma) / 20.0);
    double beta = 1.0 / (exp(-0.1 * (v + 14.0 - sigma)) + 1.0);

    return phi * (alpha * (1.0 - old) - beta * old);
}

void nm_wang_1993_ina_f (double * vars, double * params, double * ret) {
    *ret = params[WANG_G_NA] * pow(nm_wang_1993_mna(vars[WANG_V], params[WANG_SIGMA]), 3) * vars[WANG_H_NA] * (vars[WANG_V] - params[WANG_V_NA]);
    return;
}


/* IK channel */


double nm_wang_1993_nk_inf (double v, double sigma) {
    double aux1 = v + 34.0 - sigma;
    double alpha = (-0.01 * aux1) / (exp(-0.1 * aux1) - 1.0);
    double beta = 0.125 * exp(-(v + 44.0 - sigma) / 80.0);

    return alpha / (alpha + beta);
}

double nm_wang_1993_nk (double v, double sigma, double phi, double old) {
    double aux1 = v + 34.0 - sigma;
    double alpha = (-0.01 * aux1) / (exp(-0.1 * aux1) - 1.0);
    double beta = 0.125 * exp(-(v + 44.0 - sigma) / 80.0);

    return phi * (alpha * (1.0 - old) - beta * old);
}

void nm_wang_1993_ik_f (double * vars, double * params, double * ret) {
    *ret = params[WANG_G_K] * pow(vars[WANG_N_K], 4) * (vars[WANG_V] - params[WANG_V_K]);
    return;
}

/* INAP channel */

double nm_wang_1993_mnap(double v) {
    return 1.0 / (1.0 + exp(- (v + 51.0) / 5.0));
}

void nm_wang_1993_inap_f (double * vars, double * params, double * ret) {
    *ret = params[WANG_G_NAP] * nm_wang_1993_inf_f(vars[WANG_V], 51.0, 5.0) * (vars[WANG_V] - params[WANG_V_NA]);
    return;
}


/* IKS channel */

double nm_wang_1993_mks_inf (double v, double sigma) {
    return 1.0 / (1.0 + exp(-(v + 34.0) / 6.5));
}

double nm_wang_1993_hks_inf (double v, double sigma) {
    return 1.0 / (1.0 + exp((v + 65.0) / 6.6));
}

double nm_wang_1993_h1ks (double v, double phi, double old) {
    double inf = nm_wang_1993_inf_f(-v, -65.0, 6.6);
    double tau = 200.0 + (220.0 / (1.0 + exp(-(v + 71.6) / 6.85)));

    return phi * (inf - old) / tau; 
}

double nm_wang_1993_h2ks (double v, double phi, double old) {
    double inf = nm_wang_1993_inf_f(-v, -65.0, 6.6);
    double tau = 200.0 + (3200.0 / (1.0 + exp(-(v + 63.6) / 4.0)));

    return phi * (inf - old) / tau; 
}

double nm_wang_1993_mks (double v, double phi, double tau, double old) {
    double inf = nm_wang_1993_inf_f(v, 34.0, 6.5);

    return phi * (inf - old) / tau;
}

void nm_wang_1993_iks_f (double * vars, double * params, double * ret) {
    double aux1 = params[WANG_RHO] * vars[WANG_H1_KS] + (1.0 - params[WANG_RHO]) * vars[WANG_H2_KS];
    *ret = params[WANG_G_KS] * vars[WANG_M_KS] * aux1 * (vars[WANG_V] - params[WANG_V_K]);

    return;
}

/* Leakage current */

void nm_wang_1993_il_f (double * vars, double * params, double * ret) {
    *ret = params[WANG_G_L] * (vars[WANG_V] - params[WANG_V_L]);
    return;
}


/**
 * @brief Wang neuron model differential equations.
 * @param[in] vars Neuron model variables
 * @param[out] ret Return values array
 * @param[in] params Neuron models parameters
 * @param[in] syn Synapse input current value
 */

void nm_wang_1993_f (double * vars, double * ret, double * params, double syn) {
    double inap, ik, ina, iks, il;
    nm_wang_1993_inap_f(vars, params, &inap);
    nm_wang_1993_ina_f(vars, params, &ina);
    nm_wang_1993_ik_f(vars, params, &ik);
    nm_wang_1993_iks_f(vars, params, &iks);
    nm_wang_1993_il_f(vars, params, &il);

    ret[WANG_H_NA] = nm_wang_1993_hna(vars[WANG_V], params[WANG_SIGMA], params[WANG_PHI], vars[WANG_H_NA]);
    ret[WANG_N_K] = nm_wang_1993_nk(vars[WANG_V], params[WANG_SIGMA], params[WANG_PHI], vars[WANG_N_K]);
    ret[WANG_M_KS] = nm_wang_1993_mks(vars[WANG_V], 1.0, params[WANG_TAUM], vars[WANG_M_KS]);
    ret[WANG_H1_KS] = nm_wang_1993_h1ks(vars[WANG_V], 1.0, vars[WANG_H1_KS]);
    ret[WANG_H2_KS] =  nm_wang_1993_h2ks(vars[WANG_V], 1.0, vars[WANG_H2_KS]);

    ret[WANG_V] = (-(il + inap + iks + ina + ik) + params[WANG_I] - (syn * 0.001)) / params[WANG_CM];

    //printf("Iapp %f\n", syn * 0.001);

    return;
}

/**
 * @brief Wang neuron model.
 *
 * This model calculates a six-dimensional differential equation using order 6 Runge-Kutta integration method.
 * @param[in] nm Neuron model structure
 * @param[in] syn Synapse input current value
 */

void nm_wang_1993 (neuron_model nm, double syn) {
    nm.method(nm_wang_1993_f, nm.dim, nm.params[WANG_DT], nm.vars, nm.params, syn);
    return;
}

void nm_wang_1993_select_dt (double pts_live, double * dt, double * pts_burst) {
    double dts[] = {0.000700, 0.000800, 0.000900, 0.001000, 0.001100, 0.001200, 0.001300, 0.001400, 0.001500, 0.001600, 0.001700, 0.001800, 0.001900, 0.002000, 0.002100, 0.002400, 0.002800, 0.002900, 0.003200, 0.003600, 0.003700, 0.004200, 0.004300, 0.004400, 0.004600, 0.004900, 0.005200, 0.005700, 0.005900, 0.006100, 0.006500, 0.006600, 0.006700, 0.007100, 0.007200, 0.007300, 0.007600, 0.008000, 0.008200, 0.008400, 0.008900, 0.009000, 0.009500, 0.009600, 0.010000, 0.010200, 0.010600, 0.010800, 0.011400, 0.011500, 0.011800, 0.012400, 0.013000, 0.013600, 0.014100, 0.014900, 0.015000, 0.015700, 0.016700, 0.017500, 0.018100, 0.019200, 0.020200, 0.021400, 0.022800, 0.024700, 0.026000, 0.028100, 0.030500, 0.033500, 0.037200, 0.037300, 0.037600, 0.037800, 0.040800, 0.041500, 0.042000, 0.042400, 0.042900, 0.043300, 0.043800, 0.044300, 0.044800, 0.045300, 0.045900, 0.046400, 0.047000, 0.047500, 0.048100, 0.048700, 0.049300, 0.050000, 0.050600, 0.051200, 0.051400, 0.052300, 0.052400, 0.052500, 0.053500, 0.053800, 0.054100, 0.055500, 0.056400, 0.057200, 0.058200, 0.058600, 0.060700, 0.061000, 0.062200, 0.063200};
    double pts[] = {579555.000000, 454678.000000, 405505.000000, 344102.000000, 332346.500000, 295645.500000, 275165.000000, 245567.000000, 233459.000000, 223757.333333, 211716.750000, 191145.250000, 187491.400000, 171936.250000, 169710.000000, 158662.800000, 143585.166667, 123770.571429, 111618.000000, 105552.250000, 95810.300000, 93849.555556, 87404.727273, 81612.727273, 78474.272727, 76500.416667, 75557.230769, 67770.071429, 60326.937500, 59342.875000, 57580.588235, 53343.777778, 52737.888889, 51206.052632, 49155.736842, 48553.850000, 47666.300000, 46866.200000, 43694.727273, 42204.818182, 41345.750000, 40114.500000, 39465.375000, 37739.615385, 36014.407407, 35531.185185, 34256.642857, 33437.068966, 32038.066667, 31029.709677, 30701.000000, 29068.529412, 28231.411765, 27496.457143, 26564.081081, 25954.157895, 24306.425000, 23411.666667, 22573.162791, 21342.434783, 20084.714286, 19025.134615, 18083.425926, 17069.578947, 16021.622951, 15279.765625, 14453.382353, 13014.907895, 12015.658537, 11125.707865, 10063.212121, 9924.300000, 9887.860000, 9785.633663, 9677.097087, 9516.711538, 9401.095238, 9314.735849, 9206.333333, 9119.091743, 9017.263636, 8913.450450, 8818.309735, 8718.921053, 8607.078261, 8510.470085, 8403.957627, 8307.450000, 8210.016529, 8109.016260, 8012.112903, 7900.182540, 7804.787402, 7713.434109, 7683.511628, 7552.992424, 7488.886364, 7373.696296, 7248.773723, 7142.064748, 7055.771429, 6913.622378, 6802.260274, 6762.530612, 6508.895425, 6411.716129, 6332.242038, 6225.106250, 6173.863354, 6026.624242};
    unsigned int length = 110;
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
 * @brief Sets Wang model number of points per burst and integration step.
 *
 * If not previously specified by the user, the number of points per burst of the model and its integration step is set according to the living neuron number of points per burst.
 * @param[in] pts_live Number of points in a living neuron burst
 * @param[in] nm Pointer to the neuron model structure
 */

void nm_wang_1993_set_pts_burst (double pts_live, neuron_model * nm) {
    if (nm->pts_burst == -1.0) {
        nm_wang_1993_select_dt(pts_live, &(nm->params[WANG_DT]), &(nm->pts_burst));
    }
    
    return;
}


/**
 * @brief Sets Wang model number of points per burst and integration step.
 *
 * If not previously specified by the user, the number of points per burst of the model and its integration step is set according to the living neuron number of points per burst.
 * @param[in] pts_live Number of points in a living neuron burst
 * @param[in] nm Pointer to the neuron model structure
 */

void nm_wang_1993_init (neuron_model * nm, double * vars, double * params) {
    nm->dim = 6;
    nm->vars = (double *) malloc (sizeof(double) * nm->dim);
    copy_1d_array(vars, nm->vars, nm->dim);

    nm->n_params = 15;
    nm->params = (double *) malloc (sizeof(double) * nm->n_params);
    copy_1d_array(params, nm->params, nm->n_params);

    nm->max = 20;
    nm->min = -80;
    nm->pts_burst = -1.0;

    nm->vars[WANG_H_NA] = nm_wang_1993_hna_inf (nm->vars[WANG_V], nm->params[WANG_SIGMA]); /* Steady-state */
    nm->vars[WANG_N_K] = nm_wang_1993_nk_inf (nm->vars[WANG_V], nm->params[WANG_SIGMA]); /* Steady-state */
    nm->vars[WANG_M_KS] = nm_wang_1993_inf_f(nm->vars[WANG_V], 34.0, 6.5); /* Steady-state */
    nm->vars[WANG_H1_KS] = nm_wang_1993_inf_f(-nm->vars[WANG_V], -65.0, 6.6); /* Steady-state */
    nm->vars[WANG_H2_KS] =  nm_wang_1993_inf_f(-nm->vars[WANG_V], -65.0, 6.6); /* Steady-state */

    nm->func = &nm_wang_1993;
    nm->set_pts_burst = &nm_wang_1993_set_pts_burst;
    nm->method = integration_method_selector(params[WANG_DT]);

    return;
}

///@}