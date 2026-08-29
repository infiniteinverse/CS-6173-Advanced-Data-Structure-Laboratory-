% Read CSV file
data = readtable('iqSortComparisonsSmallInputSize.csv');

% Extract columns
inputSize = data.InputSize;
iSortComp = data.("Comp_ISort_");
qSortComp = data.("Comp_QSort_");

% Plot
figure;

plot(inputSize, iSortComp, '-o', 'LineWidth', 1.5);
hold on;

plot(inputSize, qSortComp, '-s', 'LineWidth', 1.5);

% Labels
xlabel('Input Size');
ylabel('Number of Comparisons');
title('Insertion Sort vs Quick Sort - Highly Inversional Input');

% Legend
legend('Insertion Sort', 'Quick Sort', 'Location', 'northwest');

% Grid
grid on;

hold off;