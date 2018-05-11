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
            nm->pts_burst = -1.0;

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
            nm->pts_burst = -1.0;

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
            nm->pts_burst = -1.0;

            nm->func = &rulkov_map;
            nm->set_pts_burst = &rlk_set_pts_burst;

            break;
        case GH:
            nm->dim = 3;
            nm->vars = (double *) malloc (sizeof(double) * nm->dim);
            copy_1d_array(vars, nm->vars, nm->dim);

            nm->n_params = 20;
            nm->params = (double *) malloc (sizeof(double) * nm->n_params);
            copy_1d_array(params, nm->params, nm->n_params);

            nm->max = 5;
            nm->min = -40;
            nm->pts_burst = -1.0;

            nm->vars[GH_M] = ghigliazza_holmes_inf (nm->vars[0], nm->params[GH_VTH_K], nm->params[GH_K_K]);
            nm->vars[GH_C] = ghigliazza_holmes_inf (nm->vars[0], nm->params[GH_VTH_KS], nm->params[GH_K_KS]);

            nm->func = &ghigliazza_holmes;
            nm->set_pts_burst = &ghigliazza_holmes_set_pts_burst;

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
 *
 * The number of points per burst of the model is equalized to the number of points per burst of the living neuron.
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
 *
 * This model calculates a two-dimensional differential equation using order 6 Runge-Kutta integration method.
 * Additionaly, a non-linear condition is also introduced.
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
 *
 * This model calculates a three-dimensional differential equation using order 6 Runge-Kutta integration method.
 * @param[in] nm Neuron model structure
 * @param[in] syn Synapse input current value
 */

void hindmarsh_rose (neuron_model nm, double syn) {
    runge_kutta_6 (hr_f, nm.dim, nm.params[HR_DT], nm.vars, nm.params, syn);

    return;
}

