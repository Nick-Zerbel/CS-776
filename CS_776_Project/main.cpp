//
//  main.cpp
//  CS_776_Project
//
//  Created by Nick Zerbel on 11/16/17.
//  Copyright © 2017 Nicholas Zerbel. All rights reserved.
//

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <assert.h>
#include "ea.hpp"
#include "agent.hpp"
#include "sim.hpp"
#include "tree.hpp"
#include "sim.hpp"

using namespace std;

void record_best_policy(ea *eap){
    ofstream best; best.open("best_policy.txt", ios::app);
    for(int i = 0; i < eap->a_size; i++){
        best << eap->pop.at(0).pol.at(i) << "\t";
    }
    best << "\n";
    best.close();
}

void run_mcts(gridworld *gp, multi_agent *map, monte_carlo *mcp, multi_tree *tp, int sruns, int ai, int amax, int rmax, int incr){
    int group; group = 0;
    for(gp->n_agents = ai; gp->n_agents <= amax;){
        for(int s = 0; s < sruns; s++){
            gp->initialize_parameters(map, mcp);
            mcp->create_root_nodes(tp, map);
            while(gp->all_agents_at_goal == false){
                gp->learn_its++; //Tracks the number of learning episodes until MCTS find a solution
                for(int anum = 0; anum < gp->n_agents; anum++){ //anum = agent number
                    mcp->set_mc_parameters(tp, anum);
                    mcp->mc_search(tp, map); //Runs MCTS for defined number of expansions
                    mcp->n_num_vec.at(anum) = mcp->node_number; //Used to track what the current node number is in each tree
                }
                gp->cred_evals(map, tp, mcp);
                for(int aaa = 0; aaa < map->n_agents; aaa++){
                    map->check_agent_coordinates(aaa, map->agent_vec.at(aaa).agent_x, map->agent_vec.at(aaa).agent_y);
                    if(map->already_taken == true){
                        gp->reset_all_agents(map, tp);
                        break;
                    }
                }
                gp->check_goal_conditions(map); //Check if all agents are coupled with goals
                if(gp->all_agents_at_goal == false){
                    gp->reset_all_agents(map, tp);
                }
                if(gp->learn_its >= rmax){
                    break;
                }
            }
            //Record Information
            gp->episodes.at(group) = gp->learn_its;
            gp->clear_all_vectors(map, mcp, tp);
        }
        group++;
        gp->n_agents += incr;
    }
}

int main() {
    srand( time(NULL) );
    
    gridworld g; monte_carlo mcts; multi_tree t; multi_agent m; ea e; limits l;
    gridworld *gp = &g; monte_carlo *mcp = &mcts; multi_tree *tp = &t; multi_agent *map = &m; ea *eap = &e; limits *lp = &l;
    
    //MCTS Parameters
    gp->x_dim = 10; //Maximum X Dimension
    gp->y_dim = 10; //Maximum Y Dimension
    int agent_increment = 5; //Increases the number of agents in a simulation by this amount
    int starting_agents = 5; //Initial number of agents being tested
    int max_agents = 25; //Maximum number of agents to be tested
    int n_groups = ((max_agents - starting_agents)/agent_increment) + 1; //Number of agent groups being tested
    mcp->max_lev = g.x_dim + g.y_dim;
    int stat_runs = 1; //Number of statistical runs for MCTS
    int max_run = 1000; //Cuts off the simulation if the number of iterations exceed this amount
    mcp->epsilon = 1; //UCB1 exploration constant (0 = greedy action selection)
    mcp->rollout_its = 100; //Number of rollout moves
    mcp->mc_iterations = 5; //Number of iterations of MCTS each agent performs
    mcp->obs_dist = 1000; //The observable distance
    
    //EA Parameters
    int ea_s_runs = 30; //Number of stat runs for the EA
    int max_gen = 100; //Maximum number of generations to evolve
    eap->pop_size = 10; //Population size (must be even)
    eap->p_cross = 0.5; //Probability of Crossover
    eap->p_mut = 0.2; //Probability of mutation
    
    //Fitness Data
    double n_successful; //Number of succsseful runs out of all stat runs
    int ep;
    double optimality; //Percentage optimality
    double learn_eps; //Average number of learning episodes.
    double reliability; //Percentage reliability
    double mr = (double)max_run;
    double total_runs = (double)n_groups;
    
    ofstream max_fit; ofstream avg_fit; ofstream min_fit;
    max_fit.open("max_fitness.txt"); avg_fit.open("average_fitness.txt"); min_fit.open("min_fitness.txt");
    
    for(int i = 0; i < n_groups; i++){
        gp->episodes.push_back(0);
    }
    for(int i = 0; i < 5; i++){
        mcp->roll_probs.push_back(0);
    }
    
    for(int srn = 0; srn < ea_s_runs; srn++){ //Stat Runs for EA
        eap->create_pop(lp);
        for(int i = 0; i < max_gen; i++){
            for(int j = 0; j < eap->pop_size; j++){
                eap->decode(0, 10, j);
                gp->goal_reward = lp->low_lim + eap->num*(abs(lp->up_lim - lp->low_lim)/(pow(2,10)-1));
                eap->decode(1, 10, j);
                gp->penalty = lp->low_lim + eap->num*(abs(lp->up_lim - lp->low_lim)/(pow(2,10)-1));
                eap->decode(2, 10, j);
                mcp->rollout_reward = lp->low_lim + eap->num*(abs(lp->up_lim - lp->low_lim)/(pow(2,10)-1));
                for(int p = 0; p < 5; p++){
                    eap->decode(3+p, 10, j);
                    mcp->roll_probs.at(p) = lp->low_lim + eap->num*(abs(lp->up_lim - lp->low_lim)/(pow(2,10)-1));
                }
                
                if(i % 10 == 0){ //Reset Agent Coordinates every 5 generations
                    map->agent_vec.clear();
                    map->goal_vec.clear();
                    map->create_agent_vec(max_agents, gp->x_dim, gp->y_dim);
                    map->create_goal_vec();
                    map->agent_vec.clear();
                    map->goal_vec.clear();
                }
                
                run_mcts(gp, map, mcp, tp, stat_runs, starting_agents, max_agents, max_run, agent_increment);
                
                //Evaluate Fitness
                n_successful = total_runs;
                learn_eps = 0;
                for(int ng = 0; ng < n_groups; ng++){
                    ep = gp->episodes.at(ng);
                    learn_eps += (double)gp->episodes.at(ng);
                    if(ep >= max_run){
                        n_successful -= 1;
                    }
                }
                learn_eps /= (double)(n_groups);
                optimality = (mr - learn_eps)/mr;
                reliability = (double)(n_successful/n_groups);
                eap->fit_vec.at(j) = reliability*100 + optimality*100;
                assert(eap->fit_vec.at(j) >= 0);
            }
            eap->re_order();
            eap->calc_fit_prob();
            max_fit << eap->fit_vec.at(0) << "\t";
            avg_fit << eap->fit_sum/eap->pop_size << "\t";
            min_fit << eap->fit_vec.at(eap->pop_size-1) << "\t";
            eap->crossover();
            eap->mutation();
        }
        record_best_policy(eap);
        max_fit << endl;
        avg_fit << endl;
        min_fit << endl;
        eap->pop.clear();
        eap->new_pop.clear();
        eap->fit_vec.clear();
        eap->fit_prob.clear();
    }
    
    max_fit.close(); avg_fit.close(); min_fit.close();
    
    return 0;
}
