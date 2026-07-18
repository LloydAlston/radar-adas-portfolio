% run_and_plot.m
% Load and run the FMCW Angle of Arrival Simulink model,
% extract the MVDR spectrum, plot the results, and save the figure.

cd('c:\Users\lloyd\radar-adas-portfolio\angle-of-arrival\scripts');

% Open and run the model
model_name = 'fmcw_range_model';
load_system(model_name);

fprintf('Running simulation for %s...\n', model_name);
out = sim(model_name);
fprintf('Simulation completed.\n');

% Extract MVDR spectrum data
scanAngles = -90:0.5:90;
Y = out.simout.Data(:,1,2); % page 2 contains the real spectrum

% Find the peak
[peakVal, peakIdx] = max(Y);
peakAngle = scanAngles(peakIdx);
fprintf('Peak found at %.1f degrees, value = %.2f\n', peakAngle, peakVal);

% Plot the MVDR Spectrum
fig = figure('Visible', 'off');
plot(scanAngles, Y, 'LineWidth', 2, 'Color', [0 0.4470 0.7410]);
xlabel('Angle (degrees)', 'FontSize', 12);
ylabel('MVDR Spectrum (dB)', 'FontSize', 12);
title('MVDR Spectrum vs. Scan Angle', 'FontSize', 14);
grid on;
hold on;

% Highlight the peak
plot(peakAngle, peakVal, 'ro', 'MarkerSize', 8, 'LineWidth', 2);
text(peakAngle + 2, peakVal - 1, sprintf('Peak: %.1f^\\circ', peakAngle), ...
     'FontSize', 10, 'FontWeight', 'bold', 'Color', 'r');

% Save the plot
output_dir = '../results';
if ~exist(output_dir, 'dir')
    mkdir(output_dir);
end
output_path = fullfile(output_dir, 'mvdr_spectrum.png');
saveas(fig, output_path);
close(fig);
fprintf('Plot saved to %s\n', output_path);
