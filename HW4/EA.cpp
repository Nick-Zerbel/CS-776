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
                while(valid == false){
                    c = rand() % (n_cities-1);
                    check_for_duplicates(c, i);
                }
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

void ea::sort(){ //Least Fit individual gets sorted to position 0, best fit goes to position n-1
    int p1, p2;
    
    for(int i = 0; i < pop_size; i++){
        p1 = i;
        for(int j = i+1; j < pop_size; j++){
            p2 = j;
            if(fit_vec.at(p2) > fit_vec.at(p1)){
                iter_swap(fit_vec.begin() + p2, fit_vec.begin() + p1);
                iter_swap(population.begin() + p2, population.begin() + p1);
                p1 = p2;
            }
        }
    }
}

void ea::evaluate_rank(){
    for(int i = 0; i < pop_size; i++){
        probability.at(i) = 2 - SP + (2*(SP-1)*(i/(pop_size-1)));
    }
}

int ea::select_parent(){
    double r1, r, min; int p;
    min = 2 - SP;
    r1 = (double)rand()/RAND_MAX;
    r = min + r1*(SP-min);
    for(int i = 0; i < pop_size; i++){
        if(i == 0){
            if(0 <= r <= probability.at(i)){
                p = i;
                break;
            }
        }
        if(i > 0){
            if(probability.at(i-1) < r <= probability.at(i)){
                p = i;
                break;
            }
        }
    }
    
    return p;
}

void ea::crossover(){
    double r; int p1, p2, cp;
    r = (double)rand()/RAND_MAX;
    p1 = select_parent();
    p2 = select_parent();
    new_pop.at(0).tour = population.at(pop_size-1).tour; //Best individual is always transferred
    new_pop.at(1).tour = population.at(pop_size-2).tour; //2nd Best individual is transferred
    for(int i = 2; i < pop_size/2; i++){
        if(r <= p_cross){
            cp = rand() % n_cities;
            if(cp == 0){
                cp += 2;
            }
            if(cp == 1){
                cp++;
            }
            if(cp == n_cities-1){
                cp -= 2;
            }
            if(cp == n_cities-2){
                cp--;
            }
            for(int j = 1; j < cp; j++){
                new_pop.at(i).tour.at(j) = population.at(p1).tour.at(j);
                new_pop.at(i+1).tour.at(j) = population.at(p2).tour.at(j);
                
            }
            for(int j = cp; j < n_cities-1; j++){
                new_pop.at(i).tour.at(j) = population.at(p2).tour.at(j);
                new_pop.at(i+1).tour.at(j) = population.at(p1).tour.at(j);
            }
        }
        if(r > p_cross){
            new_pop.at(i).tour = population.at(p1).tour;
            new_pop.at(i+1).tour = population.at(p2).tour;
        }
        //assert(new_pop.at(i).tour.at(0) == 0 && new_pop.at(i+1).tour.at(0) == 0);
        //assert(new_pop.at(i).tour.at(n_cities-1) == 0 && new_pop.at(i).tour.at(n_cities-1) == 0);
    }
    population = new_pop;
}

void ea::find_repeats(){
    int c;
    for(int i = 0; i < pop_size; i++){
        for(int j = 1; j < n_cities-1; j++){
            c = population.at(i).tour.at(j);
            for(int k = j+1; k < n_cities-1; k++){
                if(c == population.at(i).tour.at(k)){
                    population.at(i).tour.at(j) = change_city(i);
                    c = population.at(i).tour.at(j);
                }
            }
        }
    }
    /*
    for(int i = 0; i < pop_size; i++){ //Check to make sure starting and ending city do not change
        assert(population.at(i).tour.at(0) == 0);
        assert(population.at(i).tour.at(n_cities-1) == 0);
    }
    for(int i = 0; i < pop_size; i++){ //Make sure no cities are duplicated (except for the last city)
        for(int j = 1; j < n_cities-1; j++){
            c = population.at(i).tour.at(j);
            for(int k = j+1; k < n_cities-1; k++){
                assert(c != population.at(i).tour.at(k));
            }
        }
    }
     */
}

int ea::change_city(int p){
    bool valid = false; int new_city;
    while(valid == false){
        new_city = rand() % (n_cities-1);
        valid = true;
        for(int i = 0; i < n_cities; i++){ //Find a city that is missing after crossover
            if(new_city == population.at(p).tour.at(i)){
                valid = false;
            }
        }
    }
    return new_city;
}

void ea::mutate(){
    double r; int p1, p2, c;
    
    for(int i = 1; i < pop_size; i++){
        r = (double)rand()/RAND_MAX;
        if(r <= p_mut){
            p1 = rand() % (n_cities-1);
            p2 = rand() % (n_cities-1);
            if(p1 == 0){
                p1++;
            }
            if(p2 == 0){
                p2++;
            }
            while(p1 == p2){
                p2 = (rand() % (n_cities-2)) + 1;
            }
            //assert(p1 != 0 && p1 != n_cities-1);
            //assert(p2 != 0 && p2 != n_cities-1);
            iter_swap(population.at(i).tour.begin() + p1, population.at(i).tour.begin() + p2);
        }
    }
    /*
    for(int i = 0; i < pop_size; i++){ //Check to make sure starting and ending city do not change
        assert(population.at(i).tour.at(0) == 0);
        assert(population.at(i).tour.at(n_cities-1) == 0);
    }
    for(int i = 0; i < pop_size; i++){ //Make sure no cities are duplicated (except for the last city)
        for(int j = 1; j < n_cities-1; j++){
            c = population.at(i).tour.at(j);
            for(int k = j+1; k < n_cities-1; k++){
                assert(c != population.at(i).tour.at(k));
            }
        }
    }
     */
}
