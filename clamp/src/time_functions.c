#include "../includes/time_functions.h"
/* TIME MANAGEMENT FUNCTIONS */

void ts_substraction (struct timespec * start, struct timespec * stop, struct timespec * result) {
    if ((stop->tv_nsec - start->tv_nsec) < 0) {
        result->tv_sec = stop->tv_sec - start->tv_sec - 1;
        result->tv_nsec = stop->tv_nsec - start->tv_nsec + 1000000000;
    } else {
        result->tv_sec = stop->tv_sec - start->tv_sec;
        result->tv_nsec = stop->tv_nsec - start->tv_nsec;
    }

    return;
}


void ts_assign (struct timespec * ts1,  struct timespec ts2) {
    ts1->tv_sec = ts2.tv_sec;
    ts1->tv_nsec = ts2.tv_nsec;
}


void ts_add_time (struct timespec * ts, int sec, int nsec) {
    ts->tv_nsec += nsec;

    while (ts->tv_nsec >= NSEC_PER_SEC) {
          ts->tv_nsec -= NSEC_PER_SEC;
          ts->tv_sec++;
    }

    ts->tv_sec += sec;
}

void ts_convert_time (struct timespec * ts, unsigned int unit, double * res) {
    *res = 0.0;

    switch(unit) {
        case MS:
            *res += ts->tv_sec * MSEC_PER_SEC;
            *res += ts->tv_nsec / 1000000.0;
            break;
        case US:
            *res += ts->tv_sec * USEC_PER_SEC;
            *res += ts->tv_nsec / 1000.0;
            break;
        case NS:
            *res += ts->tv_sec * NSEC_PER_SEC;
            *res += ts->tv_nsec;
            break;
        case PS:
            *res += ts->tv_sec * PSEC_PER_SEC;
            *res += ts->tv_nsec * 1000.0;
            break;
        default:
            break;
    }

    return;
}