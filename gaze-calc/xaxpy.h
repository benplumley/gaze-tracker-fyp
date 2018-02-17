/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xaxpy.h
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 16-Feb-2018 21:40:13
 */

#ifndef XAXPY_H
#define XAXPY_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "gaze_calc_types.h"

/* Function Declarations */
extern void b_xaxpy(int n, double a, const double x[72], int ix0, double y[9],
                    int iy0);
extern void c_xaxpy(int n, double a, const double x[9], int ix0, double y[72],
                    int iy0);
extern void d_xaxpy(int n, double a, int ix0, double y[81], int iy0);
extern void e_xaxpy(int n, double a, int ix0, double y[64], int iy0);
extern void xaxpy(int n, double a, int ix0, double y[72], int iy0);

#endif

/*
 * File trailer for xaxpy.h
 *
 * [EOF]
 */
