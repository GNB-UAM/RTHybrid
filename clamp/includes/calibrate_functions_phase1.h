#ifdef __cplusplus
extern "C" {
#endif

#ifndef CALIBRATE_FUNCTIONS_PHASE1_H__
#define CALIBRATE_FUNCTIONS_PHASE1_H__

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
#include "device_functions.h"
#include "time_functions.h"

int ini_recibido (double *min_rel_real, double *min_abs_real, double *max_abs_real, double *max_rel_real, double *period_signal, Daq_session * session, int chan, int period, int freq, char* filename);

int signal_convolution (double * lectura, int size_l, double * result, int size_r);

int signal_average(double * lectura, int size_l, double * result, int size_r);

double signal_period_1(int seg_observacion, double * signal, int size, double th_up, double th_on);

double signal_period_2(int seg_observacion, double * signal, int size, double th_up, double th_on);

void array_to_file(double * array, int size, char * filename_date, char * tittle);

#endif //CALIBRATE_FUNCTIONS_PHASE1_H__

#ifdef __cplusplus
}
#endif
