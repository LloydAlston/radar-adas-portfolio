scanAngles = -90:0.5:90;
Y = out.simout.Data(:,1,2);
plot(scanAngles, Y);
xlabel('Angle (degrees)');
ylabel('MVDR Spectrum (dB)');
grid on;

[peakVal, peakIdx] = max(Y);
fprintf('Peak found at %.1f degrees, value = %.2f\n', scanAngles(peakIdx), peakVal);