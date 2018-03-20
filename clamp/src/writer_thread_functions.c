#include "../includes/writer_thread_functions.h"

/* Global variables */
FILE * f1 = NULL;
FILE * f2 = NULL;
FILE * summary = NULL;
FILE * f_drift = NULL;
char * filename_1 = NULL;
char * filename_2 = NULL;
char * filename_summary = NULL;
char * filename_drift = NULL;


void * writer_thread(void * arg);


/************************
WRITER THREAD MANAGEMENT
************************/

int create_writer_thread (pthread_t * thread, void *arg) {
	int err;
	pthread_attr_t attr;
	#ifndef __XENO__   
	    pthread_attr_init(&attr);
	    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	    err = pthread_create(thread, &attr, &writer_thread, arg);
	    if (err != 0) {
	        syslog(LOG_INFO, "Can't create writer_thread :[%s]", strerror(err));
	        return ERR;
	    }
    #else /* __XENO__ */
	    __real_pthread_attr_init(&attr);
	    __real_pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	    err = __real_pthread_create(thread, &attr, &writer_thread, arg);
	    if (err != 0) {
	        syslog(LOG_INFO, "Can't create writer_thread :[%s]", strerror(err));
	        return ERR;
	    }
    #endif /* __XENO__ */

    return OK;
}

int join_writer_thread (pthread_t thread) {
	#ifndef __XENO__
    	return pthread_join(thread, NULL);
    #else /* __XENO__ */
    	return __real_pthread_join(thread, NULL);
    #endif /* __XENO__ */
}


void writer_cleanup () {
    printf("\n" PRINT_RED "SIGUSR2 termination to writer_thread." PRINT_RESET "\n");

    if (f1 != NULL) fclose(f1);
    if (f2 != NULL) fclose(f2);
    if (summary != NULL) fclose(summary);
    if (f_drift != NULL) fclose(f_drift);

    free_pointers(4, &filename_1, &filename_2, &filename_summary, &filename_drift);

    printf("\n" PRINT_CYAN "writer_thread terminated." PRINT_RESET "\n");
    pthread_exit(NULL);
}


