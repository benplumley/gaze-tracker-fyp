/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: svd.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 16-Feb-2018 21:40:13
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "gaze_calc.h"
#include "svd.h"
#include "xaxpy.h"
#include "xdotc.h"
#include "xnrm2.h"
#include "xscal.h"
#include "xrot.h"
#include "xrotg.h"
#include "xswap.h"

/* Function Definitions */

/*
 * Arguments    : const double A[72]
 *                double U[81]
 *                double S[72]
 *                double V[64]
 * Return Type  : void
 */
void svd(const double A[72], double U[81], double S[72], double V[64])
{
  double b_A[72];
  double s[8];
  double e[8];
  double work[9];
  int q;
  int m;
  int iter;
  boolean_T apply_transform;
  double ztest0;
  int qs;
  int qp1jj;
  int kase;
  double snorm;
  double rt;
  double ztest;
  int exitg3;
  boolean_T exitg2;
  double f;
  double varargin_1[5];
  double mtmp;
  boolean_T exitg1;
  double sqds;
  memcpy(&b_A[0], &A[0], 72U * sizeof(double));
  memset(&s[0], 0, sizeof(double) << 3);
  memset(&e[0], 0, sizeof(double) << 3);
  memset(&work[0], 0, 9U * sizeof(double));
  memset(&U[0], 0, 81U * sizeof(double));
  memset(&V[0], 0, sizeof(double) << 6);
  for (q = 0; q < 8; q++) {
    iter = q + 9 * q;
    apply_transform = false;
    ztest0 = xnrm2(9 - q, b_A, iter + 1);
    if (ztest0 > 0.0) {
      apply_transform = true;
      if (b_A[iter] < 0.0) {
        s[q] = -ztest0;
      } else {
        s[q] = ztest0;
      }

      if (fabs(s[q]) >= 1.0020841800044864E-292) {
        ztest0 = 1.0 / s[q];
        kase = (iter - q) + 9;
        for (qp1jj = iter; qp1jj + 1 <= kase; qp1jj++) {
          b_A[qp1jj] *= ztest0;
        }
      } else {
        kase = (iter - q) + 9;
        for (qp1jj = iter; qp1jj + 1 <= kase; qp1jj++) {
          b_A[qp1jj] /= s[q];
        }
      }

      b_A[iter]++;
      s[q] = -s[q];
    } else {
      s[q] = 0.0;
    }

    for (qs = q + 1; qs + 1 < 9; qs++) {
      kase = q + 9 * qs;
      if (apply_transform) {
        xaxpy(9 - q, -(xdotc(9 - q, b_A, iter + 1, b_A, kase + 1) / b_A[q + 9 *
                       q]), iter + 1, b_A, kase + 1);
      }

      e[qs] = b_A[kase];
    }

    for (qp1jj = q; qp1jj + 1 < 10; qp1jj++) {
      U[qp1jj + 9 * q] = b_A[qp1jj + 9 * q];
    }

    if (q + 1 <= 6) {
      ztest0 = b_xnrm2(7 - q, e, q + 2);
      if (ztest0 == 0.0) {
        e[q] = 0.0;
      } else {
        if (e[q + 1] < 0.0) {
          e[q] = -ztest0;
        } else {
          e[q] = ztest0;
        }

        ztest0 = e[q];
        if (fabs(e[q]) >= 1.0020841800044864E-292) {
          ztest0 = 1.0 / e[q];
          for (qp1jj = q + 1; qp1jj + 1 < 9; qp1jj++) {
            e[qp1jj] *= ztest0;
          }
        } else {
          for (qp1jj = q + 1; qp1jj + 1 < 9; qp1jj++) {
            e[qp1jj] /= ztest0;
          }
        }

        e[q + 1]++;
        e[q] = -e[q];
        for (qp1jj = q + 1; qp1jj + 1 < 10; qp1jj++) {
          work[qp1jj] = 0.0;
        }

        for (qs = q + 1; qs + 1 < 9; qs++) {
          b_xaxpy(8 - q, e[qs], b_A, (q + 9 * qs) + 2, work, q + 2);
        }

        for (qs = q + 1; qs + 1 < 9; qs++) {
          c_xaxpy(8 - q, -e[qs] / e[q + 1], work, q + 2, b_A, (q + 9 * qs) + 2);
        }
      }

      for (qp1jj = q + 1; qp1jj + 1 < 9; qp1jj++) {
        V[qp1jj + (q << 3)] = e[qp1jj];
      }
    }
  }

  m = 6;
  e[6] = b_A[69];
  e[7] = 0.0;
  memset(&U[72], 0, 9U * sizeof(double));
  U[80] = 1.0;
  for (q = 7; q >= 0; q += -1) {
    iter = q + 9 * q;
    if (s[q] != 0.0) {
      for (qs = q + 1; qs + 1 < 10; qs++) {
        kase = (q + 9 * qs) + 1;
        d_xaxpy(9 - q, -(b_xdotc(9 - q, U, iter + 1, U, kase) / U[iter]), iter +
                1, U, kase);
      }

      for (qp1jj = q; qp1jj + 1 < 10; qp1jj++) {
        U[qp1jj + 9 * q] = -U[qp1jj + 9 * q];
      }

      U[iter]++;
      for (qp1jj = 1; qp1jj <= q; qp1jj++) {
        U[(qp1jj + 9 * q) - 1] = 0.0;
      }
    } else {
      memset(&U[q * 9], 0, 9U * sizeof(double));
      U[iter] = 1.0;
    }
  }

  for (q = 7; q >= 0; q += -1) {
    if ((q + 1 <= 6) && (e[q] != 0.0)) {
      kase = (q + (q << 3)) + 2;
      for (qs = q + 1; qs + 1 < 9; qs++) {
        qp1jj = (q + (qs << 3)) + 2;
        e_xaxpy(7 - q, -(c_xdotc(7 - q, V, kase, V, qp1jj) / V[kase - 1]), kase,
                V, qp1jj);
      }
    }

    memset(&V[q << 3], 0, sizeof(double) << 3);
    V[q + (q << 3)] = 1.0;
  }

  for (q = 0; q < 8; q++) {
    ztest0 = e[q];
    if (s[q] != 0.0) {
      rt = fabs(s[q]);
      ztest = s[q] / rt;
      s[q] = rt;
      if (q + 1 < 8) {
        ztest0 = e[q] / ztest;
      }

      xscal(ztest, U, 1 + 9 * q);
    }

    if ((q + 1 < 8) && (ztest0 != 0.0)) {
      rt = fabs(ztest0);
      ztest = rt / ztest0;
      ztest0 = rt;
      s[q + 1] *= ztest;
      b_xscal(ztest, V, 1 + ((q + 1) << 3));
    }

    e[q] = ztest0;
  }

  iter = 0;
  snorm = 0.0;
  for (qp1jj = 0; qp1jj < 8; qp1jj++) {
    ztest0 = fabs(s[qp1jj]);
    ztest = fabs(e[qp1jj]);
    if ((ztest0 >= ztest) || rtIsNaN(ztest)) {
    } else {
      ztest0 = ztest;
    }

    if ((snorm >= ztest0) || rtIsNaN(ztest0)) {
    } else {
      snorm = ztest0;
    }
  }

  while ((m + 2 > 0) && (!(iter >= 75))) {
    qp1jj = m;
    do {
      exitg3 = 0;
      q = qp1jj + 1;
      if (qp1jj + 1 == 0) {
        exitg3 = 1;
      } else {
        ztest0 = fabs(e[qp1jj]);
        if ((ztest0 <= 2.2204460492503131E-16 * (fabs(s[qp1jj]) + fabs(s[qp1jj +
               1]))) || (ztest0 <= 1.0020841800044864E-292) || ((iter > 20) &&
             (ztest0 <= 2.2204460492503131E-16 * snorm))) {
          e[qp1jj] = 0.0;
          exitg3 = 1;
        } else {
          qp1jj--;
        }
      }
    } while (exitg3 == 0);

    if (qp1jj + 1 == m + 1) {
      kase = 4;
    } else {
      qs = m + 2;
      kase = m + 2;
      exitg2 = false;
      while ((!exitg2) && (kase >= qp1jj + 1)) {
        qs = kase;
        if (kase == qp1jj + 1) {
          exitg2 = true;
        } else {
          ztest0 = 0.0;
          if (kase < m + 2) {
            ztest0 = fabs(e[kase - 1]);
          }

          if (kase > qp1jj + 2) {
            ztest0 += fabs(e[kase - 2]);
          }

          ztest = fabs(s[kase - 1]);
          if ((ztest <= 2.2204460492503131E-16 * ztest0) || (ztest <=
               1.0020841800044864E-292)) {
            s[kase - 1] = 0.0;
            exitg2 = true;
          } else {
            kase--;
          }
        }
      }

      if (qs == qp1jj + 1) {
        kase = 3;
      } else if (qs == m + 2) {
        kase = 1;
      } else {
        kase = 2;
        q = qs;
      }
    }

    switch (kase) {
     case 1:
      f = e[m];
      e[m] = 0.0;
      for (qp1jj = m; qp1jj + 1 >= q + 1; qp1jj--) {
        xrotg(&s[qp1jj], &f, &ztest0, &ztest);
        if (qp1jj + 1 > q + 1) {
          f = -ztest * e[qp1jj - 1];
          e[qp1jj - 1] *= ztest0;
        }

        xrot(V, 1 + (qp1jj << 3), 1 + ((m + 1) << 3), ztest0, ztest);
      }
      break;

     case 2:
      f = e[q - 1];
      e[q - 1] = 0.0;
      for (qp1jj = q; qp1jj + 1 <= m + 2; qp1jj++) {
        xrotg(&s[qp1jj], &f, &ztest0, &ztest);
        f = -ztest * e[qp1jj];
        e[qp1jj] *= ztest0;
        b_xrot(U, 1 + 9 * qp1jj, 1 + 9 * (q - 1), ztest0, ztest);
      }
      break;

     case 3:
      varargin_1[0] = fabs(s[m + 1]);
      varargin_1[1] = fabs(s[m]);
      varargin_1[2] = fabs(e[m]);
      varargin_1[3] = fabs(s[q]);
      varargin_1[4] = fabs(e[q]);
      kase = 1;
      mtmp = varargin_1[0];
      if (rtIsNaN(varargin_1[0])) {
        qp1jj = 2;
        exitg1 = false;
        while ((!exitg1) && (qp1jj < 6)) {
          kase = qp1jj;
          if (!rtIsNaN(varargin_1[qp1jj - 1])) {
            mtmp = varargin_1[qp1jj - 1];
            exitg1 = true;
          } else {
            qp1jj++;
          }
        }
      }

      if (kase < 5) {
        while (kase + 1 < 6) {
          if (varargin_1[kase] > mtmp) {
            mtmp = varargin_1[kase];
          }

          kase++;
        }
      }

      f = s[m + 1] / mtmp;
      ztest0 = s[m] / mtmp;
      ztest = e[m] / mtmp;
      sqds = s[q] / mtmp;
      rt = ((ztest0 + f) * (ztest0 - f) + ztest * ztest) / 2.0;
      ztest0 = f * ztest;
      ztest0 *= ztest0;
      if ((rt != 0.0) || (ztest0 != 0.0)) {
        ztest = sqrt(rt * rt + ztest0);
        if (rt < 0.0) {
          ztest = -ztest;
        }

        ztest = ztest0 / (rt + ztest);
      } else {
        ztest = 0.0;
      }

      f = (sqds + f) * (sqds - f) + ztest;
      rt = sqds * (e[q] / mtmp);
      for (qp1jj = q + 1; qp1jj <= m + 1; qp1jj++) {
        xrotg(&f, &rt, &ztest0, &ztest);
        if (qp1jj > q + 1) {
          e[qp1jj - 2] = f;
        }

        f = ztest0 * s[qp1jj - 1] + ztest * e[qp1jj - 1];
        e[qp1jj - 1] = ztest0 * e[qp1jj - 1] - ztest * s[qp1jj - 1];
        rt = ztest * s[qp1jj];
        s[qp1jj] *= ztest0;
        xrot(V, 1 + ((qp1jj - 1) << 3), 1 + (qp1jj << 3), ztest0, ztest);
        s[qp1jj - 1] = f;
        xrotg(&s[qp1jj - 1], &rt, &ztest0, &ztest);
        f = ztest0 * e[qp1jj - 1] + ztest * s[qp1jj];
        s[qp1jj] = -ztest * e[qp1jj - 1] + ztest0 * s[qp1jj];
        rt = ztest * e[qp1jj];
        e[qp1jj] *= ztest0;
        b_xrot(U, 1 + 9 * (qp1jj - 1), 1 + 9 * qp1jj, ztest0, ztest);
      }

      e[m] = f;
      iter++;
      break;

     default:
      if (s[q] < 0.0) {
        s[q] = -s[q];
        b_xscal(-1.0, V, 1 + (q << 3));
      }

      kase = q + 1;
      while ((q + 1 < 8) && (s[q] < s[kase])) {
        rt = s[q];
        s[q] = s[kase];
        s[kase] = rt;
        xswap(V, 1 + (q << 3), 1 + ((q + 1) << 3));
        b_xswap(U, 1 + 9 * q, 1 + 9 * (q + 1));
        q = kase;
        kase++;
      }

      iter = 0;
      m--;
      break;
    }
  }

  memcpy(&e[0], &s[0], sizeof(double) << 3);
  memset(&S[0], 0, 72U * sizeof(double));
  for (qp1jj = 0; qp1jj < 8; qp1jj++) {
    S[qp1jj + 9 * qp1jj] = e[qp1jj];
  }
}

/*
 * File trailer for svd.c
 *
 * [EOF]
 */
