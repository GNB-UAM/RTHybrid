#ifdef __cplusplus
extern "C" {
#endif

#ifndef SYNAPSE_MODELS_FUNCTIONS_H
#define SYNAPSE_MODELS_FUNCTIONS_H

#include <math.h>
#include "types_clamp.h"


/* MACROS */

#define ELECTRIC 0
#define GOLOWASCH 1
#define PRINZ 2

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


/* STRUCTS */

/* Electrical */

/* Struct to take the params from the GUI to Clamp */	
typedef struct {
    double g[ELEC_N_G];
    int anti;
} syn_elec_args;


/* Struct to take the params from Clamp to RT */	
typedef struct {
    int anti;
} syn_elec_params;


/*Golowash*/

/* Struct to take the params from the GUI to Clamp */	
typedef struct {
    double g[GL_N_G];
    double v_fast;
    double v_slow;
    double k1;
    double k2;
} syn_gl_args;


/* Struct to take the params from Clamp to RT */	
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


/* FUNCTIONS */

void ini_elec (synapse_model * params, double scale, double offset, void * syn_args);

void ini_golowasch (synapse_model * params, double scale, double offset, void * syn_args, double dt, double min, double max);

void ini_prinz (double ** params, double scale, double offset, double k, double vth, double dt, double period, double min, double max);

void elec_syn (double v_post, double v_pre, synapse_model * params, double * ret);

void golowasch_syn (double v_post, double v_pre, synapse_model * params, double * ret);

void prinz_syn (double v_post, double v_pre, synapse_model * params, double * ret);


#endif // SYNAPSE_MODELS_FUNCTIONS_H


#ifdef __cplusplus
}
#endif