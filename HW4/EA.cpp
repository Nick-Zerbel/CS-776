//
//  EA.cpp
//  HW4
//
//  Created by Nicholas Zerbel on 10/1/17.
//  Copyright © 2017 Nicholas Zerbel. All rights reserved.
//

#include "EA.hpp"

void ea::create_pop(){
    policy p; int c;
    vector <int> v;
    for(int i = 0; i < n_cities; i++){
        v.push_back(-1);
    }
    for(int i = 0; i < pop_size; i++){
        population.push_back(p);
        population.at(i).tour = v;
    }
    
    for(int i = 0; i < pop_size; i++){
        for(int j = 0; j < n_cities; j++){
            if(j == 0){
                population.at(i).tour.at(j) = 0; //Starting city will always be 1
            }
            if(j > 0 && j < n_cities-1){
                c = rand() % (n_cities-1);
                check_for_duplicates(c, i);
                assert(c != n_cities-1);
                while(valid == false){
                    c = rand() % (n_cities-1);
                    assert(c != n_cities-1);
                    check_for_duplicates(c, i);
                }
                assert(valid == true);
                population.at(i).tour.at(j) = c;
            }
            if(j == n_cities-1){
                population.at(i).tour.at(j) = 0; //Must return to starting city
            }
        }
        new_pop = population;
    }
    for(int i = 0; i < pop_size; i++){ //Creates fitness vector
        fit_vec.push_back(0);
        probability.push_back(0);
    }
}

void ea::check_for_duplicates(int n, int pos){ //Checks for duplicate cities in each policy
    valid = true;
    for(int i = 0; i < n_cities; i++){
        if(n == population.at(pos).tour.at(i)){
            valid = false;
        }
    }
}

void ea::avg_fitness(){
    double sum; sum = 0;
    for(int i = 0; i < pop_size; i++){ //Sum up all the fitness values for the top half of the pop
        sum += fit_vec.at(i);
    }
    f_avg = sum/pop_size;
}

void ea::sort(){
    int p1, p2;
    
    for(int i = 0; i < pop_size; i++){
        p1 = i;
        for(int j = i+1; j < pop_size; j++){
            p2 = j;
            if(fit_vec.at(p2) < fit_vec.at(p1)){
                iter_swap(fit_vec.begin() + p2, fit_vec.begin() + p1);
                iter_swap(population.begin() + p2, population.begin() + p1);
                p1 = p2;
            }
        }
    }
}

void ea::down_select(){
    int p1, p2;
    new_pop.at(0).tour = population.at(0).tour; //Best individual automatically transferred
    for(int i = 1; i < pop_size; i++){
        p1 = rand() % pop_size;
        p2 = rand() % pop_size;
        if(fit_vec.at(p1) <= fit_vec.at(p2)){
            new_pop.at(i).tour = population.at(p1).tour;
        }
        if(fit_vec.at(p1) > fit_vec.at(p2)){
            new_pop.at(i).tour = population.at(p2).tour;
        }
    }
    population = new_pop;
}

void ea::mutate(){
    double r; int p1, p2, c;
    
    for(int i = 1; i < pop_size; i++){
        r = (double)rand()/RAND_MAX;
        if(r <= p_mut){
            p1 = (rand() % (n_cities-2)) + 1;
            p2 = (rand() % (n_cities-2)) + 1;
            while(p1 == p2){
                p2 = (rand() % (n_cities-2)) + 1;
            }
            iter_swap(population.at(i).tour.begin() + p1, population.at(i).tour.begin() + p2);
        }
    }
    for(int i = 0; i < pop_size; i++){ //Check to make sure starting and ending city do not change
        assert(population.at(i).tour.at(0) == 0);
        assert(population.at(i).tour.at(n_cities-1) == 0);
    }
    for(int i = 0; i < pop_size; i++){ //Make sure no cities are duplicated (except for the last city)
        for(int j = 0; j < n_cities-1; j++){
            c = population.at(i).tour.at(j);
            for(int k = j+1; k < n_cities-1; k++){
                assert(c != population.at(i).tour.at(k));
            }
        }
    }
}
