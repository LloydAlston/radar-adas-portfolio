/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: fmcw_range_model.c
 *
 * Code generated for Simulink model 'fmcw_range_model'.
 *
 * Model version                  : 1.1
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Tue Jul 21 16:53:10 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "fmcw_range_model.h"
#include "fmcw_range_model_types.h"
#include "rtwtypes.h"
#include "rt_nonfinite.h"
#include <math.h>
#include "fmcw_range_model_private.h"
#include <string.h>
#include <float.h>

/* Block signals (default storage) */
B_fmcw_range_model_T fmcw_range_model_B;

/* Block states (default storage) */
DW_fmcw_range_model_T fmcw_range_model_DW;

/* Real-time model */
static RT_MODEL_fmcw_range_model_T fmcw_range_model_M_;
RT_MODEL_fmcw_range_model_T *const fmcw_range_model_M = &fmcw_range_model_M_;

/* Forward declaration for local functions */
static void fmcw_range__SystemCore_stepImpl(d_dspcodegen_VariableFraction_T *obj,
  const creal_T varargin_1[100], real_T varargin_2, creal_T varargout_1[100]);
static real_T fmcw_range_model_mod(real_T x, real_T y);
static void fmcw_range_m_binary_expand_op_1(creal_T in1[100], const int32_T
  in2_data[], const int32_T *in2_size, const real_T in3_data[], const int32_T
  in3_size[2], const creal_T in4[100], real_T in5);
static void fmcw_range_mod_binary_expand_op(phased_FreeSpace_fmcw_range_m_T *in1,
  const int32_T in2_data[], const int32_T *in2_size, const real_T in3_data[],
  const int32_T in3_size[2], const creal_T in4[100], real_T in5, const real_T
  in6_data[], const int32_T in6_size[2]);
static void fmcw_AbstractFreeSpace_stepImpl(phased_FreeSpace_fmcw_range_m_T *obj,
  const creal_T x_inc[100], const real_T startPos[3], const real_T endPos[3],
  const real_T startVel[3], const real_T endVel[3], creal_T y[100]);
static void fmcw_range_mod_SystemCore_setup(phased_FMCWWaveform_fmcw_rang_T *obj);
static void rate_scheduler(void);

/*
 *         This function updates active task flag for each subrate.
 *         The function is called at model base rate, hence the
 *         generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (fmcw_range_model_M->Timing.TaskCounters.TID[1])++;
  if ((fmcw_range_model_M->Timing.TaskCounters.TID[1]) > 99) {/* Sample time: [5.0E-7s, 0.0s] */
    fmcw_range_model_M->Timing.TaskCounters.TID[1] = 0;
  }

  (fmcw_range_model_M->Timing.TaskCounters.TID[2])++;
  if ((fmcw_range_model_M->Timing.TaskCounters.TID[2]) > 1999) {
                               /* Sample time: [9.9999999999999991E-6s, 0.0s] */
    fmcw_range_model_M->Timing.TaskCounters.TID[2] = 0;
  }
}

