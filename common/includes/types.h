/**
 * @file types.h
 * @brief Header file with the basic includes, defines and functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TYPES_H__
#define TYPES_H__

#include <stdlib.h>
#include <stdio.h>

#include <syslog.h>
#include <string.h>
#include <stdarg.h>

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include <sys/types.h>
#include <signal.h>
#include <sched.h>
#include <pthread.h>
#include <unistd.h>

/* Basic types */
#define ERR -1
#define OK 0
#define TRUE 1
#define FALSE 0
#define DEBUG 0
#define SYNC 0


/* Print colors */
#define PRINT_BLACK "\033[30;1m"
#define PRINT_RED "\033[31;1m"
#define PRINT_GREEN "\033[32;1m"
#define PRINT_YELLOW "\033[33;1m"
#define PRINT_BLUE "\033[34;1m"
#define PRINT_MAGENTA "\033[35;1m"
#define PRINT_CYAN "\033[36;1m"
#define PRINT_WHITE "\033[37;1m"
#define PRINT_RESET "\033[00m"


/* RT Params */
#define MAX_SAFE_STACK (8*1024)
#define PRIORITY (99)
#define MAX_LAT (900000)
#define CORE (0)


void free_pointers (int n, ...);

void copy_1d_array (double * src, double * dst, int n_elems);


#endif // TYPES_H__

#ifdef __cplusplus
}
#endif

