/**
 * @file time_functions.c
 * @brief Source file with time management functions.
 */

#include "../includes/time_functions.h"


/**
 * @brief Substracts two times (as timespec structures).
 *
 * The start time is substracted from stop and the outcome is stored in result.
 * @param[in] start Pointer to a timespec structure with the minuend
 * @param[in] stop Pointer to a timespec structure with the subtrahend
 * @param[out] result Pointer to a timespec structure with the difference
 */
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


/**
 * @brief Assigns the time stored in a timespec structure to another one.
 *
 * @param[out] dst Pointer to the destination timespec structure 
 * @param[in] src Source timespec structure
 */
void ts_assign (struct timespec * dst,  struct timespec src) {
    dst->tv_sec = src.tv_sec;
    dst->tv_nsec = src.tv_nsec;
}


/**
 * @brief Adds a number of seconds and nanoseconds to a time stored in a timespec structure.
 *
 * @param[in,out] ts Pointer to a timespec structure
 * @param[in] sec Number of seconds to be added (must be equal or greater than zero)
 * @param[in] nsec Number of nanoseconds to be added (must be equal or greater than zero)
 */
void ts_add_time (struct timespec * ts, unsigned int sec, unsigned int nsec) {
    ts->tv_nsec += nsec;

    while (ts->tv_nsec >= NSEC_PER_SEC) {
          ts->tv_nsec -= NSEC_PER_SEC;
          ts->tv_sec++;
    }

    ts->tv_sec += sec;
}

/**
 * @brief Converts a time stored in a timespec structure into an specific time measure
 *
 * @param[in] ts Pointer to a timespec structure
 * @param[in] unit Unit to be converted to. It can be milliseconds (#MS), microseconds (#US), nanoseconds (#NS) or picoseconds (#PS)
 * @param[out] res Pointer to the double variable that stores the resulting value
 */
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