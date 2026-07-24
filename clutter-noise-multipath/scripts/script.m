%% Radar Parameters

c = 3e8;
fc = 77e9;
B = 150e6;
Tchirp = 10e-6;
Fs = 200e6;

slope = B/Tchirp;

%% Load Simulink Output

beatframes = out.beatframes;

disp('Original beatframes size:')
disp(size(beatframes))

beatSignal = squeeze(beatframes);

disp('Beat signal size:')
disp(size(beatSignal))

%% ==========================================================
% DO NOT ADD NOISE (Debug Mode)
% ==========================================================

% beatSignal = awgn(beatSignal,-20,'measured');

[numSamples,numChirps] = size(beatSignal);

%% ==========================================================
% Apply Hamming Window (Range)
% ==========================================================

rangeWindow = hamming(numSamples);

beatSignal = beatSignal .* rangeWindow;

%% ==========================================================
% Range FFT
% ==========================================================

rangeFFT = fft(beatSignal,numSamples,1);

rangeFFT = rangeFFT(1:numSamples/2,:);

%% ==========================================================
% Average Range Profile
% ==========================================================

rangeProfile = mean(abs(rangeFFT),2);

figure;
plot(rangeProfile,'LineWidth',1.5);
grid on;
xlabel('Range Bin');
ylabel('Magnitude');
title('Average Range Profile');

%% ==========================================================
% Apply Hamming Window (Doppler)
% ==========================================================

dopplerWindow = hamming(numChirps).';

rangeFFT = rangeFFT .* dopplerWindow;

%% ==========================================================
% Doppler FFT
% ==========================================================

dopplerFFT = fftshift(fft(rangeFFT,numChirps,2),2);

mapMag = abs(dopplerFFT);

%% ==========================================================
% Plot Range-Doppler Map
% ==========================================================

figure;

imagesc(20*log10(mapMag+eps));

axis xy;

xlabel('Doppler Bin');

ylabel('Range Bin');

title('Range-Doppler Map');

colorbar;

%% ==========================================================
% Top 30 Peaks
% ==========================================================

[peakValues,idx] = maxk(mapMag(:),30);

[rangeBin,dopplerBin] = ind2sub(size(mapMag),idx);

fprintf('\n');
fprintf('=============== TOP 30 PEAKS ===============\n\n');

for k = 1:30

    fprintf('%2d : Range Bin = %4d    Doppler Bin = %4d    Magnitude = %.6f\n',...
        k,...
        rangeBin(k),...
        dopplerBin(k)-ceil(numChirps/2),...
        peakValues(k));

end

%% ==========================================================
% Convert Range Bin to Meters
% ==========================================================

rangeAxis = (0:numSamples/2-1)*(Fs/numSamples);

rangeMeters = rangeAxis*c/(2*slope);

fprintf('\n');
fprintf('============= RANGE ESTIMATES =============\n\n');

for k=1:30

    fprintf('%2d : %.2f m\n',k,rangeMeters(rangeBin(k)));

end