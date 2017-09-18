//
//  hillclimber.cpp
//  CS-776-HW-2
//
//  Created by Nicholas Zerbel on 9/17/17.
//  Copyright © 2017 Nicholas Zerbel. All rights reserved.
//

#include "hillclimber.hpp"

void hillclimber::create_vec(){
    double r;
    for(int i = 0; i < 150; i++){
        r = (double)(rand()/RAND_MAX);
        if(r < 0.5){
            vec[i] = 0;
            best_vec[i] = 0;
        }
        if(r >= 0.5){
            vec[i] = 1;
            best_vec[i] = 1;
        }
    }
}

void hillclimber::evaluate(){
    if(fitness > best_fit){
        for(int i = 0; i < 150; i++){
            best_vec[i] = vec[i];
        }
    }
    if(best_fit >= fitness){
        for(int i = 0; i < 150; i++){
            vec[i] = best_vec[i];
        }
    }
}

void hillclimber::mutate(){
    int p1, p2;
    
    p1 = rand() % 150;
    p2 = rand() % 150;
    
    if(vec[p1] == 0){
        vec[p1] = 1;
    }
    if(vec[p1] == 1){
        vec[p1] = 0;
    }
    
    if(vec[p2] == 0){
        vec[p2] = 1;
    }
    if(vec[p2] == 1){
        vec[p2] = 0;
    }

    for(int i = 0; i < 150; i++){
        assert(vec[i] == 0 || vec[i] == 1);
	assert(best_vec[i] == 0 || best_vec[i] == 1);
    }
}
