/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * RotZ.c
 *
 * Code generation for function 'RotZ'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "gaze_calc.h"
#include "RotZ.h"
#include "gaze_calc_data.h"
#include "blas.h"
#include "lapacke.h"

/* Function Definitions */
void RotZ(real_T theta, real_T R[9])
{
  int32_T i2;
  static const int8_T iv2[3] = { 0, 0, 1 };

  covrtLogFcn(&emlrtCoverageInstance, 3U, 0);
  covrtLogBasicBlock(&emlrtCoverageInstance, 3U, 0);

  /*  R = RotZ(theta) */
  /*  Return the (3 x 3) rotation matrix that rotates about the z axis */
  /*  The angle is in radian. */
  R[0] = muDoubleScalarCos(theta);
  R[3] = -muDoubleScalarSin(theta);
  R[6] = 0.0;
  R[1] = muDoubleScalarSin(theta);
  R[4] = muDoubleScalarCos(theta);
  R[7] = 0.0;
  for (i2 = 0; i2 < 3; i2++) {
    R[2 + 3 * i2] = iv2[i2];
  }

  covrtLogIf(&emlrtCoverageInstance, 3U, 0U, 0, false);
  covrtLogBasicBlock(&emlrtCoverageInstance, 3U, 2);
}

/* End of code generation (RotZ.c) */
