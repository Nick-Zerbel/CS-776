%Nick Zerbel
%CS 776 HW 4
%October 11, 2017

close all; clear all; clc;
format compact

pop_size = 1000;
stat_runs = 30; %Number of statistical runs
gen = 100; %Number of generations
n_cities = 52; %Number of cities
city = 'L318'; %B014, B052, E051, E076, L105, L318 are the options
n_gens = [1:1:gen];

max = load('max_fitness.txt');
avg = load('avg_fitness.txt');
min = load('min_fitness.txt');

max_avg(1:gen) = 0;
avg_avg(1:gen) = 0;
min_avg(1:gen) = 0;

for i = 1:gen
    sum1 = 0;
    sum2 = 0;
    sum3 = 0;
    for j = 1:stat_runs
        sum1 = sum1 + max(j,i);
        sum2 = sum2 + avg(j,i);
        sum3 = sum3 + min(j,i);
    end
        
    max_avg(i) = sum1/stat_runs;
    avg_avg(i) = sum2/stat_runs;
    min_avg(i) = sum3/stat_runs;
end

%Calculate Performance Characteristics
%Optimal Tour Lengths
b14 = 30;
b52 = 7542;
e51 = 426;
e76 = 538;
l105 = 14379;
l318 = 42029;

best_fits = load('best_fitness.txt');

if city == 'B014'
    t = 'Burma14 Avg. Fitness vs. Evaluations';
    quality = 100*(b14/min_avg(gen))
    count = 0;
    for i = 1:stat_runs
        q = 100*(b14/best_fits(i));
        if q >= quality
            count = count + 1;
        end
    end
    reliability = 100*(count/stat_runs)
    for i = 1:gen
        q = 100*(b14/min_avg(i));
        if q >= quality
            speed = i
            break
        end
    end
end

if city == 'B052'
    t = 'Berlin52 Avg. Fitness vs. Evaluations';
    quality = 100*(b52/min_avg(gen))
    count = 0;
    for i = 1:stat_runs
        q = 100*(b52/best_fits(i));
        if q >= quality
            count = count + 1;
        end
    end
    reliability = 100*(count/stat_runs)
    for i = 1:gen
        q = 100*(b52/min_avg(i));
        if q >= quality
            speed = i
            break
        end
    end
end

if city == 'E051'
    t = 'Eli51 Avg. Fitness vs. Evaluations';
    quality = 100*(e51/min_avg(gen))
    count = 0;
    for i = 1:stat_runs
        q = 100*(e51/best_fits(i));
        if q >= quality
            count = count + 1;
        end
    end
    reliability = 100*(count/stat_runs)
    for i = 1:gen
        q = 100*(e51/min_avg(i));
        if q >= quality
            speed = i
            break
        end
    end
end

if city == 'E076'
    t = 'Eli76 Avg. Fitness vs. Evaluations';
    quality = 100*(e76/min_avg(gen))
    count = 0;
    for i = 1:stat_runs
        q = 100*(e76/best_fits(i));
        if q >= quality
            count = count + 1;
        end
    end
    reliability = 100*(count/stat_runs)
    for i = 1:gen
        q = 100*(e76/min_avg(i));
        if q >= quality
            speed = i
            break
        end
    end
end

if city == 'L105'
    t = 'Lin105 Avg. Fitness vs. Evaluations';
    quality = 100*(l105/min_avg(gen))
    count = 0;
    for i = 1:stat_runs
        q = 100*(l105/best_fits(i));
        if q >= quality
            count = count + 1;
        end
    end
    reliability = 100*(count/stat_runs)
    for i = 1:gen
        q = 100*(l105/min_avg(i));
        if q >= quality
            speed = i
            break
        end
    end
end

if city == 'L318'
    t = 'Lin318 Avg. Fitness vs. Evaluations';
    quality = 100*(l318/min_avg(gen))
    count = 0;
    for i = 1:stat_runs
        q = 100*(l318/best_fits(i));
        if q >= quality
            count = count + 1;
        end
    end
    reliability = 100*(count/stat_runs)
    for i = 1:gen
        q = 100*(l318/min_avg(i));
        if q >= quality
            speed = i
            break
        end
    end
end

%Graph Fitness vs Generations
plot(pop_size*n_gens, min_avg)
xlabel('Number of Evaluations')
ylabel('Fitness')
title(t)
hold on
plot(pop_size*n_gens,avg_avg)
legend('Min', 'Avg')