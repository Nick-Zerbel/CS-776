//
//  main.cpp
//  HW3
//
//  Created by Nicholas Zerbel on 9/21/17.
//  Copyright © 2017 Nicholas Zerbel. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <fstream>
#include "ga.hpp"
#include "eval.hpp"

using namespace std;

void graph_1(ga *gp, eval *evp, int f, int gen, int ps){
    double f_max, f_avg, f_min;
    int generations = gen; //Number of generations
    int stat_runs = 30; //Number of statistical runs
    int p_size = ps; //Population size
    gp->p_cross = 0.67;
    gp->p_mut = 0.0001;
    
    ofstream maxdata1; maxdata1.open("g1_max.txt");
    ofstream avgdata1; avgdata1.open("g1_avg.txt");
    ofstream mindata1; mindata1.open("g1_min.txt");
    
    for(int k = 0; k < stat_runs; k++){
        if(f == 1){ //f(x) = sum(x^2) [1,3] for -5.12 <= x <= 5.12
            gp->create_pop(30, p_size); //(array-size, pop-size)
            evp->set_parameters(30, 10); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < gp->pop_size; j++){
                    gp->fit_vec.at(j) = evp->function1(gp->population.at(j).array);
                }
                gp->calculate_prob();
                f_min = *min_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_max = *max_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_avg = gp->f_total/gp->pop_size;
                maxdata1 << f_max << "\t";
                avgdata1 << f_avg << "\t";
                mindata1 << f_min << "\t";
                gp->crossover();
                gp->mutate();
            }
        }
        if(f == 2){ //f(x) = 100*(x1^2-x2)^2 + (1-x1)^2
            gp->create_pop(24, p_size); //(array-size, pop-size)
            evp->set_parameters(24, 12); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < gp->pop_size; j++){
                    gp->fit_vec.at(j) = evp->function2(gp->population.at(j).array);
                }
                gp->calculate_prob();
                f_min = *min_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_max = *max_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_avg = gp->f_total/gp->pop_size;
                maxdata1 << f_max << "\t";
                avgdata1 << f_avg << "\t";
                mindata1 << f_min << "\t";
                gp->crossover();
                gp->mutate();
            }
        }
        if(f == 3){ //f(x) = sum(integer(x)) [1,5]
            gp->create_pop(50, p_size); //(array-size, pop-size)
            evp->set_parameters(50, 10); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < gp->pop_size; j++){
                    gp->fit_vec.at(j) = evp->function3(gp->population.at(j).array);
                }
                gp->calculate_prob();
                f_min = *min_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_max = *max_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_avg = gp->f_total/gp->pop_size;
                maxdata1 << f_max << "\t";
                avgdata1 << f_avg << "\t";
                mindata1 << f_min << "\t";
                gp->crossover();
                gp->mutate();
            }
        }
        if(f == 4){ //f(x) = sum(i*x^4) [1,30] + gauss(0,1)
            gp->create_pop(240, p_size); //(array-size, pop-size)
            evp->set_parameters(240, 8); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < gp->pop_size; j++){
                    gp->fit_vec.at(j) = evp->function4(gp->population.at(j).array);
                }
                gp->calculate_prob();
                f_min = *min_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_max = *max_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_avg = gp->f_total/gp->pop_size;
                maxdata1 << f_max << "\t";
                avgdata1 << f_avg << "\t";
                mindata1 << f_min << "\t";
                gp->crossover();
                gp->mutate();
            }
        }
        
        maxdata1 << endl; avgdata1 << endl; mindata1 << endl;
        gp->population.clear();
        gp->fit_vec.clear();
        gp->new_pop.clear();
        gp->p_range.clear();
        gp->p_indv.clear();
    }
    
    maxdata1.close(); avgdata1.close(); mindata1.close();
}

