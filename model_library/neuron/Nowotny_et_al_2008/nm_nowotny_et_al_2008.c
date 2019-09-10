#include "nm_nowotny_et_al_2008.h"
#include "../../integration_methods.h"
#include "../neuron_models_aux_functions.h"

/**
 * @file nm_nowotny_et_al_2008.h
 * @brief Source file for the Nowotny_et_al_2008 model functions.
 */

/** @name Nowotny_et_al_2008
 * Nowotny_et_al_2008 neuron model.
 */
///@{

double nm_nowotny_et_al_2008_ina (double * vars, double * params);
double nm_nowotny_et_al_2008_amna (double * vars, double * params);
double nm_nowotny_et_al_2008_bmna (double * vars, double * params);
double nm_nowotny_et_al_2008_ahna (double * vars, double * params);
double nm_nowotny_et_al_2008_bhna (double * vars, double * params);
double nm_nowotny_et_al_2008_ikd (double * vars, double * params);
double nm_nowotny_et_al_2008_amkd (double * vars, double * params);
double nm_nowotny_et_al_2008_bmkd (double * vars, double * params);
double nm_nowotny_et_al_2008_im (double * vars, double * params);
double nm_nowotny_et_al_2008_minfm (double * vars, double * params);
double nm_nowotny_et_al_2008_km (double * vars, double * params);
double nm_nowotny_et_al_2008_ila (double * vars, double * params);
double nm_nowotny_et_al_2008_ivv (double * vars, double * params);
double nm_nowotny_et_al_2008_ica (double * vars, double * params);
double nm_nowotny_et_al_2008_minfcat (double * vars, double * params);
double nm_nowotny_et_al_2008_hinfcat (double * vars, double * params);
double nm_nowotny_et_al_2008_minfcas (double * vars, double * params);
double nm_nowotny_et_al_2008_ikca (double * vars, double * params);
double nm_nowotny_et_al_2008_kca_aux1 (double * vars, double * params);
double nm_nowotny_et_al_2008_kca_aux2 (double * vars, double * params);
double nm_nowotny_et_al_2008_minfkca (double * vars, double * params);
double nm_nowotny_et_al_2008_hinfkca (double * vars, double * params);
double nm_nowotny_et_al_2008_ia (double * vars, double * params);
double nm_nowotny_et_al_2008_a (double * vars, double * params);
double nm_nowotny_et_al_2008_minfa (double * vars, double * params);
double nm_nowotny_et_al_2008_hinfa (double * vars, double * params);
double nm_nowotny_et_al_2008_ih (double * vars, double * params);
double nm_nowotny_et_al_2008_minfh (double * vars, double * params);
double nm_nowotny_et_al_2008_ils (double * vars, double * params);
double nm_nowotny_et_al_2008_mna (double * vars, double * params);
double nm_nowotny_et_al_2008_hna (double * vars, double * params);
double nm_nowotny_et_al_2008_mkd (double * vars, double * params);
double nm_nowotny_et_al_2008_mm (double * vars, double * params);
double nm_nowotny_et_al_2008_Vaxon (double * vars, double * params);
double nm_nowotny_et_al_2008_mcat (double * vars, double * params);
double nm_nowotny_et_al_2008_hcat (double * vars, double * params);
double nm_nowotny_et_al_2008_mcas (double * vars, double * params);
double nm_nowotny_et_al_2008_Ca (double * vars, double * params);
double nm_nowotny_et_al_2008_mkca (double * vars, double * params);
double nm_nowotny_et_al_2008_hkca (double * vars, double * params);
double nm_nowotny_et_al_2008_ma (double * vars, double * params);
double nm_nowotny_et_al_2008_ha1 (double * vars, double * params);
double nm_nowotny_et_al_2008_ha2 (double * vars, double * params);
double nm_nowotny_et_al_2008_mh (double * vars, double * params);
double nm_nowotny_et_al_2008_V (double * vars, double * params);
double nm_nowotny_et_al_2008_set_pts_burst (double pts_live, neuron_model * nm);


double nm_nowotny_et_al_2008_ina (double * vars, double * params) {
	return vars[NM_NOWOTNY_ET_AL_2008_MNA]*vars[NM_NOWOTNY_ET_AL_2008_MNA]*vars[NM_NOWOTNY_ET_AL_2008_MNA] * vars[NM_NOWOTNY_ET_AL_2008_HNA] * params[NM_NOWOTNY_ET_AL_2008_GNA] * (vars[NM_NOWOTNY_ET_AL_2008_VAXON] - params[NM_NOWOTNY_ET_AL_2008_VNA]) * params[NM_NOWOTNY_ET_AL_2008_AREAAXON];
}

double nm_nowotny_et_al_2008_mna (double * vars, double * params) {
	double amna = nm_nowotny_et_al_2008_amna(vars, params);
	double bmna = nm_nowotny_et_al_2008_bmna(vars, params);
	return amna * (1.000000 - vars[NM_NOWOTNY_ET_AL_2008_MNA]) - bmna * vars[NM_NOWOTNY_ET_AL_2008_MNA];
}

double nm_nowotny_et_al_2008_amna (double * vars, double * params) {
	return (-16.640000 - 0.320000 * vars[NM_NOWOTNY_ET_AL_2008_VAXON]) / (exp(-13.000000 - vars[NM_NOWOTNY_ET_AL_2008_VAXON] / 4.000000) - 1.000000);
}

