//
//  main.cpp
//  HW4
//
//  Created by Nicholas Zerbel on 10/1/17.
//  Copyright © 2017 Nicholas Zerbel. All rights reserved.
//

#include <iostream>
#include "EA.hpp"
#include "eval.hpp"

using namespace std;

void burma14(domain *dp, ea *ep, string f){
    dp->n_cities = 14;
    ep->n_cities = dp->n_cities + 1;
    dp->create_city_vec(f);
    ep->create_pop();
}

void berlin52(domain *dp, ea *ep, string f){
    dp->n_cities = 52;
    ep->n_cities = dp->n_cities + 1;
    dp->create_city_vec(f);
    ep->create_pop();
}

void eil51(domain *dp, ea *ep, string f){
    dp->n_cities = 51;
    ep->n_cities = dp->n_cities + 1;
    dp->create_city_vec(f);
    ep->create_pop();
}

void eil76(domain *dp, ea *ep, string f){
    dp->n_cities = 76;
    ep->n_cities = dp->n_cities + 1;
    dp->create_city_vec(f);
    ep->create_pop();
}

void lin105(domain *dp, ea *ep, string f){
    dp->n_cities = 105;
    ep->n_cities = dp->n_cities + 1;
    dp->create_city_vec(f);
    ep->create_pop();
}

void lin318(domain *dp, ea *ep, string f){
    dp->n_cities = 318;
    ep->n_cities = dp->n_cities + 1;
    dp->create_city_vec(f);
    ep->create_pop();
}

int main() {
    domain d; ea e;
    domain *dp = &d; ea *ep = &e;
    srand( time(NULL) );
    
    string s = "lin318.tsp";
    e.pop_size = 1000;
    e.p_mut = 0.5;
    e.p_cross = 0.7;
    e.SP = 1.5;
    int generations = 100;
    int stat_runs = 30;
    
    ofstream fmax; fmax.open("max_fitness.txt");
    ofstream favg; favg.open("avg_fitness.txt");
    ofstream fmin; fmin.open("min_fitness.txt");
    ofstream bestpol; bestpol.open("best_policy.txt");
    ofstream bestfit; bestfit.open("best_fitness.txt");
    
    for(int k = 0; k < stat_runs; k++){
        cout << "Stat Run: " << k << endl;
        if(s == "burma14.tsp"){
            burma14(dp, ep, s);
        }
        if(s == "berlin52.tsp"){
            berlin52(dp, ep, s);
        }
        if(s == "eil51.tsp"){
            eil51(dp, ep, s);
        }
        if(s == "eil76.tsp"){
            eil76(dp, ep, s);
        }
        if(s == "lin105.tsp"){
            lin105(dp, ep, s);
        }
        if(s == "lin318.tsp"){
            lin318(dp, ep, s);
        }
        e.evaluate_rank();
        for(int i = 0; i < generations; i++){
            for(int j = 0; j < e.pop_size; j++){
                e.fit_vec.at(j) = d.eval(e.population.at(j).tour);
            }
            e.avg_fitness();
            e.sort();
            e.f_min = *min_element(e.fit_vec.begin(), e.fit_vec.end());
            e.f_max = *max_element(e.fit_vec.begin(), e.fit_vec.end());
            fmax << e.f_max << "\t";
            favg << e.f_avg << "\t";
            fmin << e.f_min << "\t";
            e.crossover();
            e.find_repeats();
            e.mutate();
        }
        e.sort();
        for(int i = 0; i < e.n_cities; i++){
            bestpol << e.population.at(e.pop_size-1).tour.at(i) << "\t";
        }
        bestfit << e.fit_vec.at(e.pop_size-1) << "\n";
        e.population.clear();
        e.new_pop.clear();
        e.fit_vec.clear();
        e.probability.clear();
        d.city_vec.clear();
        fmax << endl; favg << endl; fmin << endl; bestpol << endl;
    }
    
    fmax.close(); favg.close(); fmin.close(); bestfit.close(); bestpol.close();
    
    return 0;
}
