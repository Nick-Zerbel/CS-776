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

void clear_txt_files(){ //Clear all txt files which get appended when running the code
    ofstream best_p, best_f, ag, gg;
    best_p.open("best_policy.txt", ios::out | ios::trunc);
    best_f.open("best_fit.txt", ios::out | ios::trunc);
    ag.open("Agent_Coordinates.txt", ios::out | ios::trunc);
    gg.open("Goal_Coordinates.txt", ios::out | ios::trunc);
    best_p.close(); best_f.close(); ag.close(); gg.close();
}

void record_best_policy(ea *eap){ //Records best policy and fitness of all time from each stat run
    ofstream best_p, best_f;
    best_p.open("best_policy.txt", ios::app); best_f.open("best_fit.txt", ios::app);
    for(int i = 0; i < eap->a_size; i++){
        best_p << eap->best_policy.at(i) << "\t";
    }
    best_p << "\n";
    best_f << eap->best_fit << "\n";
    best_p.close(); best_f.close();
}

void assign_weights(monte_carlo *mcp, gridworld *gp, ea *eap, limit *lp, int pn){
    eap->decode(0, eap->pop.at(pn).pol);
    mcp->w_rreward = lp->lower + eap->num*((lp->upper-lp->lower)/(pow(2,eap->s_size)-1));
    eap->decode(1, eap->pop.at(pn).pol);
    mcp->w_dist = lp->lower + eap->num*((lp->upper-lp->lower)/(pow(2,eap->s_size)-1));
    eap->decode(2, eap->pop.at(pn).pol);
    gp->w_greward = lp->lower + eap->num*((lp->upper-lp->lower)/(pow(2,eap->s_size)-1));
    eap->decode(3, eap->pop.at(pn).pol);
    gp->w_penalty = lp->lower + eap->num*((lp->upper-lp->lower)/(pow(2,eap->s_size)-1));
    eap->decode(4, eap->pop.at(pn).pol);
    gp->w_step = lp->lower + eap->num*((lp->upper-lp->lower)/(pow(2,eap->s_size)-1));
    eap->decode(5, eap->pop.at(pn).pol);
    gp->w_prox = lp->lower + eap->num*((lp->upper-lp->lower)/(pow(2,eap->s_size)-1));
}

void run_mcts(gridworld *gp, multi_agent *map, monte_carlo *mcp, multi_tree *tp, int sruns, int ai, int amax, int rmax, int incr){
    int group; group = 0;
    for(gp->n_agents = ai; gp->n_agents <= amax;){
        for(int s = 0; s < sruns; s++){
            gp->initialize_parameters(map, mcp);
            mcp->create_root_nodes(tp, map);
            while(gp->gridworld_finished == false){
                gp->learn_its++; //Tracks the number of learning episodes until MCTS find a solution
                for(int anum = 0; anum < gp->n_agents; anum++){ //anum = agent number
                    mcp->set_mc_parameters(tp, anum);
                    mcp->mc_search(tp, map); //Runs MCTS for defined number of expansions
                    mcp->n_num_vec.at(anum) = mcp->node_number; //Used to track what the current node number is in each tree
                }
                gp->cred_evals(map, tp, mcp);
                //Check to see if agents have arrived at goals
                gp->check_goal_conditions(map);
                if(gp->goal_check == true){
                    gp->gridworld_finished = true;
                }
                if(gp->gridworld_finished == false){
                    gp->reset_all_agents(map, tp);
                }
                if(gp->learn_its >= rmax){
                    break;
                }
            }
            //Record Information
            gp->episodes.at(group) = (double)gp->learn_its;
            gp->clear_all_vectors(map, mcp, tp);
        }
        group++;
        gp->n_agents += incr;
    }
}

