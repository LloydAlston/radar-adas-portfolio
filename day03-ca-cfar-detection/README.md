# Day 3: CA-CFAR Detection on the Range-Doppler Map

A Cell-Averaging Constant False Alarm Rate (CA-CFAR) detector was applied to the Day 2 range-Doppler map to automatically decide which cells contain a real target, instead of manually reading off the brightest pixel. No changes were made to the Simulink model from Day 2 — this project reuses beatFrames directly and adds detection logic entirely in MATLAB post-processing.

---

## Why CA-CFAR

A fixed brightness threshold doesn't work on real radar data, because the noise floor isn't flat — it varies across the map due to clutter, leakage, and interference. CA-CFAR solves this by estimating the local noise level around every cell under test (CUT) and setting the threshold relative to that local estimate, rather than a single global cutoff.

For each CUT, a ring of training cells is averaged to estimate the local noise power. A ring of guard cells sits between the CUT and the training cells, excluded from the average — this prevents the CUT's own target energy from leaking into (and inflating) the noise estimate.

```
CUT -> [guard cells, excluded] -> [training cells, averaged for noise estimate] -> threshold = alpha * average
```

---

## Parameters

| Parameter | Value |
| :--- | :--- |
| Guard band size | 4 cells/side (both range & Doppler) |
| Training band size | 10 cells/side (both range & Doppler) |
| Total training cells ($N$) | 760 |
| Probability of false alarm ($P_{fa}$) | 1e-4 |
| **Threshold factor ($\alpha$)** | **9.266 (9.67 dB above local noise estimate)** |
| Range-of-interest | First 200 range bins (~0–200 m) |
| Valid CUT cells tested | 17,200 |
| **Expected false alarms at this $P_{fa}$** | **approx. 1.72** |
| Injected raw SNR (final test) | -40 dB (pre-FFT) |
| Range FFT coherent gain | 33.01 dB ($N=2000$) |
| Doppler FFT coherent gain | 21.07 dB ($M=128$) |
| Expected peak SNR after both FFTs | approx. 14.08 dB |

---

## Script

The script [cfar.m](file:///c:/Users/lloyd/radar-adas-portfolio/day03-ca-cfar-detection/scripts/cfar.m) reuses `out.beatframes` from the simulation model, injects controlled AWGN at a specified SNR (`awgn(data, snr_db, 'measured')`), re-runs the same 2D FFT range-Doppler processing, and then applies `phased.CFARDetector2D` over the range-of-interest.

---

## Results — SNR Sweep

CFAR was run at increasing noise levels to observe detection behavior, from clean data down to -40 dB raw pre-FFT SNR.

| Raw SNR | Total Detections | Notes |
| :--- | :--- | :--- |
| No noise (clean) | **181** | Widespread false detections along the leakage cross — see finding below |
| -10 dB | 22 | Leakage-cross detections shrinking as noise rises |
| -20 dB | 15 | Continuing to shrink |
| -30 dB | 3 | Only cells immediately adjacent to the true target remain |
| **-40 dB** | **3** | **True target recovered at range bin 51, doppler bin 52** + 2 scattered false alarms |

### Key finding: CA-CFAR is fooled by spectral leakage on clean data

The 181 detections on noise-free data are not random noise triggers — they form long, coherent lines running exactly along range bin 51 and doppler bin 52, matching the leakage-cross artifact identified in the Day 2 range-Doppler map (a rectangular-window FFT sidelobe effect).

This happens because CA-CFAR's core assumption is that training cells represent pure noise. The leakage skirt violates that assumption: those cells have genuinely elevated power for a deterministic reason (spectral leakage from the target's own energy), not from random noise. CA-CFAR correctly flags them as "above the local threshold" — it isn't malfunctioning, it's operating exactly as designed on data that breaks one of its underlying assumptions.

As injected noise increases, the local noise estimate around each cell rises with it — eventually exceeding the (fixed, small) leakage-skirt power, so those spurious detections get suppressed. What survives at high noise is the true target plus a small number of genuine statistical false alarms.

This is exactly why real FMCW radar systems apply a window function (Hamming/Hann/Taylor) before CFAR, not purely for cosmetic sidelobe suppression on a plot — a known, standard fix, intentionally not applied in this project so the failure mode could be observed and documented directly. Applying a window and re-testing is a natural next step, tracked as a future improvement below rather than folded into this result.

### Final result verification (-40 dB)

| Metric | Expected | Measured |
| :--- | :--- | :--- |
| True target location | range bin ~51, doppler bin ~52 | range bin 51, doppler bin 52 (Passed) |
| Expected false alarms | approx. 1.72 | 2 (close match) |
| Threshold factor | 9.67 dB above local noise | consistent with observed suppression behavior |

### Note on run-to-run variability

An earlier run at the same -40 dB setting produced only 1 detection (a false alarm, with the true target missed). This is not a bug — `awgn()` draws a fresh random noise realization each call, and at -40 dB the true target's margin above threshold is thin enough that an unlucky noise draw can occasionally suppress it while elevating a different cell instead. This run-to-run variability is itself a real radar engineering concept: characterizing probability of detection (Pd) properly requires running many trials and measuring the detection rate, not relying on a single run.

---

## Future improvements

- Apply a window function (Hamming/Hann) before the FFTs to suppress the leakage skirt, then re-run the clean-data CFAR test to confirm the 181 false detections collapse toward the true target only.
- Run the -40 dB test across many trials (e.g. 100+ runs) to empirically estimate probability of detection (Pd) at this SNR, rather than reporting a single pass/fail outcome.

---

## Files

- [cfar.m](file:///c:/Users/lloyd/radar-adas-portfolio/day03-ca-cfar-detection/scripts/cfar.m) — noise injection + range-Doppler processing + CFAR detection script
- [fmcw_range_model.slx](file:///c:/Users/lloyd/radar-adas-portfolio/day03-ca-cfar-detection/scripts/fmcw_range_model.slx) — simulation model (no model changes from Day 2)
