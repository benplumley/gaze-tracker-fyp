/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: gaze_calc.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 16-Feb-2018 21:40:13
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "gaze_calc.h"
#include "bsxfun.h"
#include "homography_solve.h"
#include "repmat.h"
#include "mean.h"
#include "cross.h"

/* Function Definitions */

/*
 * Arguments    : double head_x
 *                double head_y
 *                double head_z
 *                double head_roll
 *                double head_pitch
 *                double head_yaw
 *                double left_eye_x
 *                double left_eye_y
 *                double right_eye_x
 *                double right_eye_y
 *                double retmat[4]
 * Return Type  : void
 */
void gaze_calc(double head_x, double head_y, double head_z, double head_roll,
               double head_pitch, double head_yaw, double left_eye_x, double
               left_eye_y, double right_eye_x, double right_eye_y, double
               retmat[4])
{
  double face[16];
  int ia;
  static const signed char iv0[16] = { 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1,
    0, 0 };

  double dv0[9];
  double dv1[9];
  static const signed char iv1[3] = { 1, 0, 0 };

  static const signed char iv2[3] = { 0, 1, 0 };

  double dv2[9];
  double dv3[9];
  int ak;
  static const signed char iv3[3] = { 0, 0, 1 };

  int br;
  double R_data[9];
  double face_data[12];
  int ic;
  int ar;
  int k;
  double midface[3];
  double b_face[3];
  double c_face[3];
  double x[3];
  double y;
  double scale;
  double absxk;
  double t;
  signed char M2_data[9];
  static const signed char R2[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  double mscr[3];
  double a[3];
  double b[3];
  double x2[3];
  double xscr[12];
  static const signed char iv4[12] = { 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0 };

  double b_mscr[4];
  signed char b_xscr[16];
  double b_b[16];
  double C_data[12];
  double xfce[12];
  double b_a;
  double b_xfce[8];
  double c_xscr[8];
  double H[9];
  double b_left_eye_x[3];
  double b_right_eye_x[3];
  double c_b;
  double dv4[2];
  double dv5[2];

  /* % */
  /* % */
  for (ia = 0; ia < 16; ia++) {
    face[ia] = iv0[ia];
  }

  /*  a plane */
  /* R = RotA( [1;0;0]+face_rotation_rand*randn(3,1), 0.5*pi + face_rotation_rand*pi*rand,1  ); % rotation of face in world */
  head_roll *= 0.017453292519943295;
  head_pitch *= 0.017453292519943295;
  head_yaw *= 0.017453292519943295;

  /*  R = RotX(theta) */
  /*  Return the (3 x 3) rotation matrix that rotates about the x axis */
  /*  The angle is in radian. Return the (4x4) matrix if opt ~= 0. */
  /*  R = RotY(theta,opt) */
  /*  Return the (3 x 3) rotation matrix that rotates about the y axis */
  /*  The angle is in radian. Return the (4x4) matrix if opt ~= 0. */
  /*  R = RotZ(theta) */
  /*  Return the (3 x 3) rotation matrix that rotates about the z axis */
  /*  The angle is in radian. */
  dv0[1] = 0.0;
  dv0[4] = cos(head_roll);
  dv0[7] = -sin(head_roll);
  dv0[2] = 0.0;
  dv0[5] = sin(head_roll);
  dv0[8] = cos(head_roll);
  dv1[0] = cos(head_pitch);
  dv1[3] = 0.0;
  dv1[6] = sin(head_pitch);
  for (ia = 0; ia < 3; ia++) {
    dv0[3 * ia] = iv1[ia];
    dv1[1 + 3 * ia] = iv2[ia];
  }

  dv1[2] = -sin(head_pitch);
  dv1[5] = 0.0;
  dv1[8] = cos(head_pitch);
  dv3[0] = cos(head_yaw);
  dv3[3] = -sin(head_yaw);
  dv3[6] = 0.0;
  dv3[1] = sin(head_yaw);
  dv3[4] = cos(head_yaw);
  dv3[7] = 0.0;
  for (ia = 0; ia < 3; ia++) {
    for (ak = 0; ak < 3; ak++) {
      dv2[ia + 3 * ak] = 0.0;
      for (br = 0; br < 3; br++) {
        dv2[ia + 3 * ak] += dv0[ia + 3 * br] * dv1[br + 3 * ak];
      }
    }

    dv3[2 + 3 * ia] = iv3[ia];
  }

  for (ia = 0; ia < 3; ia++) {
    for (ak = 0; ak < 3; ak++) {
      dv0[ia + 3 * ak] = 0.0;
      for (br = 0; br < 3; br++) {
        dv0[ia + 3 * ak] += dv2[ia + 3 * br] * dv3[br + 3 * ak];
      }
    }
  }

  for (ia = 0; ia < 3; ia++) {
    for (ak = 0; ak < 3; ak++) {
      R_data[ak + 3 * ia] = dv0[ak + 3 * ia];
    }
  }

  R_data[12] = 1.0;

  /* R = eul2rotm(head_roll, head_pitch, head_yaw); % convert rotation angles to direction cosine matrix */
  /* T = [1;5;1]+face_translation_rand*randn(3,1); % translation of face in world */
  R_data[9] = head_x;
  R_data[10] = head_y;
  R_data[11] = head_z;

  /*  combined rotation and translation */
  for (ia = 0; ia < 4; ia++) {
    face[3 + (ia << 2)] = 1.0;
  }

  /*  need homogeneous coordinates for it to work ! */
  memset(&face_data[0], 0, 12U * sizeof(double));
  for (ak = 0; ak <= 9; ak += 3) {
    for (ic = ak; ic + 1 <= ak + 3; ic++) {
      face_data[ic] = 0.0;
    }
  }

  br = 0;
  for (ak = 0; ak <= 9; ak += 3) {
    ar = -1;
    for (k = br; k + 1 <= br + 3; k++) {
      if (face[k] != 0.0) {
        ia = ar;
        for (ic = ak; ic + 1 <= ak + 3; ic++) {
          ia++;
          face_data[ic] += face[k] * R_data[ia];
        }
      }

      ar += 3;
    }

    br += 3;
  }

  /*  do the transform */
  /*  pick out the new face coordinates */
  mean(*(double (*)[12])&face_data[0], midface);

  /*  the eye is in the middle */
  /* x = face - eye; % work out gaze direction */
  /*  calculate normal to the face passing through the eye */
  for (ia = 0; ia < 3; ia++) {
    b_face[ia] = face_data[ia] - midface[ia];
    c_face[ia] = face_data[ia + 3] - midface[ia];
  }

  cross(b_face, c_face, x);

  /* [U,S,V] = svd(x); % singular value decomposition puts a reference frame onto face */
  /* gaze = U(:,3); % gaze is the so-called 'null' vector - out of the plane */
  /*  for points IN face-space the projection onto the face plane is assumed to */
  /*  be orthogonal */
  /* P = [1 0 0;0 1 0]; */
  /* P = [0 1 0;0 0 1]; */
  /* % calculate eye depth based on known coordinates and face plane */
  y = 0.0;
  scale = 2.2250738585072014E-308;
  for (k = 0; k < 3; k++) {
    absxk = fabs(x[k]);
    if (absxk > scale) {
      t = scale / absxk;
      y = 1.0 + y * t * t;
      scale = absxk;
    } else {
      t = absxk / scale;
      y += t * t;
    }
  }

  y = scale * sqrt(y);
  for (ia = 0; ia < 3; ia++) {
    x[ia] /= y;
  }

  /*  turn x into a unit vector */
  /* eyep = eyep - (dot(x, (eyep - midface))) * x; % move eyep into the face plane */
  /* % screen is treated like the face */
  for (ia = 0; ia < 16; ia++) {
    face[ia] = iv0[ia];
  }

  for (ia = 0; ia < 4; ia++) {
    face[2 + (ia << 2)] = 0.0;
  }

  /* R2 = RotA( [1;0;0]+screen_rotation_rand*randn(3,1), 1.5*pi + screen_rotation_rand*pi*rand,1  ); % rotation of face in world */
  /* T2 = [1;1;2]+screen_translation_rand*randn(3,1); % translation of face in world */
  for (ia = 0; ia < 9; ia++) {
    M2_data[ia] = R2[ia];
  }

  for (ia = 0; ia < 3; ia++) {
    M2_data[ia + 9] = 0;
  }

  /*  combined rotation and translation */
  for (ia = 0; ia < 4; ia++) {
    face[3 + (ia << 2)] = 1.0;
  }

  /*  need homogeneous coordinates for it to work ! */
  memset(&face_data[0], 0, 12U * sizeof(double));
  for (ak = 0; ak <= 9; ak += 3) {
    for (ic = ak; ic + 1 <= ak + 3; ic++) {
      face_data[ic] = 0.0;
    }
  }

  br = 0;
  for (ak = 0; ak <= 9; ak += 3) {
    ar = -1;
    for (k = br; k + 1 <= br + 3; k++) {
      if (face[k] != 0.0) {
        ia = ar;
        for (ic = ak; ic + 1 <= ak + 3; ic++) {
          ia++;
          face_data[ic] += face[k] * (double)M2_data[ia];
        }
      }

      ar += 3;
    }

    br += 3;
  }

  mean(*(double (*)[12])&face_data[0], mscr);

  /*  middle of screen */
  /* x = screen - mscr; % work our gaze direction */
  for (ia = 0; ia < 3; ia++) {
    a[ia] = face_data[ia] - mscr[ia];
    b[ia] = face_data[ia + 3] - mscr[ia];
  }

  x2[0] = a[1] * b[2] - a[2] * b[1];
  x2[1] = a[2] * b[0] - a[0] * b[2];
  x2[2] = a[0] * b[1] - a[1] * b[0];

  /* [U2,S2,V2] = svd(x2); % singular value decomposition puts a reference frame onto face */
  /* nscr = U2(:,3); %  'null' vector - out of the screen plane */
  /* % Map a point in the screen into the face coordinates, via the world */
  /*  number of points to generate the homography from */
  /* xscr = repmat(mscr, 1, numpoints)+0.3*randn(3,numpoints); % a point on the screen */
  for (ia = 0; ia < 12; ia++) {
    xscr[ia] = iv4[ia];
  }

  /* xscr = randn(3,numpoints); % a point on the screen */
  for (ia = 0; ia < 4; ia++) {
    xscr[1 + 3 * ia] = 1.0;
  }

  /*  zero because its in the plane */
  /* xwrld = (U2*xscr) + repmat(mscr,1,numpoints) % could be a single matrix ! */
  /* xfce = P*U'*(xwrld - repmat(midface,1,numpoints)) % map into face coordinates, could be one matrix ! */
  /* xfce = P*U'*(xwrld - repmat(midface,1,numpoints)) % map into face coordinates, could be one matrix ! */
  /* xscr(4,:) = 1 % need homogeneous coordinates for it to work ! */
  /*  create homogeneous version */
  /*  create homogeneous version */
  /* mscr(4,:) = 1; % need homogeneous coordinates for it to work ! */
  /* xwrld(4,:) = 1; % need homogeneous coordinates for it to work ! */
  /* M2 */
  /* xwrld = (M2'*xscr) + repmat(mscr,1,numpoints); % could be a single matrix ! */
  /* xwrld = (M2*xscr) */
  for (ak = 0; ak < 3; ak++) {
    b_mscr[ak] = mscr[ak];
  }

  b_mscr[3] = 1.0;
  repmat(b_mscr, face);
  for (ia = 0; ia < 4; ia++) {
    for (ak = 0; ak < 3; ak++) {
      b_xscr[ak + (ia << 2)] = (signed char)xscr[ak + 3 * ia];
    }

    b_xscr[3 + (ia << 2)] = 1;
    for (ak = 0; ak < 4; ak++) {
      b_b[ak + (ia << 2)] = (double)b_xscr[ak + (ia << 2)] - face[ak + (ia << 2)];
    }
  }

  memset(&face_data[0], 0, 12U * sizeof(double));
  for (ak = 0; ak <= 9; ak += 3) {
    for (ic = ak; ic + 1 <= ak + 3; ic++) {
      face_data[ic] = 0.0;
    }
  }

  br = 0;
  for (ak = 0; ak <= 9; ak += 3) {
    ar = -1;
    for (k = br; k + 1 <= br + 3; k++) {
      if (b_b[k] != 0.0) {
        ia = ar;
        for (ic = ak; ic + 1 <= ak + 3; ic++) {
          ia++;
          face_data[ic] += b_b[k] * (double)M2_data[ia];
        }
      }

      ar += 3;
    }

    br += 3;
  }

  /*  could be a single matrix ! */
  /* midface(4,:) = 1; % need homogeneous coordinates for it to work ! */
  /*  create homogeneous version */
  for (ia = 0; ia < 4; ia++) {
    face_data[3 + 3 * ia] = 1.0;
  }

  /*  need homogeneous coordinates for it to work ! */
  /* xfce = P*U'*(xwrld - repmat(midface,1,numpoints)) % map into face coordinates, could be one matrix ! */
  /* xfce = M*(xwrld - repmat(midface,1,numpoints)); % map into face coordinates, could be one matrix ! */
  /* xfce = (M*xwrld) - repmat(midface,1,numpoints); % map into face coordinates, could be one matrix ! */
  memset(&C_data[0], 0, 12U * sizeof(double));
  for (ak = 0; ak <= 9; ak += 3) {
    for (ic = ak; ic + 1 <= ak + 3; ic++) {
      C_data[ic] = 0.0;
    }
  }

  br = 0;
  for (ak = 0; ak <= 9; ak += 3) {
    ar = -1;
    for (k = br; k + 1 <= br + 3; k++) {
      if (face_data[k] != 0.0) {
        ia = ar;
        for (ic = ak; ic + 1 <= ak + 3; ic++) {
          ia++;
          C_data[ic] += face_data[k] * R_data[ia];
        }
      }

      ar += 3;
    }

    br += 3;
  }

  for (ak = 0; ak < 3; ak++) {
    b_mscr[ak] = midface[ak];
  }

  b_mscr[3] = 1.0;
  repmat(b_mscr, face);
  for (ia = 0; ia < 16; ia++) {
    face[ia] += C_data[ia];
  }

  /* xfce = M*(xwrld + repmat(midface,1,numpoints)); */
  /* xwrld(1:2,:) */
  /* xwrld(3,:) */
  ak = 0;
  br = 0;
  for (ar = 0; ar <= 10; ar += 3) {
    for (k = 0; k < 3; k++) {
      ia = ak + k;
      b_a = face[ia % 3 + (ia / 3 << 2)] / face[3 + (br << 2)];
      xfce[ar + k] = b_a;
      a[k] = b_a;
    }

    ak += 3;
    br++;
  }

  /*  make face coords nonhomogeneous again */
  /* xscr = bsxfun(@rdivide, xscr(1:3,:), xscr(4,:)); % make face coords nonhomogeneous again */
  /* mscr = mscr(1:3,:); */
  /* xfce = xfce - (dot(x, (xfce - repmat(midface,1,numpoints)))) * x; % move them into the face plane */
  /* xscr = xscr - (dot(x2, (xscr - repmat(mscr,1,numpoints)))) * x2; % move them into the screen plane */
  /* % the points xfce and xscr must be related by a homography because the */
  /*  mapping is from one plane to another. Here is a sanity check */
  /* xscr(3,:) = 1 */
  /* xfce(3,:) = 1 */
  /* H = homography_est( xscr, xfce ) */
  /* xfce = xfce([1,3],:) */
  /* xscr = xscr([1,3],:) */
  for (ak = 0; ak < 4; ak++) {
    y = 0.0;
    for (k = 0; k < 3; k++) {
      y += x[k] * (xfce[k + 3 * ak] - midface[k]);
    }

    /*  move them into the face plane */
    scale = 0.0;
    for (k = 0; k < 3; k++) {
      xfce[k + 3 * ak] -= y * x[k];
      c_b = xscr[k + 3 * ak] - mscr[k];
      scale += x2[k] * c_b;
      b[k] = c_b;
    }

    for (ia = 0; ia < 3; ia++) {
      xscr[ia + 3 * ak] -= scale * x2[ia];
    }

    /*  move them into the screen plane */
    for (ia = 0; ia < 2; ia++) {
      b_xfce[ia + (ak << 1)] = xfce[(ia << 1) + 3 * ak];
      c_xscr[ia + (ak << 1)] = xscr[(ia << 1) + 3 * ak];
    }
  }

  homography_solve(b_xfce, c_xscr, H);

  /*  z = H*xscr; */
  /*  z_nh = bsxfun(@rdivide, z(1:2,:), z(3,:)); */
  /*  d = z_nh - xfce(1:2,:); */
  /*  max(abs(d(:))); */
  /* % */
  b_left_eye_x[0] = left_eye_x;
  b_left_eye_x[1] = left_eye_y;
  b_left_eye_x[2] = 1.0;
  b_right_eye_x[0] = right_eye_x;
  b_right_eye_x[1] = right_eye_y;
  b_right_eye_x[2] = 1.0;
  for (ia = 0; ia < 3; ia++) {
    a[ia] = 0.0;
    b[ia] = 0.0;
    for (ak = 0; ak < 3; ak++) {
      a[ia] += H[ia + 3 * ak] * b_left_eye_x[ak];
      b[ia] += H[ia + 3 * ak] * b_right_eye_x[ak];
    }
  }

  /* lefteyep = lefteyep(1:2,:); */
  /* righteyep = righteyep(1:2,:); */
  /* x2 = x2 ./ norm(x2); % turn x into a unit vector */
  bsxfun(*(double (*)[2])&a[0], a[2], dv4);
  bsxfun(*(double (*)[2])&b[0], b[2], dv5);
  for (ia = 0; ia < 2; ia++) {
    retmat[ia << 1] = dv4[ia];
    retmat[1 + (ia << 1)] = dv5[ia];
  }
}

/*
 * File trailer for gaze_calc.c
 *
 * [EOF]
 */
