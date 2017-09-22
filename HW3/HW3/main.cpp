//
//  main.cpp
//  HW3
//
//  Created by Nick Zerbel on 9/21/17.
//  Copyright © 2017 Nicholas Zerbel. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <fstream>
#include "ga.hpp"
#include "eval.hpp"

using namespace std;

int main() {
    ga g; eval ev;
    srand( time(NULL) );
    
    double f_max, f_avg, f_min;
    int generations = 1000; //Number of generations
    int func = 4; //Which function should be evaluated
    int stat_runs = 30; //Number of statistical runs
    int p_size = 80;
    
    ofstream maxdata; maxdata.open("max-fitness.txt");
    ofstream avgdata; avgdata.open("avg-fitness.txt");
    ofstream mindata; mindata.open("min-fitness.txt");
    
    for(int k = 0; k < stat_runs; k++){
        if(func == 1){
            g.create_pop(30, p_size); //(array-size, pop-size)
            ev.set_parameters(30, 10); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < g.pop_size; j++){
                    g.fit_vec.at(j) = ev.function1(g.population.at(j).array);
                }
                g.calculate_prob();
                f_min = *min_element(g.fit_vec.begin(), g.fit_vec.end());
                f_max = *max_element(g.fit_vec.begin(), g.fit_vec.end());
                f_avg = g.f_total/g.pop_size;
                maxdata << f_max << "\t";
                avgdata << f_avg << "\t";
                mindata << f_min << "\t";
                g.crossover();
                g.mutate();
            }
        }
        if(func == 2){
            g.create_pop(24, p_size); //(array-size, pop-size)
            ev.set_parameters(24, 12); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < g.pop_size; j++){
                    g.fit_vec.at(j) = ev.function2(g.population.at(j).array);
                }
                g.calculate_prob();
                f_min = *min_element(g.fit_vec.begin(), g.fit_vec.end());
                f_max = *max_element(g.fit_vec.begin(), g.fit_vec.end());
                f_avg = g.f_total/g.pop_size;
                maxdata << f_max << "\t";
                avgdata << f_avg << "\t";
                mindata << f_min << "\t";
                g.crossover();
                g.mutate();
            }
        }
        if(func == 3){
            g.create_pop(50, p_size); //(array-size, pop-size)
            ev.set_parameters(50, 10); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < g.pop_size; j++){
                    g.fit_vec.at(j) = ev.function3(g.population.at(j).array);
                }
                g.calculate_prob();
                f_min = *min_element(g.fit_vec.begin(), g.fit_vec.end());
                f_max = *max_element(g.fit_vec.begin(), g.fit_vec.end());
                f_avg = g.f_total/g.pop_size;
                maxdata << f_max << "\t";
                avgdata << f_avg << "\t";
                mindata << f_min << "\t";
                g.crossover();
                g.mutate();
            }
        }
        if(func == 4){
            g.create_pop(240, p_size); //(array-size, pop-size)
            ev.set_parameters(240, 8); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < g.pop_size; j++){
                    g.fit_vec.at(j) = ev.function4(g.population.at(j).array);
                }
                g.calculate_prob();
                f_min = *min_element(g.fit_vec.begin(), g.fit_vec.end());
                f_max = *max_element(g.fit_vec.begin(), g.fit_vec.end());
                f_avg = g.f_total/g.pop_size;
                maxdata << f_max << "\t";
                avgdata << f_avg << "\t";
                mindata << f_min << "\t";
                g.crossover();
                g.mutate();
            }
        }

        maxdata << endl; avgdata << endl; mindata << endl;
        g.population.clear();
        g.fit_vec.clear();
        g.new_pop.clear();
        g.p_range.clear();
        g.p_indv.clear();
    }
    
    maxdata.close(); avgdata.close(); mindata.close();
    
    return 0;
}
