#include "../includes/rt_thread_functions.h"

/************************
GLOBAL VARIABLES
************************/
comedi_t * d = NULL;
Comedi_session * session = NULL;
rt_args * args;
calibration_args * cal_struct = NULL;
message msg;
double * syn_aux_params = NULL;

double * lectura_a = NULL;
double * lectura_b = NULL;
double * lectura_t = NULL;
double * ret_values = NULL;
double * out_values = NULL;
int debug = 1;

/************************
RT CLEANUP
************************/
void rt_cleanup () {
    int i = 0;

    printf("\n" PRINT_RED "SIGUSR1 termination to rt_thread." PRINT_RESET "\n");

    if (session != NULL) {
        for (i = 0; i < args->n_out_chan; i++) {
            out_values[i] = 0;
        }
        
        write_comedi(session, args->n_out_chan, args->out_channels, out_values);
    }

    if (d != NULL) {
        free_pointers(1, &session);
        close_device_comedi(d);
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

    for (i = 0; i < n_elems; ++i) {
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

    if (debug == 1) syslog(LOG_INFO, "RT_THREAD: Start");

    //Declarations
    int i, cont_send = 0, lost_msg = 0;
    
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
    double rafaga_viva_pts;

    double retval = 0;
    double c_real = 0, c_model = 0;

    double ecm_result = 0;

    id = pthread_self();
    args = arg;
    msg.c_real = c_real;

    int calib_chan = 0;

    if (signal(SIGUSR1, rt_cleanup) == SIG_ERR) printf("Error catching SIGUSR1 at rt_thread.\n");

    if (debug == 1) syslog(LOG_INFO, "RT_THREAD: After signal");

    msg.n_in_chan = args->n_in_chan;
    msg.n_out_chan = args->n_out_chan;
    msg.autocal = args->calibration;
    msg.data_in = NULL;
    msg.data_out = NULL;
    msg.g_virtual_to_real = NULL;
    msg.g_real_to_virtual = NULL;

    if (debug == 1) syslog(LOG_INFO, "RT_THREAD: Before Comedi");

    //Comedi & RT
    d = open_device_comedi("/dev/comedi0");

    if (debug == 1) syslog(LOG_INFO, "RT_THREAD: Comedi device opened");

    if (create_session_comedi(d, AREF_GROUND, &session) != OK) {
        close_device_comedi(d);
        pthread_exit(NULL);
    }

    if (debug == 1) syslog(LOG_INFO, "RT_THREAD: Comedi started");


    prepare_real_time(id);

    if (debug == 1) syslog(LOG_INFO, "RT_THREAD: Real-time prepared");

    args->ini(args->vars, &min_model, &min_abs_model, &max_model);


    /************************
    CALIBRADO ESPACIO-TEMPORAL
    ************************/
    if (args->n_in_chan > 0) {
	    if ( ini_recibido (&min_real, &min_abs_real, &max_real, &max_real_relativo, &period_disp_real, session, calib_chan, args->period, args->freq, args->filename) == -1 ) {
			free_pointers(1, &session);
            close_device_comedi(d);
	        pthread_exit(NULL);
		}
		//printf("Periodo disparo = %f\n", period_disp_real);
        //period_disp_real = 0.27;
	    calcula_escala (min_abs_model, max_model, min_abs_real, max_real, &scale_virtual_to_real, &scale_real_to_virtual, &offset_virtual_to_real, &offset_real_to_virtual);
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

    //Synapse type

    switch (args->type_syn) {
		case ELECTRIC:
			syn_aux_params = NULL; 

            if(args->calibration != 0 && args->calibration != 6){
                args->g_virtual_to_real[0] = 0.0;
                args->g_real_to_virtual[0] = 0.0;
            }
    		msg.n_g = 1;

			break;
		case CHEMICAL:
			syn_aux_params = (double *) malloc (sizeof(double) * 6);
			syn_aux_params[SC_DT] = args->dt;
			syn_aux_params[SC_OLD] = 0;
            syn_aux_params[SC_BT] = period_disp_real;
            syn_aux_params[SC_MS_K1] = 1;//1;
            syn_aux_params[SC_MS_K2] = 0.03;//0.03;


            /*if (args->model==0){
                g_virtual_to_real[G_FAST] = 0.0;
                g_virtual_to_real[G_SLOW] = 0.02;
                g_real_to_virtual[G_FAST] = 0.0;
                g_real_to_virtual[G_SLOW] = 0.04;

            }*/

            if(args->calibration == 7){
                args->g_virtual_to_real[G_FAST] = 0.0;
                args->g_virtual_to_real[G_SLOW] = 0.0;
                args->g_real_to_virtual[G_FAST] = 0.0;
                args->g_real_to_virtual[G_SLOW] = 0.0;
            }

        
            if(args->calibration == 8){
                syn_aux_params[SC_MS_K1] = ini_k1;//1;
                syn_aux_params[SC_MS_K2] = ini_k2;//0.03;
            }
    		
    		msg.n_g = 2;

			break;
		default:
            free_pointers(2, &session, &cal_struct);
			close_device_comedi(d);
        	pthread_exit(NULL);
	}

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

    /************************
    INITIAL INTERACTION
    ************************/

    if (debug == 1) syslog(LOG_INFO, "RT_THREAD: Initial interaction");

    clock_gettime(CLOCK_MONOTONIC, &ts_target);
    ts_assign (&ts_start,  ts_target);
    ts_add_time(&ts_target, 0, args->period);

    for (i = 0; i < t_obs * args->freq * args->s_points; i++) {
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

            write_comedi(session, args->n_out_chan, args->out_channels, out_values);

            /*CALIBRACION*/
            if(args->calibration == 1){
                //Electrica en fase
                double ecm_old=ecm_result;
                int ret_ecm = calc_ecm(args->vars[0] * scale_virtual_to_real + offset_virtual_to_real, ret_values[0], rafaga_viva_pts, &ecm_result);
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
                    int is_syn = calc_phase (lectura_b, lectura_a, lectura_t, size_lectura, max_real_relativo, min_real, &res_phase, args->anti);
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

            if (read_comedi(session, args->n_in_chan, args->in_channels, ret_values) != 0) {
                free_pointers(2, &session, &cal_struct);
                close_device_comedi(d);
                free_pointers(8, &syn_aux_params, &(args->in_channels), &(args->out_channels), &lectura_a, &lectura_b, &lectura_t, &ret_values, &out_values);
                pthread_exit(NULL);
            }
        }
        msg.c_real = 0;
        args->func(args->dim, args->dt, args->vars, args->params, c_real);
    }

    if(args->calibration == 1){
        sum_ecm = sum_ecm / sum_ecm_cont;
        set_is_syn_by_percentage(sum_ecm);
    }
    int cont_6=0;
    int counter_mapa=0;
    int cal_7=TRUE;


    /*PULSOS DE SINCRONIZACION*/
    if (args->n_out_chan >= 1) out_values[0] = 0;
    if (args->n_out_chan >= 2) out_values[1] = -10;
    write_comedi(session, args->n_out_chan, args->out_channels, out_values);
    clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &ts_target, NULL);
    ts_add_time(&ts_target, 0, args->period);
    
    if (args->n_out_chan >= 2) out_values[1] = 10;
    
    write_comedi(session, args->n_out_chan, args->out_channels, out_values);

    /************************
    INTERACTION
    ************************/

    if (debug == 1) syslog(LOG_INFO, "RT_THREAD: Interaction started. Points = %li", args->points);

    for (i = 0; i < args->points * args->s_points; i++) {
        /*TOCA INTERACCION*/
        if (i % args->s_points == 0) {
            
            /*ESPERA HASTA EL MOMENTO DETERMINADO*/
            clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &ts_target, NULL);
            clock_gettime(CLOCK_MONOTONIC, &ts_iter);
            ts_substraction(&ts_target, &ts_iter, &ts_result);

            /*GUARDAR INFO*/
            msg.id = 1;
            msg.extra = 0;
            msg.i = cont_send;
            cont_send++;
            msg.v_model_scaled = args->vars[0] * scale_virtual_to_real + offset_virtual_to_real;
            msg.v_model = args->vars[0];
            msg.lat = ts_result.tv_sec * NSEC_PER_SEC + ts_result.tv_nsec;

            /*SINAPSIS Y CORRIENTE EN VIRTUAL TO REAL*/
            if (args->type_syn==CHEMICAL)
                syn_aux_params[SC_MIN] = min_abs_model * scale_virtual_to_real + offset_virtual_to_real;
            args->syn(args->vars[0] * scale_virtual_to_real + offset_virtual_to_real, ret_values[0], args->g_virtual_to_real, &c_model, syn_aux_params);
            msg.c_model=c_model;

            /*GUARDAR INFO*/
            ts_substraction(&ts_start, &ts_iter, &ts_result);
            msg.t_absol = (ts_result.tv_sec * NSEC_PER_SEC + ts_result.tv_nsec) * 0.000001;
            msg.t_unix = (ts_iter.tv_sec * NSEC_PER_SEC + ts_iter.tv_nsec) * 0.000001;

            /*ENVIO POR LA TARJETA*/
            if (args->n_out_chan >= 1) out_values[0] = c_model;
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

            /*ENVIO POR LA TARJETA*/
            write_comedi(session, args->n_out_chan, args->out_channels, out_values);

            /*CALIBRACION*/
            auto_calibration(
                            args, cal_struct, ret_values, rafaga_viva_pts, &ecm_result, 
                            &msg, args->g_virtual_to_real, args->g_real_to_virtual,
                            lectura_a, lectura_b, lectura_t, size_lectura, cont_send,
                            syn_aux_params, ini_k1, ini_k2
                            );
            
            /*GUARDAR INFO*/
            if (send_to_queue(args->msqid, &msg) == ERR) lost_msg++;

            /*TIEMPO*/
            ts_add_time(&ts_target, 0, args->period);

            /*LECTURA DE LA TARJETA*/
            if (read_comedi(session, args->n_in_chan, args->in_channels, ret_values) != 0) {
                /*ALGO FALLO*/
                for (i = 0; i < args->n_out_chan; i++) {
                    out_values[i] = 0;
                }
                write_comedi(session, args->n_out_chan, args->out_channels, out_values);
                free_pointers(2, &session, &cal_struct);
                close_device_comedi(d);
                free_pointers(8, &syn_aux_params, &(args->in_channels), &(args->out_channels), &lectura_a, &lectura_b, &lectura_t, &ret_values, &out_values);
                pthread_exit(NULL);
            }
        }

        /*CALCULO CORRIENTE E INTEGRACIÓN DEL MODELO*/
        if (args->type_syn==CHEMICAL)
            syn_aux_params[SC_MIN] = min_abs_real * scale_real_to_virtual + offset_real_to_virtual;
        args->syn(ret_values[0] * scale_real_to_virtual + offset_real_to_virtual, args->vars[0], args->g_real_to_virtual, &c_real, syn_aux_params);
        if (args->type_syn==CHEMICAL)
            syn_aux_params[SC_MIN] = min_abs_real;
        args->syn(ret_values[0], args->vars[0]*scale_virtual_to_real + offset_virtual_to_real, args->g_real_to_virtual, &(msg.c_real), syn_aux_params);
        args->func(args->dim, args->dt, args->vars, args->params, args->anti*c_real);
    }

    for (i = 0; i < args->n_out_chan; i++) {
    	out_values[i] = 0;
    }
    write_comedi(session, args->n_out_chan, args->out_channels, out_values);
    free_pointers(2, &session, &cal_struct);
    close_device_comedi(d);

    msg.id = 2;
    if (send_to_queue(args->msqid, &msg) == ERR) {
        perror("Closing message not sent");
    }

    free_pointers(8, &syn_aux_params, &(args->in_channels), &(args->out_channels), &lectura_a, &lectura_b, &lectura_t, &ret_values, &out_values);

    printf("End of rt_thread. Not sent messages: %d\n", lost_msg);
    pthread_exit(NULL);
}
