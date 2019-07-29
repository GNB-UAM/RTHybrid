#include "nm_ghigliazza_holmes_2004.h"
#include "../../integration_methods.h"
#include "../neuron_models_aux_functions.h"

/**
 * @file nm_ghigliazza_holmes_2004.h
 * @brief Source file for the Ghigliazza_Holmes_2004 model functions.
 */

/** @name Ghigliazza_Holmes_2004
 * Ghigliazza_Holmes_2004 neuron model.
 */
///@{

double nm_ghigliazza_holmes_2004_ica (double * vars, double * params);
double nm_ghigliazza_holmes_2004_ik (double * vars, double * params);
double nm_ghigliazza_holmes_2004_iks (double * vars, double * params);
double nm_ghigliazza_holmes_2004_il (double * vars, double * params);
double nm_ghigliazza_holmes_2004_m_inf (double * vars, double * params);
double nm_ghigliazza_holmes_2004_c_inf (double * vars, double * params);
double nm_ghigliazza_holmes_2004_n_inf (double * vars, double * params);
double nm_ghigliazza_holmes_2004_v (double * vars, double * params);
double nm_ghigliazza_holmes_2004_m (double * vars, double * params);
double nm_ghigliazza_holmes_2004_c (double * vars, double * params);
double nm_ghigliazza_holmes_2004_set_pts_burst (double pts_live, neuron_model * nm);


double nm_ghigliazza_holmes_2004_v (double * vars, double * params) {
	double ica = nm_ghigliazza_holmes_2004_ica(vars, params);
	double ik = nm_ghigliazza_holmes_2004_ik(vars, params);
	double il = nm_ghigliazza_holmes_2004_il(vars, params);
	double iks = nm_ghigliazza_holmes_2004_iks(vars, params);
	return (-(ica + ik + il + iks) + params[NM_GHIGLIAZZA_HOLMES_2004_I] - params[NM_GHIGLIAZZA_HOLMES_2004_SYN]) / params[NM_GHIGLIAZZA_HOLMES_2004_CM];
}

double nm_ghigliazza_holmes_2004_m (double * vars, double * params) {
	double m_inf = nm_ghigliazza_holmes_2004_m_inf(vars, params);
	return (params[NM_GHIGLIAZZA_HOLMES_2004_EPSILON] / 0.800000) * (m_inf - vars[NM_GHIGLIAZZA_HOLMES_2004_M]);
}

double nm_ghigliazza_holmes_2004_c (double * vars, double * params) {
	double c_inf = nm_ghigliazza_holmes_2004_c_inf(vars, params);
	return (params[NM_GHIGLIAZZA_HOLMES_2004_DELTA] / 0.800000) * (c_inf - vars[NM_GHIGLIAZZA_HOLMES_2004_C]);
}

double nm_ghigliazza_holmes_2004_ica (double * vars, double * params) {
	double n_inf = nm_ghigliazza_holmes_2004_n_inf(vars, params);
	return params[NM_GHIGLIAZZA_HOLMES_2004_GCA] * n_inf * (vars[NM_GHIGLIAZZA_HOLMES_2004_V] - params[NM_GHIGLIAZZA_HOLMES_2004_ECA]);
}

double nm_ghigliazza_holmes_2004_ik (double * vars, double * params) {
	return params[NM_GHIGLIAZZA_HOLMES_2004_GK] * vars[NM_GHIGLIAZZA_HOLMES_2004_M] * (vars[NM_GHIGLIAZZA_HOLMES_2004_V] - params[NM_GHIGLIAZZA_HOLMES_2004_EK]);
}

double nm_ghigliazza_holmes_2004_iks (double * vars, double * params) {
	return params[NM_GHIGLIAZZA_HOLMES_2004_GKS] * vars[NM_GHIGLIAZZA_HOLMES_2004_C] * (vars[NM_GHIGLIAZZA_HOLMES_2004_V] - params[NM_GHIGLIAZZA_HOLMES_2004_EK]);
}

