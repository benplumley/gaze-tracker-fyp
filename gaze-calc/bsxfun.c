/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: bsxfun.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 16-Feb-2018 21:40:13
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "gaze_calc.h"
#include "bsxfun.h"

/* Function Definitions */

/*
 * Arguments    : const double a[2]
 *                double b
 *                double c[2]
 * Return Type  : void
 */
void bsxfun(const double a[2], double b, double c[2])
{
  int k;
  for (k = 0; k < 2; k++) {
    c[k] = a[k] / b;
  }
}

/*
 * File trailer for bsxfun.c
 *
 * [EOF]
 */
