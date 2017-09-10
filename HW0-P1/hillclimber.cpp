//
//  hillclimber.cpp
//  CS 776 HW 0
//
//  Created by Nick Zerbel on 8/29/17.
//  Copyright © 2017 Nick Zerbel. All rights reserved.
//

#include "hillclimber.hpp"

void hillclimber::create_vec(){
    pos = 0;
    for(int i = 0; i < 100; i++){
        vec[i] = 0;
        m_vec[i] = 0;
    }
}

void hillclimber::mutate(){
    bool mutated;
    mutated = false;
    zero = false;
    one = false;

    if(pos > 99){
       pos = 0;
    }
        
    if(vec[pos] == 0){
        vec[pos] = 1;
        mutated = true;
        one = true;
    }
        
    if(vec[pos] == 1 && mutated == false){
        vec[pos] = 0;
        zero = true;
    }
        
}

void hillclimber::revert(){
    if(one == true){
        vec[pos] = 0;
    }
    if(zero == true){
        vec[pos] = 1;
    }
}
