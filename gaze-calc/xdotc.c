/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xdotc.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 16-Feb-2018 21:40:13
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "gaze_calc.h"
#include "xdotc.h"

/* Function Definitions */

/*
 * Arguments    : int n
 *                const double x[81]
 *                int ix0
 *                const double y[81]
 *                int iy0
 * Return Type  : double
 */
double b_xdotc(int n, const double x[81], int ix0, const double y[81], int iy0)
{
  double d;
  int ix;
  int iy;
  int k;
  d = 0.0;
  ix = ix0;
  iy = iy0;
  for (k = 1; k <= n; k++) {
    d += x[ix - 1] * y[iy - 1];
    ix++;
    iy++;
  }

  return d;
}

/*
 * Arguments    : int n
 *                const double x[64]
 *                int ix0
 *                const double y[64]
 *                int iy0
 * Return Type  : double
 */
double c_xdotc(int n, const double x[64], int ix0, const double y[64], int iy0)
{
  double d;
  int ix;
  int iy;
  int k;
  d = 0.0;
  if (n < 1) {
  } else {
    ix = ix0;
    iy = iy0;
    for (k = 1; k <= n; k++) {
      d += x[ix - 1] * y[iy - 1];
      ix++;
      iy++;
    }
  }

  return d;
}

/*
 * Arguments    : int n
 *                const double x[72]
 *                int ix0
 *                const double y[72]
 *                int iy0
 * Return Type  : double
 */
double xdotc(int n, const double x[72], int ix0, const double y[72], int iy0)
{
  double d;
  int ix;
  int iy;
  int k;
  d = 0.0;
  ix = ix0;
  iy = iy0;
  for (k = 1; k <= n; k++) {
    d += x[ix - 1] * y[iy - 1];
    ix++;
    iy++;
  }

  return d;
}

/*
 * File trailer for xdotc.c
 *
 * [EOF]
 */