void graph_2(ga *gp, eval *evp, int f, int gen, int ps){
    double f_max, f_avg, f_min;
    int generations = gen; //Number of generations
    int stat_runs = 30; //Number of statistical runs
    int p_size = ps; //Population size
    gp->p_cross = 0.67;
    gp->p_mut = 0.001;
    
    ofstream maxdata2; maxdata2.open("g2_max.txt");
    ofstream avgdata2; avgdata2.open("g2_avg.txt");
    ofstream mindata2; mindata2.open("g2_min.txt");
    
    for(int k = 0; k < stat_runs; k++){
        if(f == 1){ //f(x) = sum(x^2) [1,3] for -5.12 <= x <= 5.12
            gp->create_pop(30, p_size); //(array-size, pop-size)
            evp->set_parameters(30, 10); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < gp->pop_size; j++){
                    gp->fit_vec.at(j) = evp->function1(gp->population.at(j).array);
                }
                gp->calculate_prob();
                f_min = *min_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_max = *max_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_avg = gp->f_total/gp->pop_size;
                maxdata2 << f_max << "\t";
                avgdata2 << f_avg << "\t";
                mindata2 << f_min << "\t";
                gp->crossover();
                gp->mutate();
            }
        }
        if(f == 2){ //f(x) = 100*(x1^2-x2)^2 + (1-x1)^2
            gp->create_pop(24, p_size); //(array-size, pop-size)
            evp->set_parameters(24, 12); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < gp->pop_size; j++){
                    gp->fit_vec.at(j) = evp->function2(gp->population.at(j).array);
                }
                gp->calculate_prob();
                f_min = *min_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_max = *max_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_avg = gp->f_total/gp->pop_size;
                maxdata2 << f_max << "\t";
                avgdata2 << f_avg << "\t";
                mindata2 << f_min << "\t";
                gp->crossover();
                gp->mutate();
            }
        }
        if(f == 3){ //f(x) = sum(integer(x)) [1,5]
            gp->create_pop(50, p_size); //(array-size, pop-size)
            evp->set_parameters(50, 10); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < gp->pop_size; j++){
                    gp->fit_vec.at(j) = evp->function3(gp->population.at(j).array);
                }
                gp->calculate_prob();
                f_min = *min_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_max = *max_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_avg = gp->f_total/gp->pop_size;
                maxdata2 << f_max << "\t";
                avgdata2 << f_avg << "\t";
                mindata2 << f_min << "\t";
                gp->crossover();
                gp->mutate();
            }
        }
        if(f == 4){ //f(x) = sum(i*x^4) [1,30] + gauss(0,1)
            gp->create_pop(240, p_size); //(array-size, pop-size)
            evp->set_parameters(240, 8); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < gp->pop_size; j++){
                    gp->fit_vec.at(j) = evp->function4(gp->population.at(j).array);
                }
                gp->calculate_prob();
                f_min = *min_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_max = *max_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_avg = gp->f_total/gp->pop_size;
                maxdata2 << f_max << "\t";
                avgdata2 << f_avg << "\t";
                mindata2 << f_min << "\t";
                gp->crossover();
                gp->mutate();
            }
        }
        
        maxdata2 << endl; avgdata2 << endl; mindata2 << endl;
        gp->population.clear();
        gp->fit_vec.clear();
        gp->new_pop.clear();
        gp->p_range.clear();
        gp->p_indv.clear();
    }
    
    maxdata2.close(); avgdata2.close(); mindata2.close();
}

