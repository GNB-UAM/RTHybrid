#include "../includes/neuron_models_functions.h"

/* General functions */

void init_neuron_model (neuron_model * nm, int model) {
    nm->type = model;

    switch (model) {
        case IZ:
            nm->dim = 2;
            nm->vars = (double *) malloc (sizeof(double) * nm->dim);
            copy_1d_array(args->vars, nm->vars, nm->dim);

            nm->n_params = 6;
            nm->params = (double *) malloc (sizeof(double) * nm->n_params);
            copy_1d_array(args->params, nm->params, nm->params);

            nm->max = 30.240470;
            nm->min = -74.235106;

            nm->func = &izhikevich;
            nm->set_pts_burst = &iz_set_pts_burst;

            break;
        case HR:
            nm->dim = 3;
            nm->vars = (double *) malloc (sizeof(double) * nm->dim);
            copy_1d_array(args->vars, nm->vars, nm->dim);

            nm->n_params = 4;
            nm->params = (double *) malloc (sizeof(double) * nm->n_params);
            copy_1d_array(args->params, nm->params, nm->params);

            nm->max = 1.797032;
            nm->min = -1.608734;

            nm->func = &hindmarsh_rose;
            nm->set_pts_burst = &hr_set_pts_burst;

            break;
        case RLK:
            nm->dim = 2;
            nm->vars = (double *) malloc (sizeof(double) * nm->dim);
            copy_1d_array(args->vars, nm->vars, nm->dim);

            nm->n_params = 8;
            nm->params = (double *) malloc (sizeof(double) * nm->n_params);
            copy_1d_array(args->params, nm->params, nm->params);

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


void free_neuron_model (neuron_model * nm) {
    free_pointers(2, &(nm->vars), &(nm->params));
    return;
}

/* Models functions */

/* IZHIKEVICH */

void izh_f (double * vars, double * ret, double * params, double syn) {
	ret[0] = 0.04 * vars[0]*vars[0] + 5*vars[0] + 140 - vars[1] + params[IZ_I] - syn;
	ret[1] = params[IZ_A] * (params[IZ_B] * vars[0] - vars[1]);

	return;
}


void izhikevich (neuron_model nm, double syn) {
	runge_kutta_6 (izh_f, nm.dim, nm.params[IZ_DT], nm.vars, nm.params, syn);

	if (nm.vars[0] >= 30) {
		nm.vars[0] = nm.params[IZ_C];
		nm.vars[1] += nm.params[IZ_D];
	}

	return;
}

void iz_set_pts_burst (double pts_live, double * pts_model) {
    *pts_model = 59324.0;
    return;
}


/* HINDMARSH-ROSE */

void hr_f (double * vars, double * ret, double * params, double syn) {
    ret[0] = vars[1] + 3.0 * (vars[0]*vars[0]) - (vars[0]*vars[0]*vars[0]) - vars[2] + params[HR_I] - syn;
    ret[1] = 1.0 - 5.0 * (vars[0]*vars[0]) - vars[1];
    ret[2] = (-vars[2] + params[HR_S] * (vars[0] + 1.6)) * params[HR_R];

    return;
}

void hindmarsh_rose (neuron_model nm, double syn) {
	runge_kutta_6 (hr_f, nm.dim, nm.params[HR_DT], nm.vars, nm.params, syn);

	return;
}

void hr_set_pts_burst (double pts_live, double * pts_model) {
    *pts_model = 260166.0;
    return;
}



/* RULKOV MAP */

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

void rulkov_map (neuron_model nm, double syn) {
    double ret[2];

    if (nm.params[RLK_J] >= ((nm.params[RLK_PTS] - 400) / 400)) {

        nm.params[RLK_OLD] = nm.vars[0];
        rlk_f(nm.vars, ret, nm.params, syn);
        nm.params[RLK_J] = 0;
        nm.params[RLK_INTER] = ret[0];

    } else {

        ret[0] = nm.params[RLK_OLD] + (nm.params[RLK_INTER] - nm.params[RLK_OLD]) / ((nm.params[RLK_PTS] - 400) / 400) * nm.params[RLK_J];
        ret[1] = nm.vars[1];
        nm.params[J]++;

    }

    nm.vars[0] = ret[0];
    nm.vars[1] = ret[1];

    return;
}

void rlk_set_pts_burst (double pts_live, double * pts_model) {
    *pts_model = pts_live;
    return;
}