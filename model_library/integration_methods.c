#include "integration_methods.h"

/**
 * @file integration_methods.c
 * @brief Source file with the integration methods functions.
 */


 /**
 * @brief Integration method selector function.
 * @param[in] id Identificator of the integration method
 * @return Pointer to the integration function
*/

 void * integration_method_selector (unsigned int id) {
 	switch(id) {
 		case RK65:
 			return &runge_kutta_65;
 		case RK4:
 			return &runge_kutta_4;
 		case EULER:
 			return &euler;
 		case HEUN:
 			return &heun;
 		default:
 			return NULL;
 	}

 	return NULL;
 }

 /**
 * @brief Order (6)5 Runge-Kutta integration function.
 * @param[in] f Pointer to the model function
 * @param[in] dim Dimension of the model
 * @param[in] dt Integration step
 * @param[in,out] vars Variables to be integrated
 * @param[in] params Parameters of the model
 * @param[in] aux Auxiliary value
*/

void runge_kutta_65 (void (*f) (double *, double *, double *, double), int dim, double dt, double * vars, double * params, double aux) {
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
