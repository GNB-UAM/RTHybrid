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
            nm->vars[VAR_X] = 0.0;

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

            nm->n_params = 18;
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
        case WANG:
            wang_init(nm, vars, params);

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
    ret[0] = vars[VAR_Y] + 3.0 * (vars[VAR_X]*vars[VAR_X]) - (vars[VAR_X]*vars[VAR_X]*vars[VAR_X]) - vars[VAR_Z] + params[HR_I] - syn;
    ret[1] = 1.0 - 5.0 * (vars[VAR_X]*vars[VAR_X]) - vars[VAR_Y];
    ret[2] = (-vars[VAR_Z] + params[HR_S] * (vars[VAR_X] + 1.6)) * params[HR_R];

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

    ret[1] = vars[VAR_Y] - params[RLK_MU] * (vars[VAR_X] + 1) + params[RLK_MU] * params[RLK_SIGMA];
    u = vars[VAR_Y] - syn * params[RLK_I];


    if (vars[VAR_X] <= 0) {
        ret[0] = params[RLK_ALPHA] / (1 - vars[VAR_X]) + u;
    } else if (vars[VAR_X] >= params[RLK_ALPHA] + u) {
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
        nm.vars[VAR_X] = nm.params[RLK_OLD];
        rlk_f(nm.vars, ret, nm.params, syn);
        nm.vars[VAR_X] = ret[0];
        nm.vars[VAR_Y] = ret[1];
        nm.params[RLK_OLD] = nm.vars[VAR_X];
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
        ret[1] = nm.vars[VAR_Y];

        nm.params[RLK_J]++;

        nm.vars[VAR_X] = ret[0];
        nm.vars[VAR_Y] = ret[1];
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
    *ret = params[GH_G_CA] * ghigliazza_holmes_inf(vars[VAR_X], params[GH_VTH_CA], params[GH_K_CA]) * (vars[VAR_X] - params[GH_E_CA]);
    return;
}

void ghigliazza_holmes_il_f (double * vars, double * params, double * ret) {
    *ret = params[GH_G_L] * (vars[VAR_X] - params[GH_E_L]);
    return;
}

void ghigliazza_holmes_ik_f (double * vars, double * params, double * ret) {
    *ret = params[GH_G_K] * vars[GH_M] * (vars[VAR_X] - params[GH_E_K]);
    return;
}

void ghigliazza_holmes_iks_f (double * vars, double * params, double * ret) {
    *ret = params[GH_G_KS] * vars[GH_C] * (vars[VAR_X] - params[GH_E_K]);
    return;
}


