#include "../includes/rt_thread_functions.h"

struct Loop_params {
	unsigned long duration;
	unsigned short infinite;
	unsigned short interaction;
};


/************************
GLOBAL VARIABLES
************************/

rt_args * args;
message msg;
unsigned int lost_msg = 0;
struct timespec ts_target, ts_start;
double external_pts_per_burst = 0;

void * cal_struct = NULL;

void * dsc = NULL;
Daq_session * session = NULL;
double * input_values = NULL;
double * output_values = NULL;


double max_window = -999999, min_window = 999999;
int drift_counter = 0;
int drift_n_burst = 2;




double max_abs_model, min_rel_model, min_abs_model;
double max_abs_real, max_rel_real, min_rel_real, min_abs_real;
double scale_real_to_virtual, scale_virtual_to_real;
double offset_virtual_to_real, offset_real_to_virtual;




double * lectura_a = NULL;
double * lectura_b = NULL;
double * lectura_t = NULL;
double ecm_result = 0;



/************************
RT THREAD MANAGEMENT
************************/

void * rt_thread(void * arg);

void experiment_loop (struct Loop_params * lp, int s_points);

int create_rt_thread (pthread_t * thread, void *arg) {
    pthread_attr_t attr;
    int err;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    err = pthread_create(thread, &attr, &rt_thread, arg);
    if (err != 0) {
        syslog(LOG_INFO, "Can't create rt_thread :[%s]", strerror(err));
        return ERR;
    }

    #ifdef __XENO__
        if (pthread_setname_np((*thread), "RTHybrid - RT Thread") != 0) {
            perror("Setting RT Thread name");
        }
    #endif

    return OK;
}

int join_rt_thread (pthread_t thread, void ** value_ptr) {
    return pthread_join(thread, value_ptr);
}

int kill_rt_thread(pthread_t thread, int sig) {
	return pthread_kill(thread, sig);
}


void prepare_real_time (pthread_t id) {
    struct sched_param param;
    unsigned char dummy[MAX_SAFE_STACK];


    /* Set priority */
    param.sched_priority = PRIORITY;
    if(pthread_setschedparam(id, SCHED_FIFO, &param) == -1) {
        perror("sched_setscheduler failed");
        exit(-1);
    }

    /* Set core affinity */
    /*cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(CORE, &mask);
    if (pthread_setaffinity_np(id, sizeof(mask), &mask) != 0) {
        perror("Affinity set failure\n");
        exit(-2);
    }*/

    /* Lock memory */

    if(mlockall(MCL_CURRENT|MCL_FUTURE) == -1) {
        perror("mlockall failed");
        exit(-3);
    }

    /* Pre-fault our stack */
    memset(dummy, 0, MAX_SAFE_STACK);

    return;
}


void rt_cleanup () {
    unsigned int i = 0;

    printf("\n" PRINT_RED "SIGUSR1 termination to rt_thread." PRINT_RESET "\n");

    if (session != NULL) {
        for (i = 0; i < args->n_out_chan; i++) {
            output_values[i] = 0;
        }

       if (daq_write(session, args->n_out_chan, args->out_channels, output_values) != OK) {
            fprintf(stderr, "RT_THREAD: error writing to DAQ.\n");
        }
    }

    if (dsc != NULL) {
        free_pointers(1, &session);
        daq_close_device ((void**) &dsc);
    }

    free_pointers(7, &(args->in_channels), &(args->out_channels), &lectura_a, &lectura_b, &lectura_t, &input_values, &output_values);

    printf("\n" PRINT_CYAN "rt_thread terminated." PRINT_RESET "\n");
    pthread_exit(NULL);
}


/************************
RT THREAD
************************/

