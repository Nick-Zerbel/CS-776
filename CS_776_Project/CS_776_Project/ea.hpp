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


using namespace std;

class parameters{
public:
    double goal_r; //Goal Reward
    double p; //Penalty
    double roll_r; //Rollout Reward
    double eps; //Epsilon
    int roll_its; //Rollout Iterations
    int mc_its; //Monte Carlo Iterations
    double obs_d; //Observational Distance
};

class limits{
public:
    int gr_max = 1000;
    int gr_min = 100;
    int p_max = 100;
    int p_min = 0;
    int rr_max = 100;
    int rr_min = 1;
    int eps_max = 5;
    int eps_min = 0;
    int ri_max = 5000;
    int ri_min = 100;
    int mci_max;
    int mci_min = 5;
    int od_max = 100;
    int od_min = 5;
};

class ea{
    friend class parameters;
public:
    vector <parameters> pop;
    vector <parameters> new_pop;
    vector <double> fit_vec;
    
    void create_pop(limits *lp);
    void select_parents();
    void re_order();
    void mutation(limits *lp);
    
    double fit;
    double p_mut; //Probability of Mutation
    int pop_size;
};

#endif /* ea_hpp */