void graph_3(ga *gp, eval *evp, int f, int gen, int ps){
    double f_max, f_avg, f_min;
    int generations = gen; //Number of generations
    int stat_runs = 30; //Number of statistical runs
    int p_size = ps; //Population size
    gp->p_cross = 0.67;
    gp->p_mut = 0.01;
    
    ofstream maxdata3; maxdata3.open("g3_max.txt");
    ofstream avgdata3; avgdata3.open("g3_avg.txt");
    ofstream mindata3; mindata3.open("g3_min.txt");
    
    for(int k = 0; k < stat_runs; k++){
        if(f == 1){ //f(x) = sum(x^2) [1,3] for -5.12 <= x <= 5.12
            gp->create_pop(30, p_size); //(array-size, pop-size)
            evp->set_parameters(30, 10); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < gp->pop_size; j++){
                    gp->fit_vec.at(j) = evp->function1(gp->population.at(j).array);
                }
                gp->calculate_prob();
                f_min = *min_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_max = *max_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_avg = gp->f_total/gp->pop_size;
                maxdata3 << f_max << "\t";
                avgdata3 << f_avg << "\t";
                mindata3 << f_min << "\t";
                gp->crossover();
                gp->mutate();
            }
        }
        if(f == 2){ //f(x) = 100*(x1^2-x2)^2 + (1-x1)^2
            gp->create_pop(24, p_size); //(array-size, pop-size)
            evp->set_parameters(24, 12); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < gp->pop_size; j++){
                    gp->fit_vec.at(j) = evp->function2(gp->population.at(j).array);
                }
                gp->calculate_prob();
                f_min = *min_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_max = *max_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_avg = gp->f_total/gp->pop_size;
                maxdata3 << f_max << "\t";
                avgdata3 << f_avg << "\t";
                mindata3 << f_min << "\t";
                gp->crossover();
                gp->mutate();
            }
        }
        if(f == 3){ //f(x) = sum(integer(x)) [1,5]
            gp->create_pop(50, p_size); //(array-size, pop-size)
            evp->set_parameters(50, 10); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < gp->pop_size; j++){
                    gp->fit_vec.at(j) = evp->function3(gp->population.at(j).array);
                }
                gp->calculate_prob();
                f_min = *min_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_max = *max_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_avg = gp->f_total/gp->pop_size;
                maxdata3 << f_max << "\t";
                avgdata3 << f_avg << "\t";
                mindata3 << f_min << "\t";
                gp->crossover();
                gp->mutate();
            }
        }
        if(f == 4){ //f(x) = sum(i*x^4) [1,30] + gauss(0,1)
            gp->create_pop(240, p_size); //(array-size, pop-size)
            evp->set_parameters(240, 8); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < gp->pop_size; j++){
                    gp->fit_vec.at(j) = evp->function4(gp->population.at(j).array);
                }
                gp->calculate_prob();
                f_min = *min_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_max = *max_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_avg = gp->f_total/gp->pop_size;
                maxdata3 << f_max << "\t";
                avgdata3 << f_avg << "\t";
                mindata3 << f_min << "\t";
                gp->crossover();
                gp->mutate();
            }
        }
        
        maxdata3 << endl; avgdata3 << endl; mindata3 << endl;
        gp->population.clear();
        gp->fit_vec.clear();
        gp->new_pop.clear();
        gp->p_range.clear();
        gp->p_indv.clear();
    }
    
    maxdata3.close(); avgdata3.close(); mindata3.close();
}

