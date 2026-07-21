# Embedded Coder Code Generation — FMCW Range Estimation

This project demonstrates the conversion of an FMCW (Frequency-Modulated Continuous Wave) radar range estimation algorithm from a MATLAB/Simulink development environment into deployable embedded C code using MathWorks **Embedded Coder** (R2024b).

The generated C implementation was subsequently analysed with **Cppcheck** using MISRA C:2012 rules. After separating the production algorithm code from MathWorks runtime support files, the core radar implementation (`fmcw_range_model.c`) achieved **zero reported MISRA C:2012 violations** using Cppcheck MISRA analysis.

---

## Simulink Model

| Property | Value |
|---|---|
| Model name | `fmcw_range_model` |
| Model version | 1.1 |
| Simulink Coder | 24.2 (R2024b) |
| Target configuration | ERT (Embedded Real-Time) — generates embedded-style C without OS dependencies |
| Deployment target | Generic ARM Cortex-M configuration (selected in Embedded Coder hardware settings; not implied by ERT alone) |
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

/* Execute one base-rate time step — simulation step configured at 5e-9 s; ECU task period mapped separately at deployment */
void fmcw_range_model_step(void);

/* Release resources — call on shutdown */
void fmcw_range_model_terminate(void);
```

The real-time model handle `fmcw_range_model_M` exposes an `errorStatus` field for overrun detection. `ert_main.c` provides a desktop execution harness illustrating the call sequence (`initialize` → `step` → `terminate`) that would later be replaced by ECU scheduler/RTOS task integration.

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

- **MathWorks runtime support files** (`rt_nonfinite.c`, `rtGetNaN.c`) — vendor-generated code classified separately; compliance requires documented MISRA deviations or qualification according to project standards.
- **Simulation harness** (`ert_main.c`) — contains `printf`/`fflush` calls and a blocking `while` loop intended for desktop simulation only, not for deployment.

The generated production algorithm implementation in `fmcw_range_model.c` — comprising the Simulink block code, rate scheduler, and MATLAB Function logic — achieved zero reported MISRA C:2012 violations.

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

- The deployment target is a **generic ARM Cortex-M configuration**, selected via Embedded Coder hardware settings. ERT target selection alone does not determine the hardware platform.
- Simulation base step was configured at **5e-9 s (5 ns)**. ECU task scheduling and execution periods would be mapped separately during deployment integration.
- `ert_main.c` is a **desktop execution harness** illustrating the model lifecycle. It must be replaced by ECU scheduler/RTOS task code before deployment.
- MathWorks runtime support files (`rt_nonfinite.*`, `rtGetNaN.*`) are classified separately as vendor-generated code. They require documented MISRA deviations or vendor qualification documentation — not blanket exclusion.

---

## Verification Command

The following command was used to run MISRA C:2012 static analysis on the production code file:

```bash
cppcheck --addon=misra --enable=all --suppress=missingIncludeSystem fmcw_range_model.c
```

> **Note:** Cppcheck is a static analysis tool and does not constitute a formally qualified MISRA tool. Production-grade MISRA certification would require a qualified tool such as Polyspace, Helix QAC, LDRA, or PC-lint Plus.

---

## Tools and Versions

| Tool | Version |
|---|---|
| MATLAB / Simulink | R2024b (24.2) |
| Embedded Coder | R2024b |
| Cppcheck | 2.x with MISRA addon |
| Target hardware | ARM Cortex-M (generic) |
