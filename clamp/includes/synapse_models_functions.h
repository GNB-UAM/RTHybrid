#ifdef __cplusplus
extern "C" {
#endif

#ifndef SYNAPSE_MODELS_FUNCTIONS_H
#define SYNAPSE_MODELS_FUNCTIONS_H

#include <math.h>
#include "types_clamp.h"


/* MACROS */

#define EMPTY_SYN 0
#define ELECTRIC 1
#define GOLOWASCH 2

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

#define GL_MS_K1 0
#define GL_MS_K2 1
#define GL_MS_SS 2
#define GL_MS_VS 3


/* General */
void init_synapse_model (synapse_model * sm, int model, void * syn_args);

void free_synapse_model (synapse_model * sm);

 /* Empty */

void empty_syn (double v_post, double v_pre, synapse_model * sm, double * ret);

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


void elec_set_online_params (synapse_model * sm, double scale, double offset);

void elec_syn (double v_post, double v_pre, synapse_model * sm, double * ret);


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


void gl_set_online_params (synapse_model * sm, double scale, double offset, double min, double max);

void golowasch_syn (double v_post, double v_pre, synapse_model * params, double * ret);



#endif // SYNAPSE_MODELS_FUNCTIONS_H


#ifdef __cplusplus
}
#endif