void graph_4(ga *gp, eval *evp, int f, int gen, int ps){
    double f_max, f_avg, f_min;
    int generations = gen; //Number of generations
    int stat_runs = 30; //Number of statistical runs
    int p_size = ps; //Population size
    gp->p_cross = 0.2;
    gp->p_mut = 0.0001;
    
    ofstream maxdata4; maxdata4.open("g4_max.txt");
    ofstream avgdata4; avgdata4.open("g4_avg.txt");
    ofstream mindata4; mindata4.open("g4_min.txt");
    
    for(int k = 0; k < stat_runs; k++){
        if(f == 1){ //f(x) = sum(x^2) [1,3] for -5.12 <= x <= 5.12
            gp->create_pop(30, p_size); //(array-size, pop-size)
            evp->set_parameters(30, 10); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < gp->pop_size; j++){
                    gp->fit_vec.at(j) = evp->function1(gp->population.at(j).array);
                }
                gp->calculate_prob();
                f_min = *min_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_max = *max_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_avg = gp->f_total/gp->pop_size;
                maxdata4 << f_max << "\t";
                avgdata4 << f_avg << "\t";
                mindata4 << f_min << "\t";
                gp->crossover();
                gp->mutate();
            }
        }
        if(f == 2){ //f(x) = 100*(x1^2-x2)^2 + (1-x1)^2
            gp->create_pop(24, p_size); //(array-size, pop-size)
            evp->set_parameters(24, 12); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < gp->pop_size; j++){
                    gp->fit_vec.at(j) = evp->function2(gp->population.at(j).array);
                }
                gp->calculate_prob();
                f_min = *min_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_max = *max_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_avg = gp->f_total/gp->pop_size;
                maxdata4 << f_max << "\t";
                avgdata4 << f_avg << "\t";
                mindata4 << f_min << "\t";
                gp->crossover();
                gp->mutate();
            }
        }
        if(f == 3){ //f(x) = sum(integer(x)) [1,5]
            gp->create_pop(50, p_size); //(array-size, pop-size)
            evp->set_parameters(50, 10); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < gp->pop_size; j++){
                    gp->fit_vec.at(j) = evp->function3(gp->population.at(j).array);
                }
                gp->calculate_prob();
                f_min = *min_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_max = *max_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_avg = gp->f_total/gp->pop_size;
                maxdata4 << f_max << "\t";
                avgdata4 << f_avg << "\t";
                mindata4 << f_min << "\t";
                gp->crossover();
                gp->mutate();
            }
        }
        if(f == 4){ //f(x) = sum(i*x^4) [1,30] + gauss(0,1)
            gp->create_pop(240, p_size); //(array-size, pop-size)
            evp->set_parameters(240, 8); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < gp->pop_size; j++){
                    gp->fit_vec.at(j) = evp->function4(gp->population.at(j).array);
                }
                gp->calculate_prob();
                f_min = *min_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_max = *max_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_avg = gp->f_total/gp->pop_size;
                maxdata4 << f_max << "\t";
                avgdata4 << f_avg << "\t";
                mindata4 << f_min << "\t";
                gp->crossover();
                gp->mutate();
            }
        }
        
        maxdata4 << endl; avgdata4 << endl; mindata4 << endl;
        gp->population.clear();
        gp->fit_vec.clear();
        gp->new_pop.clear();
        gp->p_range.clear();
        gp->p_indv.clear();
    }
    
    maxdata4.close(); avgdata4.close(); mindata4.close();
}

void graph_5(ga *gp, eval *evp, int f, int gen, int ps){
    double f_max, f_avg, f_min;
    int generations = gen; //Number of generations
    int stat_runs = 30; //Number of statistical runs
    int p_size = ps; //Population size
    gp->p_cross = 0.2;
    gp->p_mut = 0.001;
    
    ofstream maxdata5; maxdata5.open("g5_max.txt");
    ofstream avgdata5; avgdata5.open("g5_avg.txt");
    ofstream mindata5; mindata5.open("g5_min.txt");
    
    for(int k = 0; k < stat_runs; k++){
        if(f == 1){ //f(x) = sum(x^2) [1,3] for -5.12 <= x <= 5.12
            gp->create_pop(30, p_size); //(array-size, pop-size)
            evp->set_parameters(30, 10); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < gp->pop_size; j++){
                    gp->fit_vec.at(j) = evp->function1(gp->population.at(j).array);
                }
                gp->calculate_prob();
                f_min = *min_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_max = *max_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_avg = gp->f_total/gp->pop_size;
                maxdata5 << f_max << "\t";
                avgdata5 << f_avg << "\t";
                mindata5 << f_min << "\t";
                gp->crossover();
                gp->mutate();
            }
        }
        if(f == 2){ //f(x) = 100*(x1^2-x2)^2 + (1-x1)^2
            gp->create_pop(24, p_size); //(array-size, pop-size)
            evp->set_parameters(24, 12); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < gp->pop_size; j++){
                    gp->fit_vec.at(j) = evp->function2(gp->population.at(j).array);
                }
                gp->calculate_prob();
                f_min = *min_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_max = *max_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_avg = gp->f_total/gp->pop_size;
                maxdata5 << f_max << "\t";
                avgdata5 << f_avg << "\t";
                mindata5 << f_min << "\t";
                gp->crossover();
                gp->mutate();
            }
        }
        if(f == 3){ //f(x) = sum(integer(x)) [1,5]
            gp->create_pop(50, p_size); //(array-size, pop-size)
            evp->set_parameters(50, 10); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < gp->pop_size; j++){
                    gp->fit_vec.at(j) = evp->function3(gp->population.at(j).array);
                }
                gp->calculate_prob();
                f_min = *min_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_max = *max_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_avg = gp->f_total/gp->pop_size;
                maxdata5 << f_max << "\t";
                avgdata5 << f_avg << "\t";
                mindata5 << f_min << "\t";
                gp->crossover();
                gp->mutate();
            }
        }
        if(f == 4){ //f(x) = sum(i*x^4) [1,30] + gauss(0,1)
            gp->create_pop(240, p_size); //(array-size, pop-size)
            evp->set_parameters(240, 8); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < gp->pop_size; j++){
                    gp->fit_vec.at(j) = evp->function4(gp->population.at(j).array);
                }
                gp->calculate_prob();
                f_min = *min_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_max = *max_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_avg = gp->f_total/gp->pop_size;
                maxdata5 << f_max << "\t";
                avgdata5 << f_avg << "\t";
                mindata5 << f_min << "\t";
                gp->crossover();
                gp->mutate();
            }
        }
        
        maxdata5 << endl; avgdata5 << endl; mindata5 << endl;
        gp->population.clear();
        gp->fit_vec.clear();
        gp->new_pop.clear();
        gp->p_range.clear();
        gp->p_indv.clear();
    }
    
    maxdata5.close(); avgdata5.close(); mindata5.close();
}

