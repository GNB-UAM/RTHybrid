#include "../includes/rt_thread_functions.h"
//#define DEBUG 1
/************************
GLOBAL VARIABLES
************************/
void * dsc = NULL;
Daq_session * session = NULL;
rt_args * args;
calibration_args * cal_struct = NULL;
message msg;
double * syn_aux_params = NULL;

double * lectura_a = NULL;
double * lectura_b = NULL;
double * lectura_t = NULL;
double * ret_values = NULL;
double * out_values = NULL;

/************************
RT CLEANUP
************************/
void rt_cleanup () {
    unsigned int i = 0;

    printf("\n" PRINT_RED "SIGUSR1 termination to rt_thread." PRINT_RESET "\n");

    if (session != NULL) {
        for (i = 0; i < args->n_out_chan; i++) {
            out_values[i] = 0;
        }
        
       if (daq_write(session, args->n_out_chan, args->out_channels, out_values) != OK) {
            fprintf(stderr, "RT_THREAD: error writing to DAQ.\n");
        }
    }

    if (dsc != NULL) {
        free_pointers(1, &session);
        daq_close_device ((void**) &dsc);
    }

    free_pointers(12, &syn_aux_params, &(args->in_channels), &(args->out_channels), &lectura_a, &lectura_b, &lectura_t, &ret_values, &out_values, &(msg.data_in), &(msg.data_out), &(msg.g_real_to_virtual), &(msg.g_virtual_to_real));

    printf("\n" PRINT_CYAN "rt_thread terminated." PRINT_RESET "\n");
    pthread_exit(NULL);
}

/************************
PREPARE REAL TIME
************************/
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
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(CORE, &mask);
    if (pthread_setaffinity_np(id, sizeof(mask), &mask) != 0) {
        perror("Affinity set failure\n");
        exit(-2);
    }

    /* Lock memory */

    if(mlockall(MCL_CURRENT|MCL_FUTURE) == -1) {
        perror("mlockall failed");
        exit(-3);
    }

    /* Pre-fault our stack */
    memset(dummy, 0, MAX_SAFE_STACK);

    return;
}

/************************
COPY 1D ARRAY
************************/
void copy_1d_array (double * src, double * dst, int n_elems) {
    int i;

    for (i = 0; i < n_elems; i++) {
        dst[i] = src[i];
    }

    return;
}

