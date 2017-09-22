%Nick Zerbel
%CS 776 HW 3
%9/27/2017

close all; clear all; clc;
format compact;

maxdata = load('max-fitness.txt');
avgdata = load('avg-fitness.txt');
mindata = load('min-fitness.txt');
pop_size = 80;

maxfitness = mean(maxdata);
avgfitness = mean(avgdata);
minfitness = mean(mindata);

x = pop_size*[0:999];

plot(x, maxfitness)
%ylim([0 80])
%xlim([0 500])
xlabel('Number of Evaluations')
ylabel('Fitness')

hold on
plot(x, avgfitness)
plot(x, minfitness)
legend('max', 'avg', 'min')