void * writer_thread(void * arg) {
    message msg;
    message msg2;
    writer_args * args;
    int i = 0, j;
    int s_points;

    args = arg;

    if (DEBUG == 1) syslog(LOG_INFO, "WRITER_THREAD: Start");

    setlocale(LC_NUMERIC, "en_US.UTF-8");

    if (signal(SIGUSR2, writer_cleanup) == SIG_ERR) printf("Error catching SIGUSR2 at writer_thread.\n");

    if (DEBUG == 1) syslog(LOG_INFO, "WRITER_THREAD: After signal");

    filename_1 = (char *) malloc (sizeof(char)*(strlen(args->filename)+7));
    filename_2 = (char *) malloc (sizeof(char)*(strlen(args->filename)+7));
    filename_summary = (char *) malloc (sizeof(char)*(strlen(args->path)+13));
    filename_drift = (char *) malloc (sizeof(char)*(strlen(args->filename)+12));

    if (sprintf(filename_1, "%s_1.txt", args->filename) < 0) {
        printf("Error creating file 1 name\n;");
        pthread_exit(NULL);
    }

    if (sprintf(filename_2, "%s_2.txt", args->filename) < 0) {
        printf("Error creating file 2 name\n;");
        pthread_exit(NULL);
    }

    if (sprintf(filename_summary, "%s/summary.txt", args->path) < 0) {
        printf("Error creating summary file name\n;");
        pthread_exit(NULL);
    }

    if (sprintf(filename_drift, "%s_drift.txt", args->filename) < 0) {
        printf("Error creating file drift name\n;");
        pthread_exit(NULL);
    }

    if (DEBUG == 1) syslog(LOG_INFO, "WRITER_THREAD: Before umask");

    umask(1);
    f1 = fopen(filename_1, "w");
    f2 = fopen(filename_2, "w");
    summary = fopen(filename_summary, "a");
    f_drift = fopen(filename_drift, "w");

    if (f1 == NULL || f2 == NULL || summary == NULL || f_drift == NULL) {
        free_pointers(4, &filename_1, &filename_2, &filename_summary, &filename_drift);

        printf("\n" PRINT_CYAN "writer_thread terminated: No data folder." PRINT_RESET "\n");
        pthread_exit(NULL);
    }

    if (DEBUG == 1) syslog(LOG_INFO, "WRITER_THREAD: Files opened");
    
    if (args->important==1){
        fprintf(summary, "*********IMPORTANT RECORD********\n");
    }

    if (DEBUG == 1) syslog(LOG_INFO, "WRITER_THREAD: Before first write to summary");
    fprintf(summary, "%s\nModel: ", args->filename);
    if (DEBUG == 1) syslog(LOG_INFO, "WRITER_THREAD: After first write to summary");

    if(args->model==1){
        fprintf(summary, "Hindmarsh Rose\n");
    }else if(args->model==0){
        fprintf(summary, "Izhikevich\n");
    }else if(args->model==2){
        fprintf(summary, "Rulkov Map\n");
    }

    fprintf(summary, "Synapse: ");
    /*Esto tiene que dar mas detalles de hacia que lado en las quimicas hay de cual*/
    if(args->type_syn==0){
        fprintf(summary, "Electric\n");
    }else if(args->type_syn==1){
        fprintf(summary, "Chemical\n");
        /*fprintf(summary, "k1 = %f\n", args->syn_gradual_k1);
        fprintf(summary, "k2 = %f\n", args->syn_gradual_k2);
        fprintf(summary, "V fast = %.2f\n", args->syn_gradual_vfast);
        fprintf(summary, "V slow = %.2f\n", args->syn_gradual_vslow);*/
    }

    fprintf(summary, "Freq = %d Hz\n", args->freq);

    fprintf(summary, "Duration = %d s\n", args->time_var);

    /*if(args->anti==1){
        fprintf(summary, "Antiphase = True\n");
    }else{
        fprintf(summary, "Antiphase = False\n");
    }*/


    fprintf(summary, "Calibration mode = %d\n", args->calibration);


    if (DEBUG == 1) syslog(LOG_INFO, "WRITER_THREAD: Before first rcv");

    receive_from_queue_block(args->msqid, &msg2);

    if (DEBUG == 1) syslog(LOG_INFO, "WRITER_THREAD: After first rcv");
    
    s_points = msg2.i;

    fprintf(summary, "Model jump points = %d\n", s_points);

    fprintf(summary, "Burst duration = %.3f s\n", msg2.t_unix);

    printf("Firing rate = %.3f s/burst\n", msg2.t_unix);

    fprintf(summary, "\n=================================\n\n");

    //fprintf(summary, "%s\nModel: %d\nSynapse: %d\nFreq: %d ns\n\n\n", args->filename, args->model, args->type_syn, args->freq);
    fclose(summary);
    summary = NULL;

    if (DEBUG == 1) syslog(LOG_INFO, "WRITER_THREAD: summary closed");

    /****************/
    /* WRITING DATA */      
    /****************/

    if (DEBUG == 1) syslog(LOG_INFO, "WRITER_THREAD: Before loop");

    while(1) {
        //Receive
        receive_from_queue_block(args->msqid, &msg);

        //Stop
        if (msg.id == 2) {
            //free_pointers(4, &msg.data_in, &msg.data_out, &msg.g_virtual_to_real, &msg.g_real_to_virtual);
            if (DEBUG == 1) if (DEBUG == 1) syslog(LOG_INFO, "WRITER_THREAD: Closing message received");
            break;
        }

        //Headers
        if (i == 0) {
            fprintf(f1, "%d %d\n", msg.n_in_chan, msg.n_out_chan);
            //if(msg.autocal==1){
            fprintf(f2, "%d %d\n", msg.autocal, msg.n_g * 2);
            //}

            i++;
        }

        //Write file 1
        fprintf(f1, "%f %f %d %ld %f %f %f %f", msg.t_unix, msg.t_absol, msg.i, msg.lat, msg.v_model, msg.v_model_scaled, msg.c_model, msg.c_real);
        for (j = 0; j < msg.n_in_chan; ++j) {
            fprintf(f1, " %f", msg.data_in[j]);
        }
        for (j = 0; j < msg.n_out_chan; ++j) {
            fprintf(f1, " %f", msg.data_out[j]);
        }
        fprintf(f1, "\n");

        //Write file 2
        fprintf(f2, "%f %d", msg.t_absol, msg.i);
        fprintf(f2, " %f", msg.ecm);
        fprintf(f2, " %f", msg.extra);
        for (j = 0; j < msg.n_g * 2; ++j) {
            fprintf(f2, " %f", msg.g_real_to_virtual[j]);
            fprintf(f2, " %f", msg.g_virtual_to_real[j]);
        }
        fprintf(f2, "\n");

        //Write drift
        fprintf(f_drift, "%f %f\n", msg.min_window, msg.max_window);

        //Free
        free_pointers(4, &msg.data_in, &msg.data_out, &msg.g_virtual_to_real, &msg.g_real_to_virtual);

    }

    if (DEBUG == 1) syslog(LOG_INFO, "WRITER_THREAD: Before closing f1 and f2.\n");
    
    fclose(f1);
    fclose(f2);
    fclose(f_drift);
    free_pointers(4, &filename_1, &filename_2, &filename_summary, &filename_drift);

    if (DEBUG == 1) syslog(LOG_INFO, "WRITER_THREAD: End.\n");
    pthread_exit(NULL);
}
