% Read numeric matrices directly (automatically skips header line)
dataLomuto = readmatrix('q8_RandQuickVSQuickLomuto.csv');
dataHoare  = readmatrix('q8_RandQuickVSQuickHoare.csv');

figure('Name', 'Randomized vs Deterministic QuickSort Comparisons', 'Color', 'w');

%% Subplot 1: Lomuto Partitioning
subplot(1, 2, 1);
plot(dataLomuto(:, 1), dataLomuto(:, 2), 'b-', 'LineWidth', 1.8);
hold on;
plot(dataLomuto(:, 1), dataLomuto(:, 3), 'r--', 'LineWidth', 1.8);
hold off;
grid on;
title('Lomuto Partition Scheme');
xlabel('Input Size (n)');
ylabel('Average Comparisons');
legend('Randomized QuickSort', 'Deterministic QuickSort', 'Location', 'northwest');

%% Subplot 2: Hoare Partitioning
subplot(1, 2, 2);
plot(dataHoare(:, 1), dataHoare(:, 2), 'b-', 'LineWidth', 1.8);
hold on;
plot(dataHoare(:, 1), dataHoare(:, 3), 'r--', 'LineWidth', 1.8);
hold off;
grid on;
title('Hoare Partition Scheme');
xlabel('Input Size (n)');
ylabel('Average Comparisons');
legend('Randomized QuickSort', 'Deterministic QuickSort', 'Location', 'northwest');