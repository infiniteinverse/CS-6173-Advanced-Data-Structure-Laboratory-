% Read numeric data directly (Column 1: Datasize, Column 2: AvgAttempts, Column 3: TheoreticalExpected)
data = readmatrix('q7_majorityElement.csv');

if isempty(data) || size(data, 2) < 3
    error('CSV file is empty or formatted incorrectly. Ensure C++ generated q7_majorityElement.csv');
end

datasize     = data(:, 1);
avgAttempts  = data(:, 2);
theoretical  = data(:, 3);

figure('Name', 'Randomized Majority Element Analysis', 'Color', 'w');

% Plot empirical average attempts
plot(datasize, avgAttempts, 'b.-', 'LineWidth', 1.2, 'MarkerSize', 8);
hold on;

% Plot theoretical expected value (E[X] = 1/p <= 2.0)
plot(datasize, theoretical, 'r--', 'LineWidth', 2.0);
hold off;

grid on;
ylim([1, 3.5]);
title('Randomized Majority Element: Attempts vs Input Size');
xlabel('Data Size (n)');
ylabel('Average Attempts Needed');
legend('Empirical Average Attempts', 'Theoretical Expectation (E[X] \approx 2.0)', ...
    'Location', 'northeast');