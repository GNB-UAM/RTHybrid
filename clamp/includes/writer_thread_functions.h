#ifdef __cplusplus
extern "C" {
#endif

#ifndef WRITER_THREAD_FUNCTIONS_H__
#define WRITER_THREAD_FUNCTIONS_H__

#include "queue_functions.h"

#include <pthread.h>
#include <locale.h>

int create_writer_thread (pthread_t * thread, void *arg);

int join_writer_thread (pthread_t thread);

#endif //WRITER_THREAD_FUNCTIONS_H__

#ifdef __cplusplus
}
#endif
