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


/**
 * @brief Order 6 Runge-Kutta integration function.
 * @param[in] f Pointer to the model function
 * @param[in] dim Dimension of the model
 * @param[in] dt Integration step
 * @param[in,out] vars Variables to be integrated
 * @param[in] params Parameters of the model
 * @param[in] aux Auxiliary value
*/

void runge_kutta_6 (void (*f) (double *, double *, double *, double), int dim, double dt, double * vars, double * params, double aux) {
    double apoyo[dim], retorno[dim];
    double k[6][dim];
    int j;

    (*f)(vars, retorno, params, aux);
    for(j = 0; j < dim; ++j) {
        k[0][j] = dt * retorno[j];
        apoyo[j] = vars[j] + k[0][j] * 0.2;
    }

    (*f)(apoyo, retorno, params, aux);
    for(j = 0; j < dim; ++j) {
        k[1][j] = dt * retorno[j];
        apoyo[j] = vars[j] + k[0][j] * 0.075 + k[1][j] * 0.225;
    }

    (*f)(apoyo, retorno, params, aux);
    for(j = 0; j < dim; ++j) {
        k[2][j] = dt * retorno[j];
        apoyo[j] = vars[j] + k[0][j] * 0.3 - k[1][j] * 0.9 + k[2][j] * 1.2;
    }

    (*f)(apoyo, retorno, params, aux);
    for(j = 0; j < dim; ++j) {
        k[3][j] = dt * retorno[j];
        apoyo[j] = vars[j] + k[0][j] * 0.075 + k[1][j] * 0.675 - k[2][j] * 0.6 + k[3][j] * 0.75;
    }

    (*f)(apoyo, retorno, params, aux);
    for(j = 0; j < dim; ++j) {
        k[4][j] = dt * retorno[j];
        apoyo[j] = vars[j] 
                + k[0][j] * 0.660493827160493
                + k[1][j] * 2.5
                - k[2][j] * 5.185185185185185
                + k[3][j] * 3.888888888888889
                - k[4][j] * 0.864197530864197;
    }

    (*f)(apoyo, retorno, params, aux);
    for(j = 0; j < dim; ++j) {
        k[5][j] = dt * retorno[j];
        apoyo[j] = vars[j] 
                + k[0][j]*0.1049382716049382
                + k[2][j]*0.3703703703703703
                + k[3][j]*0.2777777777777777
                + k[4][j]*0.2469135802469135;
    }


    for(j = 0; j < dim; ++j) {
        vars[j] += k[0][j]*0.098765432098765+
                   k[2][j]*0.396825396825396+
                   k[3][j]*0.231481481481481+
                   k[4][j]*0.308641975308641-
                   k[5][j]*0.035714285714285;
    }

    return;
}




/**
 * @brief Order 4 Runge-Kutta integration method.
 * @param[in] f Pointer to the model function
 * @param[in] dim Dimension of the model
 * @param[in] dt Integration step
 * @param[in,out] vars Variables to be integrated
 * @param[in] params Parameters of the model
 * @param[in] aux Auxiliary value
*/

void runge_kutta_4 (void (*f) (double *, double *, double *, double), int dim, double dt, double * vars, double * params, double aux) {
    double apoyo[dim], retorno[dim];
    double k[4][dim];
    int j;

    (*f)(vars, retorno, params, aux);
    for(j = 0; j < dim; ++j) {
        k[0][j] = dt * retorno[j];
        apoyo[j] = vars[j] + k[0][j] * 0.5;
    }

    (*f)(apoyo, retorno, params, aux);
    for(j = 0; j < dim; ++j) {
        k[1][j] = dt * retorno[j];
        apoyo[j] = vars[j] + k[1][j] * 0.5;
    }

    (*f)(apoyo, retorno, params, aux);
    for(j = 0; j < dim; ++j) {
        k[2][j] = dt * retorno[j];
        apoyo[j] = vars[j] + k[2][j];
    }

    (*f)(apoyo, retorno, params, aux);
    for(j = 0; j < dim; ++j) {
        k[3][j] = dt * retorno[j];
    }


    for(j = 0; j < dim; ++j) {
        vars[j] += (k[0][j] + k[1][j]*2 + k[2][j]*2 + k[3][j]) / 6.0;
    }

    //printf("hna rk %f\n\n", vars[1]);

    return;
}




/**
 * @brief Euler integration method.
 * @param[in] f Pointer to the model function
 * @param[in] dim Dimension of the model
 * @param[in] dt Integration step
 * @param[in,out] vars Variables to be integrated
 * @param[in] params Parameters of the model
 * @param[in] aux Auxiliary value
*/

void euler (void (*f) (double *, double *, double *, double), int dim, double dt, double * vars, double * params, double aux) {
    double apoyo[dim], retorno[dim];
    double k[4][dim];
    int j;

    (*f)(vars, retorno, params, aux);

    for(j = 0; j < dim; ++j) {
        vars[j] += dt * retorno[j];
    }

    //printf("hna rk %f\n\n", vars[1]);

    return;
}


/**
 * @brief Heun integration method.
 * @param[in] f Pointer to the model function
 * @param[in] dim Dimension of the model
 * @param[in] dt Integration step
 * @param[in,out] vars Variables to be integrated
 * @param[in] params Parameters of the model
 * @param[in] aux Auxiliary value
*/

void heun (void (*f) (double *, double *, double *, double), int dim, double dt, double * vars, double * params, double aux) {
    double apoyo[dim], retorno_1[dim], retorno_2[dim];
    int j;

    (*f)(vars, retorno_1, params, aux);
    for(j = 0; j < dim; ++j) {
        apoyo[j] = vars[j] + (dt * retorno_1[j]);
    }

    (*f)(apoyo, retorno_2, params, aux);
    for(j = 0; j < dim; ++j) {
        vars[j] += dt/2.0 * (retorno_1[j] + retorno_2[j]);
    }

    return;
}