double nm_nowotny_et_al_2008_bmna (double * vars, double * params) {
	return (0.280000 * vars[NM_NOWOTNY_ET_AL_2008_VAXON] + 7.000000) / (exp(vars[NM_NOWOTNY_ET_AL_2008_VAXON] / 5.000000 + 5.000000) - 1.000000);
}

double nm_nowotny_et_al_2008_ahna (double * vars, double * params) {
	return 0.128000 * exp(-2.666667 - vars[NM_NOWOTNY_ET_AL_2008_VAXON] / 18.000000);
}

double nm_nowotny_et_al_2008_bhna (double * vars, double * params) {
	return 4.000000 / (exp(-5.000000 - vars[NM_NOWOTNY_ET_AL_2008_VAXON] / 5.000000) + 1.000000);
}

double nm_nowotny_et_al_2008_hna (double * vars, double * params) {
	double ahna = nm_nowotny_et_al_2008_ahna(vars, params);
	double bhna = nm_nowotny_et_al_2008_bhna(vars, params);
	return ahna * (1.000000 - vars[NM_NOWOTNY_ET_AL_2008_HNA]) - bhna * vars[NM_NOWOTNY_ET_AL_2008_HNA];
}

double nm_nowotny_et_al_2008_ikd (double * vars, double * params) {
	return vars[NM_NOWOTNY_ET_AL_2008_MKD]*vars[NM_NOWOTNY_ET_AL_2008_MKD]*vars[NM_NOWOTNY_ET_AL_2008_MKD]*vars[NM_NOWOTNY_ET_AL_2008_MKD] * params[NM_NOWOTNY_ET_AL_2008_GKD] * (vars[NM_NOWOTNY_ET_AL_2008_VAXON] - params[NM_NOWOTNY_ET_AL_2008_VKD]) * params[NM_NOWOTNY_ET_AL_2008_AREAAXON];
}

double nm_nowotny_et_al_2008_amkd (double * vars, double * params) {
	return (-1.600000 - 0.032000 * vars[NM_NOWOTNY_ET_AL_2008_VAXON]) / (exp(-10.000000 - vars[NM_NOWOTNY_ET_AL_2008_VAXON] / 5.000000) - 1.000000);
}

double nm_nowotny_et_al_2008_bmkd (double * vars, double * params) {
	return 0.500000 * exp(-1.375000 - vars[NM_NOWOTNY_ET_AL_2008_VAXON] / 40.000000);
}

double nm_nowotny_et_al_2008_mkd (double * vars, double * params) {
	double amkd = nm_nowotny_et_al_2008_amkd(vars, params);
	double bmkd = nm_nowotny_et_al_2008_bmkd(vars, params);
	return amkd * (1.000000 - vars[NM_NOWOTNY_ET_AL_2008_MKD]) - bmkd * vars[NM_NOWOTNY_ET_AL_2008_MKD];
}

double nm_nowotny_et_al_2008_im (double * vars, double * params) {
	return params[NM_NOWOTNY_ET_AL_2008_GM] * vars[NM_NOWOTNY_ET_AL_2008_MM] * (vars[NM_NOWOTNY_ET_AL_2008_VAXON] - params[NM_NOWOTNY_ET_AL_2008_VM]) * params[NM_NOWOTNY_ET_AL_2008_AREAAXON];
}

double nm_nowotny_et_al_2008_minfm (double * vars, double * params) {
	return 1.000000 / (1.000000 + exp((vars[NM_NOWOTNY_ET_AL_2008_VAXON] - params[NM_NOWOTNY_ET_AL_2008_VMM]) / params[NM_NOWOTNY_ET_AL_2008_SMM]));
}

double nm_nowotny_et_al_2008_km (double * vars, double * params) {
	return params[NM_NOWOTNY_ET_AL_2008_KMM] * (1.000000 / (1.000000 + exp((vars[NM_NOWOTNY_ET_AL_2008_VAXON] - params[NM_NOWOTNY_ET_AL_2008_VKMM]) / params[NM_NOWOTNY_ET_AL_2008_SKMM])));
}

double nm_nowotny_et_al_2008_mm (double * vars, double * params) {
	double minfm = nm_nowotny_et_al_2008_minfm(vars, params);
	double km = nm_nowotny_et_al_2008_km(vars, params);
	return (minfm - vars[NM_NOWOTNY_ET_AL_2008_MM]) * km;
}

double nm_nowotny_et_al_2008_ila (double * vars, double * params) {
	return params[NM_NOWOTNY_ET_AL_2008_GLA] * (vars[NM_NOWOTNY_ET_AL_2008_VAXON] - params[NM_NOWOTNY_ET_AL_2008_VL]) * params[NM_NOWOTNY_ET_AL_2008_AREAAXON];
}

double nm_nowotny_et_al_2008_ivv (double * vars, double * params) {
	return params[NM_NOWOTNY_ET_AL_2008_GVV] * (vars[NM_NOWOTNY_ET_AL_2008_V] - vars[NM_NOWOTNY_ET_AL_2008_VAXON]);
}

double nm_nowotny_et_al_2008_Vaxon (double * vars, double * params) {
	double ina = nm_nowotny_et_al_2008_ina(vars, params);
	double ikd = nm_nowotny_et_al_2008_ikd(vars, params);
	double im = nm_nowotny_et_al_2008_im(vars, params);
	double ila = nm_nowotny_et_al_2008_ila(vars, params);
	double ivv = nm_nowotny_et_al_2008_ivv(vars, params);
	return (-ina - ikd - im - ila + ivv) / params[NM_NOWOTNY_ET_AL_2008_CMA];
}