void hr_select_dt (double pts_live, double * dt, double * pts_burst) {
    double dts[] = {0.000300, 0.000400, 0.000500, 0.000600, 0.000700, 0.000800, 0.000900, 0.001000, 0.001100, 0.001200, 0.001300, 0.001400, 0.001500, 0.001600, 0.001700, 0.001800, 0.001900, 0.002000, 0.002100, 0.002200, 0.002300, 0.002400, 0.002500, 0.002600, 0.002700, 0.002800, 0.002900, 0.003000, 0.003100, 0.003200, 0.003300, 0.003400, 0.003500, 0.003600, 0.003700, 0.003800, 0.003900, 0.004000, 0.004100, 0.004200, 0.004300, 0.004400, 0.004500, 0.004600, 0.004700, 0.004800, 0.004900, 0.005000, 0.005100, 0.005200, 0.005300, 0.005400, 0.005500, 0.005600, 0.005700, 0.005800, 0.006000, 0.006100, 0.006200, 0.006400, 0.006500, 0.006700, 0.006900, 0.007000, 0.007200, 0.007400, 0.007600, 0.007800, 0.008000, 0.008300, 0.008500, 0.008800, 0.009100, 0.009400, 0.009700, 0.010100, 0.010400, 0.010800, 0.011300, 0.011700, 0.012300, 0.012800, 0.013400, 0.014100, 0.014800, 0.015700, 0.016600, 0.017600, 0.018800, 0.020200, 0.021700, 0.023500, 0.025700, 0.028300, 0.028500, 0.028800, 0.029100, 0.029400, 0.029700, 0.030100, 0.030400, 0.030700, 0.031100, 0.031400, 0.031800, 0.032100, 0.032500, 0.032900, 0.033300, 0.033600, 0.034100, 0.034500, 0.034900, 0.035300, 0.035800, 0.036200, 0.036700, 0.037200, 0.037700, 0.038200, 0.038700, 0.039300, 0.039800, 0.040400, 0.041000, 0.041600, 0.042200, 0.042800, 0.043500, 0.044200, 0.044900, 0.045600, 0.046400, 0.047100, 0.047900, 0.048800, 0.049600, 0.050500, 0.051400, 0.052400, 0.053400, 0.054400, 0.055500, 0.056600, 0.057700, 0.059000, 0.060200, 0.061500, 0.062900, 0.064300, 0.065900, 0.067400, 0.069100, 0.070800, 0.072600, 0.074500, 0.076600, 0.078700, 0.081000, 0.083400, 0.085900, 0.088600, 0.091500, 0.094600, 0.097900, 0.101400, 0.105300, 0.109400, 0.113800, 0.118700, 0.124000, 0.129800, 0.136200, 0.143300, 0.149900};
    double pts[] = {962728.000000, 715229.500000, 572183.500000, 475095.666667, 406471.750000, 355268.000000, 315793.800000, 284003.500000, 258048.285714, 236544.285714, 218261.750000, 202608.888889, 189054.900000, 177238.900000, 166779.363636, 157487.250000, 149198.416667, 141718.230769, 134953.214286, 128805.266667, 123205.066667, 118060.562500, 113328.882353, 108970.058824, 104926.500000, 101172.526316, 97683.842105, 94422.150000, 91371.428571, 88511.818182, 85829.681818, 83301.608696, 80918.291667, 78670.583333, 76541.520000, 74524.692308, 72611.518519, 70796.222222, 69067.464286, 67421.172414, 65853.241379, 64354.933333, 62923.322581, 61555.451613, 60244.406250, 58988.090909, 57783.117647, 56627.470588, 55516.085714, 54447.527778, 53420.194444, 52430.081081, 51476.000000, 50556.051282, 49669.102564, 48812.050000, 47184.365854, 46410.261905, 45661.162791, 44233.750000, 43552.755556, 42252.239130, 41026.729167, 40440.645833, 39316.580000, 38253.647059, 37246.396226, 36291.111111, 35383.581818, 34103.965517, 33301.338983, 32165.704918, 31104.984127, 30111.969231, 29180.279412, 28024.400000, 27215.791667, 26207.533333, 25047.582278, 24191.060976, 23010.790698, 22111.820225, 21121.531915, 20072.787879, 19123.288462, 18026.954545, 17049.525862, 16080.772358, 15054.318182, 14010.971831, 13042.546053, 12043.660606, 11012.872928, 10001.361809, 9931.205000, 9827.787129, 9726.502439, 9627.289855, 9530.081340, 9403.485849, 9310.728972, 9219.782407, 9101.251142, 9014.339367, 8901.000000, 8817.853982, 8709.379913, 8603.554113, 8500.260684, 8424.406780, 8300.954167, 8204.765432, 8110.788618, 8018.943548, 7907.019841, 7819.709804, 7713.251938, 7609.652672, 7508.807547, 7410.602230, 7314.937500, 7203.357401, 7112.946429, 7007.404930, 6904.955017, 6805.464164, 6708.808081, 6614.863787, 6508.539216, 6405.585209, 6305.841772, 6209.168224, 6102.256881, 6011.695783, 5911.439169, 5802.584302, 5709.146132, 5607.573034, 5509.560773, 5404.615176, 5303.606383, 5206.315927, 5103.352941, 5004.401003, 4909.229064, 4801.341346, 4705.898585, 4606.713626, 4504.496614, 4406.741722, 4300.127155, 4204.787368, 4101.755647, 4003.693387, 3904.888454, 3805.797710, 3702.024119, 3603.817690, 3502.136842, 3402.052811, 3303.789735, 3203.942215, 3103.318818, 3002.646617, 2902.562500, 2803.617978, 2701.223275, 2601.574219, 2502.765664, 2401.532452, 2301.259217, 2201.178414, 2100.969506, 2000.695696, 1916.425695};
    unsigned int length = 175;
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
 * @brief Sets Hindmarsh-Rose model number of points per burst and integration step.
 *
 * If not previously specified by the user, the number of points per burst of the model and its integration step is set according to the living neuron number of points per burst.
 * @param[in] pts_live Number of points in a living neuron burst
 * @param[in] nm Pointer to the neuron model structure
 */

void hr_set_pts_burst (double pts_live, neuron_model * nm) {
    if (nm->pts_burst == -1.0) {
        hr_select_dt(pts_live, &(nm->params[HR_DT]), &(nm->pts_burst));
    }
    
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
    double u;

    ret[1] = vars[1] - params[RLK_MU] * (vars[0] + 1) + params[RLK_MU] * params[RLK_SIGMA];
    u = vars[1] - syn * params[RLK_I];


    if (vars[0] <= 0) {
        ret[0] = params[RLK_ALPHA] / (1 - vars[0]) + u;
    } else if (vars[0] >= params[RLK_ALPHA] + u) {
        ret[0] = -1;
    } else {
        ret[0] = params[RLK_ALPHA] + u;
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

void rulkov_map (neuron_model nm, double syn) {
    double ret[2];
    double t0, t1, t, x0, x1;
    double inter_pts = (nm.pts_burst - 334) / 334;

    if (nm.params[RLK_J] >= inter_pts) {
        nm.vars[X] = nm.params[RLK_OLD];
        rlk_f(nm.vars, ret, nm.params, syn);
        nm.vars[X] = ret[0];
        nm.vars[Y] = ret[1];
        nm.params[RLK_OLD] = nm.vars[0];
        nm.params[RLK_J] = 1;

        /* Next point for interpolation */
        rlk_f(nm.vars, ret, nm.params, syn);
        nm.params[RLK_INTER] = ret[0];     
    } else {
        /* Interpolation */
        t0 = 0.0;
        t1 = inter_pts;
        t = nm.params[RLK_J];
        x0 = nm.params[RLK_OLD];
        x1 = nm.params[RLK_INTER];
        ret[0] = x0 + ((t - t0) * ((x1 - x0) / (t1 - t0)));
        ret[1] = nm.vars[1];

        nm.params[RLK_J]++;

        nm.vars[0] = ret[0];
        nm.vars[1] = ret[1];
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

void rlk_set_pts_burst (double pts_live, neuron_model * nm) {
    nm->pts_burst = pts_live;
    nm->params[RLK_J] = ((nm->pts_burst - 334) / 334) + 1;
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


double ghigliazza_holmes_inf (double v, double vth, double k) {
    return 1.0 / (1.0 + exp(-k * (v - vth)));
}

void ghigliazza_holmes_ica_f (double * vars, double * params, double * ret) {
    *ret = params[GH_G_CA] * ghigliazza_holmes_inf(vars[X], params[GH_VTH_CA], params[GH_K_CA]) * (vars[X] - params[GH_E_CA]);
    return;
}

void ghigliazza_holmes_il_f (double * vars, double * params, double * ret) {
    *ret = params[GH_G_L] * (vars[X] - params[GH_E_L]);
    return;
}

void ghigliazza_holmes_ik_f (double * vars, double * params, double * ret) {
    *ret = params[GH_G_K] * vars[GH_M] * (vars[X] - params[GH_E_K]);
    return;
}

void ghigliazza_holmes_iks_f (double * vars, double * params, double * ret) {
    *ret = params[GH_G_KS] * vars[GH_C] * (vars[X] - params[GH_E_K]);
    return;
}


void ghigliazza_holmes_f (double * vars, double * ret, double * params, double syn) {
    double ica, ik, il, iks;
    ghigliazza_holmes_ica_f(vars, params, &ica);
    ghigliazza_holmes_ik_f(vars, params, &ik);
    ghigliazza_holmes_il_f(vars, params, &il);
    ghigliazza_holmes_iks_f(vars, params, &iks);

    ret[0] = (-(ica + ik + il + iks) + params[GH_I] - syn) / params[GH_CM];
    ret[1] = (params[GH_EPSILON] / 0.8) * (ghigliazza_holmes_inf(vars[X], params[GH_VTH_K], params[GH_K_K]) - vars[GH_M]);
    ret[2] = (params[GH_DELTA] / 0.8) * (ghigliazza_holmes_inf(vars[X], params[GH_VTH_KS], params[GH_K_KS]) - vars[GH_C]);

    //printf("%f = (- (%f + %f + %f + %f) + %f - %f) / %f\n\n", ret[0], ica, ik, il, iks, params[GH_I], syn, params[GH_CM]);

    return;
}

/**
 * @brief Hindmarsh-Rose neuron model.
 *
 * This model calculates a three-dimensional differential equation using order 6 Runge-Kutta integration method.
 * @param[in] nm Neuron model structure
 * @param[in] syn Synapse input current value
 */

void ghigliazza_holmes (neuron_model nm, double syn) {
    runge_kutta_6 (ghigliazza_holmes_f, nm.dim, nm.params[GH_DT], nm.vars, nm.params, syn);

    return;
}

void ghigliazza_holmes_select_dt (double pts_live, double * dt, double * pts_burst) {
    double dts[] = {0.000300, 0.000400, 0.000500, 0.000600, 0.000700, 0.000800, 0.000900, 0.001000, 0.001100, 0.001200, 0.001300, 0.001400, 0.001500, 0.001600, 0.001700, 0.001800, 0.001900, 0.002000, 0.002100, 0.002200, 0.002300, 0.002400, 0.002500, 0.002600, 0.002700, 0.002800, 0.002900, 0.003000, 0.003100, 0.003200, 0.003300, 0.003400, 0.003500, 0.003600, 0.003700, 0.003800, 0.003900, 0.004000, 0.004100, 0.004200, 0.004300, 0.004400, 0.004500, 0.004600, 0.004700, 0.004800, 0.004900, 0.005000, 0.005100, 0.005200, 0.005300, 0.005400, 0.005500, 0.005600, 0.005700, 0.005800, 0.006000, 0.006100, 0.006200, 0.006400, 0.006500, 0.006700, 0.006900, 0.007000, 0.007200, 0.007400, 0.007600, 0.007800, 0.008000, 0.008300, 0.008500, 0.008800, 0.009100, 0.009400, 0.009700, 0.010100, 0.010400, 0.010800, 0.011300, 0.011700, 0.012300, 0.012800, 0.013400, 0.014100, 0.014800, 0.015700, 0.016600, 0.017600, 0.018800, 0.020200, 0.021700, 0.023500, 0.025700, 0.028300, 0.028500, 0.028800, 0.029100, 0.029400, 0.029700, 0.030100, 0.030400, 0.030700, 0.031100, 0.031400, 0.031800, 0.032100, 0.032500, 0.032900, 0.033300, 0.033600, 0.034100, 0.034500, 0.034900, 0.035300, 0.035800, 0.036200, 0.036700, 0.037200, 0.037700, 0.038200, 0.038700, 0.039300, 0.039800, 0.040400, 0.041000, 0.041600, 0.042200, 0.042800, 0.043500, 0.044200, 0.044900, 0.045600, 0.046400, 0.047100, 0.047900, 0.048800, 0.049600, 0.050500, 0.051400, 0.052400, 0.053400, 0.054400, 0.055500, 0.056600, 0.057700, 0.059000, 0.060200, 0.061500, 0.062900, 0.064300, 0.065900, 0.067400, 0.069100, 0.070800, 0.072600, 0.074500, 0.076600, 0.078700, 0.081000, 0.083400, 0.085900, 0.088600, 0.091500, 0.094600, 0.097900, 0.101400, 0.105300, 0.109400, 0.113800, 0.118700, 0.124000, 0.129800, 0.136200, 0.143300, 0.149900};
    double pts[] = {962728.000000, 715229.500000, 572183.500000, 475095.666667, 406471.750000, 355268.000000, 315793.800000, 284003.500000, 258048.285714, 236544.285714, 218261.750000, 202608.888889, 189054.900000, 177238.900000, 166779.363636, 157487.250000, 149198.416667, 141718.230769, 134953.214286, 128805.266667, 123205.066667, 118060.562500, 113328.882353, 108970.058824, 104926.500000, 101172.526316, 97683.842105, 94422.150000, 91371.428571, 88511.818182, 85829.681818, 83301.608696, 80918.291667, 78670.583333, 76541.520000, 74524.692308, 72611.518519, 70796.222222, 69067.464286, 67421.172414, 65853.241379, 64354.933333, 62923.322581, 61555.451613, 60244.406250, 58988.090909, 57783.117647, 56627.470588, 55516.085714, 54447.527778, 53420.194444, 52430.081081, 51476.000000, 50556.051282, 49669.102564, 48812.050000, 47184.365854, 46410.261905, 45661.162791, 44233.750000, 43552.755556, 42252.239130, 41026.729167, 40440.645833, 39316.580000, 38253.647059, 37246.396226, 36291.111111, 35383.581818, 34103.965517, 33301.338983, 32165.704918, 31104.984127, 30111.969231, 29180.279412, 28024.400000, 27215.791667, 26207.533333, 25047.582278, 24191.060976, 23010.790698, 22111.820225, 21121.531915, 20072.787879, 19123.288462, 18026.954545, 17049.525862, 16080.772358, 15054.318182, 14010.971831, 13042.546053, 12043.660606, 11012.872928, 10001.361809, 9931.205000, 9827.787129, 9726.502439, 9627.289855, 9530.081340, 9403.485849, 9310.728972, 9219.782407, 9101.251142, 9014.339367, 8901.000000, 8817.853982, 8709.379913, 8603.554113, 8500.260684, 8424.406780, 8300.954167, 8204.765432, 8110.788618, 8018.943548, 7907.019841, 7819.709804, 7713.251938, 7609.652672, 7508.807547, 7410.602230, 7314.937500, 7203.357401, 7112.946429, 7007.404930, 6904.955017, 6805.464164, 6708.808081, 6614.863787, 6508.539216, 6405.585209, 6305.841772, 6209.168224, 6102.256881, 6011.695783, 5911.439169, 5802.584302, 5709.146132, 5607.573034, 5509.560773, 5404.615176, 5303.606383, 5206.315927, 5103.352941, 5004.401003, 4909.229064, 4801.341346, 4705.898585, 4606.713626, 4504.496614, 4406.741722, 4300.127155, 4204.787368, 4101.755647, 4003.693387, 3904.888454, 3805.797710, 3702.024119, 3603.817690, 3502.136842, 3402.052811, 3303.789735, 3203.942215, 3103.318818, 3002.646617, 2902.562500, 2803.617978, 2701.223275, 2601.574219, 2502.765664, 2401.532452, 2301.259217, 2201.178414, 2100.969506, 2000.695696, 1916.425695};
    unsigned int length = 175;
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
 * @brief Sets Hindmarsh-Rose model number of points per burst and integration step.
 *
 * If not previously specified by the user, the number of points per burst of the model and its integration step is set according to the living neuron number of points per burst.
 * @param[in] pts_live Number of points in a living neuron burst
 * @param[in] nm Pointer to the neuron model structure
 */

void ghigliazza_holmes_set_pts_burst (double pts_live, neuron_model * nm) {
    /*if (nm->pts_burst == -1.0) {
        ghigliazza_holmes_select_dt(pts_live, &(nm->params[GH_DT]), &(nm->pts_burst));
    }*/

    nm->params[GH_DT] = 0.001;
    nm->pts_burst = 55000;
    
    return;
}