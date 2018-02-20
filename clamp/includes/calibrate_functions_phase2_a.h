#ifndef CALIBRATE_FUNCTIONS_PHASE2_A_H__
#define CALIBRATE_FUNCTIONS_PHASE2_A_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sched.h>
#include <sys/mman.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <getopt.h>
#include "calibrate_functions_phase2.h"
#include "queue_functions.h"
#include "model_library.h"

void cal_struct_init (void ** cal_struct, unsigned int mode_auto_cal, ...);

int auto_calibration(
					rt_args * args,
					void * cal_args,
					double * ret_values,
					double rafaga_viva_pts,
					double * ecm_result,
					message * msg,
                    double * lectura_a,
                    double * lectura_b,
                    double * lectura_t,
                    int size_lectura,
                    int cont_send,
                    double ini_k1,
                    double ini_k2,
                    syn_params syn_params_live_to_model,
                    syn_params syn_params_model_to_live,
                    struct timespec * ts
					);

void calcula_escala (double min_virtual, double max_virtual, double min_viva, double max_viva, double *scale_virtual_to_real, double *scale_real_to_virtual, double *offset_virtual_to_real, double *offset_real_to_virtual);

void fix_drift (fix_drift_args args);

void regularity_control (regularity_control_args * args);

#endif 
