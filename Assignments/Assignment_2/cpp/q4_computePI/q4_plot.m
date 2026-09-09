%% 1. Read Data Safely
filename = 'PIEstimation.csv';

% If reading full 10M rows, use textscan for fast parsing and low memory
fprintf('Reading %s...\n', filename);
fid = fopen(filename, 'r');
if fid == -1
    error('Could not open file %s', filename);
end

% Read header line
fgetl(fid);

% Format matches: Iteration, Pi_Est, (X, Y), Exact_Pi, Difference
% Format spec: %f,%f,(%f,%f),%f,%f
data = textscan(fid, '%f %f (%f %f) %f %f', 'Delimiter', ',');
fclose(fid);

iter      = data{1};
pi_est    = data{2};
x_coords  = data{3};
y_coords  = data{4};
exact_pi  = data{5}(1);
error_val = data{6};

total_pts = length(iter);
fprintf('Loaded %d points successfully.\n', total_pts);

%% 2. Figure 1: Convergence and Absolute Error
figure('Name', 'Monte Carlo Pi Convergence', 'Color', 'w', 'Position', [100, 100, 1000, 450]);

% --- Convergence Curve ---
subplot(1, 2, 1);
% Downsample for smooth plotting if N is large
step_size = max(1, floor(total_pts / 50000));
idx_sub = 1:step_size:total_pts;

plot(iter(idx_sub), pi_est(idx_sub), 'b-', 'LineWidth', 1.1, 'DisplayName', 'Estimate');
hold on;
yline(exact_pi, 'r--', 'LineWidth', 1.5, 'DisplayName', sprintf('Exact \\pi \\approx %.5f', exact_pi));
grid on;
xlabel('Iteration (N)', 'FontSize', 10);
ylabel('Value of \pi', 'FontSize', 10);
title('Estimate Convergence vs. Iterations', 'FontSize', 11);
legend('Location', 'northeast');
xlim([1, total_pts]);
ylim([exact_pi - 0.2, exact_pi + 0.2]);

% --- Error on Log-Log Scale ---
subplot(1, 2, 2);
loglog(iter(idx_sub), error_val(idx_sub), 'Color', [0.3 0.3 0.8], 'LineWidth', 1.0, 'DisplayName', '|Estimate - \pi|');
hold on;

% Theoretical O(1/sqrt(N)) rate line
ref_n = iter(idx_sub);
ref_bound = 1.0 ./ sqrt(ref_n);
loglog(ref_n, ref_bound, 'k--', 'LineWidth', 1.2, 'DisplayName', 'Theoretical O(1/\surd N)');

grid on;
xlabel('Iteration (N, log scale)', 'FontSize', 10);
ylabel('Absolute Error (log scale)', 'FontSize', 10);
title('Convergence Rate (|Error|)', 'FontSize', 11);
legend('Location', 'northeast');

%% 3. Figure 2: Unit Quarter-Circle Scatter Plot
figure('Name', 'Quarter Circle Sampling', 'Color', 'w', 'Position', [150, 150, 550, 520]);

% Subsample max 8000 points to keep the scatter plot responsive
scatter_pts = min(total_pts, 8000);
x_sub = x_coords(1:scatter_pts);
y_sub = y_coords(1:scatter_pts);

inside = (x_sub.^2 + y_sub.^2 <= 1.0);

scatter(x_sub(inside), y_sub(inside), 10, [0.2 0.7 0.3], 'filled', 'DisplayName', 'Inside Circle');
hold on;
scatter(x_sub(~inside), y_sub(~inside), 10, [0.85 0.3 0.3], 'filled', 'DisplayName', 'Outside Circle');

% Boundary: x^2 + y^2 = 1
theta = linspace(0, pi/2, 200);
plot(cos(theta), sin(theta), 'k-', 'LineWidth', 2, 'DisplayName', 'x^2 + y^2 = 1');

axis equal;
xlim([0, 1]);
ylim([0, 1]);
grid on;
xlabel('x');
ylabel('y');
title(sprintf('Monte Carlo Quarter-Circle (First %d Points)', scatter_pts), 'FontSize', 11);
legend('Location', 'southwest');