int main() {
    srand( time(NULL) );
    
    gridworld g; monte_carlo mcts; multi_tree t; multi_agent m; ea e; limit lim;
    gridworld *gp = &g; monte_carlo *mcp = &mcts; multi_tree *tp = &t; multi_agent *map = &m; ea *eap = &e; limit *lp = &lim;
    
    //MCTS Parameters
    gp->x_dim = 4; //Maximum X Dimension
    gp->y_dim = 4; //Maximum Y Dimension
    int agent_increment = 1; //Increases the number of agents in a simulation by this amount
    int max_agents = 4; //Maximum number of agents to be tested
    int starting_agents = max_agents; //Initial number of agents being tested
    int n_groups = ((max_agents - starting_agents)/agent_increment) + 1; //Number of agent groups being tested
    int stat_runs = 1; //Number of statistical runs for MCTS
    int max_run = 200; //Cuts off the simulation if the number of iterations exceed this amount
    mcp->obs_dist = 10;
    mcp->epsilon = 0; //UCB1 exploration constant (0 = greedy action selection)
    mcp->rollout_steps = 10; //Number of rollout steps during random rollout
    mcp->mc_iterations = 1; //Number of iterations of MCTS each agent performs
    gp->goal_reward = 1;
    mcp->rollout_reward = 1;
    gp->penalty = 1;
    
    //EA Parameters
    int ea_s_runs = 30; //Number of stat runs for the EA
    int max_gen = 200; //Maximum number of generations to evolve
    lp->upper = 100; //Upper limit of EA weights
    lp->lower = 0; //Lower limit of EA weights
    eap->pop_size = 10; //Population size (must be even)
    eap->p_cross = 0.67; //Probability of Crossover
    eap->p_mut = 0.9; //Probability of mutation
    eap->n_weights = 6; //Number of weights the GA is evolving
    eap->s_size = (int)floor((log(lp->upper)/log(2))+1); //String Size
    //cout << eap->s_size << endl;
    eap->a_size = eap->n_weights*eap->s_size; //Array Size
    //cout << eap->a_size << endl;
    eap->n_steps = mcp->rollout_steps;
    
    //Fitness Data
    double n_successful;
    double optimality; //Percentage optimality
    double reliability; //Percentage reliability (what percentage of runs were successful)
    double mr = (double)max_run; //Double version of maximum number of MCTS runs
    double total_groups = (double)n_groups; //Total number of agent groups
    double speed; //How many episodes it takes MCTS to learn
    
    clear_txt_files(); //Clear all txt files which get appended
    
    ofstream max_fit, avg_fit, min_fit;
    max_fit.open("max_fitness.txt"); avg_fit.open("average_fitness.txt"); min_fit.open("min_fitness.txt");
    
    for(int i = 0; i < n_groups; i++){
        gp->episodes.push_back(0); //For measuring speed and reliability
    }
    
    for(int srn = 0; srn < ea_s_runs; srn++){ //Stat Runs for EA
        eap->create_pop();
        //cout << "Stat Run: " << srn << endl;
        for(int i = 0; i < max_gen; i++){
            //cout << "Gen: " << i << endl;
            if(i % 200 == 0){ //Reset Agent Coordinates every X generations
                map->create_new_sys(max_agents, gp->x_dim, gp->y_dim);
            }
            for(int j = 0; j < eap->pop_size; j++){
                assign_weights(mcp, gp, eap, lp, j);
                mcp->rollout_policy = eap->roll_pop.at(j).pol;
                run_mcts(gp, map, mcp, tp, stat_runs, starting_agents, max_agents, max_run, agent_increment);
                
                //Evaluate Fitness
                /*
                n_successful = total_groups;
                for(int ng = 0; ng < n_groups; ng++){
                    speed = mr - gp->episodes.at(ng); //Average number of episodes
                    optimality = 100*(mr - gp->episodes.at(ng))/mr;
                    if(gp->episodes.at(ng) >= mr){
                        n_successful--;
                    }
                }
                reliability = 100*(n_successful/total_groups);
                 eap->fit_vec.at(j) = reliability + optimality;
                 */
                eap->fit_vec.at(j) = mr - gp->episodes.at(0);
            }
            eap->re_order();
            eap->calc_fit_prob();
            max_fit << eap->fit_vec.at(0) << "\t";
            avg_fit << eap->fit_sum/eap->pop_size << "\t";
            min_fit << eap->fit_vec.at(eap->pop_size-1) << "\t";
            if(eap->fit_vec.at(0) > eap->best_fit){
                eap->best_fit = eap->fit_vec.at(0);
                eap->best_policy = eap->pop.at(0).pol;
            }
            eap->crossover();
            eap->mutation();
            eap->roll_crossover();
            eap->roll_mutation();
        }
        record_best_policy(eap);
        max_fit << endl; avg_fit << endl; min_fit << endl;
        eap->clear_vecs();
    }
    
    max_fit.close(); avg_fit.close(); min_fit.close();
    
    return 0;
}
