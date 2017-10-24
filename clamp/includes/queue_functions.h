#ifndef QUEUE_FUNCTIONS_H__
#define QUEUE_FUNCTIONS_H__

/*#include <sys/ipc.h>
#include <sys/msg.h>*/
#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdarg.h>
#include <syslog.h>
#include "types_clamp.h"


typedef struct {
    long id;
    int i; // Also s_points
    double t_unix; // Also period_disp_real
    double t_absol;

    /* File 1*/ 
    long lat;
    double v_model;
    double v_model_scaled;
    double c_model;
    double c_real;
    int n_in_chan;
    int n_out_chan;
    double * data_in;
    double * data_out;
    /* File 2*/
    int autocal;
    double * g_real_to_virtual;
    double * g_virtual_to_real;
    int n_g;
    double ecm; 
    double extra;
    //char mensaje [100];
} message;

int open_queue (void ** msqid);

int send_to_queue (void * msqid, message * msg);

int receive_from_queue (void * msqid, message * msg);

int close_queue (void ** msqid);

void free_pointers (int n, ...);


#endif /* queue_functions.h */
