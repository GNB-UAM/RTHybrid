#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* MACROS */

#define IZHIKEVICH 0
#define HR 1
#define RLK 2
#define ELECTRIC 0
#define CHEMICAL 1

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
#define G_FAST 0
#define G_SLOW 1

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


/* INTEGRATION FUNCTIONS */
void runge_kutta_6 (void (*f) (double *, double *, double *, double), int dim, double dt, double * vars, double * params, double syn);

/* SYNAPSES */
void elec_syn (double v_post, double v_pre, double * g, double * ret, double * aux);

void chem_syn (double v_post, double v_pre, double * g, double * ret, double * aux);

/* IZHIKEVICH */
void izh_f (double * vars, double * ret, double * params, double syn);

void izhikevich (int dim, double dt, double * vars, double * params, double syn);

void ini_iz (double *min, double *minABS, double *max);


/* HINDMARSH-ROSE */
void hr_f (double * vars, double * ret, double * params, double syn);

void hindmarsh_rose (int dim, double dt, double * vars, double * params, double syn);

void ini_hr (double *min, double *minABS, double *max);

/* HINDMARSH-ROSE */
void rlk_f (double * vars, double * ret, double * params, double syn);

void rulkov_map (int dim, double dt, double * vars, double * params, double syn);

void ini_rlk (double *min, double *minABS, double *max);
