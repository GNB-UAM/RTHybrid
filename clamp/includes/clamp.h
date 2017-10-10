#ifdef __cplusplus
extern "C" {
#endif

#ifndef CLAMP_H
#define CLAMP_H

#include "clamp/includes/rt_thread_functions.h"
#include "clamp/includes/writer_thread_functions.h"

int clamp (double freq, int time_var, int model, int synapse, int mode_auto_cal, int anti, int imp, char * input, char * output, double * vars, double * params, double * g_virtual_to_real, double * g_real_to_virtual, double step_v_to_r, double step_r_to_v);

#endif // CLAMP_H

#ifdef __cplusplus
}
#endif
