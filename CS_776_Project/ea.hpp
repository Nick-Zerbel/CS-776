//
//  ea.hpp
//  CS_776_Project
//
//  Created by Nick Zerbel on 11/16/17.
//  Copyright © 2017 Nicholas Zerbel. All rights reserved.
//

#ifndef ea_hpp
#define ea_hpp

#include <cstdlib>
#include <vector>
#include <iostream>
#include <cmath>
#include <assert.h>
#include <time.h>

using namespace std;

class limit{
public:
    double upper;
    double lower;
};

class policy{
public:
    vector <int> pol;
};

class ea{
    friend class parameters;
public:
    vector <policy> new_pop;
    vector <policy> new_roll_pop;
    vector <double> fit_vec;
    vector <double> fit_prob;
    
    //General Functions
    void create_pop();
    void re_order();
    void calc_fit_prob();
    int select_parent();
    void clear_vecs();
    
    //Population of Weights
    vector <policy> pop;
    vector <int> best_policy;
    void decode(int p, vector <int> weights);
    void crossover();
    void mutation();
    
    //Population of Actions
    vector <int> best_roll_pol;
    vector <policy> roll_pop;
    void roll_mutation();
    void roll_crossover();
    
    //Parameters
    double best_fit; //Best fitness of all time in statistical run
    double fit;
    double p_mut; //Probability of Mutation
    double p_cross; //Probability of Crossover
    double num; //Number decoded from binary string
    double fit_sum;
    int pop_size;
    int n_steps; //Number of rollout steps
    int n_weights; //Number of weights needed for EA
    int a_size; //Array Size
    int s_size; //String Size
};

#endif /* ea_hpp */
