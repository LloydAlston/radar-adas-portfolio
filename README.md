# Radar & ADAS Engineering Portfolio

**Hands-on FMCW radar, sensor fusion, and V2X communication projects — built in MATLAB/Simulink, moving from raw physics to closed-loop, standards-validated systems.**

Every project starts with a hand-calculated expected result and ends with a verified match against simulation — no black boxes, no "it looks about right." Where things didn't go as planned, that's documented too, because debugging is the actual job.

`FMCW Radar` · `Range-Doppler Processing` · `CA-CFAR Detection` · `Sensor Fusion (EKF/JPDA)` · `802.11p V2X` · `Embedded Coder / MISRA C` · `Euro NCAP AEB Validation`

---

## Why this repo exists

I'm building toward a role in **automotive radar and sensor engineering** — the systems behind adaptive cruise control, automatic emergency braking, and the sensing/communication stack of modern ADAS. This portfolio is my proof of work: every model, script, and result here was built and verified by me, one project at a time.

I'm also a **licensed amateur radio operator (VU3HXY)** — real RF hardware experience that grounds the simulation work below in physical intuition, not just textbook formulas.

---

## Licensed Amateur Radio Operator — VU3HXY

| | |
|---|---|
| **Grade** | Amateur Restricted Grade |
| **License No.** | 45384 |
| **Issued by** | Government of India, Ministry of Communications, WPC Wing |
| **Valid** | 24 Feb 2025 – 24 Jan 2083 |

- Designed, fabricated, and optimised 6m Yagi-Uda antennas for high-gain HF communication
- Built 2m Yagi beam antennas for emergency communication workshops
- Participated in **JOTA** (Jamboree on the Air), an international amateur radio event
- Took part in **SEARCH** (System for Emergency Assistance, Response and Communication Hub), disaster-response readiness
- Hands-on background in antenna theory, EM propagation, and RF system design — the physical intuition behind every simulated waveform in this repo

---

## Projects

1. [FMCW Range Estimation](./fmcw-range-estimation) — Chirp generation, dechirp mixing, beat frequency → range
2. [Range-Doppler Map](./range-doppler-map) — 128-chirp 2D FFT separating range and velocity of a moving target
3. [CA-CFAR Detection](./ca-cfar-detection) — Adaptive detection recovering a target buried 10,000× below the noise floor
4. [Angle of Arrival Estimation](./angle-of-arrival) — ULA beamforming, direction finding
5. [Embedded Coder & MISRA C Codegen](./embedded-coder-codegen) — Deploying the radar pipeline as production-grade C
6. [Multi-Target Scenario](./multi-target-scenario) — Multiple vehicles, distinct range/velocity signatures
7. [Clutter, Noise & Multipath](./clutter-noise-multipath) — Detection performance under realistic conditions
8. [EKF Single-Target Tracker](./ekf-single-target-tracker) — Extended Kalman Filter state estimation
9. [GNN/JPDA Multi-Target Tracking](./gnn-jpda-multitarget) — Data association across multiple simultaneous tracks
10. [RadarScenario ACC/AEB](./radarscenario-acc-aeb) — Ego + lead vehicle kinematics, full scenario modeling
11. [Camera-Radar Coordinate Mapping](./camera-bbox-pixel-radar) — Pixel-to-Cartesian sensor alignment
12. [Radar-Camera Fusion](./radar-camera-fusion) — Combining velocity-rich radar with classification-rich camera data
13. [Fusion Robustness Testing](./fusion-robustness-testing) — Injected latency/dropped frames — failure-mode testing
14. [802.11p V2X PHY/MAC](./80211p-v2x-phy) — Vehicle-to-vehicle communication link, WLAN Toolbox
15. [Full Front-End Simulink Model](./simulink-frontend-model) — Chirp gen → mixer → ADC → DSP chain, system-level
16. [Closed-Loop ACC Controller](./closed-loop-acc-controller) — Radar detection driving real-time speed control
17. [Euro NCAP AEB Testbench](./euro-ncap-aeb-testbench) — Standardized scenario validation, V-model methodology
18. [KPI Analyzer & Report](./kpi-analyzer-report) — Probability of detection, false alarm rate, auto-generated reports

---

## Resources & Acknowledgements

Built with the help of official MATLAB/Simulink documentation, YouTube MATLAB/Simulink tutorials (toolbox-specific workflows for Radar Toolbox, Phased Array System Toolbox, WLAN Toolbox), and AI/LLM assistance (Claude) for working through theory, verifying results, and debugging. Every model, script, and result in this repository was built and run by me — these resources supported learning and troubleshooting, not a substitute for understanding the engineering.

---

*Each project folder contains the Simulink model, processing scripts, a full README with theory + verified results, and result screenshots.*