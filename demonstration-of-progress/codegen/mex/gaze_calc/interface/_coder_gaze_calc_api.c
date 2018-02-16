/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_gaze_calc_api.c
 *
 * Code generation for function '_coder_gaze_calc_api'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "gaze_calc.h"
#include "_coder_gaze_calc_api.h"
#include "gaze_calc_data.h"
#include "blas.h"
#include "lapacke.h"

/* Function Declarations */
static real_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static real_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId);
static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *head_x,
  const char_T *identifier);
static const mxArray *emlrt_marshallOut(const real_T u[4]);

/* Function Definitions */
static real_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = c_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static real_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId)
{
  real_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 0U, &dims);
  ret = *(real_T *)mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *head_x,
  const char_T *identifier)
{
  real_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(head_x), &thisId);
  emlrtDestroyArray(&head_x);
  return y;
}

static const mxArray *emlrt_marshallOut(const real_T u[4])
{
  const mxArray *y;
  const mxArray *m0;
  static const int32_T iv3[2] = { 0, 0 };

  static const int32_T iv4[2] = { 2, 2 };

  y = NULL;
  m0 = emlrtCreateNumericArray(2, iv3, mxDOUBLE_CLASS, mxREAL);
  mxSetData((mxArray *)m0, (void *)u);
  emlrtSetDimensions((mxArray *)m0, iv4, 2);
  emlrtAssign(&y, m0);
  return y;
}

void gaze_calc_api(const mxArray * const prhs[10], const mxArray *plhs[1])
{
  real_T (*retmat)[4];
  real_T head_x;
  real_T head_y;
  real_T head_z;
  real_T head_roll;
  real_T head_pitch;
  real_T head_yaw;
  real_T left_eye_x;
  real_T left_eye_y;
  real_T right_eye_x;
  real_T right_eye_y;
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;
  retmat = (real_T (*)[4])mxMalloc(sizeof(real_T [4]));

  /* Marshall function inputs */
  head_x = emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "head_x");
  head_y = emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "head_y");
  head_z = emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "head_z");
  head_roll = emlrt_marshallIn(&st, emlrtAliasP(prhs[3]), "head_roll");
  head_pitch = emlrt_marshallIn(&st, emlrtAliasP(prhs[4]), "head_pitch");
  head_yaw = emlrt_marshallIn(&st, emlrtAliasP(prhs[5]), "head_yaw");
  left_eye_x = emlrt_marshallIn(&st, emlrtAliasP(prhs[6]), "left_eye_x");
  left_eye_y = emlrt_marshallIn(&st, emlrtAliasP(prhs[7]), "left_eye_y");
  right_eye_x = emlrt_marshallIn(&st, emlrtAliasP(prhs[8]), "right_eye_x");
  right_eye_y = emlrt_marshallIn(&st, emlrtAliasP(prhs[9]), "right_eye_y");

  /* Invoke the target function */
  gaze_calc(&st, head_x, head_y, head_z, head_roll, head_pitch, head_yaw,
            left_eye_x, left_eye_y, right_eye_x, right_eye_y, *retmat);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(*retmat);
}

/* End of code generation (_coder_gaze_calc_api.c) */