void * rt_thread(void * arg) {

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Start");

    /* Thread variables */
    pthread_t id;
    unsigned int i;


    /* Calibration variables */
    double external_firing_rate;
    int s_points;

    int calib_chan = 0;

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Before Experiments loop params");

    /* Experiments loops */
    struct Loop_params lp[3];
    unsigned int n_loops = 3;

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Variables created");


    /****************************************************
    Prepare thread
    ****************************************************/

    setlocale(LC_NUMERIC, "en_US.UTF-8");

    args = arg;
    id = pthread_self();
    prepare_real_time(id);


    if (signal(SIGUSR1, rt_cleanup) == SIG_ERR) printf("Error catching SIGUSR1 at rt_thread.\n");

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: After signal");


    lp[0].duration = args->before;
    lp[0].infinite = FALSE;
    lp[0].interaction = FALSE;

    lp[1].duration = args->time_var;
    lp[1].infinite = FALSE;
    lp[1].interaction = TRUE;

    lp[2].duration = args->after;
    lp[2].infinite = FALSE;
    lp[2].interaction = FALSE;

    
    
    /****************************************************
    Open DAQ
    ****************************************************/

    if (daq_open_device((void**) &dsc) != OK) {
        fprintf(stderr, "RT_THREAD: error opening device.\n");

        msg.id = -1;
	    if (send_to_queue(args->msqid, RT_QUEUE, BLOCK_QUEUE, &msg) == ERR) {
	        perror("Closing message not sent");
	    }
        pthread_exit(NULL);
    }

    if (daq_create_session ((void**) &dsc, &session) != OK) {
        fprintf(stderr, "RT_THREAD: error creating DAQ session.\n");
        daq_close_device ((void**) &dsc);

        msg.id = -1;
	    if (send_to_queue(args->msqid, RT_QUEUE, BLOCK_QUEUE, &msg) == ERR) {
	        perror("Closing message not sent");
	    }
        pthread_exit(NULL);
    }

    input_values = (double *) malloc (sizeof(double) * args->n_in_chan);
    output_values = (double *) malloc (sizeof(double) * args->n_out_chan);


    for (i = 0; i < args->n_out_chan; i++) {
        output_values[i] = 0;
    }
    if (daq_write(session, args->n_out_chan, args->out_channels, output_values) != OK) {
        fprintf(stderr, "RT_THREAD: error writing to DAQ.\n");
        daq_close_device ((void**) &dsc);

        msg.id = -1;
	    if (send_to_queue(args->msqid, RT_QUEUE, BLOCK_QUEUE, &msg) == ERR) {
	        perror("Closing message not sent");
	    }
        pthread_exit(NULL);
    }


    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: DAQ started");

    
    /****************************************************
    Set scale and offset values regarding external neuron
    ****************************************************/

    min_abs_model = args->nm.min;
    max_abs_model = args->nm.max;

    if (args->n_in_chan > 0) {

        if ( ini_recibido (&min_rel_real, &min_abs_real, &max_abs_real, &max_rel_real, &external_firing_rate, session, calib_chan, args->period, args->freq, args->filename, args->input_factor, args->observation) == -1 ) {
            free_pointers(1, &session);
            daq_close_device ((void**) &dsc);

            msg.id = -1;
		    if (send_to_queue(args->msqid, RT_QUEUE, BLOCK_QUEUE, &msg) == ERR) {
		        perror("Closing message not sent");
		    }
            pthread_exit(NULL);
        }

        if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: ini_recibido done");

        if (args->sec_per_burst != -1) external_firing_rate = args->sec_per_burst;

        calcula_escala (min_abs_model, max_abs_model, min_abs_real, max_abs_real, &scale_virtual_to_real, &scale_real_to_virtual, &offset_virtual_to_real, &offset_real_to_virtual);
        if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: calcula_escala done");

        
        if (DEBUG == 1) syslog(LOG_INFO,"RT_THREAD: min_abs_model=%f\n", min_abs_model);
        if (DEBUG == 1) syslog(LOG_INFO,"RT_THREAD: max_abs_model=%f\n", max_abs_model);
        if (DEBUG == 1) syslog(LOG_INFO,"RT_THREAD: min_abs_real=%f\n", min_abs_real);
        if (DEBUG == 1) syslog(LOG_INFO,"RT_THREAD: max_abs_real=%f\n", max_abs_real);
        if (DEBUG == 1) syslog(LOG_INFO,"RT_THREAD: min_rel_real=%f\n", min_rel_real);
        if (DEBUG == 1) syslog(LOG_INFO,"RT_THREAD: max_rel_real=%f\n", max_rel_real);


        external_pts_per_burst = args->freq * external_firing_rate;
        args->nm.set_pts_burst(external_pts_per_burst, &(args->nm));

        s_points = args->nm.pts_burst / external_pts_per_burst;

        if (s_points == 0) s_points = 1;

    } else {

        /*MODO SIN ENTRADA*/
        scale_real_to_virtual = 1;
        scale_virtual_to_real = 1;
        offset_virtual_to_real = 0;
        offset_real_to_virtual = 0;
        s_points = 1;
        external_firing_rate = 0;

    }


    msg.id = args->events_file_id;
    sprintf(msg.data, "\n******* Clamp experiment %s ******* \nModel = %d \nSynapse = %d \nFiring rate = %.3f \n*************", 
                        args->filename, args->nm.type, args->sm_live_to_model.type, external_firing_rate);
    send_to_queue(args->msqid, RT_QUEUE, NO_BLOCK_QUEUE, &msg);


    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Scale and offset values set");


    /****************************************************
    Initialize calibration parameters and structures
    ****************************************************/

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Syn model: %d", args->sm_live_to_model.type);
    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Syn calibration: %d", args->calibration);

    if (args->calibration >= 1 && args->calibration <= 8) {
        cal_struct_init (&cal_struct, args->calibration, min_abs_model, max_abs_model, min_abs_real,
            max_abs_real, min_rel_real, max_rel_real, scale_virtual_to_real, scale_real_to_virtual,
            offset_virtual_to_real, offset_real_to_virtual);

    } else if (args->calibration == 9) {
        if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: control_regularity min_rel_real %f max_rel_real %f\n", min_rel_real, max_rel_real);
        cal_struct_init (&cal_struct, args->calibration, &(args->sm_live_to_model), &(args->sm_model_to_live),
            min_rel_real, max_rel_real, args->auto_cal_val_1);
    }


    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Calibration struct created");

    
    /****************************************************
    Initialize synapse models
    ****************************************************/

    switch (args->sm_live_to_model.type) {
        case EMPTY_SYN:
        {
            break;
        }
        case ELECTRIC:
        {
            elec_set_online_params(&(args->sm_live_to_model), scale_real_to_virtual, offset_real_to_virtual);
            elec_set_online_params(&(args->sm_model_to_live), scale_virtual_to_real, offset_virtual_to_real);


            if(args->calibration != 0 && args->calibration != 6){
                if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Inside autocal");
                args->sm_model_to_live.g[0] = 0.0;
                args->sm_live_to_model.g[0] = 0.0;
            }

            if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Elec set finalized");
        
            break;
        }
        case GOLOWASCH:
        {
            gl_set_online_params(&(args->sm_live_to_model), scale_real_to_virtual, offset_real_to_virtual, min_abs_real, max_abs_real);
            gl_set_online_params(&(args->sm_model_to_live), scale_virtual_to_real, offset_virtual_to_real, min_abs_model, max_abs_model);

            if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Calibration mode = %i", args->calibration);

            if(args->calibration == 7){
                ((calibration_args*)cal_struct)->g_virtual_to_real = (double *) malloc (sizeof(double) * 2);
                ((calibration_args*)cal_struct)->g_real_to_virtual = (double *) malloc (sizeof(double) * 2);
                copy_1d_array(args->sm_model_to_live.g, ((calibration_args*)cal_struct)->g_virtual_to_real, 2);
                copy_1d_array(args->sm_live_to_model.g, ((calibration_args*)cal_struct)->g_real_to_virtual, 2);

                if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Map g_V-R_fast = %f", ((calibration_args*)cal_struct)->g_virtual_to_real[GL_G_FAST]);
                if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Map g_V-R_slow = %f", ((calibration_args*)cal_struct)->g_virtual_to_real[GL_G_SLOW]);
                if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Map g_R-V_fast = %f", ((calibration_args*)cal_struct)->g_real_to_virtual[GL_G_FAST]);
                if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Map g_R-V_slow = %f", ((calibration_args*)cal_struct)->g_real_to_virtual[GL_G_SLOW]);

                args->sm_model_to_live.g[GL_G_FAST] = 0.0;
                args->sm_model_to_live.g[GL_G_SLOW] = 0.0;
                args->sm_live_to_model.g[GL_G_FAST] = 0.0;
                args->sm_live_to_model.g[GL_G_SLOW] = 0.0;

                lp[1].infinite = TRUE;
            }
            
            break;
        }
        default:
            free_pointers(1, &session);
            daq_close_device ((void**) &dsc);

            msg.id = -1;
		    if (send_to_queue(args->msqid, RT_QUEUE, BLOCK_QUEUE, &msg) == ERR) {
		        perror("Closing message not sent");
		    }
            pthread_exit(NULL);
    }

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Syn struct created");

    
    /****************************************************
    Experiment loops
    ****************************************************/

    msg.id = args->data_file_id;
    sprintf(msg.data, "%d %d", args->n_in_chan, args->n_out_chan);
    if (send_to_queue(args->msqid, RT_QUEUE, BLOCK_QUEUE, &msg) == ERR) lost_msg++;

    clock_gettime(CLOCK_MONOTONIC, &ts_target);
    ts_assign(&ts_start,  ts_target);
    ts_add_time(&ts_target, 0, args->period);



    for (i = 0; i < n_loops; i++) {
        experiment_loop(&(lp[i]), s_points);
    }


    /****************************************************
    Clean-up and end
    ****************************************************/

    /*Send zero*/
    for (i = 0; i < args->n_out_chan; i++) {
        output_values[i] = 0;
    }
    if (daq_write(session, args->n_out_chan, args->out_channels, output_values) != OK) {
        fprintf(stderr, "RT_THREAD: error writing to DAQ.\n");
        daq_close_device ((void**) &dsc);

        msg.id = -1;
	    if (send_to_queue(args->msqid, RT_QUEUE, BLOCK_QUEUE, &msg) == ERR) {
	        perror("Closing message not sent");
	    }
        pthread_exit(NULL);
    }

    free_pointers(2, &session, &cal_struct);
    daq_close_device ((void**) &dsc);

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Deviced closed");

    msg.id = -1;
    if (send_to_queue(args->msqid, RT_QUEUE, BLOCK_QUEUE, &msg) == ERR) {
        perror("Closing message not sent");
    }

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Closing message sent");

    free_pointers(7, &(args->in_channels), &(args->out_channels), &lectura_a, &lectura_b, &lectura_t, &input_values, &output_values);

    printf("RT_THREAD: End. Not sent messages: %d\n", lost_msg);

    pthread_exit(NULL);
}











