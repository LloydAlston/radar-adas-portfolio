/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: fmcw_range_model_types.h
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

#ifndef fmcw_range_model_types_h_
#define fmcw_range_model_types_h_
#include "rtwtypes.h"
#ifndef struct_tag_BlgwLpgj2bjudmbmVKWwDE
#define struct_tag_BlgwLpgj2bjudmbmVKWwDE

struct tag_BlgwLpgj2bjudmbmVKWwDE
{
  uint32_T f1[8];
};

#endif                                 /* struct_tag_BlgwLpgj2bjudmbmVKWwDE */

#ifndef typedef_cell_wrap_fmcw_range_model_T
#define typedef_cell_wrap_fmcw_range_model_T

typedef struct tag_BlgwLpgj2bjudmbmVKWwDE cell_wrap_fmcw_range_model_T;

#endif                                /* typedef_cell_wrap_fmcw_range_model_T */

#ifndef struct_tag_gmKrOudSJ0nkx2QAk0sC7B
#define struct_tag_gmKrOudSJ0nkx2QAk0sC7B

struct tag_gmKrOudSJ0nkx2QAk0sC7B
{
  int32_T isInitialized;
  creal_T pSamples[2000];
  real_T pOutputStartSampleIndex;
  real_T pOutputSampleInterval[101];
};

#endif                                 /* struct_tag_gmKrOudSJ0nkx2QAk0sC7B */

#ifndef typedef_phased_FMCWWaveform_fmcw_rang_T
#define typedef_phased_FMCWWaveform_fmcw_rang_T

typedef struct tag_gmKrOudSJ0nkx2QAk0sC7B phased_FMCWWaveform_fmcw_rang_T;

#endif                             /* typedef_phased_FMCWWaveform_fmcw_rang_T */

#ifndef struct_tag_ISo1BVzI0fJN0BvG7nA87F
#define struct_tag_ISo1BVzI0fJN0BvG7nA87F

struct tag_ISo1BVzI0fJN0BvG7nA87F
{
  int32_T S0_isInitialized;
  int32_T W0_BUFF_OFFSET;
  creal_T W1_BUFF[101];
  int32_T W2_PrevNumChan;
  creal_T P0_IC;
};

#endif                                 /* struct_tag_ISo1BVzI0fJN0BvG7nA87F */

#ifndef typedef_b_dsp_VariableFractionalDelay_T
#define typedef_b_dsp_VariableFractionalDelay_T

typedef struct tag_ISo1BVzI0fJN0BvG7nA87F b_dsp_VariableFractionalDelay_T;

#endif                             /* typedef_b_dsp_VariableFractionalDelay_T */

#ifndef struct_tag_IXyuqzeIvXZCnrwtc3tqYB
#define struct_tag_IXyuqzeIvXZCnrwtc3tqYB

struct tag_IXyuqzeIvXZCnrwtc3tqYB
{
  int32_T isInitialized;
  boolean_T isSetupComplete;
  b_dsp_VariableFractionalDelay_T cSFunObject;
};

#endif                                 /* struct_tag_IXyuqzeIvXZCnrwtc3tqYB */

#ifndef typedef_d_dspcodegen_VariableFraction_T
#define typedef_d_dspcodegen_VariableFraction_T

typedef struct tag_IXyuqzeIvXZCnrwtc3tqYB d_dspcodegen_VariableFraction_T;

#endif                             /* typedef_d_dspcodegen_VariableFraction_T */

#ifndef struct_tag_E4PUWYZzLSpEuvL1WkAJIF
#define struct_tag_E4PUWYZzLSpEuvL1WkAJIF

struct tag_E4PUWYZzLSpEuvL1WkAJIF
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  cell_wrap_fmcw_range_model_T inputVarSize[2];
  real_T pNumInputChannels;
  real_T pCount;
  real_T pStart;
  creal_T pBuffer[767];
  real_T pBufferLength;
};

#endif                                 /* struct_tag_E4PUWYZzLSpEuvL1WkAJIF */

#ifndef typedef_c_phased_internal_CircularBuf_T
#define typedef_c_phased_internal_CircularBuf_T

typedef struct tag_E4PUWYZzLSpEuvL1WkAJIF c_phased_internal_CircularBuf_T;

#endif                             /* typedef_c_phased_internal_CircularBuf_T */

#ifndef struct_tag_iwRd7rT0CAm62Z4yPtkFwH
#define struct_tag_iwRd7rT0CAm62Z4yPtkFwH

struct tag_iwRd7rT0CAm62Z4yPtkFwH
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  boolean_T TunablePropsChanged;
  cell_wrap_fmcw_range_model_T inputVarSize[5];
  real_T pNumInputChannels;
  c_phased_internal_CircularBuf_T cBuffer;
  d_dspcodegen_VariableFraction_T cFractionalDelayFilter;
};

#endif                                 /* struct_tag_iwRd7rT0CAm62Z4yPtkFwH */

#ifndef typedef_phased_FreeSpace_fmcw_range_m_T
#define typedef_phased_FreeSpace_fmcw_range_m_T

typedef struct tag_iwRd7rT0CAm62Z4yPtkFwH phased_FreeSpace_fmcw_range_m_T;

#endif                             /* typedef_phased_FreeSpace_fmcw_range_m_T */

#ifndef struct_tag_bpavrHDwcLsi0fMKHvrnpC
#define struct_tag_bpavrHDwcLsi0fMKHvrnpC

struct tag_bpavrHDwcLsi0fMKHvrnpC
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  boolean_T TunablePropsChanged;
  cell_wrap_fmcw_range_model_T inputVarSize;
  real_T pNumInputChannels;
  real_T MeanRCS;
  real_T pRCS;
};

#endif                                 /* struct_tag_bpavrHDwcLsi0fMKHvrnpC */

#ifndef typedef_phased_RadarTarget_fmcw_range_T
#define typedef_phased_RadarTarget_fmcw_range_T

typedef struct tag_bpavrHDwcLsi0fMKHvrnpC phased_RadarTarget_fmcw_range_T;

#endif                             /* typedef_phased_RadarTarget_fmcw_range_T */

/* Forward declaration for rtModel */
typedef struct tag_RTM_fmcw_range_model_T RT_MODEL_fmcw_range_model_T;

#endif                                 /* fmcw_range_model_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