double nm_nowotny_et_al_2008_ica (double * vars, double * params) {
	return (vars[NM_NOWOTNY_ET_AL_2008_MCAT] * vars[NM_NOWOTNY_ET_AL_2008_HCAT] * params[NM_NOWOTNY_ET_AL_2008_GCAT] + vars[NM_NOWOTNY_ET_AL_2008_MCAS] * params[NM_NOWOTNY_ET_AL_2008_GCAS]) * params[NM_NOWOTNY_ET_AL_2008_PCA] * vars[NM_NOWOTNY_ET_AL_2008_V] * (vars[NM_NOWOTNY_ET_AL_2008_CA] * exp(vars[NM_NOWOTNY_ET_AL_2008_V] / params[NM_NOWOTNY_ET_AL_2008_RTF]) - params[NM_NOWOTNY_ET_AL_2008_CAOUT]) / (exp(vars[NM_NOWOTNY_ET_AL_2008_V] / params[NM_NOWOTNY_ET_AL_2008_RTF]) - 1.000000) * params[NM_NOWOTNY_ET_AL_2008_AREASOMA];
}

double nm_nowotny_et_al_2008_minfcat (double * vars, double * params) {
	return 1.000000 / (1.000000 + exp((vars[NM_NOWOTNY_ET_AL_2008_V] - params[NM_NOWOTNY_ET_AL_2008_VMCAT]) / params[NM_NOWOTNY_ET_AL_2008_SMCAT]));
}

double nm_nowotny_et_al_2008_mcat (double * vars, double * params) {
	double minfcat = nm_nowotny_et_al_2008_minfcat(vars, params);
	return (minfcat - vars[NM_NOWOTNY_ET_AL_2008_MCAT]) * params[NM_NOWOTNY_ET_AL_2008_KMCAT];
}

double nm_nowotny_et_al_2008_hinfcat (double * vars, double * params) {
	return 1.000000 / (1.000000 + exp((vars[NM_NOWOTNY_ET_AL_2008_V] - params[NM_NOWOTNY_ET_AL_2008_VHCAT]) / params[NM_NOWOTNY_ET_AL_2008_SHCAT]));
}

double nm_nowotny_et_al_2008_hcat (double * vars, double * params) {
	double hinfcat = nm_nowotny_et_al_2008_hinfcat(vars, params);
	return (hinfcat - vars[NM_NOWOTNY_ET_AL_2008_HCAT]) * params[NM_NOWOTNY_ET_AL_2008_KHCAT] * (1.000000 / (1.000000 + exp((vars[NM_NOWOTNY_ET_AL_2008_V] - params[NM_NOWOTNY_ET_AL_2008_VKHCAT]) / params[NM_NOWOTNY_ET_AL_2008_SKHCAT])));
}

double nm_nowotny_et_al_2008_minfcas (double * vars, double * params) {
	return 1.000000 / (1.000000 + exp((vars[NM_NOWOTNY_ET_AL_2008_V] - params[NM_NOWOTNY_ET_AL_2008_VMCAS]) / params[NM_NOWOTNY_ET_AL_2008_SMCAS]));
}

double nm_nowotny_et_al_2008_mcas (double * vars, double * params) {
	double minfcas = nm_nowotny_et_al_2008_minfcas(vars, params);
	return (minfcas - vars[NM_NOWOTNY_ET_AL_2008_MCAS]) * params[NM_NOWOTNY_ET_AL_2008_KMCAS];
}

double nm_nowotny_et_al_2008_Ca (double * vars, double * params) {
	double ica = nm_nowotny_et_al_2008_ica(vars, params);
	return -params[NM_NOWOTNY_ET_AL_2008_CICA] * ica - params[NM_NOWOTNY_ET_AL_2008_KCA] * (vars[NM_NOWOTNY_ET_AL_2008_CA] - params[NM_NOWOTNY_ET_AL_2008_CA0]);
}

double nm_nowotny_et_al_2008_ikca (double * vars, double * params) {
	return vars[NM_NOWOTNY_ET_AL_2008_MKCA] * vars[NM_NOWOTNY_ET_AL_2008_HKCA] * params[NM_NOWOTNY_ET_AL_2008_GKCA] * (vars[NM_NOWOTNY_ET_AL_2008_V] - params[NM_NOWOTNY_ET_AL_2008_VKCA]) * params[NM_NOWOTNY_ET_AL_2008_AREASOMA];
}

double nm_nowotny_et_al_2008_kca_aux1 (double * vars, double * params) {
	return 1.000000 / (1.000000 + exp((vars[NM_NOWOTNY_ET_AL_2008_V] - (params[NM_NOWOTNY_ET_AL_2008_VMKCA1] - params[NM_NOWOTNY_ET_AL_2008_F] * vars[NM_NOWOTNY_ET_AL_2008_CA])) / params[NM_NOWOTNY_ET_AL_2008_SMKCA1]));
}

double nm_nowotny_et_al_2008_kca_aux2 (double * vars, double * params) {
	return 1.000000 / (1.000000 + exp((vars[NM_NOWOTNY_ET_AL_2008_V] - (params[NM_NOWOTNY_ET_AL_2008_VMKCA2] - params[NM_NOWOTNY_ET_AL_2008_F] * vars[NM_NOWOTNY_ET_AL_2008_CA])) / params[NM_NOWOTNY_ET_AL_2008_SMKCA2]));
}

