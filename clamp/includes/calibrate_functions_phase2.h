#ifndef CALIBRATE_FUNCTIONS_PHASE2_H__
#define CALIBRATE_FUNCTIONS_PHASE2_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "types_clamp.h"

int calc_ecm (double v_a, double v_b, int life_burst_points, double *ecm_result);

int calc_phase (double * v_a, double * v_b, double * t, int size, double th_up, double th_on, double * result, int antifase);

void set_is_syn_by_percentage(double val_sin);

int is_syn_by_percentage(double val_sin);

int is_syn_by_slope(double val_sin);

int is_syn_by_variance(double val_sin);

void change_g (double *g);

#endif 