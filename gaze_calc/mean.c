/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: mean.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 16-Feb-2018 21:40:13
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "gaze_calc.h"
#include "mean.h"

/* Function Definitions */

/*
 * Arguments    : const double x[12]
 *                double y[3]
 * Return Type  : void
 */
void mean(const double x[12], double y[3])
{
  int j;
  double s;
  int k;
  for (j = 0; j < 3; j++) {
    s = x[j];
    for (k = 0; k < 3; k++) {
      s += x[j + (k + 1) * 3];
    }

    y[j] = s;
    y[j] /= 4.0;
  }
}

/*
 * File trailer for mean.c
 *
 * [EOF]
 */
