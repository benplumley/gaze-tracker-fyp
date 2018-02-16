/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * gaze_calc_initialize.c
 *
 * Code generation for function 'gaze_calc_initialize'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "gaze_calc.h"
#include "gaze_calc_initialize.h"
#include "_coder_gaze_calc_mex.h"
#include "gaze_calc_data.h"
#include "blas.h"
#include "lapacke.h"

/* Function Declarations */
static void gaze_calc_once(void);

/* Function Definitions */
static void gaze_calc_once(void)
{
  int32_T cond_starts_4_0[1] = { 519 };

  int32_T cond_ends_4_0[1] = { 549 };

  int32_T postfix_exprs_4_0[2] = { 0, -1 };

  /* Allocate instance data */
  covrtAllocateInstanceData(&emlrtCoverageInstance);

  /* Initialize Coverage Information */
  covrtScriptInit(&emlrtCoverageInstance,
                  "C:\\Users\\Ben\\Documents\\My Documents\\Bath\\Course\\Year 4\\FYP\\gaze-tracker-fyp\\demonstration-of-progress\\gaze_calc.m",
                  0, 1, 3, 0, 0, 0, 0, 1, 0, 0, 0);

  /* Initialize Function Information */
  covrtFcnInit(&emlrtCoverageInstance, 0, 0, "gaze_calc", 0, -1, 5865);

  /* Initialize Basic Block Information */
  covrtBasicBlockInit(&emlrtCoverageInstance, 0, 2, 5272, -1, 5850);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0, 1, 4628, -1, 4783);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0, 0, 136, -1, 4579);

  /* Initialize If Information */
  /* Initialize MCDC Information */
  /* Initialize For Information */
  covrtForInit(&emlrtCoverageInstance, 0, 0, 4604, 4624, 4822);

  /* Initialize While Information */
  /* Initialize Switch Information */
  /* Start callback for coverage engine */
  covrtScriptStart(&emlrtCoverageInstance, 0U);

  /* Allocate instance data */
  covrtAllocateInstanceData(&emlrtCoverageInstance);

  /* Initialize Coverage Information */
  covrtScriptInit(&emlrtCoverageInstance,
                  "C:\\Users\\Ben\\Documents\\My Documents\\Bath\\Course\\Year 4\\FYP\\gaze-tracker-fyp\\demonstration-of-progress\\Transforms\\Transforms\\RotX"
                  ".m", 1, 1, 3, 2, 0, 0, 0, 0, 0, 0, 0);

  /* Initialize Function Information */
  covrtFcnInit(&emlrtCoverageInstance, 1, 0, "RotX", 0, -1, 364);

  /* Initialize Basic Block Information */
  covrtBasicBlockInit(&emlrtCoverageInstance, 1, 2, 356, -1, 362);
  covrtBasicBlockInit(&emlrtCoverageInstance, 1, 1, 313, -1, 342);
  covrtBasicBlockInit(&emlrtCoverageInstance, 1, 0, 182, -1, 276);

  /* Initialize If Information */
  covrtIfInit(&emlrtCoverageInstance, 1, 0, 280, 294, -1, 353);
  covrtIfInit(&emlrtCoverageInstance, 1, 1, 297, 308, -1, 349);

  /* Initialize MCDC Information */
  /* Initialize For Information */
  /* Initialize While Information */
  /* Initialize Switch Information */
  /* Start callback for coverage engine */
  covrtScriptStart(&emlrtCoverageInstance, 1U);

  /* Allocate instance data */
  covrtAllocateInstanceData(&emlrtCoverageInstance);

  /* Initialize Coverage Information */
  covrtScriptInit(&emlrtCoverageInstance,
                  "C:\\Users\\Ben\\Documents\\My Documents\\Bath\\Course\\Year 4\\FYP\\gaze-tracker-fyp\\demonstration-of-progress\\Transforms\\Transforms\\RotY"
                  ".m", 2, 1, 3, 2, 0, 0, 0, 0, 0, 0, 0);

  /* Initialize Function Information */
  covrtFcnInit(&emlrtCoverageInstance, 2, 0, "RotY", 0, -1, 362);

  /* Initialize Basic Block Information */
  covrtBasicBlockInit(&emlrtCoverageInstance, 2, 2, 354, -1, 360);
  covrtBasicBlockInit(&emlrtCoverageInstance, 2, 1, 312, -1, 341);
  covrtBasicBlockInit(&emlrtCoverageInstance, 2, 0, 186, -1, 276);

  /* Initialize If Information */
  covrtIfInit(&emlrtCoverageInstance, 2, 0, 279, 293, -1, 352);
  covrtIfInit(&emlrtCoverageInstance, 2, 1, 296, 307, -1, 348);

  /* Initialize MCDC Information */
  /* Initialize For Information */
  /* Initialize While Information */
  /* Initialize Switch Information */
  /* Start callback for coverage engine */
  covrtScriptStart(&emlrtCoverageInstance, 2U);

  /* Allocate instance data */
  covrtAllocateInstanceData(&emlrtCoverageInstance);

  /* Initialize Coverage Information */
  covrtScriptInit(&emlrtCoverageInstance,
                  "C:\\Users\\Ben\\Documents\\My Documents\\Bath\\Course\\Year 4\\FYP\\gaze-tracker-fyp\\demonstration-of-progress\\Transforms\\Transforms\\RotZ"
                  ".m", 3, 1, 3, 2, 0, 0, 0, 0, 0, 0, 0);

  /* Initialize Function Information */
  covrtFcnInit(&emlrtCoverageInstance, 3, 0, "RotZ", 0, -1, 338);

  /* Initialize Basic Block Information */
  covrtBasicBlockInit(&emlrtCoverageInstance, 3, 2, 330, -1, 336);
  covrtBasicBlockInit(&emlrtCoverageInstance, 3, 1, 288, -1, 317);
  covrtBasicBlockInit(&emlrtCoverageInstance, 3, 0, 145, -1, 251);

  /* Initialize If Information */
  covrtIfInit(&emlrtCoverageInstance, 3, 0, 255, 269, -1, 328);
  covrtIfInit(&emlrtCoverageInstance, 3, 1, 272, 283, -1, 324);

  /* Initialize MCDC Information */
  /* Initialize For Information */
  /* Initialize While Information */
  /* Initialize Switch Information */
  /* Start callback for coverage engine */
  covrtScriptStart(&emlrtCoverageInstance, 3U);

  /* Allocate instance data */
  covrtAllocateInstanceData(&emlrtCoverageInstance);

  /* Initialize Coverage Information */
  covrtScriptInit(&emlrtCoverageInstance,
                  "C:\\Users\\Ben\\Documents\\My Documents\\Bath\\Course\\Year 4\\FYP\\gaze-tracker-fyp\\demonstration-of-progress\\homography_solve.m",
                  4, 1, 8, 4, 0, 0, 0, 0, 0, 1, 1);

  /* Initialize Function Information */
  covrtFcnInit(&emlrtCoverageInstance, 4, 0, "homography_solve", 0, -1, 1085);

  /* Initialize Basic Block Information */
  covrtBasicBlockInit(&emlrtCoverageInstance, 4, 7, 1051, -1, 1080);
  covrtBasicBlockInit(&emlrtCoverageInstance, 4, 6, 1019, -1, 1027);
  covrtBasicBlockInit(&emlrtCoverageInstance, 4, 5, 990, -1, 998);
  covrtBasicBlockInit(&emlrtCoverageInstance, 4, 4, 780, -1, 974);
  covrtBasicBlockInit(&emlrtCoverageInstance, 4, 3, 705, -1, 745);
  covrtBasicBlockInit(&emlrtCoverageInstance, 4, 2, 674, -1, 690);
  covrtBasicBlockInit(&emlrtCoverageInstance, 4, 1, 625, -1, 668);
  covrtBasicBlockInit(&emlrtCoverageInstance, 4, 0, 554, -1, 594);

  /* Initialize If Information */
  covrtIfInit(&emlrtCoverageInstance, 4, 0, 515, 549, -1, 599);
  covrtIfInit(&emlrtCoverageInstance, 4, 1, 600, 620, -1, 673);
  covrtIfInit(&emlrtCoverageInstance, 4, 2, 692, 700, -1, 750);
  covrtIfInit(&emlrtCoverageInstance, 4, 3, 976, 985, 1010, 1050);

  /* Initialize MCDC Information */
  covrtMcdcInit(&emlrtCoverageInstance, 4, 0, 518, 549, 1, 0, cond_starts_4_0,
                cond_ends_4_0, 2, postfix_exprs_4_0);

  /* Initialize For Information */
  /* Initialize While Information */
  /* Initialize Switch Information */
  /* Start callback for coverage engine */
  covrtScriptStart(&emlrtCoverageInstance, 4U);
}

void gaze_calc_initialize(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  mexFunctionCreateRootTLS();
  emlrtBreakCheckR2012bFlagVar = emlrtGetBreakCheckFlagAddressR2012b();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  if (emlrtFirstTimeR2012b(emlrtRootTLSGlobal)) {
    gaze_calc_once();
  }
}

/* End of code generation (gaze_calc_initialize.c) */
