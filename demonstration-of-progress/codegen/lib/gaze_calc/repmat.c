/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: repmat.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 16-Feb-2018 21:40:13
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "gaze_calc.h"
#include "repmat.h"

/* Function Definitions */

/*
 * Arguments    : const double a[4]
 *                double b[16]
 * Return Type  : void
 */
void repmat(const double a[4], double b[16])
{
  int jtilecol;
  int ibtile;
  int k;
  for (jtilecol = 0; jtilecol < 4; jtilecol++) {
    ibtile = jtilecol << 2;
    for (k = 0; k < 4; k++) {
      b[ibtile + k] = a[k];
    }
  }
}

/*
 * File trailer for repmat.c
 *
 * [EOF]
 */
