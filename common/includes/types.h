#ifdef __cplusplus
extern "C" {
#endif

#ifndef TYPES_H__
#define TYPES_H__

#include <syslog.h>

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


#endif // TYPES_H__

#ifdef __cplusplus
}
#endif

