//
//  ga.cpp
//  HW3
//
//  Created by Nicholas Zerbel on 9/21/17.
//  Copyright © 2017 Nicholas Zerbel. All rights reserved.
//

#include "ga.hpp"

void ga::create_pop(int a, int p){ //a = array suze and p = pop size
    array_size = a; pop_size = p;
    
    individual s; int val;
    for(int i = 0; i < pop_size; i++){
        population.push_back(s);
        new_pop.push_back(s);
        fit_vec.push_back(0.00);
        p_indv.push_back(0.00);
        p_range.push_back(0.00);
    }
    
    for(int i = 0; i < pop_size; i++){
        for(int j = 0; j < array_size; j++){
            val = rand() % 2;
            population.at(i).array.push_back(val);
            new_pop.at(i).array.push_back(val);
        }
    }
}

void ga::calculate_prob(){
    f_total = 0;
    for(int i = 0; i < pop_size; i++){ //Find total sum fitness of all individuals
        f_total += fit_vec.at(i);
    }
    for(int i = 0; i < pop_size; i++){ //Record probabilities of each individual being selected
        p_indv.at(i) = fit_vec.at(i)/f_total;
    }
    for(int i = 0; i < pop_size; i++){ //Create pie chart
        if(i == 0){
            p_range.at(i) = p_indv.at(i);
        }
        if(i > 0){
            p_range.at(i) = p_indv.at(i) + p_range.at(i-1);
        }
    }
}

void ga::crossover(){
    int p; //p = point of crossover
    double r;
    
    for(int i = 0; i < pop_size/2; i++){
        select_parents();
        r = (double)rand()/RAND_MAX;
        if(r <= p_cross){
            p = rand() % array_size-1; //crossover point
            p += 1; //This makes sure the crossover point isn't 0
            for(int j = 0; j < p; j++){
                new_pop.at(2*i).array.at(j) = population.at(parent1).array.at(j);
                new_pop.at(2*i+1).array.at(j) = population.at(parent2).array.at(j);
            }
            for(int j = p; j < array_size; j++){
                new_pop.at(2*i).array.at(j) = population.at(parent2).array.at(j);
                new_pop.at(2*i+1).array.at(j) = population.at(parent1).array.at(j);
            }
        }
        if(r > p_cross){
            new_pop.at(2*i) = population.at(parent1);
            new_pop.at(2*i + 1) = population.at(parent2);
        }
    }
    population = new_pop;
}

void ga::select_parents(){
    double r1, r2;
    r1 = (double)rand()/RAND_MAX;
    r2 = (double)rand()/RAND_MAX;
    parent1 = -1; parent2 = -1;
    for(int i = 0; i < pop_size; i++){
        
        if(i == 0){
            if(r1 >= 0 && r1 < p_range.at(i)){
                parent1 = i;
            }
            if(r2 >= 0 && r2 < p_range.at(i)){
                parent2 = i;
            }
        }
        
        if(i > 0){
            if(r1 >= p_range.at(i-1) && r1 < p_range.at(i)){
                parent1 = i;
            }
            if(r2 >= p_range.at(i-1) && r2 < p_range.at(i)){
                parent2 = i;
            }
        }
        if(parent1 > -1 && parent2 > -1){
            break;
        }
    }
    assert(parent1 != -1);
    assert(parent2 != -1);
}

void ga::mutate(){
    double r; int p;
    for(int i = 0; i < pop_size; i++){
        r = (double)rand()/RAND_MAX;
        if(r <= p_mut){
            p = rand() % array_size;
            if(population.at(i).array.at(p) == 0){
                population.at(i).array.at(p) = 1;
            }
            if(population.at(i).array.at(p) == 1){
                population.at(i).array.at(p) = 0;
            }
        }
    }
}
