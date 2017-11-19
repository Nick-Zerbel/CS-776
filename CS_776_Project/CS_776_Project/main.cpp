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

void record_parameters(ea *eap){ //stat-runs, max_runs, increment, starting agents, max agents
    ofstream par; par.open("best_parameters.txt");
    par << eap->pop.at(0).goal_r << endl;
    par << eap->pop.at(0).p << endl;
    par << eap->pop.at(0).roll_r << endl;
    par << eap->pop.at(0).eps << endl;
    par << eap->pop.at(0).roll_its << endl;
    par << eap->pop.at(0).mc_its << endl;
    par << eap->pop.at(0).obs_d << endl;
    par.close();
}

void create_coordinate_file(gridworld *gp, multi_agent *map, int ma){
    map->create_agent_vec(ma, gp->x_dim, gp->y_dim);
    map->create_goal_vec();
    map->agent_vec.clear(); map->goal_vec.clear();
}

void run_mcts(gridworld *gp, multi_agent *map, monte_carlo *mcp, multi_tree *tp, int sruns, int ai, int amax, int rmax, int incr){
    ofstream data_d;
    data_d.open("difference_its.txt");
    
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
            data_d << gp->learn_its << "\t";
            gp->clear_all_vectors(map, mcp, tp);
        }
        gp->n_agents += incr;
        data_d << endl;
    }
    data_d.close();
}

int main() {
    srand( time(NULL) );
    
    gridworld g; monte_carlo mcts; multi_tree t; multi_agent m; ea e; limits l;
    gridworld *gp = &g; monte_carlo *mcp = &mcts; multi_tree *tp = &t; multi_agent *map = &m; ea *eap = &e; limits *lp = &l;
    
    //Static Parameters
    bool create_file = false; //If true, a new txt file is created with agent and goal starting coordinates
    gp->x_dim = 10; //Maximum X Dimension
    gp->y_dim = 10; //Maximum Y Dimension
    int agent_increment = 1; //Increases the number of agents in a simulation by this amount
    int starting_agents = 2; //Initial number of agents being tested
    int max_agents = 5; //Maximum number of agents to be tested
    int n_groups = ((max_agents - starting_agents)/agent_increment) + 1; //Number of agent groups being tested
    mcp->max_lev = g.x_dim + g.y_dim;
    lp->mci_max = mcp->max_lev;
    int stat_runs = 10; //Number of statistical runs
    int max_run = 1000; //Cuts off the simulation if the number of iterations exceed this amount
    int max_gen = 100; //Maximum number of generations to evolve
    eap->pop_size = 10;
    eap->p_mut = 0.99; //Probability of mutation
    
    double n_successful;
    double episode;
    vector <double> reliability;
    for(int i = 0; i < n_groups; i++){
        reliability.push_back(0);
    }
    
    if(create_file == true){
        create_coordinate_file(gp, map, max_agents);
    }
    eap->create_pop(lp);
    
    ofstream fit; //Records best fitness per generation
    fit.open("best_fitness.txt");
    
    for(int i = 0; i < max_gen; i++){
        cout << "Gen: " << i << endl;
        for(int j = 0; j < eap->pop_size; j++){
            //Testing Parameters
            gp->goal_reward = eap->pop.at(i).goal_r; //Reward for reaching an unclaimed goal
            gp->penalty = eap->pop.at(i).p; //Penalty for reaching a claimed goal
            mcp->rollout_reward = eap->pop.at(i).roll_r;
            mcp->epsilon = eap->pop.at(i).eps; //UCB1 exploration constant (0 = greedy action selection)
            mcp->rollout_its = eap->pop.at(i).roll_its;//g.x_dim + g.y_dim; //Number of rollout moves
            mcp->mc_iterations = eap->pop.at(i).mc_its; //Number of iterations of MCTS each agent performs
            mcp->obs_dist = eap->pop.at(i).obs_d; //The observable distance
            
            run_mcts(gp, map, mcp, tp, stat_runs, starting_agents, max_agents, max_run, agent_increment);
            ifstream itdata("difference_its.txt");
            n_successful = (double)(n_groups * stat_runs); //Total number of runs
            for(int ng = 0; ng < n_groups; ng++){
                for(int sr = 0; sr < stat_runs; sr++){
                    itdata >> episode;
                    if(episode >= max_run){
                        n_successful--;
                    }
                }
            }
            eap->fit_vec.at(j) = n_successful/(n_groups * stat_runs); //Number of successful runs out of total runs
            itdata.close();
        }
        eap->re_order();
        fit << eap->fit_vec.at(0) << "\n";
        eap->mutation(lp);
    }
    fit.close();
    record_parameters(eap);
    
    return 0;
}