void graph_6(ga *gp, eval *evp, int f, int gen, int ps){
    double f_max, f_avg, f_min;
    int generations = gen; //Number of generations
    int stat_runs = 30; //Number of statistical runs
    int p_size = ps; //Population size
    gp->p_cross = 0.2;
    gp->p_mut = 0.01;
    
    ofstream maxdata6; maxdata6.open("g6_max.txt");
    ofstream avgdata6; avgdata6.open("g6_avg.txt");
    ofstream mindata6; mindata6.open("g6_min.txt");
    
    for(int k = 0; k < stat_runs; k++){
        if(f == 1){ //f(x) = sum(x^2) [1,3] for -5.12 <= x <= 5.12
            gp->create_pop(30, p_size); //(array-size, pop-size)
            evp->set_parameters(30, 10); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < gp->pop_size; j++){
                    gp->fit_vec.at(j) = evp->function1(gp->population.at(j).array);
                }
                gp->calculate_prob();
                f_min = *min_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_max = *max_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_avg = gp->f_total/gp->pop_size;
                maxdata6 << f_max << "\t";
                avgdata6 << f_avg << "\t";
                mindata6 << f_min << "\t";
                gp->crossover();
                gp->mutate();
            }
        }
        if(f == 2){ //f(x) = 100*(x1^2-x2)^2 + (1-x1)^2
            gp->create_pop(24, p_size); //(array-size, pop-size)
            evp->set_parameters(24, 12); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < gp->pop_size; j++){
                    gp->fit_vec.at(j) = evp->function2(gp->population.at(j).array);
                }
                gp->calculate_prob();
                f_min = *min_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_max = *max_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_avg = gp->f_total/gp->pop_size;
                maxdata6 << f_max << "\t";
                avgdata6 << f_avg << "\t";
                mindata6 << f_min << "\t";
                gp->crossover();
                gp->mutate();
            }
        }
        if(f == 3){ //f(x) = sum(integer(x)) [1,5]
            gp->create_pop(50, p_size); //(array-size, pop-size)
            evp->set_parameters(50, 10); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < gp->pop_size; j++){
                    gp->fit_vec.at(j) = evp->function3(gp->population.at(j).array);
                }
                gp->calculate_prob();
                f_min = *min_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_max = *max_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_avg = gp->f_total/gp->pop_size;
                maxdata6 << f_max << "\t";
                avgdata6 << f_avg << "\t";
                mindata6 << f_min << "\t";
                gp->crossover();
                gp->mutate();
            }
        }
        if(f == 4){ //f(x) = sum(i*x^4) [1,30] + gauss(0,1)
            gp->create_pop(240, p_size); //(array-size, pop-size)
            evp->set_parameters(240, 8); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < gp->pop_size; j++){
                    gp->fit_vec.at(j) = evp->function4(gp->population.at(j).array);
                }
                gp->calculate_prob();
                f_min = *min_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_max = *max_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_avg = gp->f_total/gp->pop_size;
                maxdata6 << f_max << "\t";
                avgdata6 << f_avg << "\t";
                mindata6 << f_min << "\t";
                gp->crossover();
                gp->mutate();
            }
        }
        
        maxdata6 << endl; avgdata6 << endl; mindata6 << endl;
        gp->population.clear();
        gp->fit_vec.clear();
        gp->new_pop.clear();
        gp->p_range.clear();
        gp->p_indv.clear();
    }
    
    maxdata6.close(); avgdata6.close(); mindata6.close();
}