double nm_nowotny_et_al_2008_minfkca (double * vars, double * params) {
	double kca_aux1 = nm_nowotny_et_al_2008_kca_aux1(vars, params);
	double kca_aux2 = nm_nowotny_et_al_2008_kca_aux2(vars, params);
	return kca_aux1 * kca_aux2 * (vars[NM_NOWOTNY_ET_AL_2008_CA] / (params[NM_NOWOTNY_ET_AL_2008_CMKCA] + vars[NM_NOWOTNY_ET_AL_2008_CA]));
}

double nm_nowotny_et_al_2008_mkca (double * vars, double * params) {
	double minfkca = nm_nowotny_et_al_2008_minfkca(vars, params);
	return (minfkca - vars[NM_NOWOTNY_ET_AL_2008_MKCA]) * params[NM_NOWOTNY_ET_AL_2008_KMKCA];
}

double nm_nowotny_et_al_2008_hinfkca (double * vars, double * params) {
	return params[NM_NOWOTNY_ET_AL_2008_CHKCA1] / (params[NM_NOWOTNY_ET_AL_2008_CHKCA2] + vars[NM_NOWOTNY_ET_AL_2008_CA]);
}

double nm_nowotny_et_al_2008_hkca (double * vars, double * params) {
	double hinfkca = nm_nowotny_et_al_2008_hinfkca(vars, params);
	return (hinfkca - vars[NM_NOWOTNY_ET_AL_2008_HKCA]) * params[NM_NOWOTNY_ET_AL_2008_KHKCA];
}

double nm_nowotny_et_al_2008_ia (double * vars, double * params) {
	double a = nm_nowotny_et_al_2008_a(vars, params);
	return vars[NM_NOWOTNY_ET_AL_2008_MA]*vars[NM_NOWOTNY_ET_AL_2008_MA]*vars[NM_NOWOTNY_ET_AL_2008_MA] * params[NM_NOWOTNY_ET_AL_2008_GA] * (vars[NM_NOWOTNY_ET_AL_2008_V] - params[NM_NOWOTNY_ET_AL_2008_VA]) * (a * vars[NM_NOWOTNY_ET_AL_2008_HA1] + (1.000000 - a) * vars[NM_NOWOTNY_ET_AL_2008_HA2]) * params[NM_NOWOTNY_ET_AL_2008_AREASOMA];
}

double nm_nowotny_et_al_2008_a (double * vars, double * params) {
	return 1.000000 / (1.000000 + exp((vars[NM_NOWOTNY_ET_AL_2008_V] - params[NM_NOWOTNY_ET_AL_2008_VAA]) / params[NM_NOWOTNY_ET_AL_2008_SAA]));
}

double nm_nowotny_et_al_2008_minfa (double * vars, double * params) {
	return 1.000000 / (1.000000 + exp((vars[NM_NOWOTNY_ET_AL_2008_V] - params[NM_NOWOTNY_ET_AL_2008_VMA]) / params[NM_NOWOTNY_ET_AL_2008_SMA]));
}

double nm_nowotny_et_al_2008_ma (double * vars, double * params) {
	double minfa = nm_nowotny_et_al_2008_minfa(vars, params);
	return (minfa - vars[NM_NOWOTNY_ET_AL_2008_MA]) * params[NM_NOWOTNY_ET_AL_2008_KMA];
}

double nm_nowotny_et_al_2008_hinfa (double * vars, double * params) {
	return 1.000000 / (1.000000 + exp((vars[NM_NOWOTNY_ET_AL_2008_V] - params[NM_NOWOTNY_ET_AL_2008_VHA]) / params[NM_NOWOTNY_ET_AL_2008_SHA]));
}

double nm_nowotny_et_al_2008_ha1 (double * vars, double * params) {
	double hinfa = nm_nowotny_et_al_2008_hinfa(vars, params);
	return (hinfa - vars[NM_NOWOTNY_ET_AL_2008_HA1]) * params[NM_NOWOTNY_ET_AL_2008_KHA1];
}

double nm_nowotny_et_al_2008_ha2 (double * vars, double * params) {
	double hinfa = nm_nowotny_et_al_2008_hinfa(vars, params);
	return (hinfa - vars[NM_NOWOTNY_ET_AL_2008_HA2]) * params[NM_NOWOTNY_ET_AL_2008_KHA2] * (1.000000 / (1.000000 + exp((vars[NM_NOWOTNY_ET_AL_2008_V] - params[NM_NOWOTNY_ET_AL_2008_VKHA2]) / params[NM_NOWOTNY_ET_AL_2008_SKHA2])));
}

double nm_nowotny_et_al_2008_ih (double * vars, double * params) {
	return vars[NM_NOWOTNY_ET_AL_2008_MH] * params[NM_NOWOTNY_ET_AL_2008_GH] * (vars[NM_NOWOTNY_ET_AL_2008_V] - params[NM_NOWOTNY_ET_AL_2008_VH]) * params[NM_NOWOTNY_ET_AL_2008_AREASOMA];
}

double nm_nowotny_et_al_2008_minfh (double * vars, double * params) {
	return 1.000000 / (1.000000 + exp((vars[NM_NOWOTNY_ET_AL_2008_V] - params[NM_NOWOTNY_ET_AL_2008_VMH]) / params[NM_NOWOTNY_ET_AL_2008_SMH]));
}

