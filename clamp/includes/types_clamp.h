#ifdef __cplusplus
extern "C" {
#endif

#ifndef TYPES_CLAMP_H__
#define TYPES_CLAMP_H__

#include <syslog.h>
#include "../../common/includes/types.h"


/* Neuron model struct */
typedef struct neuron_model neuron_model;

struct neuron_model {
    void (*func)(neuron_model nm, double);
    void (*set_pts_burst)(double, neuron_model * nm);
    unsigned int type;
    unsigned int dim;
    unsigned int n_params;
    double * vars;
    double * params;
    double min;
    double max;
    double pts_burst;
};

/* Synapse model struct */
typedef struct synapse_model synapse_model;

struct synapse_model {
    void (*func)(double, double, synapse_model*, double*);
    unsigned int type;
    double * g;
    double scale;
    double offset;
    unsigned int calibrate;
    void * type_params;
};


/* rt_thread struct */
typedef struct {
    neuron_model nm;
    synapse_model sm_model_to_live;
    synapse_model sm_live_to_model;
    long time_var;
    int before;
    int after;
    int s_points;
    void * msqid;
    int period;
    unsigned int n_in_chan;
    unsigned int n_out_chan;
    int * in_channels;
    int * out_channels;
    int freq;
    double rafaga_modelo_pts;
    char * filename;
    int calibration;
    double step_v_to_r;
    double step_r_to_v;
    double firing_rate;
    double auto_cal_val_1;
} rt_args;


/* writer_thread struct */
typedef struct {
    char * filename;
    char * path;
    void * msqid;
    long points;
    int s_points;
    int type_syn;
    int model;
    int period;
    int freq;
    int time_var;
    int calibration;
    int important;
    synapse_model sm_model_to_live;
    synapse_model sm_live_to_model;
} writer_args;

typedef struct {
    double min_abs_model;
    double max_abs_model;
    double min_abs_real;
    double max_abs_real;
    double min_rel_model;
    double max_rel_model;
    double min_rel_real;
    double max_rel_real;
    double scale_virtual_to_real;
    double scale_real_to_virtual;
    double offset_virtual_to_real;
    double offset_real_to_virtual;
    double * g_virtual_to_real;
    double * g_real_to_virtual;
    double syn_gradual_k1;
    double syn_gradual_k2;
} calibration_args;

typedef struct {
    unsigned int detect_on;
    double first_spike_times[6]; //N
    double between_firsts_periods[5]; //N - 1
    unsigned index;
    double sum_acc;
    double per;
    double thresh_up;
    double thresh_down;
    double var;

    /* Cosas que se le pasan desde rt */
    struct timespec * ts;
    double v;
    synapse_model * sm_live_to_model;
    synapse_model * sm_model_to_live;
} regularity_control_args;


typedef struct {
    double * scale_virtual_to_real;
    double * scale_real_to_virtual;
    double * offset_virtual_to_real;
    double * offset_real_to_virtual;
    double * max_window;
    double * min_window;
    double * max_rel_real;
    double * min_rel_real;
    double max_abs_model;
    double min_abs_model;
    synapse_model * sm_live_to_model;
    synapse_model * sm_model_to_live;
} fix_drift_args;


typedef struct {
    double freq;
    int after;
    int time_var;
    int before;
    int model;
    int synapse;
    int mode_auto_cal;
    int imp;
    char * input;
    char * output;
    double * vars;
    double * params;
    double * g_virtual_to_real;
    double * g_real_to_virtual;
    double step_v_to_r;
    double step_r_to_v;
    double firing_rate;
    double auto_cal_val_1;
    void * syn_args_model_to_live;
    void * syn_args_live_to_model;
} clamp_args;

#endif // TYPES_CLAMP_H__

#ifdef __cplusplus
}
#endif