double nm_ghigliazza_holmes_2004_il (double * vars, double * params) {
	return params[NM_GHIGLIAZZA_HOLMES_2004_GL] * (vars[NM_GHIGLIAZZA_HOLMES_2004_V] - params[NM_GHIGLIAZZA_HOLMES_2004_EL]);
}

double nm_ghigliazza_holmes_2004_m_inf (double * vars, double * params) {
	return 1.000000 / (1.000000 + exp(-params[NM_GHIGLIAZZA_HOLMES_2004_KK] * (vars[NM_GHIGLIAZZA_HOLMES_2004_V] - params[NM_GHIGLIAZZA_HOLMES_2004_VTHK])));
}

double nm_ghigliazza_holmes_2004_c_inf (double * vars, double * params) {
	return 1.000000 / (1.000000 + exp(-params[NM_GHIGLIAZZA_HOLMES_2004_KKS] * (vars[NM_GHIGLIAZZA_HOLMES_2004_V] - params[NM_GHIGLIAZZA_HOLMES_2004_VTHKS])));
}

double nm_ghigliazza_holmes_2004_n_inf (double * vars, double * params) {
	return 1.000000 / (1.000000 + exp(-params[NM_GHIGLIAZZA_HOLMES_2004_KCA] * (vars[NM_GHIGLIAZZA_HOLMES_2004_V] - params[NM_GHIGLIAZZA_HOLMES_2004_VTHCA])));
}

/**
 * @brief Ghigliazza_Holmes_2004 neuron model differential equations.
 * @param[in] vars Neuron model variables
 * @param[out] ret Return values array
 * @param[in] params Neuron models parameters
 * @param[in] syn Synapse input current value
 */

void nm_ghigliazza_holmes_2004_f (double * vars, double * ret, double * params, double syn) {
	params[NM_GHIGLIAZZA_HOLMES_2004_SYN] = syn;

	ret[NM_GHIGLIAZZA_HOLMES_2004_V] = nm_ghigliazza_holmes_2004_v(vars, params);
	ret[NM_GHIGLIAZZA_HOLMES_2004_M] = nm_ghigliazza_holmes_2004_m(vars, params);
	ret[NM_GHIGLIAZZA_HOLMES_2004_C] = nm_ghigliazza_holmes_2004_c(vars, params);
}

/**
 * @brief Ghigliazza_Holmes_2004 neuron model.
 * @param[in] nm Neuron model structure
 * @param[in] syn Synapse input current value
 */

void nm_ghigliazza_holmes_2004 (neuron_model nm, double syn) {
	nm.method(nm_ghigliazza_holmes_2004_f, nm.dim, nm.params[NM_GHIGLIAZZA_HOLMES_2004_DT], nm.vars, nm.params, syn);
	return;
}

/**
 * @brief Initializes Ghigliazza_Holmes_2004 neuron model.
 * @param[in] nm Pointer to the neuron model structure
 * @param[in] vars Array with the initial values of the model variables
 * @param[in] params Array with the values of the mode parameters
 */

void nm_ghigliazza_holmes_2004_init (neuron_model * nm, double * vars, double * params) {
	nm->dim = 3;
	nm->vars = (double *) malloc (sizeof(double) * nm->dim);
	copy_1d_array(vars, nm->vars, nm->dim);

	nm->n_params = 19;
	nm->params = (double *) malloc (sizeof(double) * nm->n_params);
	copy_1d_array(params, nm->params, nm->n_params);

	nm->max = 5;
	nm->min = -40;
	nm->pts_burst = -1.0;

	nm->func = &nm_ghigliazza_holmes_2004;
	nm->set_pts_burst = &nm_ghigliazza_holmes_2004_set_pts_burst;
	nm->method = integration_method_selector(params[NM_GHIGLIAZZA_HOLMES_2004_DT]);

	return;
}

/**
 * @brief Sets Ghigliazza_Holmes_2004 model number of points per burst and integration step.
 * 
 * If not previously specified by the user, the number of points per burst of the model and its integration step is set according to the living neuron number of points per burst.
 * @param[in] pts_live Number of points in a living neuron burst
 * @param[in] nm Pointer to the neuron model structure
 */

