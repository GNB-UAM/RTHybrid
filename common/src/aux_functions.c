/**
 * @file aux_functions.c
 * @brief Source file with basic auxiliary functions.
 */

#include "../includes/types.h"

/**
 * @brief Frees a variable number of pointers. The pointers will be freed and set to NULL. If a pointer to NULL is passed nothing happens.
 * @param[in] n Number of pointers that will be freed.
 * @param[in] ... Variable number of parameters, indicated by n. Pointers to the pointers to be freed (i.e. &ptr) 
 */

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


/**
 * @brief Copies the content of a one dimension double array into another one, which is already allocated.
 * @param[in] src Pointer to the source array
 * @param[out] dst Pointer to the destination array
 * @param[in] n_elems Number of elements in the arrays.
 */

void copy_1d_array (double * src, double * dst, int n_elems) {
    int i;

    for (i = 0; i < n_elems; ++i) {
        dst[i] = src[i];
    }

    return;
}