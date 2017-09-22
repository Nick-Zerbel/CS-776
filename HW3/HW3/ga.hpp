//
//  ga.hpp
//  HW3
//
//  Created by Nick Zerbel on 9/21/17.
//  Copyright © 2017 Nicholas Zerbel. All rights reserved.
//

#ifndef ga_hpp
#define ga_hpp

#include <cstdlib>
#include <vector>
#include <assert.h>
#include <iostream>

using namespace std;

class sol{
public:
    vector <int> array;
};

class ga{
    friend class sol;
public:
    vector <sol> population;
    vector <sol> new_pop;
    vector <double> fit_vec;
    vector <double> p_indv; //Probability each individual will be chosen
    vector <double> p_range; //Pie Chart
    
    void create_pop(int a, int p);
    void calculate_prob();
    void reproduce();
    void crossover();
    void select_parents();
    void mutate();
    
    int pop_size;
    int array_size; //Size of each individual array in pop
    int parent1;
    int parent2;
    double f_total; //summation of all inidividual fitnesses
    const double p_cross = 0.7; //Probability of crossover
    const double p_mut = 0.001; //Probability of mutation
};

#endif /* ga_hpp */
