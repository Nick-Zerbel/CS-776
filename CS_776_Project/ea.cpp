//
//  ea.cpp
//  CS_776_Project
//
//  Created by Nick Zerbel on 11/16/17.
//  Copyright © 2017 Nicholas Zerbel. All rights reserved.
//

#include "ea.hpp"

void ea::create_pop(limits *lp){
    policy p; int r;
    
    for(int i = 0; i < pop_size; i++){
        pop.push_back(p);
        fit_vec.push_back(0);
        fit_prob.push_back(0);
    }
    for(int i = 0; i < pop_size; i++){
        for(int j = 0; j < a_size; j++){
            r = rand() % 2;
            pop.at(i).pol.push_back(r);
        }
    }
    new_pop = pop;
}

void ea::re_order(){
    int p1, p2;
    for(int i = 0; i < pop_size; i++){
        p1 = i;
        for(int j = 0; j < pop_size; j++){
            p2 = j;
            if(i < j){
                if(fit_vec.at(p2) > fit_vec.at(p1)){
                    iter_swap(fit_vec.begin() + p1, fit_vec.begin() + p2);
                    iter_swap(pop.begin() + p1, pop.begin() + p2);
                }
            }
        }
    }
}

void ea::decode(int s, int ssize, int pos){
    num = 0;
    for(int i = 0; i < ssize; i++){
        num += pop.at(pos).pol.at(i + s*ssize)*pow(2,i);
    }
}

void ea::calc_fit_prob(){
    fit_sum = 0;
    for(int i = 0; i < pop_size; i++){
        fit_sum += fit_vec.at(i);
    }
    for(int i = 0; i < pop_size; i++){
        if(i == 0){
            fit_prob.at(i) = fit_vec.at(i)/fit_sum;
        }
        if(i > 0){
            fit_prob.at(i) = fit_prob.at(i-1) + (fit_vec.at(i)/fit_sum);
        }
    }
}

int ea::select_parent(){
    double r; int p;
    r = (double)(rand()/RAND_MAX);
    for(int i = 0; i < pop_size; i++){
        if(i == 0){
            if(0 <= r && r < fit_prob.at(i)){
                p = i;
                break;
            }
        }
        if(i > 0){
            if(fit_prob.at(i-1) <= r && r < fit_prob.at(i)){
                p = i;
                break;
            }
        }
    }
    
    return p;
}

void ea::crossover(){
    double prob; int p1, p2, cp;
    new_pop.at(0) = pop.at(0);
    new_pop.at(1) = pop.at(0);
    for(int i = 2; i < ((pop_size-2)/2); i++){
        prob = (double)(rand()/RAND_MAX);
        p1 = select_parent(); //Parent 1
        p2 = select_parent(); //Parent 2
        if(prob <= p_cross){
            cp = (rand() % (a_size-2)) + 1; //Crossover Point
            for(int j = 0; j < cp; j++){
                new_pop.at(2*i).pol.at(j) = pop.at(p1).pol.at(j);
                new_pop.at(2*i+1).pol.at(j) = pop.at(p2).pol.at(j);
            }
            for(int j = cp; j < a_size; j++){
                new_pop.at(2*i).pol.at(j) = pop.at(p2).pol.at(j);
                new_pop.at(2*i+1).pol.at(j) = pop.at(p1).pol.at(j);
            }
        }
        if(prob > p_cross){
            new_pop.at(2*i) = pop.at(p1);
            new_pop.at(2*i+1) = pop.at(p2);
        }
    }
    pop = new_pop;
    assert(pop.size() == pop_size);
}

void ea::mutation(){
    double prob; int b;
    for(int i = 2; i < pop_size; i++){
        prob = (double)(rand()/RAND_MAX);
        if(prob <= p_mut){
            b = rand() % a_size;
            if(pop.at(i).pol.at(b) == 0){
                pop.at(i).pol.at(b) = 1;
            }
            if(pop.at(i).pol.at(b) == 1){
                pop.at(i).pol.at(b) = 0;
            }
        }
    }
}
