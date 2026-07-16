
clc;

beatFrames = out.beatframes;
data = squeeze(beatFrames);
data = data(:,1:128);

cfar = phased.CFARDetector2D( ...
    'GuardBandSize', [4 4], ...
    'TrainingBandSize', [10 10], ...
    'ProbabilityFalseAlarm', 1e-4);

margin = 4 + 10;
[rIdxGrid, dIdxGrid] = ndgrid(margin+1:200-margin, margin+1:128-margin);
CUTIdx = [rIdxGrid(:).'; dIdxGrid(:).'];

%% TEST 1: No added noise at all -- sanity check the CFAR wiring itself
rangeFFT = fft(data,[],1);
mapMag_clean = abs(fftshift(fft(rangeFFT,[],2),2)).^2;
det_clean = cfar(mapMag_clean(1:200,:), CUTIdx);
idx = find(det_clean);
fprintf('--- Clean data (no noise) ---\n');
fprintf('Detections: %d\n', numel(idx));
for k = 1:numel(idx)
    fprintf('  range bin %d, doppler bin %d\n', CUTIdx(1,idx(k)), CUTIdx(2,idx(k)));
end

%% TEST 2-5: Sweep noise level to find where detection starts failing
for raw_snr_db = [-10, -20, -30, -40]
    noisyData = awgn(data, raw_snr_db, 'measured');
    rangeFFT = fft(noisyData,[],1);
    mapMag = abs(fftshift(fft(rangeFFT,[],2),2)).^2;
    det = cfar(mapMag(1:200,:), CUTIdx);
    idx = find(det);
    fprintf('\n--- Raw SNR = %d dB ---\n', raw_snr_db);
    fprintf('Detections: %d\n', numel(idx));
    for k = 1:numel(idx)
        fprintf('  range bin %d, doppler bin %d\n', CUTIdx(1,idx(k)), CUTIdx(2,idx(k)));
    end
end