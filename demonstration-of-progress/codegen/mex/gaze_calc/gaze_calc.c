/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * gaze_calc.c
 *
 * Code generation for function 'gaze_calc'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "gaze_calc.h"
#include "RotX.h"
#include "RotY.h"
#include "RotZ.h"
#include "gaze_calc_data.h"
#include "blas.h"
#include "lapacke.h"

/* Variable Definitions */
static emlrtRSInfo emlrtRSI = { 19, "gaze_calc",
  "C:\\Users\\Ben\\Documents\\My Documents\\Bath\\Course\\Year 4\\FYP\\gaze-tracker-fyp\\demonstration-of-progress\\gaze_calc.m"
};

static emlrtRSInfo b_emlrtRSI = { 29, "gaze_calc",
  "C:\\Users\\Ben\\Documents\\My Documents\\Bath\\Course\\Year 4\\FYP\\gaze-tracker-fyp\\demonstration-of-progress\\gaze_calc.m"
};

static emlrtRSInfo c_emlrtRSI = { 21, "eml_mtimes_helper",
  "E:\\Program Files\\MATLAB\\toolbox\\eml\\lib\\matlab\\ops\\eml_mtimes_helper.m"
};

static emlrtRTEInfo emlrtRTEI = { 103, 23, "eml_mtimes_helper",
  "E:\\Program Files\\MATLAB\\toolbox\\eml\\lib\\matlab\\ops\\eml_mtimes_helper.m"
};

static emlrtBCInfo emlrtBCI = { -1, -1, 26, 7, "M", "gaze_calc",
  "C:\\Users\\Ben\\Documents\\My Documents\\Bath\\Course\\Year 4\\FYP\\gaze-tracker-fyp\\demonstration-of-progress\\gaze_calc.m",
  0 };

static emlrtBCInfo b_emlrtBCI = { -1, -1, 20, 6, "R", "gaze_calc",
  "C:\\Users\\Ben\\Documents\\My Documents\\Bath\\Course\\Year 4\\FYP\\gaze-tracker-fyp\\demonstration-of-progress\\gaze_calc.m",
  0 };

static emlrtBCInfo c_emlrtBCI = { -1, -1, 20, 3, "R", "gaze_calc",
  "C:\\Users\\Ben\\Documents\\My Documents\\Bath\\Course\\Year 4\\FYP\\gaze-tracker-fyp\\demonstration-of-progress\\gaze_calc.m",
  0 };

/* Function Definitions */
void gaze_calc(const emlrtStack *sp, real_T head_x, real_T head_y, real_T head_z,
               real_T head_roll, real_T head_pitch, real_T head_yaw, real_T
               left_eye_x, real_T left_eye_y, real_T right_eye_x, real_T
               right_eye_y, real_T retmat[4])
{
  real_T unusedExpr[9];
  real_T b_unusedExpr[9];
  real_T c_unusedExpr[9];
  emlrtStack st;
  emlrtStack b_st;
  (void)head_x;
  (void)head_y;
  (void)head_z;
  (void)left_eye_x;
  (void)left_eye_y;
  (void)right_eye_x;
  (void)right_eye_y;
  (void)retmat;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  covrtLogFcn(&emlrtCoverageInstance, 0U, 0);
  covrtLogBasicBlock(&emlrtCoverageInstance, 0U, 0);

  /* % */
  /* % */
  /*  a plane */
  /* R = RotA( [1;0;0]+face_rotation_rand*randn(3,1), 0.5*pi + face_rotation_rand*pi*rand,1  ); % rotation of face in world */
  head_roll *= 0.017453292519943295;
  head_pitch *= 0.017453292519943295;
  head_yaw *= 0.017453292519943295;
  st.site = &emlrtRSI;
  RotX(head_roll, unusedExpr);
  st.site = &emlrtRSI;
  RotY(head_pitch, b_unusedExpr);
  st.site = &emlrtRSI;
  RotZ(head_yaw, c_unusedExpr);
  emlrtDynamicBoundsCheckR2012b(4, 1, 3, &c_emlrtBCI, sp);
  emlrtDynamicBoundsCheckR2012b(4, 1, 3, &b_emlrtBCI, sp);

  /* R = eul2rotm(head_roll, head_pitch, head_yaw); % convert rotation angles to direction cosine matrix */
  /* T = [1;5;1]+face_translation_rand*randn(3,1); % translation of face in world */
  emlrtDynamicBoundsCheckR2012b(4, 1, 3, &emlrtBCI, sp);

  /*  combined rotation and translation */
  /*  need homogeneous coordinates for it to work ! */
  st.site = &b_emlrtRSI;
  b_st.site = &c_emlrtRSI;
  emlrtErrorWithMessageIdR2012b(&b_st, &emlrtRTEI, "Coder:MATLAB:innerdim", 0);
}

/* End of code generation (gaze_calc.c) */
