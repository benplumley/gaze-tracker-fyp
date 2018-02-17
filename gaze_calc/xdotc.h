/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xdotc.h
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 16-Feb-2018 21:40:13
 */

#ifndef XDOTC_H
#define XDOTC_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "gaze_calc_types.h"

/* Function Declarations */
extern double b_xdotc(int n, const double x[81], int ix0, const double y[81],
                      int iy0);
extern double c_xdotc(int n, const double x[64], int ix0, const double y[64],
                      int iy0);
extern double xdotc(int n, const double x[72], int ix0, const double y[72], int
                    iy0);

#endif

/*
 * File trailer for xdotc.h
 *
 * [EOF]
 */
