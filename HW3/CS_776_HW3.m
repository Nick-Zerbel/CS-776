%Nick Zerbel
%CS 776 HW 3
%9/27/2017

close all; clear all; clc;
format compact;

pop_size = 50;
x = pop_size*[0:99];

%Graph 1 Pcross = 0.67 Pmut = 0.0001
g1max = load('g1_max.txt');
g1avg = load('g1_avg.txt');
g1min = load('g1_min.txt');

maxfitness1 = mean(g1max);
avgfitness1 = mean(g1avg);
minfitness1 = mean(g1min);

figure()
plot(x, maxfitness1)
xlabel('Number of Evaluations')
ylabel('Fitness')
title('Pcross = 0.67 Pmut = 0.0001')

hold on
plot(x, avgfitness1)
plot(x, minfitness1)
legend('max', 'avg', 'min')

%Graph 2 Pcross = 0.67 Pmut = 0.001
g2max = load('g2_max.txt');
g2avg = load('g2_avg.txt');
g2min = load('g2_min.txt');

maxfitness2 = mean(g2max);
avgfitness2 = mean(g2avg);
minfitness2 = mean(g2min);

figure()
plot(x, maxfitness2)
xlabel('Number of Evaluations')
ylabel('Fitness')
title('Pcross = 0.67 Pmut = 0.001')

hold on
plot(x, avgfitness2)
plot(x, minfitness2)
legend('max', 'avg', 'min')

%Graph 3 Pcross = 0.67 Pmut = 0.01
g3max = load('g3_max.txt');
g3avg = load('g3_avg.txt');
g3min = load('g3_min.txt');

maxfitness3 = mean(g3max);
avgfitness3 = mean(g3avg);
minfitness3 = mean(g3min);

figure()
plot(x, maxfitness3)
xlabel('Number of Evaluations')
ylabel('Fitness')
title('Pcross = 0.67 Pmut = 0.01')

hold on
plot(x, avgfitness3)
plot(x, minfitness3)
legend('max', 'avg', 'min')

%Graph 4 Pcross = 0.2 Pmut = 0.0001
g4max = load('g4_max.txt');
g4avg = load('g4_avg.txt');
g4min = load('g4_min.txt');

maxfitness4 = mean(g4max);
avgfitness4 = mean(g4avg);
minfitness4 = mean(g4min);

figure()
plot(x, maxfitness4)
xlabel('Number of Evaluations')
ylabel('Fitness')
title('Pcross = 0.2 Pmut = 0.0001')

hold on
plot(x, avgfitness4)
plot(x, minfitness4)
legend('max', 'avg', 'min')

%Graph 5 Pcross = 0.2 Pmut = 0.001
g5max = load('g5_max.txt');
g5avg = load('g5_avg.txt');
g5min = load('g5_min.txt');

maxfitness5 = mean(g5max);
avgfitness5 = mean(g5avg);
minfitness5 = mean(g5min);

figure()
plot(x, maxfitness5)
xlabel('Number of Evaluations')
ylabel('Fitness')
title('Pcross = 0.2 Pmut = 0.001')

hold on
plot(x, avgfitness5)
plot(x, minfitness5)
legend('max', 'avg', 'min')

%Graph 6 Pcross = 0.2 Pmut = 0.01
g6max = load('g6_max.txt');
g6avg = load('g6_avg.txt');
g6min = load('g6_min.txt');

maxfitness6 = mean(g6max);
avgfitness6 = mean(g6avg);
minfitness6 = mean(g6min);

figure()
plot(x, maxfitness6)
xlabel('Number of Evaluations')
ylabel('Fitness')
title('Pcross = 0.2 Pmut = 0.01')

hold on
plot(x, avgfitness6)
plot(x, minfitness6)
legend('max', 'avg', 'min')

%Graph 7 Pcross = 0.99 Pmut = 0.0001
g7max = load('g7_max.txt');
g7avg = load('g7_avg.txt');
g7min = load('g7_min.txt');

maxfitness7 = mean(g7max);
avgfitness7 = mean(g7avg);
minfitness7 = mean(g7min);

figure()
plot(x, maxfitness7)
xlabel('Number of Evaluations')
ylabel('Fitness')
title('Pcross = 0.99 Pmut = 0.0001')

hold on
plot(x, avgfitness7)
plot(x, minfitness7)
legend('max', 'avg', 'min')

%Graph 8 Pcross = 0.99 Pmut = 0.001
g8max = load('g8_max.txt');
g8avg = load('g8_avg.txt');
g8min = load('g8_min.txt');

maxfitness8 = mean(g8max);
avgfitness8 = mean(g8avg);
minfitness8 = mean(g8min);

figure()
plot(x, maxfitness8)
xlabel('Number of Evaluations')
ylabel('Fitness')
title('Pcross = 0.99 Pmut = 0.001')

hold on
plot(x, avgfitness8)
plot(x, minfitness8)
legend('max', 'avg', 'min')

%Graph 9 Pcross = 0.99 Pmut = 0.01
g9max = load('g9_max.txt');
g9avg = load('g9_avg.txt');
g9min = load('g9_min.txt');

maxfitness9 = mean(g9max);
avgfitness9 = mean(g9avg);
minfitness9 = mean(g9min);

figure()
plot(x, maxfitness9)
xlabel('Number of Evaluations')
ylabel('Fitness')
title('Pcross = 0.99 Pmut = 0.01')

hold on
plot(x, avgfitness9)
plot(x, minfitness9)
legend('max', 'avg', 'min')