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

#define MSEC_PER_SEC (1000) /* The number of millisecs per sec. */
#define USEC_PER_SEC (1000000) /* The number of microsecs per sec. */
#define NSEC_PER_SEC (1000000000) /* The number of nsecs per sec. */
#define PSEC_PER_SEC (1000000000000) /* The number of picosecs per sec. */


#define MS 0
#define US 1
#define NS 2
#define PS 3

void ts_substraction (struct timespec * start, struct timespec * stop, struct timespec * result);

void ts_assign (struct timespec * ts1,  struct timespec ts2);

void ts_add_time (struct timespec * ts, int sec, int nsec);

void ts_convert_time (struct timespec * ts, unsigned int unit, double * res);

#endif // TIME_FUNCTIONS_H

#ifdef __cplusplus
}
#endif
