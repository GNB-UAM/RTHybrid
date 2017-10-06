#include "../includes/writer_thread_functions.h"


/* Global variables */
FILE * f1 = NULL;
FILE * f2 = NULL;
FILE * f3 = NULL;
char * filename_1 = NULL;
char * filename_2 = NULL;
char * filename_3 = NULL;


void writer_cleanup () {
    printf("\n" PRINT_RED "SIGUSR2 termination to writer_thread." PRINT_RESET "\n");

    if (f1 != NULL) fclose(f1);
    if (f2 != NULL) fclose(f2);
    if (f3 != NULL) fclose(f3);

    free_pointers(3, &filename_1, &filename_2, &filename_3);

    printf("\n" PRINT_CYAN "writer_thread terminated." PRINT_RESET "\n");
    pthread_exit(NULL);
}


void * writer_thread(void * arg) {
    message msg;
    message msg2;
    pthread_t id;
    writer_args * args;
    int i = 0, j;
    int s_points;

    args = arg;
    id = pthread_self();

    syslog(LOG_INFO, "WRITER_THREAD: Start");

    if (signal(SIGUSR2, writer_cleanup) == SIG_ERR) printf("Error catching SIGUSR2 at writer_thread.\n");

    syslog(LOG_INFO, "WRITER_THREAD: After signal");

    filename_1 = (char *) malloc (sizeof(char)*(strlen(args->filename)+7));
    filename_2 = (char *) malloc (sizeof(char)*(strlen(args->filename)+7));
    filename_3 = (char *) malloc (sizeof(char)*(strlen(args->path)+13));

    if (sprintf(filename_1, "%s_1.txt", args->filename) < 0) {
        printf("Error creating file 1 name\n;");
        pthread_exit(NULL);
    }

    if (sprintf(filename_2, "%s_2.txt", args->filename) < 0) {
        printf("Error creating file 2 name\n;");
        pthread_exit(NULL);
    }

    if (sprintf(filename_3, "%s/summary.txt", args->path) < 0) {
        printf("Error creating summary file name\n;");
        pthread_exit(NULL);
    }

    syslog(LOG_INFO, "WRITER_THREAD: Before umask");

    umask(1);
    f1 = fopen(filename_1, "w");
    f2 = fopen(filename_2, "w");
    f3 = fopen(filename_3, "a");

    if (f1 == NULL || f2 == NULL || f3 == NULL) {
        free_pointers(3, &filename_1, &filename_2, &filename_3);

        printf("\n" PRINT_CYAN "writer_thread terminated: No data folder." PRINT_RESET "\n");
        pthread_exit(NULL);
    }

    syslog(LOG_INFO, "WRITER_THREAD: Files opened");
    
    if (args->important==1){
        fprintf(f3, "*********IMPORTANT RECORD********\n");
    }

    syslog(LOG_INFO, "WRITER_THREAD: Before first write to f3");
    fprintf(f3, "%s\nModel: ", args->filename);
    syslog(LOG_INFO, "WRITER_THREAD: After first write to f3");
    if(args->model==1){
        fprintf(f3, "Hindmarsh Rose\n");
    }else if(args->model==0){
        fprintf(f3, "Izhikevich\n");
    }else if(args->model==2){
        fprintf(f3, "Rulkov Map\n");
    }

    fprintf(f3, "Synapse: ");
    /*Esto tiene que dar mas detalles de hacia que lado en las quimicas hay de cual*/
    if(args->type_syn==0){
        fprintf(f3, "Electric\n");
    }else if(args->type_syn==1){
        fprintf(f3, "Chemical\n");
    }

    fprintf(f3, "Freq = %d Hz\n", args->freq);

    fprintf(f3, "Duration = %d s\n", args->time_var);

    if(args->anti==1){
        fprintf(f3, "Antiphase = True\n");
    }else{
        fprintf(f3, "Antiphase = False\n");
    }

    fprintf(f3, "Calibration mode = %d\n", args->calibration);

    syslog(LOG_INFO, "WRITER_THREAD: Before first rcv");

    receive_from_queue(args->msqid, &msg2);

    syslog(LOG_INFO, "WRITER_THREAD: After first rcv");
    
    s_points = msg2.i;

    fprintf(f3, "Model jump points = %d\n", s_points);

    fprintf(f3, "Burst duration = %f s\n", msg2.t_unix);

    printf("Periodo disparo = %f\n", msg2.t_unix);

    fprintf(f3, "\n=================================\n\n");

    //fprintf(f3, "%s\nModel: %d\nSynapse: %d\nFreq: %d ns\n\n\n", args->filename, args->model, args->type_syn, args->freq);
    fclose(f3);
    f3 = NULL;

    syslog(LOG_INFO, "WRITER_THREAD: F3 closed");

    /****************/
    /* WRITING DATA */      
    /****************/

    syslog(LOG_INFO, "WRITER_THREAD: Before loop");


    while(1) {
        //Receive
        receive_from_queue(args->msqid, &msg);

        //Stop
        if (msg.id == 2) {
            free(msg.data_in);
            free(msg.data_out);
            free(msg.g_virtual_to_real);
            free(msg.g_real_to_virtual);
            break;
        }

        //Headers
        if (i == 0) {
            fprintf(f1, "%d %d\n", msg.n_in_chan, msg.n_out_chan);
            //if(msg.autocal==1){
            fprintf(f2, "%d %d\n", msg.autocal, 2+msg.n_g);
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
        for (j = 0; j < msg.n_g; ++j) {
            fprintf(f2, " %f", msg.g_real_to_virtual[j]);
            fprintf(f2, " %f", msg.g_virtual_to_real[j]);
        }
        fprintf(f2, "\n");

        //Free
        free(msg.data_in);
        free(msg.data_out);
        free(msg.g_virtual_to_real);
        free(msg.g_real_to_virtual);
    }
    
    fclose(f1);
    fclose(f2);
    free_pointers(3, &filename_1, &filename_2, &filename_3);

    printf("End writer_thread.\n");
    pthread_exit(NULL);
}