/************************
RT THREAD
************************/
void * rt_thread(void * arg) {

    /************************
    START
    ************************/

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Start");

    //Declarations
    unsigned int cont_send = 0, lost_msg = 0;
    
    struct timespec ts_target, ts_iter, ts_result, ts_start;
    message msg2;
    pthread_t id;

    double max_model, min_model, min_abs_model;
    double max_real, min_real, min_abs_real, max_real_relativo;
    double scale_real_to_virtual;
    double scale_virtual_to_real;
    double offset_virtual_to_real;
    double offset_real_to_virtual;
    double period_disp_real;
    double rafaga_viva_pts = 0;
    int end_loop = FALSE;

    unsigned long loop_points = 0, i=0;
    int infinite_loop = FALSE;

    double c_real = 0, c_model = 0;

    double ecm_result = 0;

    id = pthread_self();
    args = arg;
    msg.c_real = c_real;

    int calib_chan = 0;

    if (signal(SIGUSR1, rt_cleanup) == SIG_ERR) printf("Error catching SIGUSR1 at rt_thread.\n");

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: After signal");

    msg.n_in_chan = args->n_in_chan;
    msg.n_out_chan = args->n_out_chan;
    msg.autocal = args->calibration;
    msg.data_in = NULL;
    msg.data_out = NULL;
    msg.g_virtual_to_real = NULL;
    msg.g_real_to_virtual = NULL;

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Before Comedi");

    //Comedi & RT
    if (daq_open_device((void**) &dsc) != OK) {
        fprintf(stderr, "RT_THREAD: error opening device.\n");
        pthread_exit(NULL);
    }

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Comedi device opened");
    /*Send zero
    for (i = 0; i < args->n_out_chan; i++) {
        out_values[i] = 0;
    }
    if (daq_write(session, args->n_out_chan, args->out_channels, out_values) != OK) {
        fprintf(stderr, "RT_THREAD: error writing to DAQ.\n");
        daq_close_device ((void**) &dsc);
        pthread_exit(NULL);
    }*/

    if (daq_create_session ((void**) &dsc, &session) != OK) {
        fprintf(stderr, "RT_THREAD: error creating DAQ session.\n");
        daq_close_device ((void**) &dsc);
        pthread_exit(NULL);
    }

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Comedi started");


    prepare_real_time(id);

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Real-time prepared");

    args->ini(&min_model, &min_abs_model, &max_model);

    //printf("min %f    min_abs %f   max %f\n", min_model, min_abs_model, max_model);


    /************************
    CALIBRADO ESPACIO-TEMPORAL
    ************************/
    if (args->n_in_chan > 0) {
	    if ( ini_recibido (&min_real, &min_abs_real, &max_real, &max_real_relativo, &period_disp_real, session, calib_chan, args->period, args->freq, args->filename) == -1 ) {
			free_pointers(1, &session);
            daq_close_device ((void**) &dsc);
	        pthread_exit(NULL);
		}
		//printf("Periodo disparo = %f\n", period_disp_real);
        if (args->firing_rate != -1) period_disp_real = args->firing_rate;
	    calcula_escala (min_abs_model, max_model, min_abs_real, max_real, &scale_virtual_to_real, &scale_real_to_virtual, &offset_virtual_to_real, &offset_real_to_virtual);
        /*printf("min_abs_model=%f\n", min_abs_model);
        printf("max_model=%f\n", max_model);
        printf("min_abs_real=%f\n", min_abs_real);
        printf("max_real=%f\n", max_real);*/

        rafaga_viva_pts = args->freq * period_disp_real;
        args->s_points = args->rafaga_modelo_pts / rafaga_viva_pts;
    } else {
        /*MODO SIN ENTRADA*/
    	scale_real_to_virtual = 1;
	    scale_virtual_to_real = 1;
	    offset_virtual_to_real = 0;
	    offset_real_to_virtual = 0;
        args->s_points = 1;
        period_disp_real = 0;
    }



    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Create calibration struct");

    /*CALIBRATION STRUCT*/
    cal_struct = (calibration_args *) malloc (sizeof(calibration_args));
    cal_struct->min_abs_model=min_abs_model;
    cal_struct->max_model=max_model;
    cal_struct->min_abs_real=min_abs_real;
    cal_struct->max_real=max_real;
    cal_struct->min_real=min_real;
    cal_struct->max_real_relativo=max_real_relativo;
    cal_struct->scale_virtual_to_real=scale_virtual_to_real;
    cal_struct->scale_real_to_virtual=scale_real_to_virtual;
    cal_struct->offset_virtual_to_real=offset_virtual_to_real;
    cal_struct->offset_real_to_virtual=offset_real_to_virtual;
    cal_struct->g_real_to_virtual = NULL;
    cal_struct->g_virtual_to_real = NULL;


    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Calibration struct created");

    /*CALIBRADO TEMPORAL*/
    msg2.i = args->s_points;
    msg2.t_unix = period_disp_real;
    msg2.id = 1;
    send_to_queue(args->msqid, &msg2);

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
    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Syn model: %d", args->type_syn);
    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Syn calibration: %d", args->calibration);

    //Synapse type
    switch (args->type_syn) {
		case ELECTRIC:
			syn_aux_params = NULL; 

            if(args->calibration != 0 && args->calibration != 6){
                if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Inside autocal");
                args->g_virtual_to_real[0] = 0.0;
                args->g_real_to_virtual[0] = 0.0;
            }
    		msg.n_g = 2;
            if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Elec set finalized");
			break;

		case CHEMICAL:
			syn_aux_params = (double *) malloc (sizeof(double) * 8);
			syn_aux_params[SC_DT] = args->dt;
			syn_aux_params[SC_OLD] = 0;
            syn_aux_params[SC_BT] = 1;
            syn_aux_params[SC_MS_K1] = args->syn_gradual_k1;//1;
            syn_aux_params[SC_MS_K2] = args->syn_gradual_k2;//0.03;
            syn_aux_params[SC_VFAST] = args->syn_gradual_vfast/100;
            syn_aux_params[SC_VSLOW] = args->syn_gradual_vslow/100;

            /*printf("Antes rvf%p\n", &args->g_real_to_virtual[G_FAST]);
            printf("Antes rvs%p\n", &args->g_real_to_virtual[G_SLOW]);
            printf("Antes vrf%p\n", &args->g_virtual_to_real[G_FAST]);
            printf("Antes vrs%p\n", &args->g_virtual_to_real[G_SLOW]);*/

            /*if (args->model==0){
                g_virtual_to_real[G_FAST] = 0.0;
                g_virtual_to_real[G_SLOW] = 0.02;
                g_real_to_virtual[G_FAST] = 0.0;
                g_real_to_virtual[G_SLOW] = 0.04;

            }*/

            if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Calibration mode = %i", args->calibration);

            if(args->calibration == 7){
                cal_struct->g_virtual_to_real = (double *) malloc (sizeof(double) * 2);
                cal_struct->g_real_to_virtual = (double *) malloc (sizeof(double) * 2);
                copy_1d_array(args->g_virtual_to_real, cal_struct->g_virtual_to_real, 2);
                copy_1d_array(args->g_real_to_virtual, cal_struct->g_real_to_virtual, 2);

                if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Map g_V-R_fast = %f", args->g_virtual_to_real[G_FAST]);
                if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Map g_V-R_slow = %f", args->g_virtual_to_real[G_SLOW]);
                if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Map g_R-V_fast = %f", args->g_real_to_virtual[G_FAST]);
                if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Map g_R-V_slow = %f", args->g_real_to_virtual[G_SLOW]);

                args->g_virtual_to_real[G_FAST] = 0.0;
                args->g_virtual_to_real[G_SLOW] = 0.0;
                args->g_real_to_virtual[G_FAST] = 0.0;
                args->g_real_to_virtual[G_SLOW] = 0.0;

                infinite_loop = TRUE;
            }

            if(args->calibration == 8){
                syn_aux_params[SC_MS_K1] = ini_k1;//1;
                syn_aux_params[SC_MS_K2] = ini_k2;//0.03;
            }
    		
    		msg.n_g = 4;
			break;

        case PRINZ:
            syn_aux_params = (double *) malloc (sizeof(double) * 8);
            syn_aux_params[PR_AUX_DT] = args->dt;
            syn_aux_params[PR_AUX_S_OLD] = 0;
            syn_aux_params[PR_AUX_V_TH] = args->syn_gradual_vslow/100.0;
            syn_aux_params[PR_AUX_DELTA] = args->syn_gradual_vfast/100.0;
            syn_aux_params[PR_AUX_K_Live_Model] = args->syn_gradual_k1;
            syn_aux_params[PR_AUX_K_Model_Live] = args->syn_gradual_k2;

            msg.n_g = 2;
            break;

		default:
            free_pointers(4, &session, &cal_struct->g_virtual_to_real, &cal_struct->g_real_to_virtual, &cal_struct);
			daq_close_device ((void**) &dsc);
        	pthread_exit(NULL);
	}

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Preparation done");

    //VARIABLES

    double sum_ecm;
    int t_obs=5;
    int sum_ecm_cont=0;
    double res_phase = 0;
    int cont_lectura=0;
    int size_lectura=2*args->freq;

    lectura_a = (double *) malloc (sizeof(double) * 2*args->freq);
    lectura_b = (double *) malloc (sizeof(double) * 2*args->freq);
    lectura_t = (double *) malloc (sizeof(double) * 2*args->freq);

    ret_values = (double *) malloc (sizeof(double) * args->n_in_chan);
    out_values = (double *) malloc (sizeof(double) * args->n_out_chan);

    clock_gettime(CLOCK_MONOTONIC, &ts_target);
    ts_assign (&ts_start,  ts_target);
    ts_add_time(&ts_target, 0, args->period);

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Before control record");
    /*Send zero*/
    for (i = 0; i < args->n_out_chan; i++) {
        out_values[i] = 0;
    }
    if (daq_write(session, args->n_out_chan, args->out_channels, out_values) != OK) {
        fprintf(stderr, "RT_THREAD: error writing to DAQ.\n");
        daq_close_device ((void**) &dsc);
        pthread_exit(NULL);
    }

    /************************
    BEFORE CONTROL RECORD
    ************************/
    loop_points = args->before * args->freq * args->s_points;
    for (i = 0; i < loop_points; i++) {
        if (i % args->s_points == 0) {
            clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &ts_target, NULL);
            clock_gettime(CLOCK_MONOTONIC, &ts_iter);

            ts_substraction(&ts_target, &ts_iter, &ts_result);
            msg.id = 1;
            msg.extra = 0;
            msg.i = cont_send;
            cont_send++;
            msg.v_model_scaled = args->vars[0] * scale_virtual_to_real + offset_virtual_to_real;
            msg.v_model = args->vars[0];
            msg.c_model = 0;
            msg.lat = ts_result.tv_sec * NSEC_PER_SEC + ts_result.tv_nsec;

            ts_substraction(&ts_start, &ts_iter, &ts_result);
            msg.t_absol = (ts_result.tv_sec * NSEC_PER_SEC + ts_result.tv_nsec) * 0.000001;
            msg.t_unix = (ts_iter.tv_sec * NSEC_PER_SEC + ts_iter.tv_nsec) * 0.000001;

            if (args->n_out_chan >= 1) out_values[0] = msg.c_model;
            if (args->n_out_chan >= 2) out_values[1] = msg.v_model_scaled;

            msg.data_in = (double *) malloc (sizeof(double) * args->n_in_chan);
            msg.data_out = (double *) malloc (sizeof(double) * args->n_out_chan);

            copy_1d_array(ret_values, msg.data_in, args->n_in_chan);
            copy_1d_array(out_values, msg.data_out, args->n_out_chan);


            msg.g_real_to_virtual = (double *) malloc (sizeof(double) * msg.n_g);
            msg.g_virtual_to_real = (double *) malloc (sizeof(double) * msg.n_g);

            copy_1d_array(args->g_real_to_virtual, msg.g_real_to_virtual, msg.n_g);
            copy_1d_array(args->g_virtual_to_real, msg.g_virtual_to_real, msg.n_g);

            if (send_to_queue(args->msqid, &msg) == ERR) lost_msg++;

            ts_add_time(&ts_target, 0, args->period);

            if (daq_read(session, args->n_in_chan, args->in_channels, ret_values) != 0) {
                free_pointers(4, &session, &cal_struct->g_virtual_to_real, &cal_struct->g_real_to_virtual, &cal_struct);
                daq_close_device ((void**) &dsc);
                free_pointers(8, &syn_aux_params, &(args->in_channels), &(args->out_channels), &lectura_a, &lectura_b, &lectura_t, &ret_values, &out_values);
                pthread_exit(NULL);
            }

        }
        msg.c_real = 0;
        args->func(args->dim, args->dt, args->vars, args->params, c_real);
    }

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: before loop end");

    /************************
    INITIAL INTERACTION
    ************************/

    loop_points = t_obs * args->freq * args->s_points;
    for (i = 0; i < loop_points; i++) {
        if (i % args->s_points == 0) {
            clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &ts_target, NULL);
            clock_gettime(CLOCK_MONOTONIC, &ts_iter);

            ts_substraction(&ts_target, &ts_iter, &ts_result);
            msg.id = 1;
            msg.extra = 0;
            msg.i = cont_send;
            cont_send++;
            msg.v_model_scaled = args->vars[0] * scale_virtual_to_real + offset_virtual_to_real;
            msg.v_model = args->vars[0];
            msg.c_model = 0;
            msg.lat = ts_result.tv_sec * NSEC_PER_SEC + ts_result.tv_nsec;

            ts_substraction(&ts_start, &ts_iter, &ts_result);
            msg.t_absol = (ts_result.tv_sec * NSEC_PER_SEC + ts_result.tv_nsec) * 0.000001;
            msg.t_unix = (ts_iter.tv_sec * NSEC_PER_SEC + ts_iter.tv_nsec) * 0.000001;

            if (args->n_out_chan >= 1) out_values[0] = msg.c_model;
            if (args->n_out_chan >= 2) out_values[1] = msg.v_model_scaled;

            msg.data_in = (double *) malloc (sizeof(double) * args->n_in_chan);
            msg.data_out = (double *) malloc (sizeof(double) * args->n_out_chan);

            copy_1d_array(ret_values, msg.data_in, args->n_in_chan);
            copy_1d_array(out_values, msg.data_out, args->n_out_chan);

            if (daq_write(session, args->n_out_chan, args->out_channels, out_values) != OK) {
                fprintf(stderr, "RT_THREAD: error writing to DAQ.\n");
                daq_close_device ((void**) &dsc);
                pthread_exit(NULL);
            }

            /*CALIBRACION*/
            if(args->calibration == 1){
                //Electrica en fase
                double ecm_old=ecm_result;
                calc_ecm(args->vars[0] * scale_virtual_to_real + offset_virtual_to_real, ret_values[0], rafaga_viva_pts, &ecm_result);
                msg.ecm = ecm_result;
                if(ecm_result!=0 && ecm_old!=ecm_result){
                    sum_ecm+=ecm_result;
                    sum_ecm_cont++;
                }
            }else if(args->calibration  == 4){
                 if(cont_lectura<size_lectura){
                    /*Guardamos info*/
                    lectura_b[cont_lectura]=args->vars[0] * scale_virtual_to_real + offset_virtual_to_real;
                    lectura_a[cont_lectura]=ret_values[0];
                    lectura_t[cont_lectura]=msg.t_absol;
                    cont_lectura++;
                }else{
                    calc_phase (lectura_b, lectura_a, lectura_t, size_lectura, max_real_relativo, min_real, &res_phase, args->anti);
                    msg.ecm = res_phase;
                    cont_lectura=0;
                }
            }

            msg.g_real_to_virtual = (double *) malloc (sizeof(double) * msg.n_g);
            msg.g_virtual_to_real = (double *) malloc (sizeof(double) * msg.n_g);

            copy_1d_array(args->g_real_to_virtual, msg.g_real_to_virtual, msg.n_g);
            copy_1d_array(args->g_virtual_to_real, msg.g_virtual_to_real, msg.n_g);

            if (send_to_queue(args->msqid, &msg) == ERR) lost_msg++;

            ts_add_time(&ts_target, 0, args->period);

            if (daq_read(session, args->n_in_chan, args->in_channels, ret_values) != 0) {
                free_pointers(4, &session, &cal_struct->g_virtual_to_real, &cal_struct->g_real_to_virtual, &cal_struct);
                daq_close_device ((void**) &dsc);
                free_pointers(8, &syn_aux_params, &(args->in_channels), &(args->out_channels), &lectura_a, &lectura_b, &lectura_t, &ret_values, &out_values);
                pthread_exit(NULL);
            }
        }
        msg.c_real = 0;
        args->func(args->dim, args->dt, args->vars, args->params, c_real);
    }

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: initial interaction loop end");

    if(args->calibration == 1){
        sum_ecm = sum_ecm / sum_ecm_cont;
        set_is_syn_by_percentage(sum_ecm, args->auto_cal_val_1);
    }

    /*PULSOS DE SINCRONIZACION*/
    if (SYNC == TRUE) {
        if (args->n_out_chan >= 1) out_values[0] = 0;
        if (args->n_out_chan >= 2) out_values[1] = -10;

        if (daq_write(session, args->n_out_chan, args->out_channels, out_values) != OK) {
            fprintf(stderr, "RT_THREAD: error writing to DAQ.\n");
            daq_close_device ((void**) &dsc);
            pthread_exit(NULL);
        }

        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &ts_target, NULL);
        ts_add_time(&ts_target, 0, args->period);

        if (args->n_out_chan >= 2) out_values[1] = 10;

        if (daq_write(session, args->n_out_chan, args->out_channels, out_values) != OK) {
            fprintf(stderr, "RT_THREAD: error writing to DAQ.\n");
            daq_close_device ((void**) &dsc);
            pthread_exit(NULL);
        }
    }


    /************************
    INTERACTION
    ************************/

    loop_points = args->time_var * args->freq * args->s_points;

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Interaction started. Points = %ld", loop_points);

    for (i = 0; i < loop_points || infinite_loop == TRUE; i++) {
        /*TOCA INTERACCION*/
        if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Inside the loop = %ld\n", i);


        if (i % args->s_points == 0) {
            /*ESPERA HASTA EL MOMENTO DETERMINADO*/
            clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &ts_target, NULL);
            clock_gettime(CLOCK_MONOTONIC, &ts_iter);
            ts_substraction(&ts_target, &ts_iter, &ts_result);

            if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Inside the loop and the if = %ld\n", i);

            /*GUARDAR INFO*/
            msg.id = 1;
            msg.extra = 0;
            msg.i = cont_send;
            cont_send++;

            if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Doing stuff at the loop");

            msg.v_model_scaled = args->vars[0] * scale_virtual_to_real + offset_virtual_to_real;
            msg.v_model = args->vars[0];
            msg.lat = ts_result.tv_sec * NSEC_PER_SEC + ts_result.tv_nsec;

            /*SINAPSIS Y CORRIENTE EN VIRTUAL TO REAL*/
            //printf("g_f = %f // g_s = %f\n", args->g_virtual_to_real[G_FAST], args->g_virtual_to_real[G_SLOW]);

            if (args->type_syn == CHEMICAL) {
                syn_aux_params[SC_MIN] = min_abs_model * scale_virtual_to_real + offset_virtual_to_real;
                syn_aux_params[SC_MAX] = max_real * scale_virtual_to_real + offset_virtual_to_real;
            } else if (args->type_syn == PRINZ) {
                syn_aux_params[PR_AUX_MIN] = min_abs_model * scale_virtual_to_real + offset_virtual_to_real;
                syn_aux_params[PR_AUX_MAX] = max_real * scale_virtual_to_real + offset_virtual_to_real;
                syn_aux_params[PR_AUX_K] = syn_aux_params[PR_AUX_K_Model_Live];
            }
            
            args->syn(ret_values[0], args->vars[0] * scale_virtual_to_real + offset_virtual_to_real, args->g_virtual_to_real, &c_model, syn_aux_params);
            msg.c_model = -(args->anti * c_model);
            //printf("c_model = %f\n", msg.c_model);

            if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Doing more stuff at the loop");

            /*GUARDAR INFO*/
            ts_substraction(&ts_start, &ts_iter, &ts_result);
            msg.t_absol = (ts_result.tv_sec * NSEC_PER_SEC + ts_result.tv_nsec) * 0.000001;
            msg.t_unix = (ts_iter.tv_sec * NSEC_PER_SEC + ts_iter.tv_nsec) * 0.000001;

            /*ENVIO POR LA TARJETA*/
            if (args->n_out_chan >= 1) out_values[0] = msg.c_model;
            if (args->n_out_chan >= 2) out_values[1] = msg.v_model_scaled;

            /*GUARDAR INFO*/
            /*msg.g_real_to_virtual = g_real_to_virtual;
            msg.g_virtual_to_real = g_virtual_to_real;*/
            msg.data_in = (double *) malloc (sizeof(double) * args->n_in_chan);
            msg.data_out = (double *) malloc (sizeof(double) * args->n_out_chan);
            copy_1d_array(ret_values, msg.data_in, args->n_in_chan);
            copy_1d_array(out_values, msg.data_out, args->n_out_chan);

            msg.g_real_to_virtual = (double *) malloc (sizeof(double) * msg.n_g);
            msg.g_virtual_to_real = (double *) malloc (sizeof(double) * msg.n_g);
            copy_1d_array(args->g_real_to_virtual, msg.g_real_to_virtual, msg.n_g);
            copy_1d_array(args->g_virtual_to_real, msg.g_virtual_to_real, msg.n_g);

            if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Before writing to device");

            /*ENVIO POR LA TARJETA*/
            if (daq_write(session, args->n_out_chan, args->out_channels, out_values) != OK) {
                fprintf(stderr, "RT_THREAD: error writing to DAQ.\n");
                daq_close_device ((void**) &dsc);
                pthread_exit(NULL);
            }

            /*CALIBRACION*/
            end_loop = auto_calibration(
                                args, cal_struct, ret_values, rafaga_viva_pts, &ecm_result,
                                &msg, args->g_virtual_to_real, args->g_real_to_virtual,
                                lectura_a, lectura_b, lectura_t, size_lectura, cont_send,
                                syn_aux_params, ini_k1, ini_k2
                                );

            if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: After ret_auto_cal");

            /*GUARDAR INFO*/
            if (send_to_queue(args->msqid, &msg) == ERR) lost_msg++;

            /*TIEMPO*/
            ts_add_time(&ts_target, 0, args->period);

            /*END*/
            if(end_loop==TRUE)
                break;

            /*LECTURA DE LA TARJETA*/
            if (daq_read(session, args->n_in_chan, args->in_channels, ret_values) != 0) {
                
                /*ALGO FALLO*/
                for (i = 0; i < args->n_out_chan; i++) {
                    out_values[i] = 0;
                }
                
                if (daq_write(session, args->n_out_chan, args->out_channels, out_values) != OK) {
                    fprintf(stderr, "RT_THREAD: error writing to DAQ.\n");
                    daq_close_device ((void**) &dsc);
                    pthread_exit(NULL);
                }

                free_pointers(4, &session, &cal_struct->g_virtual_to_real, &cal_struct->g_real_to_virtual, &cal_struct);
                daq_close_device ((void**) &dsc);
                free_pointers(8, &syn_aux_params, &(args->in_channels), &(args->out_channels), &lectura_a, &lectura_b, &lectura_t, &ret_values, &out_values);
                pthread_exit(NULL);
            }
        }

        /*CALCULO CORRIENTE E INTEGRACIÓN DEL MODELO*/
        if (args->type_syn == CHEMICAL) {
        	syn_aux_params[SC_MIN] = min_abs_real * scale_real_to_virtual + offset_real_to_virtual;
            syn_aux_params[SC_MAX] = max_real * scale_real_to_virtual + offset_real_to_virtual;
        	args->syn(args->vars[0], ret_values[0] * scale_real_to_virtual + offset_real_to_virtual, args->g_real_to_virtual, &c_real, syn_aux_params);
        	
        	syn_aux_params[SC_MIN] = min_abs_real;
            syn_aux_params[SC_MAX] = max_real;
        	args->syn(args->vars[0]*scale_virtual_to_real + offset_virtual_to_real, ret_values[0], args->g_real_to_virtual, &(msg.c_real), syn_aux_params);
    	} else if (args->type_syn == PRINZ) {
            syn_aux_params[PR_AUX_K] = syn_aux_params[PR_AUX_K_Live_Model];

            syn_aux_params[PR_AUX_MIN] = min_abs_real * scale_real_to_virtual + offset_real_to_virtual;
            syn_aux_params[PR_AUX_MAX] = max_real * scale_real_to_virtual + offset_real_to_virtual;
            args->syn(args->vars[0], ret_values[0] * scale_real_to_virtual + offset_real_to_virtual, args->g_real_to_virtual, &c_real, syn_aux_params);

            syn_aux_params[PR_AUX_MIN] = min_abs_real;
            syn_aux_params[PR_AUX_MAX] = max_real;
            args->syn(args->vars[0]*scale_virtual_to_real + offset_virtual_to_real, ret_values[0], args->g_real_to_virtual, &(msg.c_real), syn_aux_params);
        } else {
    		args->syn(args->vars[0], ret_values[0] * scale_real_to_virtual + offset_real_to_virtual, args->g_real_to_virtual, &c_real, syn_aux_params);
    		args->syn(args->vars[0]*scale_virtual_to_real + offset_virtual_to_real, ret_values[0], args->g_real_to_virtual, &(msg.c_real), syn_aux_params);
    	}

    	msg.c_real = -(args->anti * msg.c_real);
        
        args->func(args->dim, args->dt, args->vars, args->params, args->anti * c_real);
    }

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: main loop end");
    /*Send zero*/
    for (i = 0; i < args->n_out_chan; i++) {
        out_values[i] = 0;
    }
    if (daq_write(session, args->n_out_chan, args->out_channels, out_values) != OK) {
        fprintf(stderr, "RT_THREAD: error writing to DAQ.\n");
        daq_close_device ((void**) &dsc);
        pthread_exit(NULL);
    }


    /************************
    AFTER CONTROL RECORD
    ************************/

    loop_points = args->before * args->freq * args->s_points;
    for (i = 0; i < loop_points; i++) {
        if (i % args->s_points == 0) {
            clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &ts_target, NULL);
            clock_gettime(CLOCK_MONOTONIC, &ts_iter);

            ts_substraction(&ts_target, &ts_iter, &ts_result);
            msg.id = 1;
            msg.extra = 0;
            msg.i = cont_send;
            cont_send++;
            msg.v_model_scaled = args->vars[0] * scale_virtual_to_real + offset_virtual_to_real;
            msg.v_model = args->vars[0];
            msg.c_model = 0;
            msg.lat = ts_result.tv_sec * NSEC_PER_SEC + ts_result.tv_nsec;

            ts_substraction(&ts_start, &ts_iter, &ts_result);
            msg.t_absol = (ts_result.tv_sec * NSEC_PER_SEC + ts_result.tv_nsec) * 0.000001;
            msg.t_unix = (ts_iter.tv_sec * NSEC_PER_SEC + ts_iter.tv_nsec) * 0.000001;

            if (args->n_out_chan >= 1) out_values[0] = msg.c_model;
            if (args->n_out_chan >= 2) out_values[1] = msg.v_model_scaled;

            msg.data_in = (double *) malloc (sizeof(double) * args->n_in_chan);
            msg.data_out = (double *) malloc (sizeof(double) * args->n_out_chan);

            copy_1d_array(ret_values, msg.data_in, args->n_in_chan);
            copy_1d_array(out_values, msg.data_out, args->n_out_chan);


            msg.g_real_to_virtual = (double *) malloc (sizeof(double) * msg.n_g);
            msg.g_virtual_to_real = (double *) malloc (sizeof(double) * msg.n_g);

            copy_1d_array(args->g_real_to_virtual, msg.g_real_to_virtual, msg.n_g);
            copy_1d_array(args->g_virtual_to_real, msg.g_virtual_to_real, msg.n_g);

            if (send_to_queue(args->msqid, &msg) == ERR) lost_msg++;

            ts_add_time(&ts_target, 0, args->period);

            if (daq_read(session, args->n_in_chan, args->in_channels, ret_values) != 0) {
                free_pointers(4, &session, &cal_struct->g_virtual_to_real, &cal_struct->g_real_to_virtual, &cal_struct);
                daq_close_device ((void**) &dsc);
                free_pointers(8, &syn_aux_params, &(args->in_channels), &(args->out_channels), &lectura_a, &lectura_b, &lectura_t, &ret_values, &out_values);
                pthread_exit(NULL);
            }

        }
        msg.c_real = 0;
        args->func(args->dim, args->dt, args->vars, args->params, c_real);
    }

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: after loop end");

    /*Send zero*/
    for (i = 0; i < args->n_out_chan; i++) {
    	out_values[i] = 0;
    }
    if (daq_write(session, args->n_out_chan, args->out_channels, out_values) != OK) {
        fprintf(stderr, "RT_THREAD: error writing to DAQ.\n");
        daq_close_device ((void**) &dsc);
        pthread_exit(NULL);
    }

    free_pointers(4, &session, &cal_struct->g_real_to_virtual, &cal_struct->g_virtual_to_real, &cal_struct);
    daq_close_device ((void**) &dsc);

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Deviced closed");

    msg.id = 2;
    if (send_to_queue(args->msqid, &msg) == ERR) {
        perror("Closing message not sent");
    }

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: Closing message sent");

    free_pointers(8, &syn_aux_params, &(args->in_channels), &(args->out_channels), &lectura_a, &lectura_b, &lectura_t, &ret_values, &out_values);

    if (DEBUG == 1) syslog(LOG_INFO, "RT_THREAD: End. Not sent messages: %d\n", lost_msg);

    pthread_exit(NULL);
}