real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else {
    real_T tmp;
    real_T tmp_0;
    tmp = fabs(u0);
    tmp_0 = fabs(u1);
    if (rtIsInf(u1)) {
      if (tmp == 1.0) {
        y = 1.0;
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = (rtNaN);
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

real_T rt_remd_snf(real_T u0, real_T u1)
{
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1) || rtIsInf(u0)) {
    y = (rtNaN);
  } else if (rtIsInf(u1)) {
    y = u0;
  } else if ((u1 != 0.0) && (u1 != trunc(u1))) {
    real_T q;
    q = fabs(u0 / u1);
    if (!(fabs(q - floor(q + 0.5)) > DBL_EPSILON * q)) {
      y = 0.0 * u0;
    } else {
      y = fmod(u0, u1);
    }
  } else {
    y = fmod(u0, u1);
  }

  return y;
}

static void fmcw_range__SystemCore_stepImpl(d_dspcodegen_VariableFraction_T *obj,
  const creal_T varargin_1[100], real_T varargin_2, creal_T varargout_1[100])
{
  real_T frac;
  int32_T b_ti;
  int32_T buffstart_tmp_tmp;
  int32_T i;

  /* Start for MATLABSystem: '<Root>/Free Space' */
  /* System object Outputs function: dsp.VariableFractionalDelay */
  b_ti = (int32_T)floor(varargin_2);
  if (b_ti < 0) {
    b_ti = 0;
    frac = 0.0;
  } else if (b_ti >= 100) {
    b_ti = 100;
    frac = 0.0;
  } else {
    /* Start for MATLABSystem: '<Root>/Free Space' */
    frac = varargin_2 - (real_T)b_ti;
  }

  /* Start for MATLABSystem: '<Root>/Free Space' */
  buffstart_tmp_tmp = obj->cSFunObject.W0_BUFF_OFFSET;
  for (i = 0; i < 100; i++) {
    real_T accumIn_im;
    real_T accumIn_re;
    int32_T idx;
    int32_T idx_tmp;

    /* Start for MATLABSystem: '<Root>/Free Space' */
    idx_tmp = i - b_ti;
    if (idx_tmp - 1 < 0) {
      /* Start for MATLABSystem: '<Root>/Free Space' */
      idx = (idx_tmp + buffstart_tmp_tmp) - 1;
      if (idx < 0) {
        /* Start for MATLABSystem: '<Root>/Free Space' */
        idx += 101;
      }

      /* Start for MATLABSystem: '<Root>/Free Space' */
      accumIn_re = obj->cSFunObject.W1_BUFF[idx].re;
      accumIn_im = obj->cSFunObject.W1_BUFF[idx].im;
    } else {
      /* Start for MATLABSystem: '<Root>/Free Space' */
      accumIn_re = varargin_1[idx_tmp - 1].re;
      accumIn_im = varargin_1[idx_tmp - 1].im;
    }

    if (idx_tmp < 0) {
      real_T varargin_1_re;

      /* Start for MATLABSystem: '<Root>/Free Space' */
      idx = idx_tmp + buffstart_tmp_tmp;
      if (idx < 0) {
        /* Start for MATLABSystem: '<Root>/Free Space' */
        idx += 101;
      }

      /* Start for MATLABSystem: '<Root>/Free Space' */
      varargin_1_re = obj->cSFunObject.W1_BUFF[idx].re;
      varargout_1[i].re = (accumIn_re - varargin_1_re) * frac + varargin_1_re;
      varargin_1_re = obj->cSFunObject.W1_BUFF[idx].im;
      varargout_1[i].im = (accumIn_im - varargin_1_re) * frac + varargin_1_re;
    } else {
      real_T varargin_1_im;
      real_T varargin_1_re;

      /* Start for MATLABSystem: '<Root>/Free Space' */
      varargin_1_re = varargin_1[idx_tmp].re;
      varargin_1_im = varargin_1[idx_tmp].im;
      varargout_1[i].re = (accumIn_re - varargin_1_re) * frac + varargin_1_re;
      varargout_1[i].im = (accumIn_im - varargin_1_im) * frac + varargin_1_im;
    }
  }

  /* Start for MATLABSystem: '<Root>/Free Space' */
  /* System object Update function: dsp.VariableFractionalDelay */
  b_ti = obj->cSFunObject.W0_BUFF_OFFSET;
  for (i = 0; i < 100; i++) {
    /* Start for MATLABSystem: '<Root>/Free Space' */
    obj->cSFunObject.W1_BUFF[b_ti] = varargin_1[i];
    if (b_ti < 100) {
      b_ti++;
    } else {
      b_ti = 0;
    }
  }

  /* Start for MATLABSystem: '<Root>/Free Space' */
  obj->cSFunObject.W0_BUFF_OFFSET = b_ti;
}

real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

static real_T fmcw_range_model_mod(real_T x, real_T y)
{
  real_T r;

  /* Start for MATLABSystem: '<Root>/Free Space' */
  r = x;
  if (y == 0.0) {
    if (x == 0.0) {
      r = y;
    }
  } else if (rtIsNaN(x) || rtIsNaN(y) || rtIsInf(x)) {
    r = (rtNaN);
  } else if (x == 0.0) {
    r = 0.0 / y;
  } else if (rtIsInf(y)) {
    if ((y < 0.0) != (x < 0.0)) {
      r = y;
    }
  } else {
    boolean_T rEQ0;
    r = fmod(x, y);
    rEQ0 = (r == 0.0);
    if ((!rEQ0) && (y > floor(y))) {
      real_T q;
      q = fabs(x / y);
      rEQ0 = !(fabs(q - floor(q + 0.5)) > 2.2204460492503131E-16 * q);
    }

    if (rEQ0) {
      r = y * 0.0;
    } else if (((r < 0.0) && (!(y < 0.0))) || ((!(r < 0.0)) && (y < 0.0))) {
      r += y;
    }
  }

  /* End of Start for MATLABSystem: '<Root>/Free Space' */
  return r;
}

static void fmcw_range_m_binary_expand_op_1(creal_T in1[100], const int32_T
  in2_data[], const int32_T *in2_size, const real_T in3_data[], const int32_T
  in3_size[2], const creal_T in4[100], real_T in5)
{
  creal_T in1_data[100];
  int32_T i;
  int32_T in2_idx_0_tmp;
  int32_T stride_0_0;
  int32_T stride_1_0;

  /* Start for MATLABSystem: '<Root>/Free Space' */
  in2_idx_0_tmp = *in2_size;
  stride_0_0 = (in3_size[1] != 1);
  if (in5 < 1.0) {
    i = 0;
  } else {
    i = (int32_T)in5;
  }

  stride_1_0 = (i != 1);

  /* Start for MATLABSystem: '<Root>/Free Space' */
  for (i = 0; i < in2_idx_0_tmp; i++) {
    int32_T tmp;
    int32_T tmp_0;
    tmp = (int32_T)in3_data[i * stride_0_0] - 1;
    tmp_0 = i * stride_1_0;
    in1_data[i].re = in1[tmp].re + in4[tmp_0].re;
    in1_data[i].im = in1[tmp].im + in4[tmp_0].im;
  }

  for (i = 0; i < in2_idx_0_tmp; i++) {
    in1[in2_data[i]] = in1_data[i];
  }
}

static void fmcw_range_mod_binary_expand_op(phased_FreeSpace_fmcw_range_m_T *in1,
  const int32_T in2_data[], const int32_T *in2_size, const real_T in3_data[],
  const int32_T in3_size[2], const creal_T in4[100], real_T in5, const real_T
  in6_data[], const int32_T in6_size[2])
{
  creal_T in1_data[100];
  int32_T i;
  int32_T in2_idx_0_tmp;
  int32_T stride_0_0;
  int32_T stride_1_0;

  /* Start for MATLABSystem: '<Root>/Free Space' */
  in2_idx_0_tmp = *in2_size;
  stride_0_0 = (in3_size[1] != 1);

  /* Start for MATLABSystem: '<Root>/Free Space' */
  stride_1_0 = (in6_size[1] != 1);
  for (i = 0; i < in2_idx_0_tmp; i++) {
    int32_T tmp;
    int32_T tmp_0;
    tmp = (int32_T)(in6_data[i * stride_1_0] + in5) - 1;
    tmp_0 = (int32_T)in3_data[i * stride_0_0] - 1;
    in1_data[i].re = in4[tmp].re + in1->cBuffer.pBuffer[tmp_0].re;
    in1_data[i].im = in4[tmp].im + in1->cBuffer.pBuffer[tmp_0].im;
  }

  for (i = 0; i < in2_idx_0_tmp; i++) {
    /* Start for MATLABSystem: '<Root>/Free Space' */
    in1->cBuffer.pBuffer[in2_data[i]] = in1_data[i];
  }
}

static void fmcw_AbstractFreeSpace_stepImpl(phased_FreeSpace_fmcw_range_m_T *obj,
  const creal_T x_inc[100], const real_T startPos[3], const real_T endPos[3],
  const real_T startVel[3], const real_T endVel[3], creal_T y[100])
{
  creal_T b[100];
  creal_T temp[100];
  real_T popidx_data[100];
  real_T y_data[100];
  real_T L;
  real_T intd;
  real_T nDelay;
  real_T q;
  real_T r;
  real_T tgtdirec_idx_0;
  real_T tgtdirec_idx_1;
  real_T tgtdirec_idx_2;
  real_T x_re;
  int32_T b_data[100];
  int32_T i;
  int32_T loop_ub;
  int32_T overlap;
  boolean_T rEQ0;
  static const real_T tmp[100] = { 0.0, 5.0E-9, 1.0E-8, 1.5E-8, 2.0E-8, 2.5E-8,
    3.0E-8, 3.5E-8, 4.0E-8, 4.5E-8, 5.0E-8, 5.5E-8, 6.0E-8, 6.5E-8, 7.0E-8,
    7.5E-8, 8.0E-8, 8.5E-8, 9.0E-8, 9.5E-8, 1.0E-7, 1.05E-7, 1.1E-7, 1.15E-7,
    1.2E-7, 1.25E-7, 1.3E-7, 1.35E-7, 1.4E-7, 1.45E-7, 1.5E-7, 1.55E-7, 1.6E-7,
    1.65E-7, 1.7E-7, 1.75E-7, 1.8E-7, 1.85E-7, 1.9E-7, 1.95E-7, 2.0E-7, 2.05E-7,
    2.1E-7, 2.15E-7, 2.2E-7, 2.25E-7, 2.3E-7, 2.35E-7, 2.4E-7, 2.45E-7, 2.5E-7,
    2.55E-7, 2.6E-7, 2.65E-7, 2.7E-7, 2.75E-7, 2.8E-7, 2.85E-7, 2.9E-7, 2.95E-7,
    3.0E-7, 3.05E-7, 3.1E-7, 3.15E-7, 3.2E-7, 3.25E-7, 3.3E-7, 3.35E-7, 3.4E-7,
    3.45E-7, 3.5E-7, 3.55E-7, 3.6E-7, 3.65E-7, 3.7E-7, 3.75E-7, 3.8E-7, 3.85E-7,
    3.9E-7, 3.95E-7, 4.0E-7, 4.05E-7, 4.1E-7, 4.15E-7, 4.2E-7, 4.25E-7, 4.3E-7,
    4.35E-7, 4.4E-7, 4.45E-7, 4.5E-7, 4.55E-7, 4.6E-7, 4.65E-7, 4.7E-7, 4.75E-7,
    4.8E-7, 4.85E-7, 4.9E-7, 4.95E-7 };

  int32_T popidx_size[2];
  int32_T y_size[2];
  int32_T tmp_0;

  /* Start for MATLABSystem: '<Root>/Free Space' */
  intd = fabs(startPos[0] - endPos[0]);
  nDelay = fabs(startPos[1] - endPos[1]);
  q = fabs(startPos[2] - endPos[2]);
  nDelay = sqrt((intd * intd + nDelay * nDelay) + q * q);
  tgtdirec_idx_0 = endPos[0] - startPos[0];
  tgtdirec_idx_1 = endPos[1] - startPos[1];
  tgtdirec_idx_2 = endPos[2] - startPos[2];
  intd = 2.0 * nDelay / 3.0E+8;

  /* Start for MATLABSystem: '<Root>/Free Space' */
  L = 12.566370614359172 * nDelay * 256.66666666666669;
  if (L < 1.0) {
    L = 1.0;
  }

  /* Start for MATLABSystem: '<Root>/Free Space' */
  r = -12.566370614359172 * nDelay;
  if (r == 0.0) {
    /* Start for MATLABSystem: '<Root>/Free Space' */
    nDelay = -0.0 * nDelay / 0.0038961038961038961;
    q = 0.0;
  } else if (-0.0 * nDelay == 0.0) {
    nDelay = 0.0;
    q = r / 0.0038961038961038961;
  } else {
    nDelay = (rtNaN);
    q = r / 0.0038961038961038961;
  }

  /* Start for MATLABSystem: '<Root>/Free Space' */
  if (nDelay == 0.0) {
    x_re = cos(q);
    r = sin(q);
  } else if (q == 0.0) {
    x_re = (rtNaN);
    r = 0.0;
  } else {
    x_re = (rtNaN);
    r = (rtNaN);
  }

  q = sqrt(rt_powd_snf(10.0, 20.0 * log10(L) * 2.0 / 10.0));
  if (r == 0.0) {
    nDelay = x_re / q;
    q = 0.0;
  } else if (x_re == 0.0) {
    nDelay = 0.0;
    q = r / q;
  } else {
    nDelay = x_re / q;
    q = r / q;
  }

  x_re = -((((endVel[0] - startVel[0]) * tgtdirec_idx_0 + (endVel[1] - startVel
              [1]) * tgtdirec_idx_1) + (endVel[2] - startVel[2]) *
            tgtdirec_idx_2) / sqrt((tgtdirec_idx_0 * tgtdirec_idx_0 +
             tgtdirec_idx_1 * tgtdirec_idx_1) + tgtdirec_idx_2 * tgtdirec_idx_2));
  r = x_re * 12.566370614359172;
  if (r == 0.0) {
    /* Start for MATLABSystem: '<Root>/Free Space' */
    x_re = x_re * 0.0 / 0.0038961038961038961;
    r = 0.0;
  } else if (x_re * 0.0 == 0.0) {
    x_re = 0.0;
    r /= 0.0038961038961038961;
  } else {
    x_re = (rtNaN);
    r /= 0.0038961038961038961;
  }

  for (i = 0; i < 100; i++) {
    /* Start for MATLABSystem: '<Root>/Free Space' */
    tgtdirec_idx_0 = intd + tmp[i];
    temp[i].re = tgtdirec_idx_0 * x_re;
    temp[i].im = tgtdirec_idx_0 * r;
  }

  /* Start for MATLABSystem: '<Root>/Free Space' */
  for (i = 0; i < 100; i++) {
    x_re = temp[i].re;
    if (x_re == 0.0) {
      tgtdirec_idx_0 = temp[i].im;
      x_re = cos(tgtdirec_idx_0);
      r = sin(tgtdirec_idx_0);
    } else {
      tgtdirec_idx_0 = temp[i].im;
      if (tgtdirec_idx_0 == 0.0) {
        x_re = exp(x_re);
        r = 0.0;
      } else if (rtIsInf(tgtdirec_idx_0) && rtIsInf(x_re) && (x_re < 0.0)) {
        x_re = 0.0;
        r = 0.0;
      } else {
        r = exp(x_re / 2.0);
        x_re = r * cos(tgtdirec_idx_0) * r;
        r *= r * sin(tgtdirec_idx_0);
      }
    }

    temp[i].re = x_re;
    temp[i].im = r;
    tgtdirec_idx_1 = x_inc[i].re;
    tgtdirec_idx_2 = x_inc[i].im;
    tgtdirec_idx_0 = tgtdirec_idx_1 * x_re - tgtdirec_idx_2 * r;
    x_re = tgtdirec_idx_1 * r + tgtdirec_idx_2 * x_re;
    b[i].re = nDelay * tgtdirec_idx_0 - q * x_re;
    b[i].im = nDelay * x_re + q * tgtdirec_idx_0;
  }

  nDelay = intd * 2.0E+8;
  if (!(rt_remd_snf(intd, 5.0E-9) != 0.0)) {
    nDelay = rt_roundd_snf(nDelay);
    memcpy(&temp[0], &b[0], 100U * sizeof(creal_T));
  } else {
    intd = trunc(nDelay);
    if (obj->cFractionalDelayFilter.isInitialized != 1) {
      obj->cFractionalDelayFilter.isInitialized = 1;
      obj->cFractionalDelayFilter.isSetupComplete = true;

      /* System object Initialization function: dsp.VariableFractionalDelay */
      obj->cFractionalDelayFilter.cSFunObject.W0_BUFF_OFFSET = 100;
      for (i = 0; i < 101; i++) {
        obj->cFractionalDelayFilter.cSFunObject.W1_BUFF[i] =
          obj->cFractionalDelayFilter.cSFunObject.P0_IC;
      }
    }

    fmcw_range__SystemCore_stepImpl(&obj->cFractionalDelayFilter, b, nDelay -
      intd, temp);
    nDelay = intd;
  }

  if (obj->cBuffer.isInitialized != 1) {
    obj->cBuffer.isInitialized = 1;
    obj->cBuffer.pNumInputChannels = 1.0;
    obj->cBuffer.pBufferLength = 767.0;
    obj->cBuffer.isSetupComplete = true;
    memset(&obj->cBuffer.pBuffer[0], 0, 767U * sizeof(creal_T));
    obj->cBuffer.pStart = 1.0;
    obj->cBuffer.pCount = 0.0;
  }

  memset(&y[0], 0, 100U * sizeof(creal_T));
  if (!(obj->cBuffer.pCount == 0.0)) {
    intd = fmin(obj->cBuffer.pCount, 100.0);
    if (intd - 1.0 < 0.0) {
      y_size[1] = 0;
    } else {
      y_size[1] = (int32_T)(intd - 1.0) + 1;
      loop_ub = (int32_T)(intd - 1.0);
      for (i = 0; i <= loop_ub; i++) {
        y_data[i] = i;
      }
    }

    loop_ub = y_size[1];
    for (i = 0; i < loop_ub; i++) {
      popidx_data[i] = fmcw_range_model_mod((obj->cBuffer.pStart + y_data[i]) -
        1.0, obj->cBuffer.pBufferLength) + 1.0;
    }

    if (intd < 1.0) {
      overlap = 0;
    } else {
      overlap = (int32_T)intd;
    }

    for (i = 0; i < overlap; i++) {
      y[i] = obj->cBuffer.pBuffer[(int32_T)popidx_data[i] - 1];
    }

    for (i = 0; i < loop_ub; i++) {
      b_data[i] = (int32_T)popidx_data[i];
      overlap = b_data[i];
      obj->cBuffer.pBuffer[overlap - 1].re = 0.0;
      obj->cBuffer.pBuffer[overlap - 1].im = 0.0;
    }

    q = (popidx_data[y_size[1] - 1] + 1.0) - 1.0;
    r = q;
    if (!(obj->cBuffer.pBufferLength == 0.0)) {
      if (rtIsNaN(q) || rtIsNaN(obj->cBuffer.pBufferLength) || rtIsInf(q)) {
        r = (rtNaN);
      } else if (rtIsInf(obj->cBuffer.pBufferLength)) {
        if (obj->cBuffer.pBufferLength < 0.0) {
          r = obj->cBuffer.pBufferLength;
        }
      } else {
        r = fmod(q, obj->cBuffer.pBufferLength);
        rEQ0 = (r == 0.0);
        if ((!rEQ0) && (obj->cBuffer.pBufferLength > floor
                        (obj->cBuffer.pBufferLength))) {
          q = fabs(q / obj->cBuffer.pBufferLength);
          rEQ0 = !(fabs(q - floor(q + 0.5)) > 2.2204460492503131E-16 * q);
        }

        if (rEQ0) {
          r = obj->cBuffer.pBufferLength * 0.0;
        } else if (obj->cBuffer.pBufferLength < 0.0) {
          r += obj->cBuffer.pBufferLength;
        }
      }
    }

    obj->cBuffer.pStart = r + 1.0;
    obj->cBuffer.pCount -= intd;
  }

  if (nDelay <= 667.0) {
    overlap = (int32_T)(100.0 - nDelay);
    if (overlap < 1) {
      popidx_size[1] = 0;
    } else {
      popidx_size[1] = overlap;
      loop_ub = overlap - 1;
      for (i = 0; i <= loop_ub; i++) {
        popidx_data[i] = (real_T)i + 1.0;
      }
    }

    popidx_size[0] = 1;
    loop_ub = popidx_size[1] - 1;
    for (i = 0; i <= loop_ub; i++) {
      popidx_data[i] += nDelay;
    }

    loop_ub = popidx_size[1];
    for (i = 0; i < loop_ub; i++) {
      b_data[i] = (int32_T)popidx_data[i] - 1;
    }

    if (overlap < 1) {
      i = 0;
    } else {
      i = overlap;
    }

    if (popidx_size[1] == i) {
      for (i = 0; i < loop_ub; i++) {
        intd = popidx_data[i];
        b[i].re = y[(int32_T)intd - 1].re + temp[i].re;
        b[i].im = y[(int32_T)intd - 1].im + temp[i].im;
      }

      for (i = 0; i < loop_ub; i++) {
        y[b_data[i]] = b[i];
      }
    } else {
      fmcw_range_m_binary_expand_op_1(y, b_data, &popidx_size[1], popidx_data,
        popidx_size, temp, (real_T)overlap);
    }

    if (nDelay > 0.0) {
      if (overlap >= 0) {
        if (100 - overlap < 1) {
          popidx_size[1] = 0;
          y_size[0] = 1;
          y_size[1] = 0;
        } else {
          popidx_size[1] = 100 - overlap;
          loop_ub = 99 - overlap;
          y_size[0] = 1;
          y_size[1] = 100 - overlap;
          for (i = 0; i <= loop_ub; i++) {
            popidx_data[i] = (real_T)i + 1.0;
            y_data[i] = (real_T)i + 1.0;
          }
        }

        popidx_size[0] = 1;
        loop_ub = popidx_size[1] - 1;
        for (i = 0; i <= loop_ub; i++) {
          popidx_data[i] = fmcw_range_model_mod(((obj->cBuffer.pStart +
            popidx_data[i]) - 1.0) - 1.0, obj->cBuffer.pBufferLength) + 1.0;
        }

        loop_ub = popidx_size[1];
        for (i = 0; i < loop_ub; i++) {
          b_data[i] = (int32_T)popidx_data[i] - 1;
        }

        if (popidx_size[1] == y_size[1]) {
          for (i = 0; i < loop_ub; i++) {
            intd = popidx_data[i];
            tmp_0 = (overlap + (int32_T)y_data[i]) - 1;
            b[i].re = obj->cBuffer.pBuffer[(int32_T)intd - 1].re + temp[tmp_0].
              re;
            b[i].im = obj->cBuffer.pBuffer[(int32_T)intd - 1].im + temp[tmp_0].
              im;
          }

          for (i = 0; i < loop_ub; i++) {
            obj->cBuffer.pBuffer[b_data[i]] = b[i];
          }
        } else {
          fmcw_range_mod_binary_expand_op(obj, b_data, &popidx_size[1],
            popidx_data, popidx_size, temp, (real_T)overlap, y_data, y_size);
        }
      } else {
        for (i = 0; i < 100; i++) {
          tmp_0 = (int32_T)(fmcw_range_model_mod(((((real_T)(i - overlap) + 1.0)
            + obj->cBuffer.pStart) - 1.0) - 1.0, obj->cBuffer.pBufferLength) +
                            1.0);
          b_data[i] = (int32_T)(fmcw_range_model_mod(((((real_T)(i - overlap) +
            1.0) + obj->cBuffer.pStart) - 1.0) - 1.0, obj->cBuffer.pBufferLength)
                                + 1.0);
          b[i].re = obj->cBuffer.pBuffer[tmp_0 - 1].re + temp[i].re;
          b[i].im = obj->cBuffer.pBuffer[tmp_0 - 1].im + temp[i].im;
        }

        for (i = 0; i < 100; i++) {
          obj->cBuffer.pBuffer[b_data[i] - 1] = b[i];
        }
      }

      if (nDelay > obj->cBuffer.pCount) {
        obj->cBuffer.pCount = nDelay;
      }
    }
  }
}

static void fmcw_range_mod_SystemCore_setup(phased_FMCWWaveform_fmcw_rang_T *obj)
{
  int32_T b_k;
  static const real_T tmp[2000] = { 0.0, 0.0011780972450961724,
    0.00471238898038469, 0.010602875205865548, 0.018849555921538759,
    0.029452431127404304, 0.042411500823462192, 0.057726765009712452,
    0.075398223686155036, 0.095425876852789956, 0.11780972450961721,
    0.14254976665663688, 0.16964600329384877, 0.19909843442125311,
    0.23090706003884981, 0.26507188014663874, 0.30159289474462014,
    0.34047010383279375, 0.38170350741115983, 0.42529310547971827,
    0.47123889803846886, 0.519540885087412, 0.57019906662654751,
    0.62321344265587508, 0.67858401317539507, 0.73631077818510771,
    0.79639373768501243, 0.85883289167510968, 0.92362824015539924,
    0.99077978312588078, 1.060287520586555, 1.1321514525374217,
    1.2063715789784806, 1.2829478999097317, 1.361880415331175,
    1.4431691252428107, 1.5268140296446393, 1.6128151285366599,
    1.7011724219188731, 1.7918859097912783, 1.8849555921538754,
    1.9803814690066655, 2.0781635403496481, 2.1783018061828225, 2.28079626650619,
    2.3856469213197484, 2.4928537706235003, 2.6024168144174444,
    2.7143360527015803, 2.8286114854759092, 2.9452431127404308,
    3.0642309344951437, 3.1855749507400497, 3.3092751614751479,
    3.4353315667004387, 3.5637441664159213, 3.694512960621597,
    3.8276379493174644, 3.9631191325035231, 4.1009565101797749, 4.24115008234622,
    4.3836998490028574, 4.5286058101496867, 4.6758679657867077,
    4.8254863159139223, 4.9774608605313277, 5.1317915996389267,
    5.2884785332367175, 5.4475216613247, 5.608920983902876, 5.7726765009712429,
    5.9387882125298033, 6.1072561185785572, 6.278080219117502,
    6.4512605141466395, 6.62679700366597, 6.8046896876754923, 6.9849385661752059,
    7.1675436391651131, 7.35250490664521, 7.5398223686155017, 7.7294960250759859,
    7.9215258760266618, 8.11591192146753, 8.3126541613985925, 8.5117525958198446,
    8.71320722473129, 8.9170180481329275, 9.12318506602476, 9.33170827840678,
    9.5425876852789937, 9.7558232866414016, 9.9714150824940013,
    10.189363072836795, 10.409667257669778, 10.632327636992954,
    10.857344210806321, 11.084716979109885, 11.314445941903637,
    11.546531099187584, 11.780972450961723, 12.017769997226054,
    12.256923737980575, 12.498433673225295, 12.742299802960199,
    12.988522127185297, 13.237100645900592, 13.488035359106075,
    13.741326266801755, 13.996973368987621, 14.254976665663685,
    14.515336156829939, 14.778051842486388, 15.043123722633023,
    15.310551797269857, 15.580336066396878, 15.852476530014092, 16.1269731881215,
    16.4038260407191, 16.683035087806896, 16.964600329384879, 17.248521765453059,
    17.534799396011429, 17.823433221059993, 18.114423240598747,
    18.407769454627694, 18.703471863146831, 19.001530466156158,
    19.301945263655689, 19.6047162556454, 19.909843442125311, 20.217326823095412,
    20.527166398555707, 20.839362168506188, 21.15391413294687,
    21.470822291877738, 21.7900866452988, 22.111707193210059, 22.435683935611504,
    22.762016872503146, 23.090706003884971, 23.421751329757, 23.755152850119213,
    24.09091056497163, 24.429024474314229, 24.769494578147025,
    25.112320876470008, 25.457503369283184, 25.805042056586558,
    26.154936938380118, 26.507188014663878, 26.861795285437822,
    27.218758750701969, 27.578078410456296, 27.939754264700824,
    28.303786313435538, 28.670174556660452, 29.038918994375553,
    29.410019626580841, 29.783476453276332, 30.159289474462007,
    30.537458690137885, 30.917984100303944, 31.300865704960202,
    31.686103504106647, 32.073697497743289, 32.463647685870122,
    32.855954068487151, 33.25061664559437, 33.647635417191772,
    34.047010383279378, 34.448741543857167, 34.852828898925161,
    35.259272448483337, 35.66807219253171, 36.079228131070273,
    36.492740264099041, 36.908608591617984, 37.326833113627117,
    37.747413830126455, 38.170350741115975, 38.5956438465957, 39.023293146565607,
    39.453298641025718, 39.885660329976005, 40.320378213416504,
    40.757452291347178, 41.19688256376805, 41.638669030679111,
    42.082811692080369, 42.529310547971818, 42.978165598353456,
    43.429376843225285, 43.882944282587331, 44.33886791643954,
    44.797147744781945, 45.257783767614548, 45.720775984937355,
    46.186124396750337, 46.653829003053517, 47.123889803846893,
    47.596306799130446, 48.071079988904216, 48.54820937316817, 49.0276949519223,
    49.509536725166633, 49.993734692901178, 50.480288855125885,
    50.969199211840795, 51.460465763045896, 51.954088508741187,
    52.450067448926688, 52.948402583602366, 53.449093912768234, 53.9521414364243,
    54.457545154570568, 54.965305067207019, 55.475421174333654,
    55.987893475950486, 56.502721972057522, 57.019906662654741,
    57.539447547742149, 58.061344627319755, 58.585597901387544,
    59.112207369945551, 59.641173032993727, 60.172494890532093,
    60.706172942560649, 61.24220718907943, 61.780597630088373,
    62.321344265587513, 62.864447095576843, 63.40990612005637,
    63.957721339026108, 64.507892752486, 65.060420360436112, 65.6153041628764,
    66.172544159806918, 66.732140351227585, 67.294092737138456,
    67.858401317539517, 68.425066092430768, 68.994087061812237,
    69.565464225683883, 70.139197584045718, 70.715287136897729,
    71.293732884239972, 71.874534826072377, 72.457692962394987,
    73.043207293207772, 73.631077818510775, 74.221304538303954,
    74.813887452587323, 75.408826561360883, 76.006121864624632,
    76.605773362378613, 77.207781054622757, 77.812144941357076, 78.4188650225816,
    79.027941298296341, 79.639373768501244, 80.253162433196351,
    80.869307292381649, 81.487808346057136, 82.108665594222828, 82.7318790368787,
    83.357448674024752, 83.985374505661014, 84.615656531787479,
    85.248294752404135, 85.883289167510952, 86.520639777107974, 87.1603465811952,
    87.802409579772629, 88.446828772840234, 89.09360416039803,
    89.742735742446015, 90.394223518984219, 91.048067490012585,
    91.70426765553114, 92.362824015539886, 93.023736570038864, 93.687005319028,
    94.352630262507333, 95.020611400476852, 95.690948732936576,
    96.363642259886518, 97.038691981326622, 97.716097897256915, 98.3958600076774,
    99.0779783125881, 99.762452811988979, 100.44928350588003, 101.13847039426128,
    101.83001347713274, 102.52391275449439, 103.22016822634623,
    103.91877989268825, 104.61974775352047, 105.32307180884291,
    106.02875205865551, 106.73678850295831, 107.44718114175129,
    108.15992997503446, 108.87503500280788, 109.59249622507143,
    110.31231364182518, 111.03448725306913, 111.75901705880329,
    112.48590305902763, 113.21514525374215, 113.94674364294687,
    114.68069822664181, 115.41700900482689, 116.15567597750221,
    116.89669914466769, 117.64007850632336, 118.38581406246925,
    119.13390581310533, 119.88435375823158, 120.63715789784803,
    121.3923182319547, 122.14983476055154, 122.90970748363856,
    123.67193640121577, 124.43652151328318, 125.20346281984081,
    125.97276032088861, 126.74441401642659, 127.51842390645477,
    128.29478999097316, 129.07351226998173, 129.85459074348049,
    130.63802541146944, 131.4238162739486, 132.21196333091794,
    133.00246658237748, 133.79532602832717, 134.59054166876709,
    135.38811350369721, 136.18804153311751, 136.99032575702802,
    137.79496617542867, 138.60196278831958, 139.41131559570064,
    140.22302459757191, 141.03708979393335, 141.853511184785, 142.67228877012684,
    143.49342254995886, 144.31691252428109, 145.1427586930935,
    145.97096105639616, 146.80151961418895, 147.63443436647194,
    148.4697053132451, 149.30733245450847, 150.14731579026207,
    150.98965532050582, 151.83435104523977, 152.6814029644639,
    153.53081107817829, 154.3825753863828, 155.23669588907754,
    156.09317258626243, 156.95200547793758, 157.81319456410287,
    158.67673984475834, 159.54264131990402, 160.4108989895399,
    161.28151285366602, 162.15448291228225, 163.02980916538871,
    163.90749161298535, 164.7875302550722, 165.66992509164922,
    166.55467612271644, 167.44178334827384, 168.33124676832148,
    169.22306638285929, 170.11724219188727, 171.01377419540546,
    171.91266239341383, 172.81390678591239, 173.71750737290114,
    174.62346415438017, 175.53177713034933, 176.44244630080863,
    177.35547166575816, 178.2708532251979, 179.18859097912778, 180.1086849275479,
    181.03113507045819, 181.95594140785869, 182.88310393974942,
    183.8126226661303, 184.74449758700135, 185.67872870236263,
    186.61531601221407, 187.5542595165557, 188.49555921538757,
    189.43921510870956, 190.38522719652178, 191.33359547882426,
    192.28431995561687, 193.23740062689967, 194.19283749267268,
    195.15063055293584, 196.1107798076892, 197.07328525693276,
    198.03814690066653, 199.00536473889048, 199.97493877160471, 200.946868998809,
    201.92115542050354, 202.8977980366883, 203.87679684736318,
    204.85815185252829, 205.84186305218358, 206.82793044632905,
    207.81635403496475, 208.8071338180907, 209.80026979570675,
    210.79576196781304, 211.79361033440946, 212.7938148954961,
    213.79637565107294, 214.80129260113998, 215.80856574569719,
    216.81819508474462, 217.83018061828227, 218.8445223463101,
    219.86122026882808, 220.88027438583626, 221.90168469733462,
    222.92545120332321, 223.95157390380194, 224.98005279877088,
    226.01088788823009, 227.04407917217944, 228.07962665061896,
    229.11753032354866, 230.1577901909686, 231.20040625287871,
    232.24537850927902, 233.29270696016948, 234.34239160555018,
    235.39443244542113, 236.4488294797822, 237.50558270863343,
    238.56469213197491, 239.62615774980654, 240.68997956212837,
    241.75615756894041, 242.82469177024259, 243.895582166035, 244.96882875631772,
    246.04443154109049, 247.12239052035349, 248.20270569410667,
    249.28537706235005, 250.37040462508361, 251.45778838230737,
    252.54752833402131, 253.63962448022548, 254.73407682091991,
    255.83088535610443, 256.93005008577916, 258.031571009944, 259.13544812859914,
    260.24168144174445, 261.35027094937993, 262.46121665150559,
    263.57451854812149, 264.69017663922767, 265.80819092482392,
    266.92856140491034, 268.051288079487, 269.17637094855382, 270.30381001211083,
    271.43360527015807, 272.56575672269548, 273.70026436972307,
    274.83712821124095, 275.97634824724895, 277.11792447774712,
    278.26185690273553, 279.40814552221411, 280.55679033618287,
    281.70779134464181, 282.86114854759091, 284.01686194503026,
    285.17493153695989, 286.33535732337958, 287.49813930428951,
    288.66327747968961, 289.83077184957995, 291.0006224139604,
    292.17282917283109, 293.34739212619195, 294.5243112740431,
    295.70358661638437, 296.88521815321582, 298.0692058845375,
    299.25554981034929, 300.44424993065132, 301.63530624544353,
    302.82871875472597, 304.02448745849853, 305.22261235676143,
    306.42309344951445, 307.6259307367576, 308.831124218491, 310.03867389471458,
    311.2485797654283, 312.46084183063226, 313.6754600903264, 314.89243454451076,
    316.11176519318536, 317.33345203635008, 318.557495074005, 319.7838943061501,
    321.01264973278541, 322.24376135391088, 323.47722916952659,
    324.71305317963248, 325.95123338422854, 327.1917697833149,
    328.43466237689131, 329.67991116495796, 330.92751614751478,
    332.17747732456183, 333.429794696099, 334.68446826212647, 335.94149802264405,
    337.20088397765187, 338.46262612714992, 339.72672447113814,
    340.99317900961654, 342.26198974258506, 343.53315667004381,
    344.80667979199279, 346.08255910843189, 347.36079461936123,
    348.6413863247808, 349.92433422469065, 351.20963831909052,
    352.49729860798061, 353.78731509136094, 355.07968776923138,
    356.37441664159212, 357.671501708443, 358.97094296978406, 360.27274042561538,
    361.57689407593688, 362.88340392074849, 364.19226996005034,
    365.50349219384231, 366.81707062212456, 368.133005244897, 369.45129606215954,
    370.77194307391233, 372.09494628015545, 373.4203056808887, 374.748021276112,
    376.07809306582561, 377.41052105002933, 378.74530522872328,
    380.08244560190741, 381.42194216958183, 382.7637949317463,
    384.10800388840113, 385.45456903954607, 386.80349038518119,
    388.15476792530649, 389.50840165992196, 390.86439158902766,
    392.22273771262348, 393.5834400307096, 394.94649854328583, 396.3119132503524,
    397.67968415190904, 399.04981124795592, 400.42229453849291,
    401.79713402352013, 403.17432970303759, 404.5538815770451,
    405.93578964554297, 407.32005390853095, 408.70667436600922,
    410.09565101797756, 411.48698386443618, 412.88067290538493,
    414.2767181408239, 415.675119570753, 417.07587719517238, 418.47899101408188,
    419.88446102748162, 421.29228723537165, 422.70246963775173,
    424.11500823462205, 425.52990302598249, 426.94715401183322,
    428.36676119217412, 429.78872456700515, 431.2130441363264,
    432.63971990013783, 434.06875185843961, 435.50014001123151,
    436.93388435851347, 438.36998490028571, 439.80844163654814,
    441.24925456730074, 442.69242369254351, 444.13794901227652,
    445.58583052649982, 447.03606823521318, 448.48866213841677,
    449.94361223611054, 451.40091852829448, 452.8605810149686, 454.3225996961329,
    455.78697457178748, 457.25370564193219, 458.72279290656724,
    460.19423636569229, 461.66803601930758, 463.1441918674131,
    464.62270391000885, 466.10357214709467, 467.58679657867077, 469.072377204737,
    470.56031402529345, 472.0506070403402, 473.543256249877, 475.0382616539041,
    476.53562325242132, 478.03534104542871, 479.53741503292633,
    481.04184521491413, 482.54863159139211, 484.05777416236026,
    485.56927292781882, 487.08312788776732, 488.59933904220617,
    490.11790639113508, 491.63882993455422, 493.1621096724636, 494.6877456048631,
    496.21573773175282, 497.74608605313273, 499.278790569003, 500.81385127936323,
    502.35126818421378, 503.89104128355444, 505.43317057738528,
    506.97765606570636, 508.5244977485176, 510.07369562581908,
    511.62524969761074, 513.17915996389263, 514.73542642466475,
    516.29404907992694, 517.85502792967941, 519.418362973922, 520.98405421265477,
    522.55210164587777, 524.122505273591, 525.69526509579441, 527.270381112488,
    528.84785332367176, 530.42768172934575, 532.00986632950992,
    533.59440712416415, 535.18130411330867, 536.77055729694348,
    538.36216667506835, 539.95613224768363, 541.55245401478885,
    543.15113197638436, 544.75216613247, 546.355556483046, 547.96130302811207,
    549.56940576766829, 551.17986470171468, 552.79267983025136,
    554.40785115327833, 556.02537867079536, 557.64526238280257,
    559.26750228930007, 560.89209839028763, 562.51905068576536,
    564.14835917573339, 565.78002386019159, 567.41404473914, 569.05042181257863,
    570.68915508050736, 572.33024454292638, 573.97369019983546,
    575.61949205123483, 577.26765009712437, 578.91816433750409, 580.571034772374,
    582.22626140173406, 583.88384422558465, 585.54378324392508,
    587.20607845675579, 588.87072986407668, 590.53773746588774, 592.207101262189,
    593.8788212529804, 595.552897438262, 597.22932981803388, 598.908118392296,
    600.58926316104828, 602.27276412429069, 603.95862128202327, 605.646834634246,
    607.33740418095908, 609.03032992216231, 610.7256118578556,
    612.42324998803917, 614.12324431271315, 615.82559483187708,
    617.53030154553119, 619.23736445367558, 620.94678355631015,
    622.65855885343478, 624.3726903450497, 626.0891780311548, 627.8080219117503,
    629.52922198683575, 631.25277825641149, 632.97869072047729,
    634.70695937903338, 636.43758423207964, 638.17056527961608,
    639.9059025216427, 641.64359595815961, 643.38364558916669,
    645.12605141466406, 646.87081343465138, 648.617931649129, 650.36740605809678,
    652.11923666155485, 653.873423459503, 655.62996645194141, 657.3888656388699,
    659.15012102028879, 660.91373259619775, 662.67970036659688,
    664.44802433148629, 666.21870449086578, 667.99174084473555,
    669.76713339309538, 671.5448821359455, 673.32498707328591, 675.1074482051165,
    676.89226553143715, 678.67943905224809, 680.46896876754909,
    682.26085467734038, 684.05509678162184, 685.85169508039348,
    687.6506495736553, 689.45196026140729, 691.25562714364958,
    693.06165022038192, 694.87002949160456, 696.68076495731736,
    698.49385661752069, 700.30930447221385, 702.1271085213973,
    703.94726876507082, 705.76978520323451, 707.59465783588848,
    709.42188666303264, 711.251471684667, 713.08341290079159, 714.91771031140638,
    716.75436391651112, 718.59337371610627, 720.43473971019159,
    722.27846189876709, 724.12454028183276, 725.97297485938861,
    727.82376563143475, 729.676912597971, 731.53241575899767, 733.39027511451445,
    735.25049066452118, 737.11306240901831, 738.97799034800539,
    740.84527448148287, 742.71491480945053, 744.58691133190837,
    746.46126404885626, 748.33797296029445, 750.21703806622281,
    752.09845936664146, 753.98223686155029, 755.86837055094918,
    757.75686043483825, 759.64770651321771, 761.54090878608713,
    763.43646725344684, 765.33438191529706, 767.23465277163723,
    769.13727982246746, 771.042263067788, 772.94960250759868, 774.85929814189956,
    776.77134997069072, 778.685757993972, 780.60252221174335, 782.521642624005,
    784.44311923075679, 786.366952031999, 788.293141027731, 790.22168621795345,
    792.15258760266613, 794.08584518186888, 796.02145895556191,
    797.95942892374546, 799.89975508641885, 801.8424374435823, 803.787475995236,
    805.73487074138006, 807.68462168201415, 809.63672881713853,
    811.5911921467532, 813.54801167085782, 815.50718738945272,
    817.46871930253792, 819.43260741011318, 821.39885171217861,
    823.36745220873433, 825.33840889978023, 827.31172178531619,
    829.28739086534256, 831.265416139859, 833.24579760886593, 835.22853527236282,
    837.21362913034989, 839.201079182827, 841.19088542979443, 843.18304787125214,
    845.17756650719991, 847.17444133763786, 849.17367236256609,
    851.17525958198439, 853.17920299589309, 855.18550260429174,
    857.19415840718068, 859.20517040455991, 861.21853859642931,
    863.23426298278878, 865.25234356363853, 867.27278033897846,
    869.2955733088088, 871.32072247312908, 873.34822783193954, 875.3780893852404,
    877.41030713303121, 879.44488107531231, 881.48181121208347, 883.521097543345,
    885.56274006909655, 887.60673878933846, 889.65309370407056,
    891.70180481329282, 893.75287211700515, 895.80629561520777,
    897.86207530790057, 899.92021119508354, 901.9807032767568,
    904.04355155292035, 906.10875602357407, 908.17631668871775,
    910.24623354835182, 912.31850660247585, 914.39313585109028,
    916.47012129419466, 918.54946293178944, 920.63116076387439,
    922.71521479044952, 924.80162501151483, 926.89039142707031,
    928.98151403711609, 931.07499284165192, 933.17082784067793,
    935.26901903419412, 937.36956642220071, 939.47247000469736,
    941.57772978168452, 943.68534575316153, 945.79531791912882,
    947.90764627958629, 950.0223308345337, 952.13937158397152,
    954.25876852789963, 956.3805216663178, 958.50463099922615,
    960.63109652662467, 962.75991824851349, 964.89109616489236,
    967.02463027576164, 969.160520581121, 971.29876708097038, 973.43936977531018,
    975.58232866414, 977.72764374746021, 979.87531502527088, 982.02534249757139,
    984.177726164362, 986.33246602564293, 988.489562081414, 990.64901433167518,
    992.81082277642668, 994.97498741566835, 997.1415082494002,
    999.31038527762223, 1001.4816185003344, 1003.6552079175369,
    1005.8311535292295, 1008.0094553354123, 1010.1901133360852,
    1012.3731275312484, 1014.5584979209019, 1016.7462245050458,
    1018.9363072836796, 1021.1287462568035, 1023.3235414244177,
    1025.520692786522, 1027.7202003431166, 1029.9220640942012, 1032.126284039776,
    1034.3328601798414, 1036.5417925143965, 1038.7530810434421,
    1040.9667257669778, 1043.1827266850037, 1045.4010837975197,
    1047.621797104526, 1049.8448666060224, 1052.0702923020092, 1054.298074192486,
    1056.5282122774533, 1058.7607065569107, 1060.995557030858,
    1063.2327636992957, 1065.4723265622233, 1067.7142456196414,
    1069.9585208715496, 1072.205152317948, 1074.4541399588365,
    1076.7054837942153, 1078.9591838240842, 1081.2152400484433,
    1083.4736524672928, 1085.7344210806323, 1087.9975458884621,
    1090.2630268907819, 1092.5308640875921, 1094.8010574788923,
    1097.0736070646833, 1099.3485128449638, 1101.6257748197347,
    1103.9053929889958, 1106.1873673527471, 1108.4716979109885, 1110.75838466372,
    1113.0474276109421, 1115.3388267526541, 1117.6325820888565,
    1119.9286936195488, 1122.2271613447315, 1124.5279852644042,
    1126.8311653785672, 1129.1367016872202, 1131.4445941903637,
    1133.7548428879973, 1136.067447780121, 1138.3824088667354,
    1140.6997261478396, 1143.0193996234339, 1145.3414292935183,
    1147.6658151580932, 1149.992557217158, 1152.3216554707133,
    1154.6531099187584, 1156.986920561294, 1159.3230873983198,
    1161.6616104298355, 1164.0024896558416, 1166.3457250763379,
    1168.6913166913243, 1171.039264500801, 1173.3895685047678,
    1175.7422287032248, 1178.0972450961724, 1180.45461768361, 1182.8143464655375,
    1185.1764314419552, 1187.5408726128633, 1189.9076699782615, 1192.27682353815,
    1194.6483332925284, 1197.0221992413972, 1199.3984213847561,
    1201.7769997226053, 1204.1579342549446, 1206.5412249817741,
    1208.926871903094, 1211.3148750189039, 1213.7052343292039,
    1216.0979498339941, 1218.4930215332747, 1220.8904494270457,
    1223.2902335153067, 1225.6923737980578, 1228.0968702752989,
    1230.5037229470304, 1232.912931813252, 1235.3244968739641,
    1237.7384181291661, 1240.1546955788583, 1242.5733292230407,
    1244.9943190617132, 1247.4176650948759, 1249.843367322529,
    1252.2714257446723, 1254.7018403613056, 1257.1346111724292,
    1259.5697381780431, 1262.0072213781471, 1264.4470607727415,
    1266.8892563618258, 1269.3338081454003, 1271.780716123465, 1274.22998029602,
    1276.6816006630652, 1279.1355772246004, 1281.5919099806258,
    1284.0505989311416, 1286.5116440761476, 1288.9750454156435,
    1291.4408029496299, 1293.9089166781064, 1296.3793866010731, 1298.85221271853,
    1301.327395030477, 1303.8049335369142, 1306.2848282378418,
    1308.7670791332596, 1311.2516862231673, 1313.7386495075652,
    1316.2279689864536, 1318.7196446598318, 1321.2136765277005,
    1323.7100645900591, 1326.2088088469081, 1328.7099092982473,
    1331.2133659440765, 1333.719178784396, 1336.2273478192058,
    1338.7378730485059, 1341.250754472296, 1343.7659920905762,
    1346.2835859033469, 1348.8035359106075, 1351.3258421123587,
    1353.8505045085997, 1356.377523099331, 1358.9068978845526,
    1361.4386288642643, 1363.9727160384662, 1366.509159407158,
    1369.0479589703402, 1371.5891147280129, 1374.1326266801752,
    1376.678494826828, 1379.2267191679712, 1381.7772997036045,
    1384.3302364337276, 1386.885529358341, 1389.4431784774449, 1392.003183791039,
    1394.5655452991232, 1397.130263001698, 1399.6973368987626,
    1402.2667669903171, 1404.8385532763621, 1407.4126957568972,
    1409.9891944319224, 1412.5680493014381, 1415.1492603654438,
    1417.7328276239396, 1420.3187510769255, 1422.9070307244019,
    1425.4976665663685, 1428.0906586028252, 1430.6860068337719,
    1433.283711259209, 1435.8837718791362, 1438.4861886935537,
    1441.0909617024615, 1443.6980909058593, 1446.3075763037475,
    1448.9194178961257, 1451.533615682994, 1454.1501696643525,
    1456.7690798402014, 1459.3903462105404, 1462.0139687753692,
    1464.6399475346889, 1467.2682824884982, 1469.8989736367978,
    1472.532020979588, 1475.1674245168679, 1477.8051842486382,
    1480.4453001748989, 1483.0877722956493, 1485.7326006108904,
    1488.3797851206218, 1491.0293258248432, 1493.6812227235548,
    1496.3354758167561, 1498.9920851044481, 1501.6510505866302,
    1504.3123722633024, 1506.9760501344649, 1509.6420842001173,
    1512.3104744602604, 1514.9812209148931, 1517.6543235640165,
    1520.3297824076296, 1523.0075974457334, 1525.6877686783273,
    1528.3702961054112, 1531.0551797269852, 1533.7424195430497,
    1536.4320155536045, 1539.1239677586493, 1541.8182761581843,
    1544.5149407522094, 1547.2139615407248, 1549.9153385237303,
    1552.6190717012259, 1555.3251610732118, 1558.0336066396878,
    1560.744408400654, 1563.4575663561106, 1566.1730805060572,
    1568.8909508504939, 1571.6111773894211, 1574.3337601228384,
    1577.0586990507456, 1579.7859941731433, 1582.5156454900318,
    1585.2476530014096, 1587.9820167072776, 1590.7187366076362,
    1593.4578127024847, 1596.1992449918237, 1598.9430334756526,
    1601.6891781539716, 1604.4376790267811, 1607.1885360940805,
    1609.9417493558701, 1612.6973188121503, 1615.4552444629203,
    1618.2155263081804, 1620.9781643479309, 1623.7431585821719,
    1626.5105090109025, 1629.2802156341238, 1632.0522784518355,
    1634.8266974640369, 1637.6034726707287, 1640.3826040719102,
    1643.1640916675826, 1645.9479354577447, 1648.734135442397,
    1651.5226916215397, 1654.3136039951726, 1657.1068725632956,
    1659.9024973259086, 1662.700478283012, 1665.5008154346058,
    1668.3035087806895, 1671.1085583212634, 1673.9159640563275,
    1676.725725985882, 1679.5378441099265, 1682.3523184284616,
    1685.1691489414866, 1687.9883356490018, 1690.8098785510069,
    1693.6337776475025, 1696.4600329384882, 1699.2886444239641, 1702.11961210393,
    1704.9529359783862, 1707.7886160473329, 1710.6266523107695,
    1713.4670447686965, 1716.3097934211135, 1719.1548982680206,
    1722.0023593094181, 1724.8521765453056, 1727.7043499756833,
    1730.5588796005513, 1733.41576541991, 1736.2750074337584, 1739.1366056420973,
    1742.000560044926, 1744.8668706422447, 1747.7355374340539,
    1750.6065604203534, 1753.4799396011429, 1756.3556749764225,
    1759.2337665461926, 1762.1142143104526, 1764.997018269203,
    1767.8821784224433, 1770.7696947701741, 1773.659567312395,
    1776.5517960491061, 1779.4463809803074, 1782.3433221059993,
    1785.2426194261809, 1788.1442729408527, 1791.0482826500147,
    1793.9546485536671, 1796.8633706518094, 1799.7744489444422,
    1802.6878834315648, 1805.6036741131779, 1808.521820989281,
    1811.4423240598744, 1814.3651833249578, 1817.2903987845316,
    1820.2179704385958, 1823.14789828715, 1826.0801823301942, 1829.0148225677287,
    1831.9518189997536, 1834.8911716262689, 1837.832880447274,
    1840.7769454627692, 1843.7233666727548, 1846.6721440772303,
    1849.6232776761963, 1852.5767674696524, 1855.5326134575987,
    1858.4908156400354, 1861.4513740169621, 1864.4142885883787,
    1867.3795593542857, 1870.3471863146831, 1873.3171694695704,
    1876.289508818948, 1879.2642043628157, 1882.2412561011738,
    1885.2206640340221, 1888.2024281613608, 1891.1865484831897,
    1894.173024999508, 1897.1618577103172, 1900.1530466156164,
    1903.1465917154057, 1906.1424930096853, 1909.140750498455,
    1912.1413641817148, 1915.1443340594651, 1918.1496601317053,
    1921.1573423984357, 1924.1673808596565, 1927.1797755153673,
    1930.1945263655684, 1933.2116334102598, 1936.231096649441,
    1939.2529160831134, 1942.2770917112753, 1945.3036235339273,
    1948.3325115510693, 1951.3637557627019, 1954.3973561688247,
    1957.4333127694374, 1960.4716255645403, 1963.5122945541334,
    1966.5553197382169, 1969.6007011167906, 1972.6484386898544,
    1975.6985324574082, 1978.7509824194524, 1981.8057885759868,
    1984.8629509270113, 1987.922469472526, 1990.9843442125309,
    1994.0485751470267, 1997.1151622760119, 2000.1841055994873,
    2003.2554051174529, 2006.3290608299089, 2009.4050727368551,
    2012.483440838291, 2015.5641651342178, 2018.6472456246343,
    2021.7326823095411, 2024.8204751889382, 2027.9106242628254,
    2031.0031295312028, 2034.0979909940704, 2037.1952086514282,
    2040.2947825032763, 2043.3967125496147, 2046.500998790443,
    2049.6076412257621, 2052.7166398555705, 2055.82799467987, 2058.941705698659,
    2062.0577729119382, 2065.1761963197077, 2068.2969759219677,
    2071.4201117187176, 2074.5456037099575, 2077.6734518956878,
    2080.8036562759085, 2083.9362168506191, 2087.0711336198196,
    2090.2084065835111, 2093.3480357416925, 2096.4900210943638,
    2099.6343626415255, 2102.7810603831776, 2105.9301143193197,
    2109.0815244499522, 2112.2352907750742, 2115.391413294687, 2118.54989200879,
    2121.710726917383, 2124.8739180204661, 2128.0394653180397,
    2131.2073688101032, 2134.3776284966566, 2137.5502443777009,
    2140.7252164532347, 2143.9025447232593, 2147.0822291877739,
    2150.2642698467785, 2153.4486667002734, 2156.6354197482588,
    2159.8245289907345, 2163.0159944276998, 2166.2098160591554,
    2169.4059938851015, 2172.6045279055375, 2175.8054181204639, 2179.00866452988,
    2182.214267133787, 2185.4222259321841, 2188.6325409250708,
    2191.8452121124483, 2195.0602394943157, 2198.2776230706731,
    2201.497362841521, 2204.7194588068587, 2207.9439109666869,
    2211.1707193210054, 2214.3998838698139, 2217.6314046131133,
    2220.8652815509022, 2224.1015146831814, 2227.3401040099507,
    2230.5810495312103, 2233.82435124696, 2237.0700091572003, 2240.31802326193,
    2243.5683935611505, 2246.8211200548608, 2250.0762027430615,
    2253.3336416257525, 2256.5934367029336, 2259.855587974605,
    2263.1200954407664, 2266.3869591014181, 2269.65617895656, 2272.9277550061925,
    2276.2016872503145, 2279.477975688927, 2282.7566203220294,
    2286.0376211496227, 2289.3209781717055, 2292.6066913882787,
    2295.8947607993418, 2299.1851864048958, 2302.4779682049393,
    2305.7731061994737, 2309.0706003884975, 2312.3704507720122,
    2315.6726573500164, 2318.9772201225114, 2322.284139089496,
    2325.5934142509714, 2328.9050456069363, 2332.2190331573925,
    2335.5353769023386, 2338.8540768417743, 2342.1751329757003,
    2345.4985453041163, 2348.8243138270232, 2352.1524385444195,
    2355.4829194563067, 2358.8157565626834, 2362.150949863551, 2365.488499358908,
    2368.8284050487559, 2372.1706669330938, 2375.5152850119216, 2378.86225928524,
    2382.211589753048, 2385.563276415347, 2388.9173192721355, 2392.2737183234149,
    2395.6324735691842, 2398.9935850094434, 2402.3570526441931,
    2405.7228764734327, 2409.0910564971628, 2412.4615927153832,
    2415.8344851280931, 2419.2097337352939, 2422.5873385369841,
    2425.9672995331653, 2429.3496167238363, 2432.7342901089974,
    2436.1213196886492, 2439.5107054627906, 2442.9024474314224,
    2446.2965455945446, 2449.6929999521567, 2453.0918105042597,
    2456.4929772508526, 2459.896500191935, 2463.3023793275083,
    2466.7106146575716, 2470.1212061821248, 2473.5341539011683,
    2476.9494578147023, 2480.3671179227263, 2483.7871342252406,
    2487.2095067222449, 2490.6342354137391, 2494.0613202997242,
    2497.4907613801988, 2500.9225586551638, 2504.3567121246192,
    2507.7932217885646, 2511.2320876470012, 2514.6733096999269,
    2518.116887947343, 2521.562822389249, 2525.011113025646, 2528.4617598565324,
    2531.9147628819092, 2535.3701221017764, 2538.8278375161335,
    2542.2879091249811, 2545.7503369283186, 2549.2151209261465,
    2552.6822611184643, 2556.1517575052726, 2559.6236100865708, 2563.09781886236,
    2566.5743838326384, 2570.0533049974074, 2573.5345823566668,
    2577.0182159104165, 2580.5042056586562, 2583.9925516013855,
    2587.4832537386055, 2590.976312070316, 2594.471726596516, 2597.9694973172063,
    2601.4696242323871, 2604.9721073420583, 2608.4769466462194,
    2611.9841421448705, 2615.4936938380119, 2619.0056017256438,
    2622.5198658077657, 2626.0364860843774, 2629.5554625554796,
    2633.0767952210722, 2636.6004840811552, 2640.1265291357281,
    2643.654930384791, 2647.1856878283443, 2650.7188014663875,
    2654.2542712989216, 2657.7920973259452, 2661.3322795474587,
    2664.8748179634631, 2668.4197125739574, 2671.9669633789422,
    2675.5165703784169, 2679.0685335723815, 2682.622852960837, 2686.179528543782,
    2689.7385603212178, 2693.2999482931436, 2696.86369245956, 2700.429792820466,
    2703.9982493758621, 2707.5690621257486, 2711.1422310701255,
    2714.7177562089923, 2718.2956375423491, 2721.8758750701963,
    2725.4584687925339, 2729.0434187093615, 2732.6307248206795,
    2736.2203871264874, 2739.8124056267857, 2743.4067803215739,
    2747.003511210853, 2750.6025982946212, 2754.2040415728807,
    2757.8078410456292, 2761.4139967128694, 2765.0225085745983,
    2768.6333766308185, 2772.2466008815277, 2775.8621813267287,
    2779.4801179664182, 2783.1004108005995, 2786.7230598292695,
    2790.3480650524311, 2793.9754264700828, 2797.605144082223,
    2801.2372178888554, 2804.8716478899764, 2808.5084340855892,
    2812.1475764756906, 2815.7890750602833, 2819.432929839365, 2823.079140812938,
    2826.7277079810005, 2830.3786313435539, 2834.0319109005968,
    2837.6875466521305, 2841.3455385981538, 2845.0058867386679,
    2848.6685910736715, 2852.3336516031663, 2856.00106832715, 2859.6708412456255,
    2863.3429703585907, 2867.0174556660445, 2870.6942971679905,
    2874.3734948644251, 2878.055048755351, 2881.7389588407664,
    2885.4252251206731, 2889.1138475950684, 2892.804826263955,
    2896.4981611273311, 2900.1938521851985, 2903.8918994375545,
    2907.5923028844027, 2911.295062525739, 2915.0001783615667,
    2918.7076503918838, 2922.4174786166923, 2926.1296630359907,
    2929.8442036497786, 2933.5611004580578, 2937.2803534608256,
    2941.0019626580847, 2944.7259280498333, 2948.4522496360732,
    2952.1809274168018, 2955.9119613920216, 2959.6453515617309,
    2963.3810979259315, 2967.1192004846207, 2970.8596592378021,
    2974.6024741854721, 2978.3476453276335, 2982.0951726642834,
    2985.8450561954251, 2989.5972959210571, 2993.3518918411778,
    2997.1088439557902, 3000.8681522648913, 3004.6298167684845,
    3008.3938374665659, 3012.1602143591385, 3015.9289474462012,
    3019.7000367277542, 3023.4734822037967, 3027.2492838743306,
    3031.027441739353, 3034.8079557988672, 3038.5908260528709,
    3042.3760525013649, 3046.1636351443485, 3049.9535739818234,
    3053.7458690137873, 3057.5405202402426, 3061.3375276611882,
    3065.1368912766225, 3068.9386110865489, 3072.742687090964, 3076.54911928987,
    3080.3579076832652, 3084.1690522711519, 3087.9825530535277,
    3091.7984100303947, 3095.6166232017504, 3099.4371925675982,
    3103.2601181279347, 3107.0853998827629, 3110.9130378320792,
    3114.7430319758878, 3118.5753823141849, 3122.4100888469734,
    3126.2471515742523, 3130.08657049602, 3133.9283456122789, 3137.7724769230272,
    3141.6189644282667, 3145.4678081279958, 3149.3190080222157,
    3153.1725641109242, 3157.0284763941249, 3160.8867448718138,
    3164.7473695439949, 3168.6103504106645, 3172.4756874718259,
    3176.3433807274755, 3180.2134301776173, 3184.0858358222476,
    3187.9605976613693, 3191.8377156949819, 3195.7171899230825,
    3199.5990203456754, 3203.4832069627569, 3207.3697497743292,
    3211.2586487803915, 3215.1499039809441, 3219.0435153759863,
    3222.9394829655203, 3226.8378067495428, 3230.7384867280566,
    3234.6415229010595, 3238.5469152685541, 3242.4546638305374,
    3246.3647685870128, 3250.2772295379764, 3254.1920466834313,
    3258.1092200233757, 3262.0287495578109, 3265.950635286737,
    3269.8748772101517, 3273.8014753280572, 3277.7304296404527,
    3281.6617401473391, 3285.5954068487144, 3289.5314297445811,
    3293.4698088349373, 3297.4105441197848, 3301.3536355991209,
    3305.2990832729488, 3309.2468871412648, 3313.1970472040734,
    3317.1495634613702, 3321.1044359131583, 3325.0616645594359,
    3329.0212494002049, 3332.9831904354637, 3336.9474876652116,
    3340.9141410894513, 3344.88315070818, 3348.8545165213995, 3352.8282385291081,
    3356.8043167313081, 3360.7827511279975, 3364.7635417191777,
    3368.746688504847, 3372.7321914850086, 3376.7200506596582,
    3380.7102660287997, 3384.7028375924297, 3388.6977653505514,
    3392.6950493031622, 3396.6946894502644, 3400.6966857918565,
    3404.7010383279376, 3408.7077470585104, 3412.7168119835724,
    3416.7282331031251, 3420.742010417167, 3424.758143925701, 3428.7766336287227,
    3432.7974795262371, 3436.8206816182396, 3440.8462399047339,
    3444.8741543857172, 3448.9044250611914, 3452.9370519311551, 3456.97203499561,
    3461.0093742545541, 3465.049069707989, 3469.0911213559139,
    3473.1355291983296, 3477.1822932352352, 3481.2314134666303,
    3485.2828898925163, 3489.3367225128914, 3493.3929113277582,
    3497.451456337114, 3501.5123575409616, 3505.5756149392973,
    3509.6412285321248, 3513.7091983194414, 3517.7795243012492,
    3521.8522064775461, 3525.9272448483339, 3530.0046394136111, 3534.08439017338,
    3538.1664971276373, 3542.2509602763862, 3546.3377796196255,
    3550.4269551573539, 3554.5184868895735, 3558.6123748162822,
    3562.7086189374822, 3566.8072192531713, 3570.9081757633512,
    3575.0114884680206, 3579.1171573671813, 3583.2251824608311,
    3587.3355637489722, 3591.4483012316023, 3595.5633949087237,
    3599.6808447803342, 3603.8006508464364, 3607.9228131070272,
    3612.0473315621093, 3616.1742062116814, 3620.303437055743,
    3624.4350240942963, 3628.5689673273378, 3632.705266754871,
    3636.8439223768933, 3640.9849341934073, 3645.1283022044095,
    3649.2740264099034, 3653.4221068098864, 3657.5725434043611,
    3661.725336193324, 3665.8804851767786, 3670.0379903547228,
    3674.1978517271577, 3678.3600692940818, 3682.5246430554976,
    3686.6915730114024, 3690.8608591617981, 3695.0325015066842,
    3699.2065000460593, 3703.3828547799258, 3707.5615657082813,
    3711.742632831128, 3715.9260561484643, 3720.1118356602915,
    3724.2999713666077, 3728.4904632674156, 3732.6833113627117,
    3736.8785156524996, 3741.0760761367765, 3745.2759928155451,
    3749.4782656888028, 3753.6828947565514, 3757.8898800187894,
    3762.0992214755183, 3766.3109191267381, 3770.5249729724464,
    3774.7413830126461, 3778.9601492473348, 3783.1812716765153,
    3787.4047503001839, 3791.6305851183452, 3795.8587761309941,
    3800.0893233381348, 3804.322226739765, 3808.5574863358861,
    3812.7951021264967, 3817.0350741115985, 3821.2774022911885,
    3825.5220866652712, 3829.769127233842, 3834.0185239969046,
    3838.2702769544576, 3842.5243861064987, 3846.780851453032,
    3851.0396729940539, 3855.3008507295676, 3859.5643846595694,
    3863.8302747840639, 3868.0985211030466, 3872.3691236165209,
    3876.6420823244839, 3880.9173972269382, 3885.1950683238815,
    3889.4750956153166, 3893.7574791012407, 3898.0422187816562, 3902.32931465656,
    3906.618766725956, 3910.9105749898408, 3915.2047394482174,
    3919.5012601010835, 3923.8001369484386, 3928.1013699902855,
    3932.404959226621, 3936.7109046574478, 3941.0192062827641,
    3945.3298641025717, 3949.6428781168684, 3953.9582483256559,
    3958.2759747289324, 3962.5960573267007, 3966.9184961189585,
    3971.2432911057067, 3975.5704422869439, 3979.8999496626734,
    3984.2318132328915, 3988.5660329976008, 3992.9026089568006,
    3997.2415411104889, 4001.582829458669, 4005.9264740013377,
    4010.2724747384987, 4014.6208316701477, 4018.9715447962885,
    4023.3246141169179, 4027.6800396320396, 4032.0378213416493,
    4036.3979592457508, 4040.7604533443409, 4045.1253036374233,
    4049.4925101249937, 4053.8620728070564, 4058.2339916836077, 4062.60826675465,
    4066.9848980201832, 4071.3638854802048, 4075.7452291347186, 4080.12892898372,
    4084.5149850272142, 4088.9033972651969, 4093.2941656976709,
    4097.6872903246331, 4102.0827711460879, 4106.4806081620318,
    4110.8808013724665, 4115.2833507773894, 4119.6882563768049,
    4124.0955181707086, 4128.505136159104, 4132.9171103419894,
    4137.3314407193657, 4141.74812729123, 4146.1671700575862, 4150.5885690184332,
    4155.0123241737683, 4159.4384355235952, 4163.8669030679112,
    4168.2977268067179, 4172.7309067400147, 4177.1664428678023,
    4181.6043351900789, 4186.0445837068473, 4190.4871884181039,
    4194.9321493238522, 4199.3794664240895, 4203.8291397188186,
    4208.2811692080368, 4212.7355548917458, 4217.1922967699438,
    4221.6513948426336, 4226.1128491098134, 4230.5766595714822,
    4235.0428262276428, 4239.5113490782906, 4243.9822281234319,
    4248.4554633630614, 4252.9310547971827, 4257.4090024257921,
    4261.8893062488933, 4266.3719662664835, 4270.8569824785654,
    4275.3443548851365, 4279.8340834861983, 4284.3261682817492,
    4288.8206092717919, 4293.3174064563236, 4297.8165598353462, 4302.31806940886,
    4306.8219351768612, 4311.3281571393545, 4315.8367352963369,
    4320.347669647811, 4324.8609601937733, 4329.3766069342282,
    4333.8946098691713, 4338.4149689986052, 4342.9376843225291,
    4347.4627558409447, 4351.9901835538485, 4356.5199674612431,
    4361.0521075631277, 4365.5866038595041, 4370.1234563503685,
    4374.6626650357239, 4379.2042299155692, 4383.7481509899062,
    4388.2944282587332, 4392.8430617220483, 4397.3940513798552,
    4401.9473972321521, 4406.5030992789389, 4411.0611575202147,
    4415.6215719559832, 4420.18434258624, 4424.7494694109882, 4429.3169524302248,
    4433.886791643954, 4438.4589870521713, 4443.03353865488, 4447.6104464520786,
    4452.1897104437685, 4456.7713306299465, 4461.3553070106163,
    4465.941639585777, 4470.5303283554258, 4475.1213733195655,
    4479.7147744781951, 4484.3105318313164, 4488.9086453789259,
    4493.5091151210263, 4498.1119410576166, 4502.7171231886987,
    4507.3246615142689, 4511.9345560343309, 4516.546806748881,
    4521.1614136579237, 4525.7783767614546, 4530.3976960594782,
    4535.019371551989, 4539.6434032389916, 4544.2697911204841,
    4548.8985351964675, 4553.5296354669417, 4558.1630919319041,
    4562.7989045913582, 4567.4370734453005, 4572.0775984937354,
    4576.7204797366585, 4581.3657171740733, 4586.0133108059772,
    4590.6632606323728, 4595.3155666532566, 4599.9702288686321,
    4604.6272472784967, 4609.2866218828531, 4613.9483526816975,
    4618.6124396750338, 4623.2788828628591, 4627.9476822451761,
    4632.6188378219831, 4637.2923495932791, 4641.968217559066, 4646.646441719342,
    4651.32702207411, 4656.0099586233664, 4660.6952513671149, 4665.3829003053515,
    4670.07290543808, 4674.7652667652974, 4679.4599842870066, 4684.1570580032039,
    4688.856487913893, 4693.5582740190712, 4698.2624163187411,
    4702.9689148128991, 4707.67776950155 };

  /* Start for MATLABSystem: '<Root>/FMCW Waveform' */
  obj->isInitialized = 1;
  for (b_k = 0; b_k < 2000; b_k++) {
    real_T obj_pSamples;

    /* Start for MATLABSystem: '<Root>/FMCW Waveform' */
    obj_pSamples = tmp[b_k];
    obj->pSamples[b_k].re = cos(obj_pSamples);
    obj->pSamples[b_k].im = sin(obj_pSamples);
  }
}

/* Model step function */
void fmcw_range_model_step(void)
{
  creal_T rtb_FMCWWaveform[100];
  creal_T unusedExpr[100];
  real_T OutputSampleIndex[101];
  real_T OutputSampleIndex_0;
  int32_T b_k;
  if (fmcw_range_model_M->Timing.TaskCounters.TID[1] == 0) {
    /* MATLABSystem: '<Root>/FMCW Waveform' */
    for (b_k = 0; b_k < 101; b_k++) {
      OutputSampleIndex_0 = (fmcw_range_model_DW.obj.pOutputStartSampleIndex +
        fmcw_range_model_DW.obj.pOutputSampleInterval[b_k]) - 1.0;
      if (rtIsNaN(OutputSampleIndex_0) || rtIsInf(OutputSampleIndex_0)) {
        OutputSampleIndex_0 = (rtNaN);
      } else if (OutputSampleIndex_0 == 0.0) {
        OutputSampleIndex_0 = 0.0;
      } else {
        OutputSampleIndex_0 = fmod(OutputSampleIndex_0, 2000.0);
        if (OutputSampleIndex_0 == 0.0) {
          OutputSampleIndex_0 = 0.0;
        } else if (OutputSampleIndex_0 < 0.0) {
          OutputSampleIndex_0 += 2000.0;
        }
      }

      OutputSampleIndex[b_k] = OutputSampleIndex_0 + 1.0;
    }

    fmcw_range_model_DW.obj.pOutputStartSampleIndex = OutputSampleIndex[100];
    for (b_k = 0; b_k < 100; b_k++) {
      rtb_FMCWWaveform[b_k] = fmcw_range_model_DW.obj.pSamples[(int32_T)
        OutputSampleIndex[b_k] - 1];
    }

    /* End of MATLABSystem: '<Root>/FMCW Waveform' */

    /* MATLABSystem: '<Root>/Free Space' incorporates:
     *  Constant: '<Root>/Constant'
     *  Constant: '<Root>/Constant1'
     *  MATLABSystem: '<Root>/FMCW Waveform'
     */
    fmcw_AbstractFreeSpace_stepImpl(&fmcw_range_model_DW.obj_g, rtb_FMCWWaveform,
      fmcw_range_model_ConstP.Constant1_Value,
      fmcw_range_model_ConstP.Constant_Value,
      fmcw_range_model_ConstP.Constant1_Value,
      fmcw_range_model_ConstP.Constant1_Value, unusedExpr);

    /* MATLABSystem: '<Root>/Radar Target' */
    if (fmcw_range_model_DW.obj_h.MeanRCS != 10.0) {
      if (fmcw_range_model_DW.obj_h.isInitialized == 1) {
        fmcw_range_model_DW.obj_h.TunablePropsChanged = true;
      }

      fmcw_range_model_DW.obj_h.MeanRCS = 10.0;
    }

    if (fmcw_range_model_DW.obj_h.TunablePropsChanged) {
      fmcw_range_model_DW.obj_h.TunablePropsChanged = false;
      fmcw_range_model_DW.obj_h.pRCS = 10.0;
    }

    /* End of MATLABSystem: '<Root>/Radar Target' */

    /* Buffer: '<Root>/Buffer' */
    fmcw_range_model_DW.Buffer_inBufPtrIdx += 100;
    if (fmcw_range_model_DW.Buffer_inBufPtrIdx >= 4000) {
      fmcw_range_model_DW.Buffer_inBufPtrIdx -= 4000;
    }

    fmcw_range_model_DW.Buffer_bufferLength += 100;
    if (fmcw_range_model_DW.Buffer_bufferLength > 4000) {
      fmcw_range_model_DW.Buffer_outBufPtrIdx =
        (fmcw_range_model_DW.Buffer_outBufPtrIdx +
         fmcw_range_model_DW.Buffer_bufferLength) - 4000;
      if (fmcw_range_model_DW.Buffer_outBufPtrIdx > 4000) {
        fmcw_range_model_DW.Buffer_outBufPtrIdx -= 4000;
      }

      fmcw_range_model_DW.Buffer_bufferLength = 4000;
    }
  }

  /* Buffer: '<Root>/Buffer' */
  if (fmcw_range_model_M->Timing.TaskCounters.TID[2] == 0) {
    fmcw_range_model_DW.Buffer_bufferLength -= 2000;
    if (fmcw_range_model_DW.Buffer_bufferLength < 0) {
      fmcw_range_model_DW.Buffer_outBufPtrIdx +=
        fmcw_range_model_DW.Buffer_bufferLength;
      if (fmcw_range_model_DW.Buffer_outBufPtrIdx < 0) {
        fmcw_range_model_DW.Buffer_outBufPtrIdx += 4000;
      }

      fmcw_range_model_DW.Buffer_bufferLength = 0;
    }

    b_k = 4000;
    if (fmcw_range_model_DW.Buffer_outBufPtrIdx > 2000) {
      b_k = fmcw_range_model_DW.Buffer_outBufPtrIdx;
      fmcw_range_model_DW.Buffer_outBufPtrIdx = 0;
    }

    fmcw_range_model_DW.Buffer_outBufPtrIdx =
      (fmcw_range_model_DW.Buffer_outBufPtrIdx + b_k) - 2000;
    if (fmcw_range_model_DW.Buffer_outBufPtrIdx == 4000) {
      fmcw_range_model_DW.Buffer_outBufPtrIdx = 0;
    }
  }

  rate_scheduler();
}

/* Model initialize function */
void fmcw_range_model_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  {
    int32_T i;

    /* InitializeConditions for Buffer: '<Root>/Buffer' */
    fmcw_range_model_DW.Buffer_inBufPtrIdx = 2000;
    fmcw_range_model_DW.Buffer_bufferLength = 2000;

    /* Start for MATLABSystem: '<Root>/FMCW Waveform' */
    fmcw_range_model_DW.obj.isInitialized = 0;
    fmcw_range_mod_SystemCore_setup(&fmcw_range_model_DW.obj);

    /* InitializeConditions for MATLABSystem: '<Root>/FMCW Waveform' */
    fmcw_range_model_DW.obj.pOutputStartSampleIndex = 1.0;
    for (i = 0; i < 101; i++) {
      fmcw_range_model_DW.obj.pOutputSampleInterval[i] = i;
    }

    /* End of InitializeConditions for MATLABSystem: '<Root>/FMCW Waveform' */

    /* Start for MATLABSystem: '<Root>/Free Space' */
    fmcw_range_model_DW.obj_g.TunablePropsChanged = false;
    fmcw_range_model_DW.obj_g.matlabCodegenIsDeleted = false;
    fmcw_range_model_DW.obj_g.isInitialized = 1;
    fmcw_range_model_DW.obj_g.pNumInputChannels = 1.0;
    fmcw_range_model_DW.obj_g.cBuffer.pNumInputChannels = -1.0;
    fmcw_range_model_DW.obj_g.cBuffer.isInitialized = 0;
    fmcw_range_model_DW.obj_g.cBuffer.matlabCodegenIsDeleted = false;
    fmcw_range_model_DW.obj_g.cFractionalDelayFilter.isInitialized = 0;

    /* System object Constructor function: dsp.VariableFractionalDelay */
    fmcw_range_model_DW.obj_g.cFractionalDelayFilter.cSFunObject.P0_IC.re = 0.0;
    fmcw_range_model_DW.obj_g.cFractionalDelayFilter.cSFunObject.P0_IC.im = 0.0;
    fmcw_range_model_DW.obj_g.isSetupComplete = true;

    /* Start for MATLABSystem: '<Root>/Radar Target' */
    fmcw_range_model_DW.obj_h.matlabCodegenIsDeleted = false;
    fmcw_range_model_DW.obj_h.MeanRCS = 10.0;
    fmcw_range_model_DW.obj_h.isInitialized = 1;
    fmcw_range_model_DW.obj_h.pNumInputChannels = 1.0;
    fmcw_range_model_DW.obj_h.isSetupComplete = true;
    fmcw_range_model_DW.obj_h.TunablePropsChanged = false;

    /* InitializeConditions for MATLABSystem: '<Root>/Radar Target' */
    fmcw_range_model_DW.obj_h.pRCS = 10.0;
  }
}

