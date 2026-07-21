/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: fmcw_range_model.h
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

#ifndef fmcw_range_model_h_
#define fmcw_range_model_h_
#ifndef fmcw_range_model_COMMON_INCLUDES_
#define fmcw_range_model_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* fmcw_range_model_COMMON_INCLUDES_ */

#include "fmcw_range_model_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"
#include "rtGetNaN.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct {
  creal_T fy[4096];
  creal_T fy_tmp[4096];
  creal_T wwc[3999];
} B_fmcw_range_model_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  phased_FMCWWaveform_fmcw_rang_T obj; /* '<Root>/FMCW Waveform' */
  phased_FreeSpace_fmcw_range_m_T obj_g;/* '<Root>/Free Space' */
  phased_RadarTarget_fmcw_range_T obj_h;/* '<Root>/Radar Target' */
  int32_T Buffer_inBufPtrIdx;          /* '<Root>/Buffer' */
  int32_T Buffer_outBufPtrIdx;         /* '<Root>/Buffer' */
  int32_T Buffer_bufferLength;         /* '<Root>/Buffer' */
  boolean_T isInitialized;             /* '<Root>/Free Space' */
} DW_fmcw_range_model_T;

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: [50;0;0]
   * Referenced by: '<Root>/Constant'
   */
  real_T Constant_Value[3];

  /* Expression: [0;0;0]
   * Referenced by: '<Root>/Constant1'
   */
  real_T Constant1_Value[3];
} ConstP_fmcw_range_model_T;

/* Real-time Model Data Structure */
struct tag_RTM_fmcw_range_model_T {
  const char_T * volatile errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    struct {
      uint16_T TID[3];
    } TaskCounters;
  } Timing;
};

/* Block signals (default storage) */
extern B_fmcw_range_model_T fmcw_range_model_B;

/* Block states (default storage) */
extern DW_fmcw_range_model_T fmcw_range_model_DW;

/* Constant parameters (default storage) */
extern const ConstP_fmcw_range_model_T fmcw_range_model_ConstP;

/* Model entry point functions */
extern void fmcw_range_model_initialize(void);
extern void fmcw_range_model_step(void);
extern void fmcw_range_model_terminate(void);

/* Real-time Model object */
extern RT_MODEL_fmcw_range_model_T *const fmcw_range_model_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Display' : Unused code path elimination
 * Block '<Root>/Spectrum Analyzer1' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'fmcw_range_model'
 * '<S1>'   : 'fmcw_range_model/Dechirp Mixer'
 * '<S2>'   : 'fmcw_range_model/MATLAB Function'
 */
#endif                                 /* fmcw_range_model_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
