clc;
clear;
close all;

%% Insertion Sort vs QuickSort

data = readtable('iqSortComparison.csv');

inputSize = data{:, 1};
compISort = data{:, 2};
compQSort = data{:, 3};

figure;

plot(inputSize, compISort, 'LineWidth', 1.5);
hold on;

plot(inputSize, compQSort, 'LineWidth', 1.5);

xlabel('Input Size');
ylabel('Number of Comparisons');
title('Insertion Sort vs QuickSort');

legend('Insertion Sort', ...
    'QuickSort', ...
    'Location', 'northwest');

grid on;




%% QuickSort vs Hybrid QuickSort

data = readtable('qhSortComparison.csv');

inputSize = data{:, 1};
compQSort = data{:, 2};
compHQSort = data{:, 3};

figure;

plot(inputSize, compQSort, 'LineWidth', 1.5);
hold on;

plot(inputSize, compHQSort, 'LineWidth', 1.5);

xlabel('Input Size');
ylabel('Number of Comparisons');
title('QuickSort vs Hybrid QuickSort');

legend('QuickSort', ...
    'Hybrid QuickSort', ...
    'Location', 'northwest');

grid on;