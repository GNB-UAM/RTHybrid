#include "../includes/writer_thread_functions.h"

/* Global variables */

void * writer_thread(void * arg);


/************************
WRITER THREAD MANAGEMENT
************************/

int create_writer_thread (pthread_t * thread, void *arg) {
	int err;
	pthread_attr_t attr;
	
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    err = pthread_create(thread, &attr, &writer_thread, arg);
    if (err != 0) {
        syslog(LOG_INFO, "Can't create writer_thread :[%s]", strerror(err));
        return ERR;
    }

    #ifdef __XENO__
        if (pthread_setname_np((*thread), "RTHybrid - RT Writer Thread") != 0) {
            perror("Setting RT Thread name");
        }
    #endif

    return OK;
}

int join_writer_thread (pthread_t thread, void ** value_ptr) {
    return pthread_join(thread, value_ptr);
}

int kill_writer_thread(pthread_t thread, int sig) {
    return pthread_kill(thread, sig);
}


void writer_cleanup () {
    printf("\n" PRINT_RED "SIGUSR2 termination to writer_thread." PRINT_RESET "\n");

    printf("\n" PRINT_CYAN "writer_thread terminated." PRINT_RESET "\n");
    pthread_exit(NULL);
}



void * writer_thread(void * arg) {
    message msg;
    writer_args * args;
    args = arg;

    if (DEBUG == 1) syslog(LOG_INFO, "WRITER_THREAD: Start");

    setlocale(LC_NUMERIC, "en_US.UTF-8");

    if (signal(SIGUSR2, writer_cleanup) == SIG_ERR) printf("Error catching SIGUSR2 at writer_thread.\n");

    if (DEBUG == 1) syslog(LOG_INFO, "WRITER_THREAD: After signal");

    for (;;) {
        receive_from_queue(args->msqid, NRT_QUEUE, BLOCK_QUEUE, &msg);

        if (msg.id < 0) {
            if (DEBUG == 1) syslog(LOG_INFO, "WRITER_THREAD: Closing message received");
            break;
        } else {
            fprintf(get_fd_by_index(msg.id), "%s\n", msg.data);
        }
    }

    if (DEBUG == 1) syslog(LOG_INFO, "WRITER_THREAD: End.\n");
    pthread_exit(NULL);
}
