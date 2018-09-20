/**
 * @file integration_methods.h
 * @brief Header file for the integration methods functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef INTEGRATION_METHODS_H
#define INTEGRATION_METHODS_H

#include "../common/includes/types.h"


#define RK65 0
#define RK4 1
#define EULER 2
#define HEUN 3

void * integration_method_selector (unsigned int id);

void runge_kutta_65 (void (*f) (double *, double *, double *, double), int dim, double dt, double * vars, double * params, double aux);

void runge_kutta_4 (void (*f) (double *, double *, double *, double), int dim, double dt, double * vars, double * params, double aux);

void euler (void (*f) (double *, double *, double *, double), int dim, double dt, double * vars, double * params, double aux);

void heun (void (*f) (double *, double *, double *, double), int dim, double dt, double * vars, double * params, double aux);
 

#endif // INTEGRATION_METHODS_H


#ifdef __cplusplus
}
#endif