double nm_nowotny_et_al_2008_mh (double * vars, double * params) {
	double minfh = nm_nowotny_et_al_2008_minfh(vars, params);
	return (minfh - vars[NM_NOWOTNY_ET_AL_2008_MH]) * (params[NM_NOWOTNY_ET_AL_2008_KMH] / (1.000000 / (1.000000 + exp((vars[NM_NOWOTNY_ET_AL_2008_V] - params[NM_NOWOTNY_ET_AL_2008_VKMH]) / params[NM_NOWOTNY_ET_AL_2008_SKMH]))));
}

double nm_nowotny_et_al_2008_ils (double * vars, double * params) {
	return params[NM_NOWOTNY_ET_AL_2008_GLS] * (vars[NM_NOWOTNY_ET_AL_2008_V] - params[NM_NOWOTNY_ET_AL_2008_VL]) * params[NM_NOWOTNY_ET_AL_2008_AREASOMA];
}

double nm_nowotny_et_al_2008_V (double * vars, double * params) {
	double ica = nm_nowotny_et_al_2008_ica(vars, params);
	double ikca = nm_nowotny_et_al_2008_ikca(vars, params);
	double ia = nm_nowotny_et_al_2008_ia(vars, params);
	double ih = nm_nowotny_et_al_2008_ih(vars, params);
	double ils = nm_nowotny_et_al_2008_ils(vars, params);
	double ivv = nm_nowotny_et_al_2008_ivv(vars, params);
	return (-ica - ikca - ia - ih - ils - ivv + (params[NM_NOWOTNY_ET_AL_2008_I] + params[NM_NOWOTNY_ET_AL_2008_IOFFSET] - params[NM_NOWOTNY_ET_AL_2008_SYN]) * params[NM_NOWOTNY_ET_AL_2008_ISCALE]) / params[NM_NOWOTNY_ET_AL_2008_CMS];
}

/**
 * @brief Nowotny_et_al_2008 neuron model differential equations.
 * @param[in] vars Neuron model variables
 * @param[out] ret Return values array
 * @param[in] params Neuron models parameters
 * @param[in] syn Synapse input current value
 */

void nm_nowotny_et_al_2008_f (double * vars, double * ret, double * params, double syn) {
	params[NM_NOWOTNY_ET_AL_2008_SYN] = syn;

	ret[NM_NOWOTNY_ET_AL_2008_MNA] = nm_nowotny_et_al_2008_mna(vars, params);
	ret[NM_NOWOTNY_ET_AL_2008_HNA] = nm_nowotny_et_al_2008_hna(vars, params);
	ret[NM_NOWOTNY_ET_AL_2008_MKD] = nm_nowotny_et_al_2008_mkd(vars, params);
	ret[NM_NOWOTNY_ET_AL_2008_MM] = nm_nowotny_et_al_2008_mm(vars, params);
	ret[NM_NOWOTNY_ET_AL_2008_VAXON] = nm_nowotny_et_al_2008_Vaxon(vars, params);
	ret[NM_NOWOTNY_ET_AL_2008_MCAT] = nm_nowotny_et_al_2008_mcat(vars, params);
	ret[NM_NOWOTNY_ET_AL_2008_HCAT] = nm_nowotny_et_al_2008_hcat(vars, params);
	ret[NM_NOWOTNY_ET_AL_2008_MCAS] = nm_nowotny_et_al_2008_mcas(vars, params);
	ret[NM_NOWOTNY_ET_AL_2008_CA] = nm_nowotny_et_al_2008_Ca(vars, params);
	ret[NM_NOWOTNY_ET_AL_2008_MKCA] = nm_nowotny_et_al_2008_mkca(vars, params);
	ret[NM_NOWOTNY_ET_AL_2008_HKCA] = nm_nowotny_et_al_2008_hkca(vars, params);
	ret[NM_NOWOTNY_ET_AL_2008_MA] = nm_nowotny_et_al_2008_ma(vars, params);
	ret[NM_NOWOTNY_ET_AL_2008_HA1] = nm_nowotny_et_al_2008_ha1(vars, params);
	ret[NM_NOWOTNY_ET_AL_2008_HA2] = nm_nowotny_et_al_2008_ha2(vars, params);
	ret[NM_NOWOTNY_ET_AL_2008_MH] = nm_nowotny_et_al_2008_mh(vars, params);
	ret[NM_NOWOTNY_ET_AL_2008_V] = nm_nowotny_et_al_2008_V(vars, params);
}

/**
 * @brief Nowotny_et_al_2008 neuron model.
 * @param[in] nm Neuron model structure
 * @param[in] syn Synapse input current value
 */

void nm_nowotny_et_al_2008 (neuron_model nm, double syn) {
	nm.method(nm_nowotny_et_al_2008_f, nm.dim, nm.params[NM_NOWOTNY_ET_AL_2008_DT], nm.vars, nm.params, syn);
	return;
}

/**
 * @brief Initializes Nowotny_et_al_2008 neuron model.
 * @param[in] nm Pointer to the neuron model structure
 * @param[in] vars Array with the initial values of the model variables
 * @param[in] params Array with the values of the mode parameters
 */

void nm_nowotny_et_al_2008_init (neuron_model * nm, double * vars, double * params) {
	nm->dim = 16;
	nm->vars = (double *) malloc (sizeof(double) * nm->dim);
	copy_1d_array(vars, nm->vars, nm->dim);

	nm->n_params = 75;
	nm->params = (double *) malloc (sizeof(double) * nm->n_params);
	copy_1d_array(params, nm->params, nm->n_params);

    nm->max = -32;
    nm->min = -67;
	nm->pts_burst = -1.0;

	nm->func = &nm_nowotny_et_al_2008;
	nm->set_pts_burst = &nm_nowotny_et_al_2008_set_pts_burst;
	nm->method = integration_method_selector(params[NM_NOWOTNY_ET_AL_2008_DT]);

	return;
}

