/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xrot.h
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 16-Feb-2018 21:40:13
 */

#ifndef XROT_H
#define XROT_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "gaze_calc_types.h"

/* Function Declarations */
extern void b_xrot(double x[81], int ix0, int iy0, double c, double s);
extern void xrot(double x[64], int ix0, int iy0, double c, double s);

#endif

/*
 * File trailer for xrot.h
 *
 * [EOF]
 */
