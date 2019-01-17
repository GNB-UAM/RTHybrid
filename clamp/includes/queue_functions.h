#ifdef __cplusplus
extern "C" {
#endif

#ifndef QUEUE_FUNCTIONS_H__
#define QUEUE_FUNCTIONS_H__


#include <sys/types.h>

#include "types_clamp.h"
#include "time_functions.h"


#define RT_QUEUE 0
#define NRT_QUEUE 1
#define BLOCK_QUEUE 0
#define NO_BLOCK_QUEUE 1


typedef struct {
    short id;
    char data[128];
} message;


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
    /* Deriva */
    double min_window;
    double max_window;
} message_2;


int open_queue (void ** rt_msqid, void ** nrt_msqid);

int send_to_queue (void * msqid, unsigned int is_rt, unsigned int is_blocking, message * msg);

int receive_from_queue (void * msqid, unsigned int is_rt, unsigned int is_blocking, message * msg);

int close_queue (void ** rt_msqid, void ** nrt_msqid);


#endif /* queue_functions.h */

#ifdef __cplusplus
}
#endif