/**
 * @brief Sets Nowotny_et_al_2008 model number of points per burst and integration step.
 * 
 * If not previously specified by the user, the number of points per burst of the model and its integration step is set according to the living neuron number of points per burst.
 * @param[in] pts_live Number of points in a living neuron burst
 * @param[in] nm Pointer to the neuron model structure
 */

double nm_nowotny_et_al_2008_set_pts_burst (double pts_live, neuron_model * nm) {
	int length = 0;
	int method = nm->params[NM_NOWOTNY_ET_AL_2008_DT];

	switch(method) {
		case EULER:
		{
			length = 109.000000-22;
			double dts[] = {/*0.005100, 0.005200, 0.005300, 0.005400, 0.005500, 0.005600, 0.005700, 0.005800, 0.005900, 0.006000, 0.006100, 0.006300, 0.006500, 0.006700, 0.006900, 0.007100, 0.007300, 0.007500, 0.007700, 0.007900, 0.008100, 0.008200,*/ 0.008400, 0.008700, 0.009000, 0.009300, 0.009600, 0.009900, 0.010300, 0.010700, 0.011100, 0.011300, 0.011800, 0.012300, 0.012800, 0.013400, 0.014000, 0.014500, 0.015300, 0.016100, 0.017000, 0.017900, 0.019000, 0.020200, 0.021700, 0.023300, 0.025200, 0.027400, 0.030000, 0.030300, 0.030700, 0.031100, 0.031500, 0.031800, 0.032200, 0.032600, 0.033100, 0.033500, 0.033900, 0.034300, 0.034700, 0.035100, 0.035600, 0.036100, 0.036600, 0.037100, 0.037600, 0.038100, 0.038600, 0.039100, 0.039700, 0.040300, 0.040800, 0.041400, 0.042000, 0.042600, 0.043200, 0.043800, 0.044500, 0.045200, 0.045900, 0.046600, 0.047400, 0.048200, 0.049000, 0.049800, 0.050700, 0.051600, 0.052500, 0.053500, 0.054500, 0.055500, 0.056600, 0.057700, 0.058900, 0.060100, 0.061400, 0.062700, 0.064100, 0.065500, 0.067000, 0.068600, 0.070200, 0.071900, 0.073800, 0.075700, 0.077700, 0.079600, 0.081100};
			double pts[] = {/*807704.000000, 763097.000000, 739535.000000, 712325.000000, 699420.000000, 686964.000000, 674934.000000, 660234.000000, 649064.000000, 638264.000000, 627814.000000, 607911.000000, 589229.000000, 571659.000000, 555104.000000, 539478.000000, 524707.000000, 510722.000000, 497461.000000, 484871.000000, 472902.000000, 407920.500000, 397119.000000,*/ 383381.000000, 370557.000000, 358561.000000, 347314.000000, 336748.000000, 323617.000000, 311468.000000, 300193.500000, 283446.666667, 271366.333333, 260268.000000, 250036.666667, 238766.333333, 228461.666667, 216408.000000, 204999.250000, 194724.000000, 184319.750000, 173145.000000, 163009.600000, 152173.666667, 141516.500000, 131046.428571, 121007.428571, 110769.750000, 100729.444444, 99711.555556, 98385.000000, 97092.222222, 95832.333333, 94713.900000, 93509.700000, 92333.400000, 91091.400000, 89983.900000, 88900.400000, 87841.500000, 86655.000000, 85644.727273, 84413.727273, 83216.818182, 82097.181818, 80963.727273, 79740.416667, 78667.166667, 77621.416667, 76602.583333, 75413.916667, 74260.500000, 73232.076923, 72140.923077, 71080.692308, 70050.307692, 69049.307692, 68000.714286, 66898.214286, 65830.214286, 64795.428571, 63730.066667, 62619.733333, 61545.933333, 60457.750000, 59453.750000, 58361.937500, 57309.625000, 56250.764706, 55161.941176, 54114.882353, 53069.444444, 52000.222222, 50947.157895, 49869.157895, 48841.263158, 47745.000000, 46717.750000, 45646.428571, 44638.476190, 43598.954545, 42546.863636, 41543.173913, 40519.958333, 39471.333333, 38447.160000, 37416.807692, 36411.115385, 35246.111111};

			select_dt_neuron_model(dts, pts, length, pts_live, &(nm->params[NM_NOWOTNY_ET_AL_2008_DT]), &(nm->pts_burst));
			break;
		}
		case HEUN:
		{
			length = 103.000000-21;
			double dts[] = {/*0.005100, 0.005200, 0.005300, 0.005500, 0.005600, 0.005700, 0.005800, 0.005900, 0.006000, 0.006100, 0.006200, 0.006400, 0.006600, 0.006800, 0.007000, 0.007200, 0.007400, 0.007600, 0.007800, 0.008000, 0.008200,*/ 0.008400, 0.008700, 0.009000, 0.009300, 0.009600, 0.009900, 0.010300, 0.010700, 0.011100, 0.011400, 0.011900, 0.012400, 0.012900, 0.013500, 0.014100, 0.014600, 0.015400, 0.016200, 0.017100, 0.018000, 0.019200, 0.020400, 0.021900, 0.023500, 0.025500, 0.027800, 0.030500, 0.030900, 0.031300, 0.031700, 0.032100, 0.032400, 0.032800, 0.033200, 0.033600, 0.034000, 0.034400, 0.034800, 0.035300, 0.035800, 0.036300, 0.036800, 0.037300, 0.037800, 0.038300, 0.038800, 0.039300, 0.039900, 0.040500, 0.041100, 0.041700, 0.042300, 0.042900, 0.043500, 0.044200, 0.044900, 0.045600, 0.046300, 0.047100, 0.047900, 0.048700, 0.049500, 0.050400, 0.051300, 0.052200, 0.053200, 0.054200, 0.055200, 0.056300, 0.057400, 0.058600, 0.059800, 0.061000, 0.062300, 0.063600, 0.065000, 0.066400, 0.067900, 0.069400, 0.070900, 0.072300, 0.074300};
			double pts[] = {/*802802.000000, 788294.000000, 743632.000000, 703970.000000, 691390.000000, 676124.000000, 664463.000000, 653196.000000, 642303.000000, 631761.000000, 621567.000000, 602142.000000, 583895.000000, 566722.000000, 550529.000000, 535236.000000, 520770.000000, 507065.000000, 494064.000000, 481712.000000, 469963.000000, 400639.000000,*/ 386824.000000, 373930.000000, 361868.500000, 350560.000000, 339937.500000, 326736.500000, 314522.500000, 303188.000000, 283880.333333, 271953.666667, 260988.333333, 250873.333333, 239724.333333, 229524.333333, 217363.500000, 206073.500000, 195898.500000, 185590.000000, 174406.000000, 163508.200000, 152842.166667, 142377.333333, 132077.142857, 121723.714286, 111294.500000, 101204.888889, 99896.222222, 98620.666667, 97377.777778, 96165.666667, 95099.900000, 93941.500000, 92811.000000, 91707.500000, 90630.000000, 89578.000000, 88549.600000, 87297.000000, 85954.363636, 84772.090909, 83622.545455, 82503.454545, 81414.272727, 80353.181818, 79226.833333, 78220.916667, 77047.083333, 75908.333333, 74803.000000, 73658.307692, 72616.307692, 71603.230769, 70587.461538, 69473.153846, 68340.785714, 67295.357143, 66281.928571, 65160.142857, 64034.533333, 62987.200000, 61974.266667, 60873.000000, 59777.312500, 58752.750000, 57654.750000, 56570.058824, 55552.529412, 54474.764706, 53415.722222, 52328.444444, 51266.157895, 50262.315789, 49217.368421, 48194.800000, 47150.950000, 46127.857143, 45080.666667, 44059.090909, 43004.409091, 41985.478261, 40973.434783};

			select_dt_neuron_model(dts, pts, length, pts_live, &(nm->params[NM_NOWOTNY_ET_AL_2008_DT]), &(nm->pts_burst));
			break;
		}
		case RK4:
		{
			length = 111.000000-21;
			double dts[] = {/*0.005100, 0.005200, 0.005300, 0.005500, 0.005600, 0.005700, 0.005800, 0.005900, 0.006000, 0.006100, 0.006200, 0.006400, 0.006600, 0.006800, 0.007000, 0.007200, 0.007400, 0.007600, 0.007800, 0.008000, 0.008200,*/ 0.008400, 0.008700, 0.009000, 0.009300, 0.009600, 0.009900, 0.010300, 0.010700, 0.011100, 0.011400, 0.011900, 0.012400, 0.012900, 0.013500, 0.014100, 0.014700, 0.015500, 0.016400, 0.017200, 0.018200, 0.019400, 0.020600, 0.022100, 0.023700, 0.025700, 0.028000, 0.030800, 0.031200, 0.031600, 0.032000, 0.032300, 0.032700, 0.033100, 0.033500, 0.033900, 0.034300, 0.034700, 0.035100, 0.035500, 0.036000, 0.036500, 0.037000, 0.037500, 0.038000, 0.038500, 0.039000, 0.039600, 0.040200, 0.040800, 0.041400, 0.042000, 0.042600, 0.043300, 0.044000, 0.044700, 0.045400, 0.046100, 0.046900, 0.047600, 0.048400, 0.049200, 0.050100, 0.051000, 0.051900, 0.052800, 0.053800, 0.054800, 0.055900, 0.057000, 0.058100, 0.059300, 0.060500, 0.061800, 0.063100, 0.064500, 0.065900, 0.067400, 0.069000, 0.070600, 0.072300, 0.074100, 0.076000, 0.078000, 0.080100, 0.082300, 0.084600, 0.087000, 0.089500, 0.092000, 0.094100};
			double pts[] = {/*802795.000000, 788298.000000, 743636.000000, 703976.000000, 691394.000000, 676129.000000, 664468.000000, 653200.000000, 642307.000000, 631766.000000, 621572.000000, 602147.000000, 583900.000000, 566727.000000, 550534.000000, 535242.000000, 520776.000000, 507071.000000, 494070.000000, 481717.000000, 469968.000000, 400636.000000,*/ 386821.500000, 373927.500000, 361865.000000, 350557.000000, 339934.500000, 326733.000000, 314518.500000, 303184.500000, 283873.333333, 271946.000000, 260980.333333, 250864.666667, 239715.333333, 229514.666667, 215872.000000, 204730.250000, 193495.000000, 182498.800000, 172471.200000, 161803.000000, 151336.166667, 141064.500000, 130935.285714, 120745.857143, 110464.625000, 100179.111111, 98894.777778, 97643.000000, 96422.444444, 95349.700000, 94183.300000, 93045.200000, 91934.300000, 90849.500000, 89790.000000, 88755.100000, 87743.700000, 86628.363636, 85425.181818, 84254.909091, 83116.454545, 82008.363636, 80929.363636, 79784.416667, 78761.500000, 77568.250000, 76410.666667, 75287.250000, 74124.230769, 73065.538462, 72036.615385, 70872.076923, 69744.692308, 68597.071429, 67539.714286, 66514.214286, 65379.785714, 64374.533333, 63310.466667, 62281.333333, 61162.866667, 60048.250000, 59007.375000, 58001.875000, 56895.000000, 55857.294118, 54758.588235, 53678.277778, 52662.555556, 51597.555556, 50554.789474, 49492.263158, 48456.400000, 47405.800000, 46385.142857, 45354.333333, 44291.409091, 43278.409091, 42252.043478, 41238.521739, 40190.875000, 39163.480000, 38136.840000, 37110.692308, 36081.111111, 35062.250000, 34032.571429, 33000.931034, 31980.166667};

			select_dt_neuron_model(dts, pts, length, pts_live, &(nm->params[NM_NOWOTNY_ET_AL_2008_DT]), &(nm->pts_burst));
			break;
		}
		case RK65:
		{
			length = 112.000000-21;
			double dts[] = {/*0.005100, 0.005200, 0.005300, 0.005500, 0.005600, 0.005700, 0.005800, 0.005900, 0.006000, 0.006100, 0.006200, 0.006400, 0.006600, 0.006800, 0.007000, 0.007200, 0.007400, 0.007600, 0.007800, 0.008000, 0.008200,*/ 0.008400, 0.008700, 0.009000, 0.009300, 0.009600, 0.009900, 0.010300, 0.010700, 0.011100, 0.011400, 0.011900, 0.012400, 0.012900, 0.013500, 0.014100, 0.014600, 0.015400, 0.016200, 0.017100, 0.018100, 0.019300, 0.020500, 0.022000, 0.023600, 0.025600, 0.027900, 0.030600, 0.031000, 0.031400, 0.031800, 0.032200, 0.032600, 0.033000, 0.033400, 0.033800, 0.034200, 0.034600, 0.035000, 0.035400, 0.035900, 0.036400, 0.036900, 0.037400, 0.037900, 0.038400, 0.038900, 0.039500, 0.040100, 0.040700, 0.041300, 0.041900, 0.042500, 0.043100, 0.043800, 0.044500, 0.045200, 0.045900, 0.046600, 0.047400, 0.048200, 0.049000, 0.049800, 0.050600, 0.051500, 0.052400, 0.053400, 0.054400, 0.055400, 0.056500, 0.057600, 0.058800, 0.060000, 0.061300, 0.062600, 0.064000, 0.065400, 0.066900, 0.068400, 0.070000, 0.071700, 0.073500, 0.075300, 0.077300, 0.079300, 0.081500, 0.083800, 0.086200, 0.088700, 0.091400, 0.094300, 0.097400};
			double pts[] = {/*802795.000000, 788298.000000, 743636.000000, 703976.000000, 691394.000000, 676129.000000, 664468.000000, 653200.000000, 642307.000000, 631766.000000, 621572.000000, 602147.000000, 583900.000000, 566727.000000, 550534.000000, 535242.000000, 520776.000000, 507071.000000, 494070.000000, 481717.000000, 469968.000000, 400636.000000,*/ 386821.500000, 373927.500000, 361865.000000, 350557.000000, 339934.500000, 326733.000000, 314518.500000, 303184.500000, 283873.333333, 271946.000000, 260980.333333, 250864.666667, 239715.333333, 229514.666667, 217350.500000, 206059.500000, 195883.750000, 185574.000000, 173424.200000, 162641.200000, 152074.166667, 141705.500000, 131489.857143, 121217.142857, 110860.125000, 100833.333333, 99532.222222, 98264.333333, 97028.333333, 95823.000000, 94471.500000, 93326.400000, 92208.700000, 91117.500000, 90051.700000, 89010.700000, 87993.400000, 86872.090909, 85662.090909, 84485.454545, 83340.636364, 82226.545455, 81141.636364, 79990.916667, 78962.750000, 77763.333333, 76599.750000, 75470.500000, 74374.083333, 73238.153846, 72204.153846, 71199.076923, 70061.153846, 68903.285714, 67836.214286, 66801.642857, 65798.214286, 64687.714286, 63570.333333, 62532.466667, 61527.933333, 60519.437500, 59461.750000, 58440.375000, 57346.000000, 56262.941176, 55247.294118, 54171.705882, 53113.166667, 52029.166667, 50968.105263, 49887.105263, 48850.947368, 47765.200000, 46742.450000, 45679.619048, 44677.619048, 43643.500000, 42608.363636, 41553.652174, 40550.041667, 39500.583333, 38495.520000, 37448.846154, 36421.500000, 35401.740741, 34398.500000, 33371.379310, 32350.833333, 31330.096774};

			select_dt_neuron_model(dts, pts, length, pts_live, &(nm->params[NM_NOWOTNY_ET_AL_2008_DT]), &(nm->pts_burst));
			break;
		}
    }

	return nm->params[NM_NOWOTNY_ET_AL_2008_DT];
}

///@}
