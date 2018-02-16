/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * RotX.c
 *
 * Code generation for function 'RotX'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "gaze_calc.h"
#include "RotX.h"
#include "gaze_calc_data.h"
#include "blas.h"
#include "lapacke.h"

/* Function Definitions */
void RotX(real_T theta, real_T R[9])
{
  int32_T i0;
  static const int8_T iv0[3] = { 1, 0, 0 };

  covrtLogFcn(&emlrtCoverageInstance, 1U, 0);
  covrtLogBasicBlock(&emlrtCoverageInstance, 1U, 0);

  /*  R = RotX(theta) */
  /*  Return the (3 x 3) rotation matrix that rotates about the x axis */
  /*  The angle is in radian. Return the (4x4) matrix if opt ~= 0. */
  for (i0 = 0; i0 < 3; i0++) {
    R[3 * i0] = iv0[i0];
  }

  R[1] = 0.0;
  R[4] = muDoubleScalarCos(theta);
  R[7] = -muDoubleScalarSin(theta);
  R[2] = 0.0;
  R[5] = muDoubleScalarSin(theta);
  R[8] = muDoubleScalarCos(theta);
  covrtLogIf(&emlrtCoverageInstance, 1U, 0U, 0, false);
  covrtLogBasicBlock(&emlrtCoverageInstance, 1U, 2);
}

/* End of code generation (RotX.c) */