void experiment_loop (struct Loop_params * lp, int s_points) {
	unsigned long loop_points = 0, i = 0;

	struct timespec ts_iter, ts_result;

	int end_loop = FALSE;

    fix_drift_args fx_args;

    double c_model = 0.0, c_external = 0.0;
    double c_external_scaled = 0.0, v_model_scaled = 0.0;   /* Scaled to the other side range */
    double t_elapsed;                           /* In milliseconds */
    long lat;                                   /* In nanoseconds */



    loop_points = lp->duration * args->freq * s_points;


	for (i = 0; i < loop_points || lp->infinite == TRUE; i++) {


        if (i % s_points == 0) {
            
            /* Sleep */
            clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &ts_target, NULL);
            
            /* Wake up and get times and latency */
            clock_gettime(CLOCK_MONOTONIC, &ts_iter);
            ts_substraction(&ts_target, &ts_iter, &ts_result);
            lat = ts_result.tv_sec * NSEC_PER_SEC + ts_result.tv_nsec;
            ts_substraction(&ts_start, &ts_iter, &ts_result);
            t_elapsed = (ts_result.tv_sec * NSEC_PER_SEC + ts_result.tv_nsec) * 0.000001;

            ts_add_time(&ts_target, 0, args->period);

            if (lp->interaction == TRUE) {
                /* Calculate synapse from the model to the external neuron (scaled to external range) */
                args->sm_model_to_live.calibrate = SYN_CALIB_PRE;
                args->sm_model_to_live.func(input_values[VAR_X], args->nm.vars[VAR_X], &(args->sm_model_to_live), &c_model);
            }

            /* Send the model current and voltage (scaled) to the DAQ */
            v_model_scaled = args->nm.vars[VAR_X] * scale_virtual_to_real + offset_virtual_to_real;
            if (args->n_out_chan >= 1) output_values[0] = -c_model / args->output_factor;
            if (args->n_out_chan >= 2) output_values[1] = v_model_scaled;


            if (daq_write(session, args->n_out_chan, args->out_channels, output_values) != OK) {
                fprintf(stderr, "RT_THREAD: error writing to DAQ.\n");
                daq_close_device ((void**) &dsc);
                pthread_exit(NULL);
            }

            /* Send data to the message queue */
            sprintf(msg.data, "%.3f %ld %.3f %.3f %.3f %.3f", t_elapsed, lat, v_model_scaled, input_values[0], -c_model, -c_external_scaled);
            if (send_to_queue(args->msqid, RT_QUEUE, NO_BLOCK_QUEUE, &msg) == ERR) lost_msg++;


            /* Auto calibration */
            /*end_loop = auto_calibration(
                                args, cal_struct, input_values, external_pts_per_burst, &ecm_result,
                                &msg, lectura_a, lectura_b, lectura_t, size_lectura, cont_send,
                                ini_k1, ini_k2, args->sm_live_to_model, args->sm_model_to_live,
                                &ts_iter
                                );

            if(end_loop==TRUE) break;*/


            /* Read data from the DAQ */
            if (daq_read(session, args->n_in_chan, args->in_channels, input_values) != 0) {

                for (i = 0; i < args->n_out_chan; i++) {
                    output_values[i] = 0;
                }

                if (daq_write(session, args->n_out_chan, args->out_channels, output_values) != OK) {
                    fprintf(stderr, "RT_THREAD: error writing to DAQ.\n");
                    daq_close_device ((void**) &dsc);
                    pthread_exit(NULL);
                }

                free_pointers(2, &session, &cal_struct);
                daq_close_device ((void**) &dsc);
                free_pointers(7, &(args->in_channels), &(args->out_channels), &lectura_a, &lectura_b, &lectura_t, &input_values, &output_values);

                pthread_exit(NULL);
            }

            input_values[0] = (input_values[0] * 1000.0) / args->input_factor;


            /* Recalculate the minimum and maximum thresholds and fix drift */
            if (args->check_drift == TRUE) {
                if (min_window > input_values[0]) min_window = input_values[0];
                if (max_window < input_values[0]) max_window = input_values[0];

                if (drift_counter >= (drift_n_burst * external_pts_per_burst)) {
                    drift_counter = 0;

                    fx_args.scale_virtual_to_real = &scale_virtual_to_real;
                    fx_args.scale_real_to_virtual = &scale_real_to_virtual;
                    fx_args.offset_virtual_to_real = &offset_virtual_to_real;
                    fx_args.offset_real_to_virtual = &offset_real_to_virtual;
                    fx_args.max_window = &max_window;
                    fx_args.min_window = &min_window;
                    fx_args.max_rel_real = &max_rel_real;
                    fx_args.min_rel_real = &min_rel_real;
                    fx_args.max_abs_model = max_abs_model;
                    fx_args.min_abs_model = min_abs_model;
                    fx_args.sm_live_to_model = &(args->sm_live_to_model);
                    fx_args.sm_model_to_live = &(args->sm_model_to_live);

                    fix_drift(fx_args);

                    max_window = -999999;
                    min_window = 999999;
                }

                drift_counter++;
            }

            if (lp->interaction == TRUE) {
                /* Calculate the input synapse (scaled to the external range) */
                args->sm_live_to_model.calibrate = SYN_CALIB_POST;
                args->sm_live_to_model.func(args->nm.vars[0], input_values[0], &(args->sm_live_to_model), &c_external_scaled);
            }
        }

        if (lp->interaction == TRUE) {
            /* Calculate synapse from the external neuron to the model (scaled to model range) */
            args->sm_live_to_model.calibrate = SYN_CALIB_PRE;
            args->sm_live_to_model.func(args->nm.vars[0], input_values[0], &(args->sm_live_to_model), &c_external);
        }

        /* Calculate neuron model */
        args->nm.func(args->nm, c_external);
    }
}
