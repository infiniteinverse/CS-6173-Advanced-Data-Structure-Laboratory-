% Read the CSV files from current directory
dataLomuto = readtable('q8_RandQuickVSQuickLomuto.csv');
dataHoare  = readtable('q8_RandQuickVSQuickHoare.csv');

figure('Name', 'Randomized vs Deterministic QuickSort Comparisons', 'Color', 'w');

%% Subplot 1: Lomuto Partitioning
subplot(1, 2, 1);
plot(dataLomuto.Datasize, dataLomuto.RandQuickComp, 'b-', 'LineWidth', 1.8);
hold on;
plot(dataLomuto.Datasize, dataLomuto.QuickComp, 'r--', 'LineWidth', 1.8);
hold off;
grid on;
title('Lomuto Partition Scheme');
xlabel('Input Size (n)');
ylabel('Average Comparisons');
legend('Randomized QuickSort', 'Deterministic QuickSort', 'Location', 'northwest');

%% Subplot 2: Hoare Partitioning
subplot(1, 2, 2);
plot(dataHoare.Datasize, dataHoare.RandQuickComp, 'b-', 'LineWidth', 1.8);
hold on;
plot(dataHoare.Datasize, dataHoare.QuickComp, 'r--', 'LineWidth', 1.8);
hold off;
grid on;
title('Hoare Partition Scheme');
xlabel('Input Size (n)');
ylabel('Average Comparisons');
legend('Randomized QuickSort', 'Deterministic QuickSort', 'Location', 'northwest');