clc;


%% Get radar beat signal from Simulink output
beatFrames = out.beatframes;     % Beat signal from radar model

data = squeeze(beatFrames);      % Convert 3D data to 2D matrix

data = data(:,1:128);            % Use 128 chirps for Doppler processing


%% Range FFT
rangeFFT = fft(data,[],1);       % FFT along samples -> range information


%% Doppler FFT
rangeDopplerMap = fftshift(fft(rangeFFT,[],2),2);

mapMag = abs(rangeDopplerMap);   % Magnitude of Range-Doppler map


%% Radar parameters
B = 150e6;       % Chirp bandwidth
T = 10e-6;       % Chirp duration
Fs = 200e6;      % Sampling frequency
N = 2000;        % Samples per chirp
c = 3e8;         % Speed of light

slope = B/T;     % FMCW chirp slope


%% Range axis calculation
freqAxis = (0:N-1)*(Fs/N);

rangeAxis = freqAxis*c/(2*slope);


%% Doppler axis
dopplerBins = -64:63;


%% Remove DC component and find target peak
mapMag(1:10,:) = 0;              % Remove leakage near zero range

[~,idx] = max(mapMag(:));

[rBin,vBin] = ind2sub(size(mapMag),idx);


%% Display detected target information
fprintf("Range bin = %d\n",rBin);
fprintf("Doppler bin = %d\n",vBin);

fprintf("Range = %.2f m\n",rangeAxis(rBin));
fprintf("Doppler bin value = %d\n",dopplerBins(vBin));


%% Convert Doppler bin to velocity
fc = 77e9;                      % Radar carrier frequency
lambda = c/fc;                  % Wavelength

Nd = 128;                       % Number of chirps

PRF = 1/T;

dopplerFreq = dopplerBins(vBin)*(PRF/Nd);

velocity = dopplerFreq*lambda/2;


fprintf("Velocity = %.2f m/s\n",velocity);
fprintf("Velocity = %.2f km/h\n",velocity*3.6);


%% Plot Range-Doppler map
figure;

imagesc(dopplerBins,rangeAxis(1:100),...
    20*log10(mapMag(1:100,:)));

xlabel("Doppler bin");
ylabel("Range (m)");
title("Range Doppler Map");

colorbar;
axis xy;