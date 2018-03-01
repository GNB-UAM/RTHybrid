#ifdef __cplusplus
extern "C" {
#endif

#ifndef MODEL_LIBRARY_H
#define MODEL_LIBRARY_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "types_clamp.h"


/* MACROS */

#define IZHIKEVICH 0
#define HR 1
#define RLK 2
#define ELECTRIC 0
#define GOLOWASCH 1
#define PRINZ 2

#define X 0
#define Y 1
#define Z 2

/*Izhikevich*/
#define I_IZ 0
#define A_IZ 1
#define B_IZ 2
#define C_IZ 3
#define D_IZ 4

/*Hindmarsh-Rose*/
#define I_HR 0
#define R_HR 1
#define S_HR 2

/*Rulkov Map*/
#define I_RLK 0
#define ALPHA_RLK 1
#define MU_RLK 2
#define SIGMA_RLK 3
#define J_RLK 4
#define OLD_RLK 5
#define PTS_RLK 6
#define INTER_RLK 7

/*Synapses*/

/* General */
#define SYN_MODEL_TO_LIVE 0
#define SYN_LIVE_TO_MODEL 1

#define SYN_SCALE 0
#define SYN_OFFSET 1
#define SYN_CALIBRATE 2

#define SYN_CALIB_PRE 0
#define SYN_CALIB_POST 1

/* Electrical */
#define ELEC_N_G 1
#define ELEC_G 0

#define ELEC_ANTI 3

/*Golowash*/
#define GL_G_FAST 0
#define GL_G_SLOW 1
#define GL_N_G 2

#define GL_MIN 3
#define GL_MAX 4
#define GL_K1 5
#define GL_K2 6
#define GL_DT 7
#define GL_VFAST 8
#define GL_VSLOW 9
#define GL_PERIOD 10
#define GL_MS_OLD 11


#define MS_K1 0
#define MS_K2 1
#define MS_SS 2
#define MS_VS 3

#define SC_DT 0
#define SC_MIN 1
#define SC_OLD 2
#define SC_BT 3
#define SC_MS_K1 4
#define SC_MS_K2 5
#define SC_VSLOW 6
#define SC_VFAST 7
#define SC_MAX 8

/*Prinz*/
#define PR_AUX_VPRE 0
#define PR_AUX_VTH 1
#define PR_AUX_DELTA 2
#define PR_AUX_K 3

#define PR_MIN 3
#define PR_MAX 4
#define PR_S_OLD 5
#define PR_K 6
#define PR_DT 7
#define PR_VTH 8
#define PR_PERIOD 9

/* Neuron model struct */
typedef struct {
    void (*func)(int, double, double*, double*, double);
    void (*ini)(double, double*);
    void (*min_max)(double*, double*, double*);
    unsigned int type;
    unsigned int dim;
    unsigned int n_params;
    double * vars;
    double * params;
    double min;
    double max;
    double pts_burst;
}

/* STRUCTS */
typedef struct {
    double g[ELEC_N_G];
    int anti;
} syn_elec_args;

typedef struct {
    double g[GL_N_G];
    double v_fast;
    double v_slow;
    double k1;
    double k2;
} syn_gl_args;

typedef struct {
    int anti;
} syn_elec_params;

typedef struct {
    double min;
    double max;
    double k1;
    double k2;
    double v_fast;
    double v_slow;
    double ms_old;
    double dt;
} syn_gl_params;


/* AUXILIAR FUNCTIONS */
void free_synapse (syn_params * params);

/* INTEGRATION FUNCTIONS */
void runge_kutta_6 (void (*f) (double *, double *, double *, double), int dim, double dt, double * vars, double * params, double syn);

/* SYNAPSES */
void ini_elec (syn_params * params, double scale, double offset, void * syn_args);

void ini_golowasch (syn_params * params, double scale, double offset, void * syn_args, double dt, double min, double max);

void ini_prinz (double ** params, double scale, double offset, double k, double vth, double dt, double period, double min, double max);

void elec_syn (double v_post, double v_pre, syn_params * params, double * ret);

void golowasch_syn (double v_post, double v_pre, syn_params * params, double * ret);

void prinz_syn (double v_post, double v_pre, syn_params * params, double * ret);

/* IZHIKEVICH */
void izh_f (double * vars, double * ret, double * params, double syn);

void izhikevich (int dim, double dt, double * vars, double * params, double syn);

void ini_iz (double pts_live, double * pts_model);

void min_max_iz (double *min, double *minABS, double *max);

/* HINDMARSH-ROSE */
void hr_f (double * vars, double * ret, double * params, double syn);

void hindmarsh_rose (int dim, double dt, double * vars, double * params, double syn);

void ini_hr (double pts_live, double * pts_model);

void min_max_hr (double *min, double *minABS, double *max);

/* RULKOV */
void rlk_f (double * vars, double * ret, double * params, double syn);

void rulkov_map (int dim, double dt, double * vars, double * params, double syn);

void ini_rlk (double pts_live, double * pts_model);

void min_max_rlk (double *min, double *minABS, double *max);

#endif // MODEL_LIBRARY_H


#ifdef __cplusplus
}
#endif
