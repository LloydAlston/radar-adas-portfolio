# Embedded Coder Code Generation — FMCW Range Estimation

This project demonstrates the conversion of an FMCW (Frequency-Modulated Continuous Wave) radar range estimation algorithm from a MATLAB/Simulink development environment into deployable embedded C code using MathWorks **Embedded Coder** (R2024b).

The generated C implementation was subsequently analysed with **Cppcheck** using MISRA C:2012 rules. After separating the production algorithm code from MathWorks runtime support files, the core radar implementation (`fmcw_range_model.c`) passed MISRA C:2012 analysis with **no reported violations**.

---

## Simulink Model

| Property | Value |
|---|---|
| Model name | `fmcw_range_model` |
| Model version | 1.1 |
| Simulink Coder | 24.2 (R2024b) |
| Target selection | `ert.tlc` (Embedded Real-Time) |
| Embedded hardware | ARM Compatible → ARM Cortex-M |
| Code generated | Tue 21 Jul 2026 |

### Model Blocks

| Block | Role |
|---|---|
| **FMCW Waveform** | Generates the swept-frequency transmit chirp |
| **Free Space** | Models two-way propagation loss and delay |
| **Radar Target** | Applies target RCS-based reflection |
| **Dechirp Mixer** | Multiplies TX and RX signals to produce the IF beat |
| **Buffer** | Accumulates samples for FFT processing |
| **MATLAB Function** | Computes range via FFT and peak detection |

> Blocks `Display` and `Spectrum Analyzer1` were eliminated by Embedded Coder's unused-code-path optimisation and are absent from the generated C.

---

## Generated C API

The generated code exposes three entry-point functions:

```c
/* Initialise all model states — call once before the control loop */
void fmcw_range_model_initialize(void);

/* Execute one base-rate time step (5 ns base rate, 3 task rates) */
void fmcw_range_model_step(void);

/* Release resources — call on shutdown */
void fmcw_range_model_terminate(void);
```

The real-time model handle `fmcw_range_model_M` exposes an `errorStatus` field for overrun detection. `ert_main.c` provides a minimal integration harness showing how to wire `rt_OneStep()` to a hardware timer or interrupt service routine on the target MCU.

---

## MISRA C:2012 Analysis

Static analysis was performed with **Cppcheck** with the `--addon=misra` flag.

### Findings Summary

| Scope | Files Analysed | MISRA Violations |
|---|---|---|
| All generated files | `fmcw_range_model.c`, `ert_main.c`, `rt_nonfinite.c`, `rtGetNaN.c`, ... | Violations present |
| **Production code only** | `fmcw_range_model.c` | **0 violations** |

### Violation Classification

Violations identified in the full scan originate exclusively from:

- **MathWorks runtime support files** (`rt_nonfinite.c`, `rtGetNaN.c`) — library code outside the scope of the user-authored algorithm.
- **Simulation harness** (`ert_main.c`) — contains `printf`/`fflush` calls and a blocking `while` loop intended for desktop simulation only, not for deployment.

The production algorithm file `fmcw_range_model.c` isolates all FMCW signal-processing logic and passed MISRA C:2012 static analysis cleanly.

### Key Algorithm Functions (fmcw_range_model.c)

| Function | Description |
|---|---|
| `fmcw_range_model_initialize()` | State and object initialisation |
| `fmcw_range_model_step()` | Per-step execution: waveform generation, propagation, mixing, FFT, range output |
| `fmcw_range_model_terminate()` | Teardown |
| `fmcw_AbstractFreeSpace_stepImpl()` | Free-space channel model with fractional delay |
| `fmcw_range__SystemCore_stepImpl()` | Variable fractional delay filter (propagation delay) |
| `rt_powd_snf()` / `rt_remd_snf()` | Portable power / remainder helpers with NaN/Inf guards |

---

## Deployment Notes

- The code targets **ARM Cortex-M** (configurable in Embedded Coder hardware settings).
- Base sample rate is **5 ns** (200 MHz); subrates at 500 ns and ~10 us are managed internally by `rate_scheduler()`.
- `ert_main.c` is a **simulation-only harness** and must be replaced with target-specific ISR/timer integration before deployment.
- MathWorks runtime files (`rt_nonfinite.*`, `rtGetNaN.*`) must be included in the build but are not subject to MISRA compliance for production certification purposes.

---

## Tools and Versions

| Tool | Version |
|---|---|
| MATLAB / Simulink | R2024b (24.2) |
| Embedded Coder | R2024b |
| Cppcheck | 2.x with MISRA addon |
| Target hardware | ARM Cortex-M (generic) |
