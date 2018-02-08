#include "queue_functions.h"

#include <pthread.h>
#include <locale.h>

int create_writer_thread (pthread_t * thread, void *arg);

int join_writer_thread (pthread_t thread);
