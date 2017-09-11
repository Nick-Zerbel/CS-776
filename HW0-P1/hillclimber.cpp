//
//  hillclimber.cpp
//  CS 776 HW 0
//
//  Created by Nicholas Zerbel on 8/29/17.
//  Copyright © 2017 Nicholas Zerbel. All rights reserved.
//

#include "hillclimber.hpp"

void hillclimber::create_vec(){
    double r;
    for(int i = 0; i < 100; i++){
        r = (double)(rand()/RAND_MAX);
        if(r < 0.5){
            vec[i] = 0;
        }
        if(r >= 0.5){
            vec[i] = 1;
        }
    }
}

//Random Changes----------------------------------------------------------------------------
void hillclimber::random_mutate1(){
    int i; bool mutated; mutated = false;
    zero_i = false; one_i = false;

    i = rand() % 100;
    pos1 = i;

    if(vec[i] == 0){
        vec[i] = 1;
        mutated = true;
        one_i = true;
    }
    if(vec[i] == 1 && mutated == false){
        vec[i] = 0;
        zero_i = true;
    }
}

void hillclimber::random_mutate2(){
    int i, j; bool mutated_i; bool mutated_j;
    mutated_i = false; mutated_j = false;
    zero_i = false; zero_j = false; one_i = false; one_j = false;

    i = rand() % 100; //Two different, random positions are selected
    j = rand() % 100;
    while(j == i){
        j = rand() % 100;
    }

    pos1 = i; pos2 = j;

    if(vec[i] == 0){
        vec[i] = 1;
        mutated_i = true;
        one_i = true;
    }
    if(vec[j] == 0){
        vec[j] = 1;
        mutated_j = true;
        one_j = true;
    }
    if(vec[i] == 1 && mutated_i == false){
        vec[i] = 0;
        zero_i = true;
    }
    if(vec[j] == 1 && mutated_j == false){
        vec[j] = 0;
        zero_j = true;
    }
}

void hillclimber::random_mutate3(){
    int i, j, k;
    bool mutated_i; bool mutated_j; bool mutated_k;
    
    zero_i = false; zero_j = false; zero_k = false;
    one_i = false; one_j = false; one_k = false;
    mutated_i = false; mutated_j = false; mutated_k = false;

    i = rand() % 100; //Three different, random positions are selected
    j = rand() % 100;
    while(j == i){
        j = rand() % 100;
    }
    k = rand() % 100;
    while(k == j || k == i){
        k = rand() % 100;
    }

    pos1 = i; pos2 = j; pos3 = k;
    
    if(vec[i] == 0){
        vec[i] = 1;
        mutated_i = true;
        one_i = true;
    }
    if(vec[j] == 0){
        vec[j] = 1;
        mutated_j = true;
        one_j = true;
    }

    if(vec[k] == 0){
        vec[k] = 1;
        mutated_k = true;
        one_k = true;
    }

    if(vec[i] == 1 && mutated_i == false){
        vec[i] = 0;
        zero_i = true;
    }
    if(vec[j] == 1 && mutated_j == false){
        vec[j] = 0;
        zero_j = true;
    }
    if(vec[k] == 1 && mutated_k == false){
        vec[k] = 0;
        zero_k = true;
    }
}

void hillclimber::rand_revert1(){
    if(one_i == true){
        vec[pos1] = 0;
    }
    if(zero_i == true){
        vec[pos1] = 1;
    }
}

void hillclimber::rand_revert2(){
    if(one_i == true){
        vec[pos1] = 0;
    }
    if(zero_i == true){
        vec[pos1] = 1;
    }
    if(one_j == true){
        vec[pos2] = 0;
    }
    if(zero_j == true){
        vec[pos2] = 1;
    }
}

void hillclimber::rand_revert3(){
    if(one_i == true){
        vec[pos1] = 0;
    }
    if(zero_i == true){
        vec[pos1] = 1;
    }
    if(one_j == true){
        vec[pos2] = 0;
    }
    if(zero_j == true){
        vec[pos2] = 1;
    }
    if(one_k == true){
        vec[pos3] = 0;
    }
    if(zero_k == true){
        vec[pos3] = 1;
    }
}
