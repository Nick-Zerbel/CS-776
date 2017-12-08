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
    vector <policy> combined_pop;
    vector <policy> pop;
    vector <policy> new_pop;
    vector <double> combined_fit;
    vector <double> pfit_vec; //Parent fitness vector
    vector <double> ofit_vec; //Offspring fitness vector
    vector <double> fit_prob; //Overall fitness probabilities
    vector <int> best_policy;
    
    //General Functions
    void create_pop();
    void clear_vecs();
    void decode(int p, vector <int> invec); //Decode policy for rewards and penalties
    void rollout_decode(int p, vector <int> invec); //Decode policy for rollout actions
    
    //Fitness Calculations
    void re_order();
    void calc_fit_prob();
    
    //Mu + Lambda Selection
    int select_parent();
    void crossover();
    void mutation();
    void create_new_pop();
    
    //Parameters
    double best_fit; //Best fitness of all time in statistical run
    double fit;
    double p_mut; //Probability of Mutation
    double p_cross; //Probability of Crossover
    double num; //Number decoded from binary string
    double fit_sum; //Sum of all fitness scores for population
    int pop_size; //Size of EA population
    int mu;
    int lambda;
    int n_steps; //Number of rollout steps
    int n_weights; //Number of reward/penalty values needed
    int a_size; //Array Size
    int s_size_r; //String Size for Rewards and Penalties
};

#endif /* ea_hpp */
