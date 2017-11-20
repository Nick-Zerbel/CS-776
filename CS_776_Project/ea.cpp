//
//  ea.cpp
//  CS_776_Project
//
//  Created by Nick Zerbel on 11/16/17.
//  Copyright © 2017 Nicholas Zerbel. All rights reserved.
//

#include "ea.hpp"

void ea::create_pop(limits *lp){
    parameters p;
    
    for(int i = 0; i < pop_size; i++){
        pop.push_back(p);
        fit_vec.push_back(0);
    }
    for(int i = 0; i < pop_size; i++){
        pop.at(i).goal_r = (double)((rand() % (lp->gr_max - lp->gr_min)) + lp->gr_min);
        pop.at(i).p = (double)((rand() % (lp->p_max - lp->p_min)) + lp->p_min);
        pop.at(i).roll_r = (double)((rand() % (lp->rr_max - lp->rr_min) + lp->rr_min));
        pop.at(i).eps = (double)((rand() % (lp->eps_max - lp->eps_min)) + lp->eps_min) + (double)(rand()/RAND_MAX);
        pop.at(i).roll_its = (rand() % (lp->ri_max - lp->ri_min)) + lp->ri_min;
        pop.at(i).mc_its = (rand() % (lp->mci_max - lp->mci_min)) + lp->mci_min;
        pop.at(i).obs_d = (double)((rand() % (lp->od_max - lp->od_min)) + lp->od_min);
    }
}

void ea::re_order(){
    int p1, p2;
    for(int i = 0; i < pop_size; i++){
        p1 = i;
        for(int j = 0; j < pop_size; j++){
            p2 = j;
            if(i != j){
                if(fit_vec.at(j) > fit_vec.at(i)){
                    iter_swap(fit_vec.begin() + p1, fit_vec.begin() + p2);
                    iter_swap(pop.begin() + p1, pop.begin() + p2);
                }
            }
        }
    }
}

void ea::mutation(limits *lp){
    double prob; int par;
    for(int i = 1; i < pop_size; i++){
        prob = (double)(rand()/RAND_MAX);
        if(prob <= p_mut){
            par = rand() % 7;
            if(par == 0){
                pop.at(i).goal_r = (double)((rand() % (lp->gr_max - lp->gr_min)) + lp->gr_min);
            }
            if(par == 1){
                pop.at(i).p = (double)((rand() % (lp->p_max - lp->p_min)) + lp->p_min);
            }
            if(par == 2){
                pop.at(i).roll_r = (double)((rand() % (lp->rr_max - lp->rr_min) + lp->rr_min));
            }
            if(par == 3){
                pop.at(i).eps = (double)((rand() % (lp->eps_max - lp->eps_min)) + lp->eps_min) + (double)(rand()/RAND_MAX);
            }
            if(par == 4){
                pop.at(i).roll_its = (rand() % (lp->ri_max - lp->ri_min)) + lp->ri_min;
            }
            if(par == 5){
                pop.at(i).mc_its = (rand() % (lp->mci_max - lp->mci_min)) + lp->mci_min;
            }
            if(par == 6){
                pop.at(i).obs_d = (double)((rand() % (lp->od_max - lp->od_min)) + lp->od_min);
            }
        }
    }
}
