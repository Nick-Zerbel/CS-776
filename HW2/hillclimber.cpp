//
//  hillclimber.cpp
//  CS-776-HW-2
//
//  Created by Nicholas Zerbel on 9/17/17.
//  Copyright © 2017 Nicholas Zerbel. All rights reserved.
//

#include "hillclimber.hpp"

void hillclimber::create_vec(){
    int r;
    for(int i = 0; i < 150; i++){
        r = rand() % 2;
		vec[i] = r;
		best_vec[i] = r;
    }
}

void hillclimber::evaluate(){
    if(fitness > best_fit){ //Compare to mutating vector
		best_fit = fitness;
        for(int i = 0; i < 150; i++){
            best_vec[i] = vec[i];
        }
    }
    if(r_fitness > best_fit){ //Compare to random vector
		best_fit = r_fitness;
		for(int i = 0; i < 150; i++){
			best_vec[i] = r_vec[i];
		}
	}
    if(best_fit >= fitness){ //Assign best vec to mutating vector
        for(int i = 0; i < 150; i++){
            vec[i] = best_vec[i];
        }
    }
}

void hillclimber::mutate(){
    int p1;
	double r;

	for(int i = 0; i < 30; i++){
		p1 = rand() % 5;
		r = (double)rand()/RAND_MAX;
		if(vec[p1+(i*5)] == 0 && r >= 0.5){
			vec[p1+(i*5)] = 1;
		}
		if(vec[p1+(i*5)] == 1 && r >= 0.5){
			vec[p1+(i*5)] = 0;
		}
	}

	for(int i = 0; i < 150; i++){
		p1 = rand() % 2;
		r_vec[i] = p1;
	}
}