void ghigliazza_holmes_f (double * vars, double * ret, double * params, double syn) {
    double ica, ik, il, iks;
    ghigliazza_holmes_ica_f(vars, params, &ica);
    ghigliazza_holmes_ik_f(vars, params, &ik);
    ghigliazza_holmes_il_f(vars, params, &il);
    ghigliazza_holmes_iks_f(vars, params, &iks);

    ret[0] = (-(ica + ik + il + iks) + params[GH_I] - syn) / params[GH_CM];
    ret[1] = (params[GH_EPSILON] / 0.8) * (ghigliazza_holmes_inf(vars[VAR_X], params[GH_VTH_K], params[GH_K_K]) - vars[GH_M]);
    ret[2] = (params[GH_DELTA] / 0.8) * (ghigliazza_holmes_inf(vars[VAR_X], params[GH_VTH_KS], params[GH_K_KS]) - vars[GH_C]);

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
    double dts[] = {0.000090, 0.000200, 0.000300, 0.000400, 0.000500, 0.000600, 0.000700, 0.000800, 0.000900, 0.001000, 0.001100, 0.001200, 0.001300, 0.001400, 0.001500, 0.001600, 0.001700, 0.001800, 0.001900, 0.002000, 0.002100, 0.002200, 0.002300, 0.002400, 0.002500, 0.002600, 0.002700, 0.002800, 0.002900, 0.003100, 0.003300, 0.003400, 0.003700, 0.003900, 0.004100, 0.004400, 0.004800, 0.005200, 0.005700, 0.006200, 0.006300, 0.006400, 0.006500, 0.006600, 0.006700, 0.006800, 0.006900, 0.007000, 0.007100, 0.007200, 0.007300, 0.007400, 0.007500, 0.007600, 0.007700, 0.007800, 0.007900, 0.008000, 0.008100, 0.008200, 0.008300, 0.008500, 0.008600, 0.008700, 0.008800, 0.008900, 0.009100, 0.009200, 0.009400, 0.009500, 0.009600, 0.009800, 0.009900, 0.010100, 0.010300, 0.010500, 0.010600, 0.010800, 0.011000, 0.011200, 0.011400, 0.011600, 0.011800, 0.012100, 0.012300, 0.012600, 0.012800, 0.013100, 0.013400, 0.013700, 0.014000, 0.014300, 0.014600, 0.015000, 0.015400, 0.015700, 0.016200, 0.016600, 0.017000, 0.017500, 0.018000, 0.018600, 0.019200, 0.019800, 0.020500, 0.021200, 0.022000, 0.022800, 0.023800, 0.025300, 0.025400, 0.025800, 0.026500, 0.027500, 0.028600, 0.029900, 0.031300, 0.032900, 0.034700, 0.036700, 0.039100, 0.041800, 0.045000, 0.048800, 0.053700, 0.058900, 0.059000, 0.059100, 0.059300, 0.059500, 0.059800, 0.060100, 0.060500, 0.060900, 0.061300, 0.061800, 0.062300, 0.062900, 0.063500, 0.064100, 0.064700, 0.065400, 0.066200, 0.066900, 0.067800, 0.068600, 0.069500, 0.070500, 0.071600, 0.072800, 0.074100, 0.078200, 0.078300, 0.078400, 0.078500, 0.078700, 0.079000, 0.079400, 0.079900, 0.080500, 0.081200, 0.082000, 0.083100, 0.084400, 0.085400, 0.086900, 0.088500, 0.090200, 0.095900, 0.096400, 0.096600, 0.097100, 0.097400, 0.097800, 0.097900, 0.098300, 0.098400, 0.099600, 0.100000};
    double pts[] = {699369.000000, 314716.000000, 209810.666667, 157358.000000, 125886.333333, 104905.375000, 89918.900000, 78678.916667, 69936.923077, 62943.200000, 57221.062500, 52452.647059, 48417.842105, 44959.428571, 41962.181818, 39339.541667, 37025.461538, 34968.518519, 33128.071429, 31471.700000, 29973.062500, 28610.666667, 27366.742857, 26226.513514, 25177.473684, 24209.125000, 23312.536585, 22479.977273, 21704.844444, 20304.604167, 19074.098039, 18513.132075, 17012.210526, 16139.885246, 15352.682540, 14306.088235, 13114.160000, 12105.658537, 11044.144444, 10153.917526, 9992.838384, 9836.790000, 9685.549020, 9538.903846, 9396.628571, 9258.547170, 9124.462963, 8994.227273, 8867.657658, 8744.601770, 8624.921053, 8508.482759, 8395.161017, 8284.816667, 8177.338843, 8072.617886, 7970.556452, 7871.048000, 7774.000000, 7679.325581, 7586.931298, 7408.684211, 7322.674074, 7238.642336, 7156.532374, 7076.264286, 6921.020979, 6845.944444, 6700.585034, 6630.208054, 6561.298013, 6427.714286, 6362.948387, 6237.283019, 6116.500000, 6000.343373, 5943.916168, 5834.205882, 5728.494253, 5626.579545, 5528.255556, 5433.338798, 5341.650538, 5209.836842, 5125.561856, 5004.186869, 4926.450495, 4814.334951, 4707.279621, 4604.953704, 4507.058824, 4413.314159, 4323.469565, 4209.341772, 4101.226337, 4023.817814, 3901.298039, 3808.708812, 3720.588015, 3616.269091, 3517.943463, 3407.229452, 3303.790698, 3207.048387, 3101.971963, 3004.686747, 2902.483965, 2809.636620, 2707.913043, 2677.077957, 2513.696970, 2407.893720, 2310.482599, 2203.452539, 2103.575949, 2000.086172, 1901.386667, 1801.178700, 1701.360068, 1603.536116, 1500.996992, 1401.432584, 1300.979140, 1201.802647, 1101.315673, 1016.018311, 997.329670, 987.000000, 973.000000, 963.000000, 951.173333, 941.427898, 930.189944, 920.261751, 911.211679, 900.810640, 891.132025, 880.305727, 870.144599, 860.541774, 851.415673, 841.295703, 830.347465, 821.253903, 810.175994, 800.870890, 791.000000, 780.702893, 770.243827, 760.000000, 750.166667, 744.650522, 735.289183, 707.761871, 694.811544, 683.270178, 671.600806, 660.991396, 651.112125, 642.758199, 630.231400, 620.509938, 611.988971, 600.000000, 590.823286, 580.347851, 570.189960, 560.583847, 550.453994, 540.418605, 531.053135, 523.058639, 511.223132, 501.296891, 499.694000, 492.422868, 490.999017, 482.209459, 470.684880};
    unsigned int length = 179, i;

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
    if (nm->pts_burst == -1.0) {
        ghigliazza_holmes_select_dt(pts_live, &(nm->params[GH_DT]), &(nm->pts_burst));
    }
    
    return;
}