void graph_7(ga *gp, eval *evp, int f, int gen, int ps){
    double f_max, f_avg, f_min;
    int generations = gen; //Number of generations
    int stat_runs = 30; //Number of statistical runs
    int p_size = ps; //Population size
    gp->p_cross = 0.99;
    gp->p_mut = 0.0001;
    
    ofstream maxdata7; maxdata7.open("g7_max.txt");
    ofstream avgdata7; avgdata7.open("g7_avg.txt");
    ofstream mindata7; mindata7.open("g7_min.txt");
    
    for(int k = 0; k < stat_runs; k++){
        if(f == 1){ //f(x) = sum(x^2) [1,3] for -5.12 <= x <= 5.12
            gp->create_pop(30, p_size); //(array-size, pop-size)
            evp->set_parameters(30, 10); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < gp->pop_size; j++){
                    gp->fit_vec.at(j) = evp->function1(gp->population.at(j).array);
                }
                gp->calculate_prob();
                f_min = *min_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_max = *max_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_avg = gp->f_total/gp->pop_size;
                maxdata7 << f_max << "\t";
                avgdata7 << f_avg << "\t";
                mindata7 << f_min << "\t";
                gp->crossover();
                gp->mutate();
            }
        }
        if(f == 2){ //f(x) = 100*(x1^2-x2)^2 + (1-x1)^2
            gp->create_pop(24, p_size); //(array-size, pop-size)
            evp->set_parameters(24, 12); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < gp->pop_size; j++){
                    gp->fit_vec.at(j) = evp->function2(gp->population.at(j).array);
                }
                gp->calculate_prob();
                f_min = *min_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_max = *max_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_avg = gp->f_total/gp->pop_size;
                maxdata7 << f_max << "\t";
                avgdata7 << f_avg << "\t";
                mindata7 << f_min << "\t";
                gp->crossover();
                gp->mutate();
            }
        }
        if(f == 3){ //f(x) = sum(integer(x)) [1,5]
            gp->create_pop(50, p_size); //(array-size, pop-size)
            evp->set_parameters(50, 10); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < gp->pop_size; j++){
                    gp->fit_vec.at(j) = evp->function3(gp->population.at(j).array);
                }
                gp->calculate_prob();
                f_min = *min_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_max = *max_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_avg = gp->f_total/gp->pop_size;
                maxdata7 << f_max << "\t";
                avgdata7 << f_avg << "\t";
                mindata7 << f_min << "\t";
                gp->crossover();
                gp->mutate();
            }
        }
        if(f == 4){ //f(x) = sum(i*x^4) [1,30] + gauss(0,1)
            gp->create_pop(240, p_size); //(array-size, pop-size)
            evp->set_parameters(240, 8); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < gp->pop_size; j++){
                    gp->fit_vec.at(j) = evp->function4(gp->population.at(j).array);
                }
                gp->calculate_prob();
                f_min = *min_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_max = *max_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_avg = gp->f_total/gp->pop_size;
                maxdata7 << f_max << "\t";
                avgdata7 << f_avg << "\t";
                mindata7 << f_min << "\t";
                gp->crossover();
                gp->mutate();
            }
        }
        
        maxdata7 << endl; avgdata7 << endl; mindata7 << endl;
        gp->population.clear();
        gp->fit_vec.clear();
        gp->new_pop.clear();
        gp->p_range.clear();
        gp->p_indv.clear();
    }
    
    maxdata7.close(); avgdata7.close(); mindata7.close();
}

