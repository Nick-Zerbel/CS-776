//
//  hillclimber.hpp
//  CS-776-HW-2
//
//  Created by Nicholas Zerbel on 9/17/17.
//  Copyright © 2017 Nicholas Zerbel. All rights reserved.
//

#ifndef hillclimber_hpp
#define hillclimber_hpp

#include <iostream>
#include <cstdlib>
#include <assert.h>

using namespace std;

class hillclimber{
public:
    int vec[150]; //Array that gets mutated
	int r_vec[150]; //Array that is being constantly mutated to enhance exploration
    int best_vec[150]; //Array that represents best solution found
    
    void create_vec();
    void mutate();
    void evaluate();

    double fitness;
	double r_fitness;
    double best_fit;
};

#endif /* hillclimber_hpp */
