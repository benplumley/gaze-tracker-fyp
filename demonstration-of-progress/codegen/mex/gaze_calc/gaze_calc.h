/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * gaze_calc.h
 *
 * Code generation for function 'gaze_calc'
 *
 */

#ifndef GAZE_CALC_H
#define GAZE_CALC_H

/* Include files */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mwmathutil.h"
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include "covrt.h"
#include "rtwtypes.h"
#include "gaze_calc_types.h"

/* Function Declarations */
extern void gaze_calc(const emlrtStack *sp, real_T head_x, real_T head_y, real_T
                      head_z, real_T head_roll, real_T head_pitch, real_T
                      head_yaw, real_T left_eye_x, real_T left_eye_y, real_T
                      right_eye_x, real_T right_eye_y, real_T retmat[4]);

#endif

/* End of code generation (gaze_calc.h) */
