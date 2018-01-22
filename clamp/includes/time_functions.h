#ifdef __cplusplus
extern "C" {
#endif

#ifndef TIME_FUNCTIONS_H
#define TIME_FUNCTIONS_H

//#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sched.h>
#include <sys/mman.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <getopt.h>

#define NSEC_PER_SEC (1000000000) /* The number of nsecs per sec. */

void ts_substraction (struct timespec * start, struct timespec * stop, struct timespec * result);

void ts_assign (struct timespec * ts1,  struct timespec ts2);

void ts_add_time (struct timespec * ts, int sec, int nsec);

#endif // TIME_FUNCTIONS_H

#ifdef __cplusplus
}
#endif
