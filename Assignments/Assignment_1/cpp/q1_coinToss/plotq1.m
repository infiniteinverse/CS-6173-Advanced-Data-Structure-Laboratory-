clear;
clc;
close all;

%% =========================
% ONE COIN
% ==========================

oneCoin = readtable("oneCoinToss.csv");

figure('Name', 'One Coin Toss', 'NumberTitle', 'off');

plot(oneCoin.Toss, oneCoin.HeadProbability, ...
    'LineWidth', 1.5, ...
    'DisplayName', 'Heads');

hold on;

plot(oneCoin.Toss, oneCoin.TailProbability, ...
    'LineWidth', 1.5, ...
    'DisplayName', 'Tails');

% Theoretical probability
yline(0.5, '--', ...
    'DisplayName', 'Theoretical = 0.5');

xlabel('Number of Tosses');
ylabel('Probability');
title('One Coin Toss');

legend('Location', 'best');
grid on;

hold off;


%% =========================
% TWO COINS
% ==========================

twoCoin = readtable("twoCoinToss.csv");

figure('Name', 'Two Coin Toss', 'NumberTitle', 'off');

% Columns 6-9 are P(HH), P(HT), P(TH), P(TT)

plot(twoCoin.Toss, twoCoin{:,6}, ...
    'LineWidth', 1.5, ...
    'DisplayName', 'P(HH)');

hold on;

plot(twoCoin.Toss, twoCoin{:,7}, ...
    'LineWidth', 1.5, ...
    'DisplayName', 'P(HT)');

plot(twoCoin.Toss, twoCoin{:,8}, ...
    'LineWidth', 1.5, ...
    'DisplayName', 'P(TH)');

plot(twoCoin.Toss, twoCoin{:,9}, ...
    'LineWidth', 1.5, ...
    'DisplayName', 'P(TT)');

% Theoretical probability
yline(0.25, '--', ...
    'DisplayName', 'Theoretical = 0.25');

xlabel('Number of Tosses');
ylabel('Probability');

title('Two Coin Toss');

legend('Location', 'best');

grid on;

hold off;