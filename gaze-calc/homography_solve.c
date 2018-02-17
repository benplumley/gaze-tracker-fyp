/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: homography_solve.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 16-Feb-2018 21:40:13
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "gaze_calc.h"
#include "homography_solve.h"
#include "svd.h"

/* Function Definitions */

/*
 * HOMOGRAPHY_SOLVE finds a homography from point pairs
 *    V = HOMOGRAPHY_SOLVE(PIN, POUT) takes a 2xN matrix of input vectors and
 *    a 2xN matrix of output vectors, and returns the homogeneous
 *    transformation matrix that maps the inputs to the outputs, to some
 *    approximation if there is noise.
 *
 *    This uses the SVD method of
 *    http://www.robots.ox.ac.uk/%7Evgg/presentations/bmvc97/criminispaper/node3.html
 * Arguments    : const double pin[8]
 *                const double pout[8]
 *                double v[9]
 * Return Type  : void
 */
void homography_solve(const double pin[8], const double pout[8], double v[9])
{
  double b_pin[12];
  double rowsXY[72];
  double b_rowsXY[12];
  int i0;
  double U[81];
  double unusedU0[72];
  double unusedU1[64];
  double y[9];
  int i1;

  /*  David Young, University of Sussex, February 2008 */
  /*  Solve equations using SVD */
  for (i0 = 0; i0 < 4; i0++) {
    b_pin[3 * i0] = pin[i0 << 1];
    b_pin[1 + 3 * i0] = pin[1 + (i0 << 1)];
    b_pin[2 + 3 * i0] = 1.0;
    rowsXY[6 + 9 * i0] = pout[i0 << 1] * pin[i0 << 1];
    rowsXY[7 + 9 * i0] = pout[i0 << 1] * pin[1 + (i0 << 1)];
    rowsXY[8 + 9 * i0] = pout[i0 << 1];
    for (i1 = 0; i1 < 3; i1++) {
      b_rowsXY[i1 + 3 * i0] = -b_pin[i1 + 3 * i0];
      rowsXY[i1 + 9 * i0] = b_rowsXY[i1 + 3 * i0];
      rowsXY[(i1 + 9 * i0) + 3] = 0.0;
      rowsXY[i1 + 9 * (i0 + 4)] = 0.0;
      rowsXY[(i1 + 9 * (i0 + 4)) + 3] = b_rowsXY[i1 + 3 * i0];
    }

    rowsXY[6 + 9 * (i0 + 4)] = pout[1 + (i0 << 1)] * pin[i0 << 1];
    rowsXY[7 + 9 * (i0 + 4)] = pout[1 + (i0 << 1)] * pin[1 + (i0 << 1)];
    rowsXY[8 + 9 * (i0 + 4)] = pout[1 + (i0 << 1)];
  }

  svd(rowsXY, U, unusedU0, unusedU1);
  memcpy(&y[0], &U[72], 9U * sizeof(double));
  for (i0 = 0; i0 < 3; i0++) {
    for (i1 = 0; i1 < 3; i1++) {
      v[i1 + 3 * i0] = y[i0 + 3 * i1];
    }
  }
}

/*
 * File trailer for homography_solve.c
 *
 * [EOF]
 */
