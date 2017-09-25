#ifdef __cplusplus
extern "C" {
#endif

#ifndef CLAMP_H
#define CLAMP_H

#include "clamp/includes/rt_thread_functions.h"
#include "clamp/includes/writer_thread_functions.h"

int clamp (int freq, int time_var, int model, int synapse, int mode_auto_cal, int anti, int imp, char * input, char * output);

#endif // CLAMP_H

#ifdef __cplusplus
}
#endif
