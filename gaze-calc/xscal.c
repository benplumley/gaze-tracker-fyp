/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xscal.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 16-Feb-2018 21:40:13
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "gaze_calc.h"
#include "xscal.h"

/* Function Definitions */

/*
 * Arguments    : double a
 *                double x[64]
 *                int ix0
 * Return Type  : void
 */
void b_xscal(double a, double x[64], int ix0)
{
  int k;
  for (k = ix0; k <= ix0 + 7; k++) {
    x[k - 1] *= a;
  }
}

/*
 * Arguments    : double a
 *                double x[81]
 *                int ix0
 * Return Type  : void
 */
void xscal(double a, double x[81], int ix0)
{
  int k;
  for (k = ix0; k <= ix0 + 8; k++) {
    x[k - 1] *= a;
  }
}

/*
 * File trailer for xscal.c
 *
 * [EOF]
 */
