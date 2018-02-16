/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * RotY.c
 *
 * Code generation for function 'RotY'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "gaze_calc.h"
#include "RotY.h"
#include "gaze_calc_data.h"
#include "blas.h"
#include "lapacke.h"

/* Function Definitions */
void RotY(real_T theta, real_T R[9])
{
  int32_T i1;
  static const int8_T iv1[3] = { 0, 1, 0 };

  covrtLogFcn(&emlrtCoverageInstance, 2U, 0);
  covrtLogBasicBlock(&emlrtCoverageInstance, 2U, 0);

  /*  R = RotY(theta,opt) */
  /*  Return the (3 x 3) rotation matrix that rotates about the y axis */
  /*  The angle is in radian. Return the (4x4) matrix if opt ~= 0. */
  R[0] = muDoubleScalarCos(theta);
  R[3] = 0.0;
  R[6] = muDoubleScalarSin(theta);
  for (i1 = 0; i1 < 3; i1++) {
    R[1 + 3 * i1] = iv1[i1];
  }

  R[2] = -muDoubleScalarSin(theta);
  R[5] = 0.0;
  R[8] = muDoubleScalarCos(theta);
  covrtLogIf(&emlrtCoverageInstance, 2U, 0U, 0, false);
  covrtLogBasicBlock(&emlrtCoverageInstance, 2U, 2);
}

/* End of code generation (RotY.c) */
