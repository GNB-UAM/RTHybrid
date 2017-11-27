#ifdef __cplusplus
extern "C" {
#endif

#ifndef TYPES_CLAMP_H__
#define TYPES_CLAMP_H__

#include <syslog.h>
#include "../../common/includes/types.h"

typedef struct {
    void (*func)(int, double, double*, double*, double);
    void (*ini)(double*, double*, double*);
    void (*syn)(double, double, double*, double*, double*);
    double * vars;
    double * params;
    double * g_virtual_to_real;
    double * g_real_to_virtual;
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
    int anti;
    int model;
    double step_v_to_r;
    double step_r_to_v;
    double firing_rate;
    double syn_gradual_k1;
    double syn_gradual_k2;
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
    int anti;
    int important;
    double syn_gradual_k1;
    double syn_gradual_k2;
} writer_args;

typedef struct {
    double min_abs_model;
    double max_model;
    double min_abs_real;
    double max_real;
    double scale_virtual_to_real;
    double scale_real_to_virtual;
    double offset_virtual_to_real;
    double offset_real_to_virtual;
    double max_real_relativo;
    double min_real;
    double * g_virtual_to_real;
    double * g_real_to_virtual;
    double syn_gradual_k1;
    double syn_gradual_k2;
} calibration_args;


typedef struct {
    double freq;
    int after;
    int time_var;
    int before;
    int model;
    int synapse;
    int mode_auto_cal;
    int anti;
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
    double syn_gradual_k1;
    double syn_gradual_k2;
    double auto_cal_val_1;
} clamp_args;

#endif // TYPES_CLAMP_H__

#ifdef __cplusplus
}
#endif