/** @name Wang
 *  Wang neuron model from (Wang, 1993). 
 */
///@{

/**
 * @brief Wang neuron model differential equations.
 * @param[in] vars Neuron model variables
 * @param[out] ret Return values array
 * @param[in] params Neuron models parameters
 * @param[in] syn Synapse input current value
 */

double wang_inf_f (double x, double y, double z) {
    return 1.0 / (1.0 + exp(-(x + y) / z));
}


/* INA channel */

double wang_mna (double v, double sigma) {
    double aux1 = -0.1 * (v + 30.0 - sigma);
    double alpha = aux1 / (exp(aux1) - 1.0);
    double beta = 4.0 * exp((-v - 55.0 + sigma) / 18.0);

    return alpha / (alpha + beta);
}

double wang_hna_inf (double v, double sigma) {
    double alpha = 0.07 * exp(-(v + 44.0 - sigma) / 20.0);
    double beta = 1.0 / (exp(-0.1 * (v + 14.0 - sigma)) + 1.0);

    return alpha / (alpha + beta);
}

double wang_hna (double v, double sigma, double phi, double old) {
    double alpha = 0.07 * exp(-(v + 44.0 - sigma) / 20.0);
    double beta = 1.0 / (exp(-0.1 * (v + 14.0 - sigma)) + 1.0);

    return phi * (alpha * (1.0 - old) - beta * old);
}

void wang_ina_f (double * vars, double * params, double * ret) {
    *ret = params[WANG_G_NA] * pow(wang_mna(vars[VAR_X], params[WANG_SIGMA]), 3) * vars[WANG_H_NA] * (vars[VAR_X] - params[WANG_V_NA]);
    return;
}


/* IK channel */


double wang_nk_inf (double v, double sigma) {
    double aux1 = v + 34.0 - sigma;
    double alpha = (-0.01 * aux1) / (exp(-0.1 * aux1) - 1.0);
    double beta = 0.125 * exp(-(v + 44.0 - sigma) / 80.0);

    return alpha / (alpha + beta);
}

double wang_nk (double v, double sigma, double phi, double old) {
    double aux1 = v + 34.0 - sigma;
    double alpha = (-0.01 * aux1) / (exp(-0.1 * aux1) - 1.0);
    double beta = 0.125 * exp(-(v + 44.0 - sigma) / 80.0);

    return phi * (alpha * (1.0 - old) - beta * old);
}

void wang_ik_f (double * vars, double * params, double * ret) {
    *ret = params[WANG_G_K] * pow(vars[WANG_N_K], 4) * (vars[VAR_X] - params[WANG_V_K]);
    return;
}

/* INAP channel */

double wang_mnap(double v) {
    return 1.0 / (1.0 + exp(- (v + 51.0) / 5.0));
}

void wang_inap_f (double * vars, double * params, double * ret) {
    *ret = params[WANG_G_NAP] * wang_inf_f(vars[VAR_X], 51.0, 5.0) * (vars[VAR_X] - params[WANG_V_NA]);
    return;
}


/* IKS channel */

double wang_mks_inf (double v, double sigma) {
    return 1.0 / (1.0 + exp(-(v + 34.0) / 6.5));
}

double wang_hks_inf (double v, double sigma) {
    return 1.0 / (1.0 + exp((v + 65.0) / 6.6));
}