void graph_8(ga *gp, eval *evp, int f, int gen, int ps){
    double f_max, f_avg, f_min;
    int generations = gen; //Number of generations
    int stat_runs = 30; //Number of statistical runs
    int p_size = ps; //Population size
    gp->p_cross = 0.99;
    gp->p_mut = 0.001;
    
    ofstream maxdata8; maxdata8.open("g8_max.txt");
    ofstream avgdata8; avgdata8.open("g8_avg.txt");
    ofstream mindata8; mindata8.open("g8_min.txt");
    
    for(int k = 0; k < stat_runs; k++){
        if(f == 1){ //f(x) = sum(x^2) [1,3] for -5.12 <= x <= 5.12
            gp->create_pop(30, p_size); //(array-size, pop-size)
            evp->set_parameters(30, 10); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < gp->pop_size; j++){
                    gp->fit_vec.at(j) = evp->function1(gp->population.at(j).array);
                }
                gp->calculate_prob();
                f_min = *min_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_max = *max_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_avg = gp->f_total/gp->pop_size;
                maxdata8 << f_max << "\t";
                avgdata8 << f_avg << "\t";
                mindata8 << f_min << "\t";
                gp->crossover();
                gp->mutate();
            }
        }
        if(f == 2){ //f(x) = 100*(x1^2-x2)^2 + (1-x1)^2
            gp->create_pop(24, p_size); //(array-size, pop-size)
            evp->set_parameters(24, 12); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < gp->pop_size; j++){
                    gp->fit_vec.at(j) = evp->function2(gp->population.at(j).array);
                }
                gp->calculate_prob();
                f_min = *min_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_max = *max_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_avg = gp->f_total/gp->pop_size;
                maxdata8 << f_max << "\t";
                avgdata8 << f_avg << "\t";
                mindata8 << f_min << "\t";
                gp->crossover();
                gp->mutate();
            }
        }
        if(f == 3){ //f(x) = sum(integer(x)) [1,5]
            gp->create_pop(50, p_size); //(array-size, pop-size)
            evp->set_parameters(50, 10); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < gp->pop_size; j++){
                    gp->fit_vec.at(j) = evp->function3(gp->population.at(j).array);
                }
                gp->calculate_prob();
                f_min = *min_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_max = *max_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_avg = gp->f_total/gp->pop_size;
                maxdata8 << f_max << "\t";
                avgdata8 << f_avg << "\t";
                mindata8 << f_min << "\t";
                gp->crossover();
                gp->mutate();
            }
        }
        if(f == 4){ //f(x) = sum(i*x^4) [1,30] + gauss(0,1)
            gp->create_pop(240, p_size); //(array-size, pop-size)
            evp->set_parameters(240, 8); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < gp->pop_size; j++){
                    gp->fit_vec.at(j) = evp->function4(gp->population.at(j).array);
                }
                gp->calculate_prob();
                f_min = *min_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_max = *max_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_avg = gp->f_total/gp->pop_size;
                maxdata8 << f_max << "\t";
                avgdata8 << f_avg << "\t";
                mindata8 << f_min << "\t";
                gp->crossover();
                gp->mutate();
            }
        }
        
        maxdata8 << endl; avgdata8 << endl; mindata8 << endl;
        gp->population.clear();
        gp->fit_vec.clear();
        gp->new_pop.clear();
        gp->p_range.clear();
        gp->p_indv.clear();
    }
    
    maxdata8.close(); avgdata8.close(); mindata8.close();
}

