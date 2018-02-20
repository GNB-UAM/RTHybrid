#ifdef __cplusplus
extern "C" {
#endif

#ifndef TYPES_CLAMP_H__
#define TYPES_CLAMP_H__

#include <syslog.h>
#include "../../common/includes/types.h"

typedef struct {
    unsigned int syn_type;
    double * g;
    double scale;
    double offset;
    unsigned int calibrate;
    void * type_params;
} syn_params;

typedef struct {
    void (*func)(int, double, double*, double*, double);
    void (*ini)(double*, double*, double*);
    void (*syn)(double, double, syn_params*, double*);
    double * vars;
    double * params;
    int dim;
    double dt;
    int type_syn;
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
    int rafaga_modelo_pts;
    char * filename;
    int calibration;
    int model;
    double step_v_to_r;
    double step_r_to_v;
    double firing_rate;
    void * syn_args_model_to_live;
    void * syn_args_live_to_model;
    double auto_cal_val_1;
} rt_args;


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
    void * syn_args_model_to_live;
    void * syn_args_live_to_model;
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
    syn_params * syn_aux_params_live_to_model;
    syn_params * syn_aux_params_model_to_live;
    int model;
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
