#include "../includes/rt_thread_functions.h"

/************************
GLOBAL VARIABLES
************************/
void * dsc = NULL;
Daq_session * session = NULL;
rt_args * args;
void * cal_struct = NULL;
message msg;


double * lectura_a = NULL;
double * lectura_b = NULL;
double * lectura_t = NULL;
double * input_values = NULL;
double * output_values = NULL;


void * rt_thread(void * arg);

/************************
RT THREAD MANAGEMENT
************************/
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

int join_rt_thread (pthread_t thread) {
    return pthread_join(thread, NULL);
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


void double_array_to_str(int n, double * array, char * str) {
    int i;

    sprintf(str, "%f", array[0]);

    for (i = 1; i < n; i++) {
        sprintf(str, "%s %f", str, array[i]);
    }

    return;
}


void * rt_thread(void * arg) {

    /************************
    START
    ************************/

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Start");

    //Declarations
    unsigned int cont_send = 0, lost_msg = 0;

    /* Thread variables */
    struct timespec ts_target, ts_iter, ts_result, ts_start;
    message msg2;
    pthread_t id;

    /* Calibration variables */
    double max_abs_model, min_rel_model, min_abs_model;
    double max_abs_real, max_rel_real, min_rel_real, min_abs_real;
    double scale_real_to_virtual;
    double scale_virtual_to_real;
    double offset_virtual_to_real;
    double offset_real_to_virtual;
    double period_disp_real;
    double rafaga_viva_pts = 0;
    int end_loop = FALSE;

    double max_window = -999999, min_window = 999999;
    int drift_counter = 0;
    fix_drift_args fx_args;

    /* Loop variables */
    unsigned long loop_points = 0, i=0;
    int s_points;
    int infinite_loop = FALSE;

    /* Current variables */
    double c_real = 0, c_model = 0;

    double t_elapsed, c_real_aux, v_model_scaled;
    long lat;

    double ecm_result = 0;


    setlocale(LC_NUMERIC, "en_US.UTF-8");

    id = pthread_self();
    args = arg;
    //msg.c_real = c_real;

    int calib_chan = 0;

    if (signal(SIGUSR1, rt_cleanup) == SIG_ERR) printf("Error catching SIGUSR1 at rt_thread.\n");

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: After signal");

    /*msg.n_in_chan = args->n_in_chan;
    msg.n_out_chan = args->n_out_chan;
    msg.autocal = args->calibration;
    msg.data_in = NULL;
    msg.data_out = NULL;
    msg.g_virtual_to_real = NULL;
    msg.g_real_to_virtual = NULL;*/

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Before Comedi");

    //Comedi & RT
    input_values = (double *) malloc (sizeof(double) * args->n_in_chan);
    output_values = (double *) malloc (sizeof(double) * args->n_out_chan);


    if (daq_open_device((void**) &dsc) != OK) {
        fprintf(stderr, "RT_THREAD: error opening device.\n");
        pthread_exit(NULL);
    }

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Comedi device opened");

    if (daq_create_session ((void**) &dsc, &session) != OK) {
        fprintf(stderr, "RT_THREAD: error creating DAQ session.\n");
        daq_close_device ((void**) &dsc);
        pthread_exit(NULL);
    }

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Comedi started");


    prepare_real_time(id);

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Real-time prepared");

    min_abs_model = args->nm.min;
    max_abs_model = args->nm.max;


    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Model initiated");
    //printf("min %f    min_abs %f   max %f\n", min_rel_model, min_abs_model, max_abs_model);



    /************************
    CALIBRADO ESPACIO-TEMPORAL
    ************************/
    if (args->n_in_chan > 0) {
        if ( ini_recibido (&min_rel_real, &min_abs_real, &max_abs_real, &max_rel_real, &period_disp_real, session, calib_chan, args->period, args->freq, args->filename) == -1 ) {
            free_pointers(1, &session);
            daq_close_device ((void**) &dsc);
            pthread_exit(NULL);
        }

        if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: ini_recibido done");

        //printf("Periodo disparo = %f\n", period_disp_real);
        if (args->sec_per_burst != -1) period_disp_real = args->sec_per_burst;

        calcula_escala (min_abs_model, max_abs_model, min_abs_real, max_abs_real, &scale_virtual_to_real, &scale_real_to_virtual, &offset_virtual_to_real, &offset_real_to_virtual);
        if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: calcula_escala done");

        
        if (DEBUG == 1) syslog(LOG_INFO,"RT_THREAD: min_abs_model=%f\n", min_abs_model);
        if (DEBUG == 1) syslog(LOG_INFO,"RT_THREAD: max_abs_model=%f\n", max_abs_model);
        if (DEBUG == 1) syslog(LOG_INFO,"RT_THREAD: min_abs_real=%f\n", min_abs_real);
        if (DEBUG == 1) syslog(LOG_INFO,"RT_THREAD: max_abs_real=%f\n", max_abs_real);
        if (DEBUG == 1) syslog(LOG_INFO,"RT_THREAD: min_rel_real=%f\n", min_rel_real);
        if (DEBUG == 1) syslog(LOG_INFO,"RT_THREAD: max_rel_real=%f\n", max_rel_real);


        rafaga_viva_pts = args->freq * period_disp_real;
        args->nm.set_pts_burst(rafaga_viva_pts, &(args->nm));

        s_points = args->nm.pts_burst / rafaga_viva_pts;

        if (s_points == 0) s_points = 1;
    } else {
        /*MODO SIN ENTRADA*/
        scale_real_to_virtual = 1;
        scale_virtual_to_real = 1;
        offset_virtual_to_real = 0;
        offset_real_to_virtual = 0;
        s_points = 1;
        period_disp_real = 0;
    }

    /*msg.min_window = min_abs_real;
    msg.max_window = max_abs_real;*/

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Create calibration struct");


    /*CALIBRADO TEMPORAL*/
    msg2.id = args->events_file_id;
    sprintf(msg2.data, "\n******* Clamp experiment %s ******* \nModel = %d \nSynapse = %d \nFiring rate = %.3f \n*************", 
                        args->filename, args->nm.type, args->sm_live_to_model.type, period_disp_real);
    send_to_queue(args->msqid, RT_QUEUE, NO_BLOCK_QUEUE, &msg2);

    //printf("\n - Phase 1 OK\n - Phase 2 START\n\n");
    /*fflush(stdout);
    sleep(1);*/

    /************************
    SINAPSIS
    ************************/

    double ini_k1=0.4;
    double ini_k2=0.01;

    /************************
    PREPARATION
    ************************/
    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Syn model: %d", args->sm_live_to_model.type);
    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Syn calibration: %d", args->calibration);

        /*CALIBRATION STRUCT*/
    /*cal_struct = (calibration_args *) malloc (sizeof(calibration_args));
    cal_struct->min_abs_model=min_abs_model;
    cal_struct->max_abs_model=max_abs_model;
    cal_struct->min_abs_real=min_abs_real;
    cal_struct->max_abs_real=max_abs_real;
    cal_struct->min_rel_real=min_rel_real;
    cal_struct->max_rel_real=max_rel_real;
    cal_struct->scale_virtual_to_real=scale_virtual_to_real;
    cal_struct->scale_real_to_virtual=scale_real_to_virtual;
    cal_struct->offset_virtual_to_real=offset_virtual_to_real;
    cal_struct->offset_real_to_virtual=offset_real_to_virtual;
    cal_struct->g_real_to_virtual = NULL;
    cal_struct->g_virtual_to_real = NULL;*/

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

    //Synapse type
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
            //msg.n_g = ELEC_N_G;
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

                infinite_loop = TRUE;
            }

            /*Calchange*/
            /*if(args->calibration == 8){
                syn_aux_params[SC_MS_K1] = ini_k1;
                syn_aux_params[SC_MS_K2] = ini_k2;/
            }*/

            //msg.n_g = GL_N_G;
            
            break;
        }
        default:
            free_pointers(1, &session);
            daq_close_device ((void**) &dsc);
            pthread_exit(NULL);
    }

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Syn struct created");



    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Preparation done");

    //VARIABLES

    double sum_ecm = 0.0;
    int t_obs=5;
    int sum_ecm_cont=0;
    double res_phase = 0;
    int cont_lectura=0;
    int size_lectura=2*args->freq;

    lectura_a = (double *) malloc (sizeof(double) * 2*args->freq);
    lectura_b = (double *) malloc (sizeof(double) * 2*args->freq);
    lectura_t = (double *) malloc (sizeof(double) * 2*args->freq);

    clock_gettime(CLOCK_MONOTONIC, &ts_target);
    ts_assign (&ts_start,  ts_target);
    ts_add_time(&ts_target, 0, args->period);

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Before control record");
    /*Send zero*/
    for (i = 0; i < args->n_out_chan; i++) {
        output_values[i] = 0;
    }
    if (daq_write(session, args->n_out_chan, args->out_channels, output_values) != OK) {
        fprintf(stderr, "RT_THREAD: error writing to DAQ.\n");
        daq_close_device ((void**) &dsc);
        pthread_exit(NULL);
    }

    msg.id = args->data_file_id;
    sprintf(msg.data, "%d %d", args->n_in_chan, args->n_out_chan);
    if (send_to_queue(args->msqid, RT_QUEUE, NO_BLOCK_QUEUE, &msg) == ERR) lost_msg++;

    /************************
    BEFORE CONTROL RECORD
    ************************/
    loop_points = args->before * args->freq * s_points;
    for (i = 0; i < loop_points; i++) {
        if (i % s_points == 0) {
            clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &ts_target, NULL);
            clock_gettime(CLOCK_MONOTONIC, &ts_iter);

            ts_substraction(&ts_target, &ts_iter, &ts_result);
            lat = ts_result.tv_sec * NSEC_PER_SEC + ts_result.tv_nsec;

            ts_substraction(&ts_start, &ts_iter, &ts_result);
            t_elapsed = (ts_result.tv_sec * NSEC_PER_SEC + ts_result.tv_nsec) * 0.000001;
            v_model_scaled = args->nm.vars[X] * scale_virtual_to_real + offset_virtual_to_real;

            if (args->n_out_chan >= 1) output_values[0] = 0.0;
            if (args->n_out_chan >= 2) output_values[1] = v_model_scaled;

            
            sprintf(msg.data, "%f %ld %f %f %f %f", t_elapsed, lat, v_model_scaled, input_values[0], 0.0, 0.0);

            if (send_to_queue(args->msqid, RT_QUEUE, NO_BLOCK_QUEUE, &msg) == ERR) lost_msg++;

            ts_add_time(&ts_target, 0, args->period);

            if (daq_read(session, args->n_in_chan, args->in_channels, input_values) != 0) {
                free_pointers(2, &session, &cal_struct);
                daq_close_device ((void**) &dsc);
                free_pointers(7, &(args->in_channels), &(args->out_channels), &lectura_a, &lectura_b, &lectura_t, &input_values, &output_values);

                pthread_exit(NULL);
            }

        }
        //msg.c_real = 0;
        args->nm.func(args->nm, c_real);
    }

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: before loop end");

    /************************
    INITIAL INTERACTION
    ************************/

    loop_points = t_obs * args->freq * s_points;
    for (i = 0; i < loop_points; i++) {
        if (i % s_points == 0) {
            clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &ts_target, NULL);
            clock_gettime(CLOCK_MONOTONIC, &ts_iter);

        ts_substraction(&ts_target, &ts_iter, &ts_result);
            lat = ts_result.tv_sec * NSEC_PER_SEC + ts_result.tv_nsec;

            ts_substraction(&ts_start, &ts_iter, &ts_result);
            t_elapsed = (ts_result.tv_sec * NSEC_PER_SEC + ts_result.tv_nsec) * 0.000001;
            v_model_scaled = args->nm.vars[X] * scale_virtual_to_real + offset_virtual_to_real;

            if (args->n_out_chan >= 1) output_values[0] = 0.0;
            if (args->n_out_chan >= 2) output_values[1] = v_model_scaled;

            
            sprintf(msg.data, "%f %ld %f %f %f %f", t_elapsed, lat, v_model_scaled, input_values[0], 0.0, 0.0);

            if (daq_write(session, args->n_out_chan, args->out_channels, output_values) != OK) {
                fprintf(stderr, "RT_THREAD: error writing to DAQ.\n");
                daq_close_device ((void**) &dsc);
                pthread_exit(NULL);
            }

            
            if(args->calibration == 1){
                //Electrica en fase
                double ecm_old=ecm_result;
                calc_ecm(args->nm.vars[0] * scale_virtual_to_real + offset_virtual_to_real, input_values[0], rafaga_viva_pts, &ecm_result);
                //msg.ecm = ecm_result;
                if(ecm_result!=0 && ecm_old!=ecm_result){
                    sum_ecm+=ecm_result;
                    sum_ecm_cont++;
                }
            }else if(args->calibration  == 4){
                 if(cont_lectura<size_lectura){
                    
                    lectura_b[cont_lectura]=args->nm.vars[0] * scale_virtual_to_real + offset_virtual_to_real;
                    lectura_a[cont_lectura]=input_values[0];
                    lectura_t[cont_lectura]=t_elapsed;
                    cont_lectura++;
                }else{ 
                    calc_phase (lectura_b, lectura_a, lectura_t, size_lectura, max_rel_real, min_rel_real, &res_phase, args->sm_live_to_model);
                    //msg.ecm = res_phase;
                    cont_lectura=0;
                }
            }



            if (send_to_queue(args->msqid, RT_QUEUE, NO_BLOCK_QUEUE, &msg) == ERR) lost_msg++;

            ts_add_time(&ts_target, 0, args->period);

            if (daq_read(session, args->n_in_chan, args->in_channels, input_values) != 0) {
                free_pointers(2, &session, &cal_struct);
                daq_close_device ((void**) &dsc);
                free_pointers(7, &(args->in_channels), &(args->out_channels), &lectura_a, &lectura_b, &lectura_t, &input_values, &output_values);

                pthread_exit(NULL);
            }

            
            if (min_window > input_values[0]) min_window = input_values[0];
            if (max_window < input_values[0]) max_window = input_values[0];

            if (drift_counter >= (2 * rafaga_viva_pts)) {
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

                /*msg.min_window = min_window;
                msg.max_window = max_window;*/

                max_window = -999999;
                min_window = 999999;
            }

            drift_counter++;
        }
        //msg.c_real = 0;
        args->nm.func(args->nm, c_real);
    }

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: initial interaction loop end");

    if(args->calibration == 1){
        sum_ecm = sum_ecm / sum_ecm_cont;
        set_is_syn_by_percentage(sum_ecm, args->auto_cal_val_1);
    }

    /*PULSOS DE SINCRONIZACION*/
    if (SYNC == TRUE) {
        if (args->n_out_chan >= 1) output_values[0] = 0;
        if (args->n_out_chan >= 2) output_values[1] = -10;

        if (daq_write(session, args->n_out_chan, args->out_channels, output_values) != OK) {
            fprintf(stderr, "RT_THREAD: error writing to DAQ.\n");
            daq_close_device ((void**) &dsc);
            pthread_exit(NULL);
        }

        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &ts_target, NULL);
        ts_add_time(&ts_target, 0, args->period);

        if (args->n_out_chan >= 2) output_values[1] = 10;

        if (daq_write(session, args->n_out_chan, args->out_channels, output_values) != OK) {
            fprintf(stderr, "RT_THREAD: error writing to DAQ.\n");
            daq_close_device ((void**) &dsc);
            pthread_exit(NULL);
        }
    }


    /************************
    INTERACTION
    ************************/

    loop_points = args->time_var * args->freq * s_points;

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Interaction started. Points = %ld", loop_points);

    for (i = 0; i < loop_points || infinite_loop == TRUE; i++) {
        if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Inside the loop = %ld\n", i);


        if (i % s_points == 0) {
            
            clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &ts_target, NULL);
            clock_gettime(CLOCK_MONOTONIC, &ts_iter);
            ts_substraction(&ts_target, &ts_iter, &ts_result);

            if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Inside the loop and the if = %ld\n", i);


            ts_substraction(&ts_target, &ts_iter, &ts_result);
            lat = ts_result.tv_sec * NSEC_PER_SEC + ts_result.tv_nsec;

            if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Doing stuff at the loop");


            args->sm_model_to_live.calibrate = SYN_CALIB_PRE;
            args->sm_model_to_live.func(input_values[X], args->nm.vars[X], &(args->sm_model_to_live), &c_model);
            

            if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Doing more stuff at the loop");

            ts_substraction(&ts_start, &ts_iter, &ts_result);
            t_elapsed = (ts_result.tv_sec * NSEC_PER_SEC + ts_result.tv_nsec) * 0.000001;
            v_model_scaled = args->nm.vars[X] * scale_virtual_to_real + offset_virtual_to_real;

            if (args->n_out_chan >= 1) output_values[0] = 0.0;
            if (args->n_out_chan >= 2) output_values[1] = v_model_scaled;


            sprintf(msg.data, "%f %ld %f %f %f %f", t_elapsed, lat, v_model_scaled, input_values[0], -c_model, -c_real_aux);


            if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Before writing to device");

            if (daq_write(session, args->n_out_chan, args->out_channels, output_values) != OK) {
                fprintf(stderr, "RT_THREAD: error writing to DAQ.\n");
                daq_close_device ((void**) &dsc);
                pthread_exit(NULL);
            }

            end_loop = auto_calibration(
                                args, cal_struct, input_values, rafaga_viva_pts, &ecm_result,
                                &msg, lectura_a, lectura_b, lectura_t, size_lectura, cont_send,
                                ini_k1, ini_k2, args->sm_live_to_model, args->sm_model_to_live,
                                &ts_iter
                                );

            if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: After ret_auto_cal");

            if (send_to_queue(args->msqid, RT_QUEUE, NO_BLOCK_QUEUE, &msg) == ERR) lost_msg++;

            ts_add_time(&ts_target, 0, args->period);

            if(end_loop==TRUE)
                break;

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

            args->sm_live_to_model.calibrate = SYN_CALIB_POST;
            args->sm_live_to_model.func(args->nm.vars[0], input_values[0], &(args->sm_live_to_model), &c_real_aux);



            if (min_window > input_values[0]) min_window = input_values[0];
            if (max_window < input_values[0]) max_window = input_values[0];

            if (drift_counter >= (2 * rafaga_viva_pts)) {
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

                /*msg.min_window = min_window;
                msg.max_window = max_window;*/

                max_window = -999999;
                min_window = 999999;
            }

            drift_counter++;
        }


        args->sm_live_to_model.calibrate = SYN_CALIB_PRE;
        args->sm_live_to_model.func(args->nm.vars[0], input_values[0], &(args->sm_live_to_model), &c_real);

        args->nm.func(args->nm, c_real);
    }

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: main loop end");
    /*Send zero*/
    for (i = 0; i < args->n_out_chan; i++) {
        output_values[i] = 0;
    }
    if (daq_write(session, args->n_out_chan, args->out_channels, output_values) != OK) {
        fprintf(stderr, "RT_THREAD: error writing to DAQ.\n");
        daq_close_device ((void**) &dsc);
        pthread_exit(NULL);
    }


    /************************
    AFTER CONTROL RECORD
    ************************/

    loop_points = args->before * args->freq * s_points;
    for (i = 0; i < loop_points; i++) {
        if (i % s_points == 0) {
            clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &ts_target, NULL);
            clock_gettime(CLOCK_MONOTONIC, &ts_iter);

            ts_substraction(&ts_target, &ts_iter, &ts_result);
            lat = ts_result.tv_sec * NSEC_PER_SEC + ts_result.tv_nsec;

            ts_substraction(&ts_start, &ts_iter, &ts_result);
            t_elapsed = (ts_result.tv_sec * NSEC_PER_SEC + ts_result.tv_nsec) * 0.000001;
            v_model_scaled = args->nm.vars[X] * scale_virtual_to_real + offset_virtual_to_real;

            if (args->n_out_chan >= 1) output_values[0] = 0.0;
            if (args->n_out_chan >= 2) output_values[1] = v_model_scaled;

            
            sprintf(msg.data, "%f %ld %f %f %f %f", t_elapsed, lat, v_model_scaled, input_values[0], 0.0, 0.0);

            if (send_to_queue(args->msqid, RT_QUEUE, NO_BLOCK_QUEUE, &msg) == ERR) lost_msg++;

            ts_add_time(&ts_target, 0, args->period);

            if (daq_read(session, args->n_in_chan, args->in_channels, input_values) != 0) {
                free_pointers(2, &session, &cal_struct);
                daq_close_device ((void**) &dsc);
                free_pointers(7, &(args->in_channels), &(args->out_channels), &lectura_a, &lectura_b, &lectura_t, &input_values, &output_values);

                pthread_exit(NULL);
            }

        }
        args->nm.func(args->nm, c_real);
    }

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: after loop end");

    /*Send zero*/
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
