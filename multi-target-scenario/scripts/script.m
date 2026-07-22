%% Extract data from SimulationOutput
beatFrames = out.beatframes;
 j
% Remove singleton dimension
data = squeeze(beatFrames);

% Use 128 chirps
data = data(:,1:128);

%% Parameters
Nr = 2000;      % Samples per chirp
Nd = 128;       % Number of chirps

%% Range FFT
rangeFFT = fft(data,Nr,1);

%% Doppler FFT
dopplerFFT = fft(rangeFFT,Nd,2);

%% Shift Doppler
RD = fftshift(dopplerFFT,2);

%% Magnitude
mapMag = abs(RD);

%% Remove DC leakage
mapMag = mapMag(11:1000,:);


%% Plot Range-Doppler Map
figure;
imagesc(20*log10(mapMag+eps));
axis xy;
xlabel('Doppler Bin');
ylabel('Range Bin');
title('Day 6 Multi Target Range-Doppler Map');
colorbar;


%% Peak Detection with suppression

tempMap = mapMag;

numTargets = 2;

rangeGuard = 5;
dopplerGuard = 5;


fprintf('=============================\n');
fprintf('Detected Targets\n');
fprintf('=============================\n');


for k = 1:numTargets

    % Find strongest peak
    [~,idx] = max(tempMap(:));

    [rBin,vBin] = ind2sub(size(tempMap),idx);


    % Convert bins
    rangeBin = rBin + 10;
    dopplerBin = vBin - 65;


    fprintf('Target %d\n',k);
    fprintf('Range Bin    : %d\n',rangeBin);
    fprintf('Doppler Bin  : %d\n\n',dopplerBin);


    % Suppress detected area
    r1 = max(1,rBin-rangeGuard);
    r2 = min(size(tempMap,1),rBin+rangeGuard);

    d1 = max(1,vBin-dopplerGuard);
    d2 = min(size(tempMap,2),vBin+dopplerGuard);


    tempMap(r1:r2,d1:d2)=0;

end