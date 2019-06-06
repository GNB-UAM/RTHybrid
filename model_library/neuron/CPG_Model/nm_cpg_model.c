#include "nm_cpg_model.h"
#include "../../integration_methods.h"
#include "../neuron_models_aux_functions.h"

#include "../Komendantov_Kononenko_1996/nm_komendantov_kononenko_1996.h"
#include "../../synapse/Golowasch_et_al_1999/sm_golowasch_et_al_1999.h"

/**
 * @file nm_cpg_model.h
 * @brief Source file for the CPG_Model model functions.
 */

/** @name CPG_Model
 * CPG_Model neuron model.
 */
///@{

synapse_model sm;

/**
 * @brief CPG_Model neuron model.
 * @param[in] nm Neuron model structure
 * @param[in] syn Synapse input current value
 */

void nm_cpg_model (neuron_model nm, double syn) {
    neuron_model ** neuron_1 = (neuron_model**) &nm.params[0];
    neuron_model ** neuron_2 = (neuron_model**) &nm.params[1];

    double syn_1_2;
    sm.g[GL_G_FAST] = 0.2;
    sm.g[GL_G_SLOW] = 0.0;
    sm.func((*neuron_2)->vars[0], (*neuron_1)->vars[0], &sm, &syn_1_2);

    double syn_2_1;
    sm.g[GL_G_FAST] = 0.0;
    sm.g[GL_G_SLOW] = 0.02;
    sm.func((*neuron_1)->vars[0], (*neuron_2)->vars[0], &sm, &syn_2_1);

    nm_komendantov_kononenko_1996(**neuron_1, syn_2_1 + syn);
    nm_komendantov_kononenko_1996(**neuron_2, syn_1_2);

    nm.vars[0] = (*neuron_1)->vars[0];
    nm.vars[1] = (*neuron_2)->vars[0];

    //printf("%f %f %f %f\n", (*neuron_1)->vars[0], (*neuron_2)->vars[0], syn_1_2, syn_2_1);

	return;
}

/**
 * @brief Initializes CPG_Model neuron model.
 * @param[in] nm Pointer to the neuron model structure
 * @param[in] vars Array with the initial values of the model variables
 * @param[in] params Array with the values of the mode parameters
 */

void nm_cpg_model_init (neuron_model * nm, double * vars, double * params) {
    double g_fast = vars[1];
    double v_fast = vars[2];
    /*double g_slow = vars[3];
    double v_slow = vars[4];*/

    /* Se usa el array de los parametros de neuron_model para guardar punteros a las estructuras de las neuronas del CPG, en vez de doubles */
    nm->params = /*(double *)*/ malloc (sizeof(neuron_model*) * 2);

    /* Como no se puede hacer casting de double a puntero hay que sacar el puntero a cada posición del array y hacerle el casting a neuron_model**
     * y después guardar en el contenido el puntero a la estructura del modelo, reservando espacio con malloc*/
    neuron_model ** neuron_1 = (neuron_model**) &nm->params[0];
    neuron_model ** neuron_2 = (neuron_model**) &nm->params[1];
    *neuron_1 = (neuron_model*) malloc (sizeof (neuron_model));
    *neuron_2 = (neuron_model*) malloc (sizeof (neuron_model));

    nm_komendantov_kononenko_1996_init(*neuron_1, vars, params);
    nm_komendantov_kononenko_1996_init(*neuron_2, vars, params);

    nm->vars = (double *) malloc (sizeof(double) * 2);
    nm->vars[0] = vars[0];
    nm->vars[1] = vars[0];

    nm->set_pts_burst = &nm_cpg_model_set_pts_burst;
    nm->func = &nm_cpg_model;
    nm->min = (*neuron_1)->min;
    nm->max = (*neuron_1)->max;
    nm->type = (*neuron_1)->type;


    /* Sinapsis */
    sm.type_params = (syn_gl_params *) malloc (sizeof(syn_gl_params));
    syn_gl_params * aux_gl_params = sm.type_params;

    sm.calibrate = SYN_CALIB_PRE;
    aux_gl_params->k1 = 1;
    aux_gl_params->k2 = 0.03;
    aux_gl_params->v_fast = v_fast/100.0;
    aux_gl_params->v_slow = 15.0/100.0;
    aux_gl_params->ms_old = 0.0;
    aux_gl_params->s_fast = 5.0/100.0;
    aux_gl_params->s_slow = 1.0/100.0;

    sm.offset = 0;
    sm.scale = 1;
    aux_gl_params->min = -55;
    aux_gl_params->max = 40;
    aux_gl_params->dt = (*neuron_1)->params[NM_KOMENDANTOV_KONONENKO_1996_DT];
    aux_gl_params->method = (*neuron_1)->method;

    sm.g = (double *) malloc (sizeof(double) * GL_N_G);
    sm.g[GL_G_FAST] = g_fast;
    sm.g[GL_G_SLOW] = 0.2;

    sm.func = &sm_golowasch_et_al_1999;

	return;
}

/**
 * @brief Sets CPG_Model model number of points per burst and integration step.
 * 
 * If not previously specified by the user, the number of points per burst of the model and its integration step is set according to the living neuron number of points per burst.
 * @param[in] pts_live Number of points in a living neuron burst
 * @param[in] nm Pointer to the neuron model structure
 * @return Integration step, default -1
 */

double nm_cpg_model_set_pts_burst (double pts_live, neuron_model * nm) {
    neuron_model ** neuron_1 = (neuron_model**) &nm->params[0];
    neuron_model ** neuron_2 = (neuron_model**) &nm->params[1];

    nm_komendantov_kononenko_1996_set_pts_burst(pts_live, *neuron_1);
    nm_komendantov_kononenko_1996_set_pts_burst(pts_live, *neuron_2);

    nm->pts_burst = (*neuron_1)->pts_burst;
    nm->method = (*neuron_1)->method;

    return (*neuron_1)->params[NM_KOMENDANTOV_KONONENKO_1996_DT];
}

///@}
