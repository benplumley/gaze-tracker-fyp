/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_gaze_calc_api.h
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 16-Feb-2018 21:40:13
 */

#ifndef _CODER_GAZE_CALC_API_H
#define _CODER_GAZE_CALC_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_gaze_calc_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void gaze_calc(real_T head_x, real_T head_y, real_T head_z, real_T
                      head_roll, real_T head_pitch, real_T head_yaw, real_T
                      left_eye_x, real_T left_eye_y, real_T right_eye_x, real_T
                      right_eye_y, real_T retmat[4]);
extern void gaze_calc_api(const mxArray * const prhs[10], const mxArray *plhs[1]);
extern void gaze_calc_atexit(void);
extern void gaze_calc_initialize(void);
extern void gaze_calc_terminate(void);
extern void gaze_calc_xil_terminate(void);

#endif

/*
 * File trailer for _coder_gaze_calc_api.h
 *
 * [EOF]
 */
