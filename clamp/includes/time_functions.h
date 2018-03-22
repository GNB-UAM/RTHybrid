/**
 * @file time_functions.h
 * @brief Header file with time management functions and macros.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TIME_FUNCTIONS_H
#define TIME_FUNCTIONS_H

#include <sys/time.h>


#define MSEC_PER_SEC (1000) /* The number of millisecs per sec. */
#define USEC_PER_SEC (1000000) /* The number of microsecs per sec. */
#define NSEC_PER_SEC (1000000000) /* The number of nsecs per sec. */
#define PSEC_PER_SEC (1000000000000) /* The number of picosecs per sec. */


#define MS 0
#define US 1
#define NS 2
#define PS 3

void ts_substraction (struct timespec * start, struct timespec * stop, struct timespec * result);

void ts_assign (struct timespec * dst,  struct timespec src);

void ts_add_time (struct timespec * ts, unsigned int sec, unsigned int nsec);

void ts_convert_time (struct timespec * ts, unsigned int unit, double * res);

#endif // TIME_FUNCTIONS_H

#ifdef __cplusplus
}
#endif
