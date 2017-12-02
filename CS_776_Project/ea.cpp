//
//  ea.cpp
//  CS_776_Project
//
//  Created by Nick Zerbel on 11/16/17.
//  Copyright © 2017 Nicholas Zerbel. All rights reserved.
//

#include "ea.hpp"

void ea::create_pop(){
    policy p, p2; int r;
    
    for(int i = 0; i < pop_size; i++){
        pop.push_back(p);
        roll_pop.push_back(p2);
        fit_vec.push_back(0);
        fit_prob.push_back(0);
    }
    for(int i = 0; i < pop_size; i++){
        for(int j = 0; j < a_size; j++){
            r = rand() % 2;
            pop.at(i).pol.push_back(r);
        }
    }
    for(int i = 0; i < pop_size; i++){
        for(int j = 0; j < n_steps; j++){
            r = rand() % 5;
            roll_pop.at(i).pol.push_back(r);
        }
    }
    new_pop = pop;
    new_roll_pop = roll_pop;
    best_fit = 0;
    best_policy = pop.at(0).pol;
    best_roll_pol = roll_pop.at(0).pol;
}

void ea::decode(int p, vector <int> weights){
    num = 0;
    for(int i = 0; i < s_size; i++){
        num += weights.at(i+s_size*p)*pow(2,i);
    }
}

void ea::re_order(){
    for(int i = 0; i < pop_size; i++){
        for(int j = 0; j < pop_size; j++){
            if(i < j){
                if(fit_vec.at(j) > fit_vec.at(i)){
                    iter_swap(fit_vec.begin() + i, fit_vec.begin() + j);
                    iter_swap(pop.begin() + i, pop.begin() + j);
                    iter_swap(roll_pop.begin() + i, roll_pop.begin() + j);
                }
            }
        }
    }
}

void ea::calc_fit_prob(){
    fit_sum = 0; double p = (double)pop_size;
    for(int i = 0; i < pop_size; i++){
        fit_sum += fit_vec.at(i);
        fit_prob.at(i) = 0;
    }
    if(fit_sum > 0){
        for(int i = 0; i < pop_size; i++){
            if(i == 0){
                fit_prob.at(i) = fit_vec.at(i)/fit_sum;
            }
            if(i > 0){
                fit_prob.at(i) = fit_prob.at(i-1) + (fit_vec.at(i)/fit_sum);
            }
        }
    }
    if(fit_sum == 0){
        for(int i = 0; i < pop_size; i++){
            if(i == 0){
                fit_prob.at(i) = 1/p;
            }
            if(i > 0){
                fit_prob.at(i) = fit_prob.at(i-1) + (1/p);
            }
        }
    }
}

int ea::select_parent(){
    double r; int p;
    r = (double)(rand())/RAND_MAX;
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
    assert(0 <= p && p < pop_size);
    return p;
}

void ea::crossover(){
    double prob; int p1, p2, cp;
    //new_pop.at(0) = pop.at(0);
    //new_pop.at(1) = pop.at(1);
    for(int i = 0; i < (pop_size/2); i++){
        prob = (double)(rand())/RAND_MAX;
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

void ea::roll_crossover(){
    double prob; int p1, p2, cp;
    //new_pop.at(0) = roll_pop.at(0);
    //new_pop.at(1) = roll_pop.at(1);
    for(int i = 0; i < (pop_size/2); i++){
        prob = (double)(rand())/RAND_MAX;
        p1 = select_parent(); //Parent 1
        p2 = select_parent(); //Parent 2
        if(prob <= p_cross){
            cp = (rand() % (n_steps-2)) + 1; //Crossover Point
            for(int j = 0; j < cp; j++){
                new_roll_pop.at(2*i).pol.at(j) = roll_pop.at(p1).pol.at(j);
                new_roll_pop.at(2*i+1).pol.at(j) = roll_pop.at(p2).pol.at(j);
            }
            for(int j = cp; j < n_steps; j++){
                new_roll_pop.at(2*i).pol.at(j) = roll_pop.at(p2).pol.at(j);
                new_roll_pop.at(2*i+1).pol.at(j) = roll_pop.at(p1).pol.at(j);
            }
        }
        if(prob > p_cross){
            new_roll_pop.at(2*i) = roll_pop.at(p1);
            new_roll_pop.at(2*i+1) = roll_pop.at(p2);
        }
    }
    roll_pop = new_roll_pop;
    assert(roll_pop.size() == pop_size);
}

void ea::mutation(){
    double prob; int b;
    for(int i = 0; i < pop_size; i++){
        prob = (double)(rand())/RAND_MAX;
        if(prob <= p_mut){
            b = rand() % a_size; //Which element gets mutated
            if(pop.at(i).pol.at(b) == 0){
                pop.at(i).pol.at(b) = 1;
            }
            if(pop.at(i).pol.at(b) == 1){
                pop.at(i).pol.at(b) == 0;
            }
        }
    }
}

void ea::roll_mutation(){
    double prob; int b, a;
    for(int i = 0; i < pop_size; i++){
        prob = (double)(rand())/RAND_MAX;
        if(prob <= p_mut){
            b = rand() % n_steps;
            a = rand() % 5;
            roll_pop.at(i).pol.at(b) = a;
        }
    }
}

void ea::clear_vecs(){
    pop.clear();
    roll_pop.clear();
    new_pop.clear();
    fit_vec.clear();
    fit_prob.clear();
}