/* Model terminate function */
void fmcw_range_model_terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/Free Space' */
  if (!fmcw_range_model_DW.obj_g.matlabCodegenIsDeleted) {
    fmcw_range_model_DW.obj_g.matlabCodegenIsDeleted = true;
    if ((fmcw_range_model_DW.obj_g.isInitialized == 1) &&
        fmcw_range_model_DW.obj_g.isSetupComplete) {
      fmcw_range_model_DW.obj_g.pNumInputChannels = -1.0;
      if (fmcw_range_model_DW.obj_g.cBuffer.isInitialized == 1) {
        fmcw_range_model_DW.obj_g.cBuffer.isInitialized = 2;
        if (fmcw_range_model_DW.obj_g.cBuffer.isSetupComplete) {
          fmcw_range_model_DW.obj_g.cBuffer.pNumInputChannels = -1.0;
        }
      }

      if (fmcw_range_model_DW.obj_g.cFractionalDelayFilter.isInitialized == 1) {
        fmcw_range_model_DW.obj_g.cFractionalDelayFilter.isInitialized = 2;
      }
    }
  }

  if (!fmcw_range_model_DW.obj_g.cBuffer.matlabCodegenIsDeleted) {
    fmcw_range_model_DW.obj_g.cBuffer.matlabCodegenIsDeleted = true;
    if (fmcw_range_model_DW.obj_g.cBuffer.isInitialized == 1) {
      fmcw_range_model_DW.obj_g.cBuffer.isInitialized = 2;
      if (fmcw_range_model_DW.obj_g.cBuffer.isSetupComplete) {
        fmcw_range_model_DW.obj_g.cBuffer.pNumInputChannels = -1.0;
      }
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Free Space' */

  /* Terminate for MATLABSystem: '<Root>/Radar Target' */
  if (!fmcw_range_model_DW.obj_h.matlabCodegenIsDeleted) {
    fmcw_range_model_DW.obj_h.matlabCodegenIsDeleted = true;
    if ((fmcw_range_model_DW.obj_h.isInitialized == 1) &&
        fmcw_range_model_DW.obj_h.isSetupComplete) {
      fmcw_range_model_DW.obj_h.pNumInputChannels = -1.0;
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Radar Target' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
