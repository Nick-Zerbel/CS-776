//
//  EA.hpp
//  HW4
//
//  Created by Nicholas Zerbel on 10/1/17.
//  Copyright © 2017 Nicholas Zerbel. All rights reserved.
//

#ifndef EA_hpp
#define EA_hpp

#include <cstdlib>
#include <iostream>
#include <vector>
#include <assert.h>
#include <fstream>

using namespace std;

class policy{
public:
    vector <int> tour;
};

class ea{
    friend class policy;
public:
    vector <policy> population;
    vector <policy> new_pop;
    vector <double> fit_vec;
    vector <double> probability;
    
    void create_pop();
    void check_for_duplicates(int n, int pos);
    void avg_fitness();
    void sort();
    void evaluate_rank();
    int select_parent();
    void crossover();
    void find_repeats();
    int change_city(int p);
    void mutate();
    
    
    double p_mut; //Probability of mutation
    double p_cross; //Probability of crossover
    double SP; //Selective Pressure
    int pop_size; //Number of policies in population
    int n_cities; //Number of cities in a policy
    bool valid;
    double f_max;
    double f_avg;
    double f_min;
};

#endif /* EA_hpp */
