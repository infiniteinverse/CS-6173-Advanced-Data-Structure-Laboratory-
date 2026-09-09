%% 1. Load Data
sm_data = readtable('monte_carlo_sample_mean.csv');
hm_data = readtable('monte_carlo_hit_or_miss.csv');

exact_pi = pi;

%% 2. Figure 1: Convergence Comparison
figure('Name', 'Monte Carlo Convergence', 'Color', 'w', 'Position', [100, 100, 900, 450]);

plot(sm_data.Iteration, sm_data.Integral_Estimate, 'b-', 'LineWidth', 1.2, 'DisplayName', 'Sample Mean');
hold on;
plot(hm_data.Iteration, hm_data.Integral_Estimate, 'r-', 'LineWidth', 1.2, 'DisplayName', 'Hit-or-Miss');
yline(exact_pi, 'k--', 'LineWidth', 1.8, 'DisplayName', sprintf('Exact Value (\\pi \\approx %.4f)', exact_pi));

grid on;
xlabel('Iteration (N)', 'FontSize', 11);
ylabel('Integral Estimate', 'FontSize', 11);
title('Monte Carlo Integration: Convergence vs. Iterations', 'FontSize', 13);
legend('Location', 'northeast', 'FontSize', 10);
xlim([1, max(sm_data.Iteration)]);
ylim([exact_pi - 0.5, exact_pi + 0.5]);

%% 3. Figure 2: Visualizing the Two Methods
figure('Name', 'Method Visualizations', 'Color', 'w', 'Position', [100, 100, 1100, 480]);

% --- Left Subplot: Hit-or-Miss Sampling Area ---
subplot(1, 2, 1);
hits = hm_data.Is_Hit == 1;
misses = hm_data.Is_Hit == 0;

% Plot points (subsampling to max 3000 points if N is large for faster rendering)
max_pts = min(height(hm_data), 3000);
scatter(hm_data.X(hits(1:max_pts)), hm_data.Y(hits(1:max_pts)), 8, ...
    [0.2, 0.7, 0.3], 'filled', 'DisplayName', 'Hit (y \le f(x))');
hold on;
scatter(hm_data.X(misses(1:max_pts)), hm_data.Y(misses(1:max_pts)), 8, ...
    [0.85, 0.3, 0.3], 'filled', 'DisplayName', 'Miss (y > f(x))');

% Plot true boundary curve f(x) = sqrt(4 - x^2)
x_curve = linspace(0, 2, 200);
y_curve = sqrt(4 - x_curve.^2);
plot(x_curve, y_curve, 'k-', 'LineWidth', 2, 'DisplayName', 'f(x) = \surd(4 - x^2)');

grid on;
axis equal;
xlim([0, 2]);
ylim([0, 2]);
xlabel('x');
ylabel('y');
title('Hit-or-Miss Method: 2D Domain Sampling');
legend('Location', 'southwest', 'FontSize', 9);

% --- Right Subplot: Sample Mean Sampling ---
subplot(1, 2, 2);
plot(x_curve, y_curve, 'k-', 'LineWidth', 2, 'DisplayName', 'f(x) = \surd(4 - x^2)');
hold on;

% Sample points along the curve
sm_pts = min(height(sm_data), 200);
scatter(sm_data.X(1:sm_pts), sm_data.F_X(1:sm_pts), 14, ...
    'b', 'filled', 'DisplayName', 'Sampled f(x_i)');
stem(sm_data.X(1:sm_pts), sm_data.F_X(1:sm_pts), 'Color', [0.7 0.7 0.9], ...
    'Marker', 'none', 'HandleVisibility', 'off');

grid on;
xlim([0, 2]);
ylim([0, 2.2]);
xlabel('x');
ylabel('f(x)');
title('Sample Mean Method: 1D Function Evaluations');
legend('Location', 'southwest', 'FontSize', 9);