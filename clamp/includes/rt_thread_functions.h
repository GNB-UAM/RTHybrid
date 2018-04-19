#ifndef RT_THREAD_FUNCTIONS_H__
#define RT_THREAD_FUNCTIONS_H__

#include "time_functions.h"
#include "neuron_models_functions.h"
#include "synapse_models_functions.h"
#include "queue_functions.h"
#include "calibrate_functions_phase1.h"
#include "calibrate_functions_phase2_a.h"
#include "calibrate_functions_phase2.h"

#include <pthread.h>
#include <locale.h>

int create_rt_thread (pthread_t * thread, void *arg);

int join_rt_thread (pthread_t thread);

#endif