double wang_h1ks (double v, double phi, double old) {
    double inf = wang_inf_f(-v, -65.0, 6.6);
    double tau = 200.0 + (220.0 / (1.0 + exp(-(v + 71.6) / 6.85)));

    return phi * (inf - old) / tau; 
}

double wang_h2ks (double v, double phi, double old) {
    double inf = wang_inf_f(-v, -65.0, 6.6);
    double tau = 200.0 + (3200.0 / (1.0 + exp(-(v + 63.6) / 4.0)));

    return phi * (inf - old) / tau; 
}

double wang_mks (double v, double phi, double tau, double old) {
    double inf = wang_inf_f(v, 34.0, 6.5);

    return phi * (inf - old) / tau;
}

void wang_iks_f (double * vars, double * params, double * ret) {
    double aux1 = params[WANG_RHO] * vars[WANG_H1_KS] + (1.0 - params[WANG_RHO]) * vars[WANG_H2_KS];
    *ret = params[WANG_G_KS] * vars[WANG_M_KS] * aux1 * (vars[VAR_X] - params[WANG_V_K]);

    return;
}

/* Leakage current */

void wang_il_f (double * vars, double * params, double * ret) {
    *ret = params[WANG_G_L] * (vars[VAR_X] - params[WANG_V_L]);
    return;
}


/* Model */

void wang_f (double * vars, double * ret, double * params, double syn) {
    double inap, ik, ina, iks, il;
    wang_inap_f(vars, params, &inap);
    wang_ina_f(vars, params, &ina);
    wang_ik_f(vars, params, &ik);
    wang_iks_f(vars, params, &iks);
    wang_il_f(vars, params, &il);

    ret[WANG_H_NA] = wang_hna(vars[VAR_X], params[WANG_SIGMA], params[WANG_PHI], vars[WANG_H_NA]);
    ret[WANG_N_K] = wang_nk(vars[VAR_X], params[WANG_SIGMA], params[WANG_PHI], vars[WANG_N_K]);
    ret[WANG_M_KS] = wang_mks(vars[VAR_X], 1.0, params[WANG_TAUM], vars[WANG_M_KS]);
    ret[WANG_H1_KS] = wang_h1ks(vars[VAR_X], 1.0, vars[WANG_H1_KS]);
    ret[WANG_H2_KS] =  wang_h2ks(vars[VAR_X], 1.0, vars[WANG_H2_KS]);

    ret[VAR_X] = (-(il + inap + iks + ina + ik) + params[WANG_I] - (syn * 0.001)) / params[WANG_CM];

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

void wang (neuron_model nm, double syn) {
    runge_kutta_6 (wang_f, nm.dim, nm.params[WANG_DT], nm.vars, nm.params, syn);
    return;
}

void wang_select_dt (double pts_live, double * dt, double * pts_burst) {
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

void wang_set_pts_burst (double pts_live, neuron_model * nm) {
    if (nm->pts_burst == -1.0) {
        wang_select_dt(pts_live, &(nm->params[WANG_DT]), &(nm->pts_burst));
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

void wang_init (neuron_model * nm, double * vars, double * params) {
    nm->dim = 6;
    nm->vars = (double *) malloc (sizeof(double) * nm->dim);
    copy_1d_array(vars, nm->vars, nm->dim);

    nm->n_params = 15;
    nm->params = (double *) malloc (sizeof(double) * nm->n_params);
    copy_1d_array(params, nm->params, nm->n_params);

    nm->max = 20;
    nm->min = -80;
    nm->pts_burst = -1.0;

    nm->vars[WANG_H_NA] = wang_hna_inf (nm->vars[VAR_X], nm->params[WANG_SIGMA]); /* Steady-state */
    nm->vars[WANG_N_K] = wang_nk_inf (nm->vars[VAR_X], nm->params[WANG_SIGMA]); /* Steady-state */
    nm->vars[WANG_M_KS] = wang_inf_f(nm->vars[VAR_X], 34.0, 6.5); /* Steady-state */
    nm->vars[WANG_H1_KS] = wang_inf_f(-nm->vars[VAR_X], -65.0, 6.6); /* Steady-state */
    nm->vars[WANG_H2_KS] =  wang_inf_f(-nm->vars[VAR_X], -65.0, 6.6); /* Steady-state */

    nm->func = &wang;
    nm->set_pts_burst = &wang_set_pts_burst;

    return;
}

///@}