void graph_9(ga *gp, eval *evp, int f, int gen, int ps){
    double f_max, f_avg, f_min;
    int generations = gen; //Number of generations
    int stat_runs = 30; //Number of statistical runs
    int p_size = ps; //Population size
    gp->p_cross = 0.99;
    gp->p_mut = 0.01;
    
    ofstream maxdata9; maxdata9.open("g9_max.txt");
    ofstream avgdata9; avgdata9.open("g9_avg.txt");
    ofstream mindata9; mindata9.open("g9_min.txt");
    
    for(int k = 0; k < stat_runs; k++){
        if(f == 1){ //f(x) = sum(x^2) [1,3] for -5.12 <= x <= 5.12
            gp->create_pop(30, p_size); //(array-size, pop-size)
            evp->set_parameters(30, 10); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < gp->pop_size; j++){
                    gp->fit_vec.at(j) = evp->function1(gp->population.at(j).array);
                }
                gp->calculate_prob();
                f_min = *min_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_max = *max_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_avg = gp->f_total/gp->pop_size;
                maxdata9 << f_max << "\t";
                avgdata9 << f_avg << "\t";
                mindata9 << f_min << "\t";
                gp->crossover();
                gp->mutate();
            }
        }
        if(f == 2){ //f(x) = 100*(x1^2-x2)^2 + (1-x1)^2
            gp->create_pop(24, p_size); //(array-size, pop-size)
            evp->set_parameters(24, 12); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < gp->pop_size; j++){
                    gp->fit_vec.at(j) = evp->function2(gp->population.at(j).array);
                }
                gp->calculate_prob();
                f_min = *min_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_max = *max_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_avg = gp->f_total/gp->pop_size;
                maxdata9 << f_max << "\t";
                avgdata9 << f_avg << "\t";
                mindata9 << f_min << "\t";
                gp->crossover();
                gp->mutate();
            }
        }
        if(f == 3){ //f(x) = sum(integer(x)) [1,5]
            gp->create_pop(50, p_size); //(array-size, pop-size)
            evp->set_parameters(50, 10); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < gp->pop_size; j++){
                    gp->fit_vec.at(j) = evp->function3(gp->population.at(j).array);
                }
                gp->calculate_prob();
                f_min = *min_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_max = *max_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_avg = gp->f_total/gp->pop_size;
                maxdata9 << f_max << "\t";
                avgdata9 << f_avg << "\t";
                mindata9 << f_min << "\t";
                gp->crossover();
                gp->mutate();
            }
        }
        if(f == 4){ //f(x) = sum(i*x^4) [1,30] + gauss(0,1)
            gp->create_pop(240, p_size); //(array-size, pop-size)
            evp->set_parameters(240, 8); //(array-size, string-size)
            for(int i = 0; i < generations; i++){
                for(int j = 0; j < gp->pop_size; j++){
                    gp->fit_vec.at(j) = evp->function4(gp->population.at(j).array);
                }
                gp->calculate_prob();
                f_min = *min_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_max = *max_element(gp->fit_vec.begin(), gp->fit_vec.end());
                f_avg = gp->f_total/gp->pop_size;
                maxdata9 << f_max << "\t";
                avgdata9 << f_avg << "\t";
                mindata9 << f_min << "\t";
                gp->crossover();
                gp->mutate();
            }
        }
        
        maxdata9 << endl; avgdata9 << endl; mindata9 << endl;
        gp->population.clear();
        gp->fit_vec.clear();
        gp->new_pop.clear();
        gp->p_range.clear();
        gp->p_indv.clear();
    }
    
    maxdata9.close(); avgdata9.close(); mindata9.close();
}

int main() {
    ga g; eval ev;
    ga *gp = &g; eval *evp = &ev;
    srand( time(NULL) );
    
    int func = 4; //Which function should be evaluated
    int gn = 100; //Generations
    int p_s = 50; //pop size
    
    cout << "Function: " << func << endl;
    
    graph_1(gp, evp, func, gn, p_s); //Pcross = 0.67 Pmut = 0.0001
    graph_2(gp, evp, func, gn, p_s); //Pcross = 0.67 Pmut = 0.001
    graph_3(gp, evp, func, gn, p_s); //Pcross = 0.67 Pmut = 0.01
    graph_4(gp, evp, func, gn, p_s); //Pcross = 0.2 Pmut = 0.0001
    graph_5(gp, evp, func, gn, p_s); //Pcross = 0.2 Pmut = 0.001
    graph_6(gp, evp, func, gn, p_s); //Pcross = 0.2 Pmut = 0.01
    graph_7(gp, evp, func, gn, p_s); //Pcross = 0.99 Pmut = 0.0001
    graph_8(gp, evp, func, gn, p_s); //Pcross = 0.99 Pmut = 0.001
    graph_9(gp, evp, func, gn, p_s); //Pcross = 0.99 Pmut = 0.01
    
    return 0;
}
