#ifndef RT_THREAD_FUNCTIONS_H__
#define RT_THREAD_FUNCTIONS_H__

#include "time_functions.h"
#include "model_library.h"
#include "queue_functions.h"
#include "calibrate_functions_phase1.h"
#include "calibrate_functions_phase2_a.h"
#include "calibrate_functions_phase2.h"

#define MAX_SAFE_STACK (8*1024)
#define PRIORITY (99)
#define MAX_LAT (900000)
#define CORE (0)

void prepare_real_time (pthread_t id);

void copy_1d_array (double * src, double * dst, int n_elems);

void * rt_thread (void * arg);

#endif