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

class policy{
public:
    vector <int> pol;
};

class ea{
    friend class parameters;
public:
    vector <policy> pop;
    vector <policy> new_pop;
    vector <double> fit_vec;
    vector <double> fit_prob;
    
    void create_pop();
    void select_parents();
    void re_order();
    void calc_fit_prob();
    void mutation();
    void crossover();
    int select_parent();
    void clear_vecs();
    
    double fit;
    double p_mut; //Probability of Mutation
    double p_cross; //Probability of Crossover
    double num;
    double fit_sum;
    int pop_size;
    int a_size; //Size of binary array
};

#endif /* ea_hpp */
