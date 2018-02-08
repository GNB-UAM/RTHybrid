#include "../includes/types.h"


void free_pointers (int n, ...) {
    va_list l;
    void ** arg;
    int i = 0;
    va_start(l, n);

    for(i = 0; i < n; i++) {
        //syslog(LOG_INFO, "Free %d", i);
        arg = va_arg(l, void**);
        if(*arg != NULL){
            free(*arg);
            *arg = NULL;
        }
    }
    va_end(l);
}




void copy_1d_array (double * src, double * dst, int n_elems) {
    int i;

    for (i = 0; i < n_elems; ++i) {
        dst[i] = src[i];
    }

    return;
}