double nm_ghigliazza_holmes_2004_set_pts_burst (double pts_live, neuron_model * nm) {
	int length = 0;
	int method = nm->params[NM_GHIGLIAZZA_HOLMES_2004_DT];

	switch(method) {
		case EULER:
		{
			length = 148.000000 - 129;
			double dts[] = {0.000200, 0.000300, 0.000400, 0.000500, 0.000600, 0.000700, 0.000800, 0.000900, 0.001000, 0.001100, 0.001200, 0.001300, 0.001400, 0.001500, 0.001600, 0.001700, 0.001800, 0.001900, 0.002000/*, 0.002100, 0.002200, 0.002300, 0.002500, 0.002800, 0.002900, 0.003100, 0.003300, 0.003600, 0.003900, 0.004300, 0.005000, 0.005100, 0.005200, 0.005300, 0.005400, 0.005500, 0.005600, 0.005700, 0.005800, 0.005900, 0.006000, 0.006100, 0.006200, 0.006300, 0.006400, 0.006500, 0.006600, 0.006800, 0.007000, 0.007200, 0.007400, 0.007600, 0.007800, 0.008000, 0.009300, 0.009400, 0.009500, 0.009600, 0.009700, 0.009800, 0.010000, 0.010200, 0.010400, 0.010700, 0.011000, 0.011300, 0.011700, 0.012100, 0.012600, 0.013100, 0.013600, 0.014200, 0.014900, 0.015700, 0.016500, 0.017400, 0.018500, 0.019700, 0.021100, 0.022700, 0.024600, 0.026800, 0.029400, 0.029700, 0.030000, 0.030400, 0.030800, 0.031200, 0.031600, 0.032000, 0.032400, 0.032800, 0.033200, 0.033600, 0.034000, 0.034400, 0.034900, 0.035400, 0.035900, 0.036400, 0.036900, 0.037400, 0.037900, 0.038400, 0.039000, 0.039600, 0.040200, 0.040800, 0.041400, 0.042000, 0.042700, 0.043400, 0.044100, 0.044800, 0.045500, 0.046300, 0.047100, 0.047900, 0.048700, 0.049600, 0.050500, 0.051400, 0.052400, 0.053400, 0.054500, 0.055600, 0.056700, 0.057800, 0.059000, 0.060400, 0.061600, 0.063000, 0.064400, 0.065900, 0.067500, 0.069200, 0.071000, 0.073200, 0.075100, 0.077200, 0.079400, 0.081700, 0.084100, 0.086700, 0.089900, 0.093000, 0.096300, 0.100000*/};
			double pts[] = {298219.000000, 196721.750000, 146875.200000, 117273.000000, 97693.666667, 83809.500000, 73475.833333, 65513.500000, 59228.733333, 54207.764706, 50271.666667/*, 46260.350000, 40287.043478, 37146.640000, 34611.814815, 32464.137931, 30605.290323, 28975.787879, 27534.742857, 26252.351351, 25106.394737, 24080.450000, 22348.558140, 20843.702128, 18419.018868, 16636.559322, 15444.682540, 14063.414286, 12979.653333, 11856.156627, 10839.219780, 9859.130000, 9172.906542, 8807.303571, 8527.517241, 8291.672269, 8083.901639, 7896.312000, 7724.296875, 7564.907692, 7416.105263, 7276.411765, 7144.688406, 7020.070922, 6901.839161, 6789.431507, 6682.351351, 6482.638158, 6300.133758, 6132.919255, 5979.600000, 5839.165680, 5711.000000, 5594.870056, 5465.867403, 4439.470852, 4056.048980, 3871.121094, 3740.928302, 3637.461538, 3473.653846, 3342.717172, 3231.527687, 3088.878882, 2966.113433, 2857.577586, 2729.376374, 2615.686842, 2489.370927, 2376.968900, 2275.803204, 2166.570806, 2052.925773, 1937.881323, 1835.789668, 1733.658537, 1623.812398, 1519.251524, 1413.436879, 1309.499343, 1204.560386, 1102.470718, 1002.269347, 991.876740, 981.700787, 968.455340, 955.566092, 943.019849, 930.800373, 918.896869, 907.297273, 895.990126, 884.962766, 874.207713, 863.713420, 853.469632, 841.005055, 828.906146, 817.152334, 805.732042, 794.629777, 783.833464, 773.329202, 763.105505, 751.195636, 739.658519, 728.472263, 717.626168, 707.089235, 696.900907, 685.336994, 674.161377, 663.376080, 652.999346, 642.858339, 631.645794, 620.999378, 610.399756, 600.333133, 589.495868, 579.000000, 569.000000, 558.000000, 547.002191, 536.001074, 526.000000, 516.000000, 505.514676, 495.001487, 484.996600, 474.757129, 464.518605, 454.460419, 444.401690, 433.865769, 423.371186, 413.124483, 401.993159, 391.121378, 380.144597, 370.130467, 360.003965, 350.000701, 339.997958, 329.975884, 317.574245, 307.420129, 296.512021*/};

			select_dt_neuron_model(dts, pts, length, pts_live, &(nm->params[NM_GHIGLIAZZA_HOLMES_2004_DT]), &(nm->pts_burst));
			break;
		}
		case HEUN:
		{
			length = 153.000000 - 62;
			double dts[] = {0.000200, 0.000300, 0.000400, 0.000500, 0.000600, 0.000700, 0.000800, 0.000900, 0.001000, 0.001100, 0.001200, 0.001300, 0.001400, 0.001500, 0.001600, 0.001700, 0.001800, 0.001900, 0.002000, 0.002100, 0.002200, 0.002300, 0.002400, 0.002600, 0.002800, 0.003000, 0.003200, 0.003400, 0.003700, 0.004000, 0.004300, 0.004700, 0.005100, 0.005600, 0.006200, 0.006300, 0.006400, 0.006500, 0.006600, 0.006700, 0.006800, 0.006900, 0.007000, 0.007100, 0.007200, 0.007300, 0.007400, 0.007500, 0.007600, 0.007700, 0.007800, 0.008000, 0.008200, 0.008400, 0.008600, 0.008800, 0.009000, 0.009200, 0.009400, 0.009600, 0.009800, 0.010000, 0.010200, 0.010400, 0.010600, 0.010800, 0.011000, 0.011200, 0.011500, 0.011800, 0.012100, 0.012400, 0.012700, 0.013000, 0.013300, 0.013700, 0.014100, 0.014500, 0.014900, 0.015400, 0.015900, 0.016000, 0.016300, 0.016700, 0.017100, 0.017600, 0.018100, 0.018600, 0.019200, 0.019800, 0.020500, /*0.021200, 0.022000, 0.022900, 0.023800, 0.024800, 0.025900, 0.027100, 0.028500, 0.030100, 0.031900, 0.036300, 0.036800, 0.038300, 0.040700, 0.047500, 0.048000, 0.050400, 0.050800, 0.051300, 0.051800, 0.058300, 0.058400, 0.058500, 0.058600, 0.058800, 0.059000, 0.059200, 0.059500, 0.059800, 0.060200, 0.060700, 0.061200, 0.061800, 0.062500, 0.063300, 0.072800, 0.072900, 0.073000, 0.073100, 0.073200, 0.073300, 0.073400, 0.073600, 0.073800, 0.074100, 0.074500, 0.075100, 0.075600, 0.076300, 0.077100, 0.078000, 0.079100, 0.080300, 0.081600, 0.083200, 0.084900, 0.086700, 0.088900, 0.091500, 0.093900, 0.096600, 0.100000*/};
			double pts[] = {314716.000000, 209810.666667, 157358.000000, 125886.285714, 104905.375000, 89918.900000, 78679.000000, 69936.923077, 62943.214286, 57221.187500, 52452.777778, 48418.000000, 44959.666667, 41962.409091, 39339.833333, 37025.807692, 34968.888889, 33128.551724, 31472.166667, 29973.625000, 28611.294118, 27367.457143, 26227.243243, 24210.050000, 22481.046512, 20982.630435, 19671.591837, 18514.792453, 17014.210526, 15738.822581, 14641.507463, 13396.493151, 12346.987500, 11246.215909, 10160.103093, 9999.242424, 9843.430000, 9692.421569, 9546.019417, 9403.980952, 9266.149533, 9132.324074, 9002.345455, 8876.036036, 8753.247788, 8633.850877, 8517.689655, 8404.644068, 8294.588235, 8187.421488, 8083.008197, 7882.064000, 7690.992248, 7509.090909, 7335.733333, 7170.333333, 7012.361702, 6861.340278, 6716.829932, 6578.430464, 6445.772727, 6318.515924, 6196.356250, 6078.993865, 5966.180723, 5857.656805, 5753.203488, 5652.613636, 5508.550000, 5372.162162, 5242.915344, 5120.371134, 5004.106061, 4893.798030, 4789.154589, 4658.084507, 4536.461187, 4424.480000, 4323.269565, 4218.881356, 4107.896694, 3942.376984, 3792.034351, 3660.356618, 3550.575000, 3429.058621, 3319.203333, 3218.142395, 3106.268750, 3003.015060, 2891.831395, /*2789.310924, 2681.371968, 2570.208763, 2468.547030, 2365.346793, 2262.224490, 2160.607375, 2054.610309, 1948.011719, 1844.754159, 1741.296684, 1552.534992, 1450.899709, 1350.795670, 1247.770000, 1107.000000, 1006.991927, 996.866267, 985.230010, 974.552195, 963.636100, 888.490214, 852.753202, 835.394142, 814.761011, 799.935096, 789.000790, 775.844600, 765.000000, 753.000000, 740.499629, 729.913743, 718.473381, 707.000708, 695.520891, 684.228082, 657.053289, 640.815266, 611.268054, 594.222487, 547.899067, 529.284049, 510.395503, 498.018445, 484.410281, 471.878602, 461.816921, 446.908277, 435.067944, 424.244586, 413.884424, 402.814516, 392.473291, 382.339457, 371.387361, 361.000723, 350.996488, 340.255022, 329.171278, 317.476009, 307.216723, 296.988707*/};

			select_dt_neuron_model(dts, pts, length, pts_live, &(nm->params[NM_GHIGLIAZZA_HOLMES_2004_DT]), &(nm->pts_burst));
			break;
		}
		case RK4:
		{
			length = 141.000000;
			double dts[] = {0.000200, 0.000300, 0.000400, 0.000500, 0.000600, 0.000700, 0.000800, 0.000900, 0.001000, 0.001100, 0.001200, 0.001300, 0.001400, 0.001500, 0.001600, 0.001700, 0.001800, 0.001900, 0.002000, 0.002100, 0.002200, 0.002300, 0.002400, 0.002600, 0.002800, 0.003000, 0.003200, 0.003400, 0.003700, 0.004000, 0.004300, 0.004700, 0.005100, 0.005600, 0.006200, 0.006300, 0.006400, 0.006500, 0.006600, 0.006700, 0.006800, 0.006900, 0.007000, 0.007100, 0.007200, 0.007300, 0.007400, 0.007500, 0.007600, 0.007700, 0.007800, 0.007900, 0.008100, 0.008300, 0.008500, 0.008700, 0.008900, 0.009100, 0.009300, 0.009500, 0.009700, 0.009900, 0.010100, 0.010300, 0.010500, 0.010700, 0.010900, 0.011100, 0.011400, 0.011700, 0.012000, 0.012300, 0.012600, 0.012900, 0.013200, 0.013500, 0.013900, 0.014300, 0.014700, 0.015100, 0.015500, 0.015900, 0.016400, 0.016900, 0.017400, 0.017900, 0.018500, 0.019100, 0.019700, 0.020400, 0.021100, 0.021900, 0.022700, 0.023600, 0.024600, 0.025700, 0.026900, 0.028100, 0.029500, 0.031000, 0.032700, 0.034500, 0.036500, 0.038800, 0.041400, 0.044300, 0.047700, 0.051600, 0.056100, 0.061500, 0.062100, 0.062800, 0.063500, 0.064200, 0.064900, 0.065600, 0.066300, 0.067000, 0.067800, 0.068600, 0.069400, 0.070200, 0.071000, 0.071900, 0.072800, 0.073700, 0.074600, 0.075600, 0.076600, 0.077600, 0.085500, 0.086300, 0.087100, 0.087800, 0.088900, 0.089900, 0.090700, 0.092000, 0.093000, 0.099500, 0.100000};
			double pts[] = {314716.000000, 209810.666667, 157358.000000, 125886.428571, 104905.375000, 89918.900000, 78679.000000, 69936.923077, 62943.142857, 57221.125000, 52452.666667, 48417.842105, 44959.428571, 41962.136364, 39339.500000, 37025.423077, 34968.444444, 33128.000000, 31471.600000, 29972.937500, 28610.529412, 27366.628571, 26226.324324, 24208.925000, 22479.697674, 20981.065217, 19669.755102, 18512.698113, 17011.684211, 15735.806452, 14637.955224, 13392.164384, 12341.800000, 11239.852273, 10152.123711, 9990.979798, 9834.870000, 9683.558824, 9536.844660, 9394.504762, 9256.345794, 9122.194444, 8991.881818, 8865.234234, 8742.097345, 8622.347826, 8505.827586, 8392.423729, 8281.991597, 8174.438017, 8069.634146, 7967.483871, 7770.755906, 7583.507692, 7405.074627, 7234.839416, 7072.257143, 6916.818182, 6768.068493, 6625.586667, 6488.967320, 6357.884615, 6231.974843, 6110.969136, 5994.563636, 5882.514793, 5774.581395, 5670.525714, 5521.300000, 5379.722826, 5245.227513, 5117.288660, 4995.442211, 4879.264706, 4768.365385, 4662.394366, 4528.214612, 4401.544248, 4281.758621, 4168.322176, 4060.738776, 3958.569721, 3837.861004, 3724.292135, 3617.250909, 3516.187279, 3402.112628, 3295.205298, 3194.801282, 3085.126935, 2982.718563, 2873.691643, 2772.337047, 2666.513369, 2557.992308, 2448.356265, 2338.946009, 2238.847191, 2132.316239, 2028.792683, 1922.872832, 1822.005484, 1721.479310, 1618.527597, 1515.709726, 1415.008511, 1312.211564, 1210.604848, 1110.545050, 1009.516684, 999.371371, 987.782394, 976.449658, 965.367505, 954.529637, 943.959357, 933.560748, 923.415896, 912.086758, 901.039711, 890.273619, 879.777974, 869.537859, 858.323024, 847.433418, 836.859296, 826.600166, 815.574694, 805.000000, 794.777247, 783.926217, 770.863426, 760.000761, 748.976762, 736.070007, 724.955007, 714.551502, 703.977449, 692.824549, 681.808191, 670.168343};

			select_dt_neuron_model(dts, pts, length, pts_live, &(nm->params[NM_GHIGLIAZZA_HOLMES_2004_DT]), &(nm->pts_burst));
			break;
		}
		case RK65:
		{
			length = 144.000000;
			double dts[] = {0.000200, 0.000300, 0.000400, 0.000500, 0.000600, 0.000700, 0.000800, 0.000900, 0.001000, 0.001100, 0.001200, 0.001300, 0.001400, 0.001500, 0.001600, 0.001700, 0.001800, 0.001900, 0.002000, 0.002100, 0.002200, 0.002300, 0.002400, 0.002600, 0.002800, 0.003000, 0.003200, 0.003400, 0.003700, 0.004000, 0.004300, 0.004700, 0.005100, 0.005600, 0.006200, 0.006300, 0.006400, 0.006500, 0.006600, 0.006700, 0.006800, 0.006900, 0.007000, 0.007100, 0.007200, 0.007300, 0.007400, 0.007500, 0.007600, 0.007700, 0.007800, 0.007900, 0.008100, 0.008300, 0.008500, 0.008700, 0.008900, 0.009100, 0.009300, 0.009500, 0.009700, 0.009900, 0.010100, 0.010300, 0.010500, 0.010700, 0.010900, 0.011100, 0.011400, 0.011700, 0.012000, 0.012300, 0.012600, 0.012900, 0.013200, 0.013500, 0.013900, 0.014300, 0.014700, 0.015100, 0.015500, 0.015900, 0.016400, 0.016900, 0.017400, 0.017900, 0.018500, 0.019100, 0.019700, 0.020400, 0.021100, 0.021900, 0.022700, 0.023600, 0.024600, 0.025700, 0.026900, 0.028200, 0.029600, 0.031100, 0.032800, 0.034700, 0.036800, 0.039100, 0.041700, 0.044700, 0.048200, 0.052300, 0.057100, 0.062900, 0.063600, 0.064300, 0.065000, 0.065700, 0.066400, 0.067200, 0.068000, 0.068800, 0.069600, 0.070400, 0.071300, 0.072200, 0.073100, 0.074000, 0.074900, 0.075900, 0.076900, 0.077900, 0.078900, 0.080000, 0.081100, 0.082200, 0.083300, 0.084500, 0.085800, 0.087100, 0.088500, 0.089900, 0.091400, 0.092800, 0.094600, 0.096300, 0.098700, 0.100000};
			double pts[] = {314716.000000, 209810.666667, 157358.000000, 125886.428571, 104905.375000, 89918.900000, 78679.000000, 69936.923077, 62943.142857, 57221.125000, 52452.666667, 48417.842105, 44959.428571, 41962.136364, 39339.500000, 37025.423077, 34968.444444, 33128.000000, 31471.600000, 29972.937500, 28610.529412, 27366.628571, 26226.324324, 24208.925000, 22479.697674, 20981.065217, 19669.755102, 18512.698113, 17011.684211, 15735.806452, 14637.955224, 13392.164384, 12341.800000, 11239.852273, 10152.123711, 9990.979798, 9834.870000, 9683.568627, 9536.854369, 9394.504762, 9256.355140, 9122.203704, 8991.890909, 8865.243243, 8742.106195, 8622.356522, 8505.836207, 8392.423729, 8282.000000, 8174.446281, 8069.642276, 7967.491935, 7770.763780, 7583.515385, 7405.082090, 7234.854015, 7072.271429, 6916.832168, 6768.082192, 6625.600000, 6488.986928, 6357.903846, 6232.000000, 6110.993827, 5994.587879, 5882.544379, 5774.610465, 5670.560000, 5521.338889, 5379.760870, 5245.269841, 5117.335052, 4995.492462, 4879.323529, 4768.427885, 4662.460094, 4528.287671, 4401.623894, 4281.853448, 4168.426778, 4060.853061, 3958.697211, 3838.003861, 3724.453184, 3617.429091, 3516.388693, 3402.341297, 3295.463576, 3195.096154, 3085.464396, 2983.101796, 2874.132565, 2772.846797, 2667.104278, 2558.691517, 2449.181818, 2339.931925, 2232.071588, 2126.511727, 2023.961460, 1919.080769, 1814.027273, 1710.543739, 1609.967742, 1509.649017, 1408.418900, 1306.280105, 1204.074789, 1103.165746, 1001.957874, 991.000992, 980.293425, 969.820388, 959.573487, 949.546578, 938.348684, 927.421541, 916.753903, 906.336661, 896.165171, 885.000886, 874.125984, 863.528954, 853.196413, 843.124051, 832.225000, 821.634868, 811.309504, 801.263833, 790.551424, 780.041374, 770.000771, 760.000000, 749.999249, 739.000000, 728.574034, 717.581178, 706.796886, 696.539749, 686.534708, 675.025676, 664.403590, 654.229862, 644.101225};

			select_dt_neuron_model(dts, pts, length, pts_live, &(nm->params[NM_GHIGLIAZZA_HOLMES_2004_DT]), &(nm->pts_burst));
			break;
		}
	}

	return nm->params[NM_GHIGLIAZZA_HOLMES_2004_DT];
}

///@}