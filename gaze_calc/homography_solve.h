/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: homography_solve.h
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 16-Feb-2018 21:40:13
 */

#ifndef HOMOGRAPHY_SOLVE_H
#define HOMOGRAPHY_SOLVE_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "gaze_calc_types.h"

/* Function Declarations */
extern void homography_solve(const double pin[8], const double pout[8], double
  v[9]);

#endif

/*
 * File trailer for homography_solve.h
 *
 * [EOF]
 */
