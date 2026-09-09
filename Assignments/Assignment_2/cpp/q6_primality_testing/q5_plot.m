% Read table preserving original headers and string types
opts = detectImportOptions('primality_comparison_results.csv');
opts = setvartype(opts, {'Ground_Truth', 'Fermat_Verdict', 'Fermat_Type', ...
    'Fermat_Correct', 'MR_Verdict', 'MR_Type', 'MR_Correct'}, 'string');
data = readtable('primality_comparison_results.csv', opts);

% Extract metric counts for Fermat Test
f_TP = sum(data.Fermat_Type == "TP");
f_TN = sum(data.Fermat_Type == "TN");
f_FP = sum(startsWith(data.Fermat_Type, "FP"));
f_FN = sum(data.Fermat_Type == "FN");

% Extract metric counts for Miller-Rabin Test
mr_TP = sum(data.MR_Type == "TP");
mr_TN = sum(data.MR_Type == "TN");
mr_FP = sum(startsWith(data.MR_Type, "FP"));
mr_FN = sum(data.MR_Type == "FN");

total_tested = height(data);
total_composites = sum(data.Ground_Truth == "COMPOSITE");

% Derived statistics
f_acc     = (f_TP + f_TN) / total_tested * 100;
mr_acc    = (mr_TP + mr_TN) / total_tested * 100;
f_fp_rate = (f_FP / total_composites) * 100;
mr_fp_rate = (mr_FP / total_composites) * 100;

figure('Name', 'Primality Testing Performance: Fermat vs Miller-Rabin', 'Color', 'w');

%% Subplot 1: Confusion Matrix Comparison (Bar Chart)
subplot(1, 2, 1);
counts = [f_TP,  f_TN,  f_FP,  f_FN; 
    mr_TP, mr_TN, mr_FP, mr_FN];

b = bar(categorical({'Fermat Test', 'Miller-Rabin'}), counts);
b(1).FaceColor = [0.20, 0.60, 0.20]; % TP: Green
b(2).FaceColor = [0.20, 0.40, 0.80]; % TN: Blue
b(3).FaceColor = [0.85, 0.20, 0.20]; % FP: Red (False Detections)
b(4).FaceColor = [0.90, 0.60, 0.00]; % FN: Orange

grid on;
title('Test Verdict Distribution');
ylabel('Count');
legend({'True Positives (TP)', 'True Negatives (TN)', ...
    'False Positives (FP)', 'False Negatives (FN)'}, ...
    'Location', 'northoutside', 'Orientation', 'horizontal');

%% Subplot 2: Accuracy vs. False Detection Rate
subplot(1, 2, 2);
rates = [f_acc,  f_fp_rate; 
    mr_acc, mr_fp_rate];

b2 = bar(categorical({'Fermat Test', 'Miller-Rabin'}), rates);
b2(1).FaceColor = [0.15, 0.65, 0.35]; % Accuracy: Green
b2(2).FaceColor = [0.85, 0.25, 0.25]; % False Detection Rate: Red

grid on;
ylim([0, 105]);
title('Accuracy vs False Positive Rate (k = 1)');
ylabel('Percentage (%)');
legend({'Overall Accuracy', 'False Detection Rate (on Composites)'}, ...
    'Location', 'northoutside', 'Orientation', 'horizontal');