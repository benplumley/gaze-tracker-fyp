/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: gaze_calc.h
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 16-Feb-2018 21:40:13
 */

#ifndef GAZE_CALC_H
#define GAZE_CALC_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "gaze_calc_types.h"

/* Function Declarations */
extern void gaze_calc(double head_x, double head_y, double head_z, double
                      head_roll, double head_pitch, double head_yaw, double
                      left_eye_x, double left_eye_y, double right_eye_x, double
                      right_eye_y, double starting_distance, double retmat[4]);

#endif

/*
 * File trailer for gaze_calc.h
 *
 * [EOF]
 */
