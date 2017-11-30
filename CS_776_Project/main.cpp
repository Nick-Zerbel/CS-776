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

void clear_txt_files(){
    ofstream best, ag, gg;
    best.open("best_policy.txt", ios::out | ios::trunc);
    ag.open("Agent_Coordinates.txt", ios::out | ios::trunc);
    gg.open("Goal_Coordinates.txt", ios::out | ios::trunc);
    best.close(); ag.close(); gg.close();
}

void record_best_policy(ea *eap){ //Records best policy from each stat run
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
                if(gp->learn_its >= rmax){
                    break;
                }
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
            }
            //Record Information
            gp->episodes.at(group) = (double)gp->learn_its;
            gp->agent_steps.at(group) = (double)*max_element(gp->end_lev.begin(), gp->end_lev.end());
            gp->clear_all_vectors(map, mcp, tp);
        }
        group++;
        gp->n_agents += incr;
    }
}

int main() {
    srand( time(NULL) );
    
    gridworld g; monte_carlo mcts; multi_tree t; multi_agent m; ea e;
    gridworld *gp = &g; monte_carlo *mcp = &mcts; multi_tree *tp = &t; multi_agent *map = &m; ea *eap = &e;
    
    //MCTS Parameters
    gp->x_dim = 4; //Maximum X Dimension
    gp->y_dim = 4; //Maximum Y Dimension
    int agent_increment = 1; //Increases the number of agents in a simulation by this amount
    int starting_agents = 4; //Initial number of agents being tested
    int max_agents = 4; //Maximum number of agents to be tested
    int n_groups = ((max_agents - starting_agents)/agent_increment) + 1; //Number of agent groups being tested
    int stat_runs = 1; //Number of statistical runs for MCTS
    int max_run = 300; //Cuts off the simulation if the number of iterations exceed this amount
    mcp->epsilon = 0; //UCB1 exploration constant (0 = greedy action selection)
    mcp->rollout_steps = 20; //Number of rollout moves
    mcp->mc_iterations = 3; //Number of iterations of MCTS each agent performs
    gp->goal_reward = 10;
    mcp->rollout_reward = 1;
    gp->penalty = 1;
    
    //EA Parameters
    int ea_s_runs = 10; //Number of stat runs for the EA
    int max_gen = 100; //Maximum number of generations to evolve
    eap->pop_size = 10; //Population size (must be even)
    eap->p_cross = 0.7; //Probability of Crossover
    eap->p_mut = 0.2; //Probability of mutation
    eap->a_size = mcp->rollout_steps;
    
    //Fitness Data
    double n_successful; //Number of succsseful runs out of all stat runs
    double optimality; //Percentage optimality
    double max_steps = (double)gp->x_dim + (double)gp->y_dim; //Maximum Number of steps
    double reliability; //Percentage reliability
    double mr = (double)max_run; //Double version of maximum number of MCTS runs
    double total_groups = (double)n_groups; //Total number of agent groups
    double speed;
    
    clear_txt_files(); //Clear all txt files which get appended
    
    ofstream max_fit, avg_fit, min_fit;
    max_fit.open("max_fitness.txt"); avg_fit.open("average_fitness.txt"); min_fit.open("min_fitness.txt");
    
    for(int i = 0; i < n_groups; i++){
        gp->episodes.push_back(0); //For measuring speed and reliability
        gp->agent_steps.push_back(0); //For measuring optimality
    }
    
    for(int srn = 0; srn < ea_s_runs; srn++){ //Stat Runs for EA
        eap->create_pop();
        cout << "Stat Run: " << srn << endl;
        for(int i = 0; i < max_gen; i++){
            cout << "Gen: " << i << endl;
            if(i % 100 == 0){ //Reset Agent Coordinates every X generations
                map->create_new_sys(max_agents, gp->x_dim, gp->y_dim);
            }
            for(int j = 0; j < eap->pop_size; j++){
                mcp->rollout_policy = eap->pop.at(j).pol;
                run_mcts(gp, map, mcp, tp, stat_runs, starting_agents, max_agents, max_run, agent_increment);
                
                //Evaluate Fitness
                n_successful = total_groups;
                speed = 0;
                optimality = 0;
                for(int ng = 0; ng < n_groups; ng++){
                    speed += mr - gp->episodes.at(ng);
                    optimality += max_steps - gp->agent_steps.at(ng);
                    if(gp->episodes.at(ng) >= mr){
                        n_successful -= 1;
                    }
                }
                reliability = n_successful/total_groups; //Number of successful runs out of total runs
                
                eap->fit_vec.at(j) = speed;
            }
            eap->re_order();
            eap->calc_fit_prob();
            max_fit << *max_element(eap->fit_vec.begin(), eap->fit_vec.end()) << "\t";
            avg_fit << eap->fit_sum/eap->pop_size << "\t";
            min_fit << *min_element(eap->fit_vec.begin(), eap->fit_vec.end())<< "\t";
            eap->crossover();
            eap->mutation();
        }
        record_best_policy(eap);
        max_fit << endl; avg_fit << endl; min_fit << endl;
        eap->clear_vecs();
    }
    
    max_fit.close(); avg_fit.close(); min_fit.close();
    
    return 0;
}
