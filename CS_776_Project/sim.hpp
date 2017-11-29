//
//  sim.hpp
//  MAMCTS
//
//  Created by Nick Zerbel on 5/25/17.
//  Copyright © 2017 Nick Zerbel. All rights reserved.
//

#ifndef sim_hpp
#define sim_hpp

#include <cstdlib>
#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <time.h>
#include <fstream>
#include "agent.hpp"
#include "tree.hpp"
#include "mcts.hpp"

using namespace std;

class gridworld{
public:
    void initialize_parameters(multi_agent *map, monte_carlo *mcp);
    void cred_evals(multi_agent *map, multi_tree* tp, monte_carlo *mcp);
    void check_goal_conditions(multi_agent *map); //Check if all agents have made it to a goal
    
    //Credit Evaluation
    vector <int> node_vec; //Keeps track of current nodes during credit evaluations
    vector <int> dif_node_vec; //Keeps Track of where each agent's rollout ends in cred eval
    vector <double> dif_rewards; //Tacks the difference reward for each agent
    vector <bool> ag_sim;
    vector <int> episodes;
    vector <int> end_lev;
    void reset_all_agents(multi_agent *map, multi_tree *tp);
    void calculate_global(multi_agent *map, monte_carlo *mcp, multi_tree *tp);
    void calculate_difference(multi_agent *map, monte_carlo *mcp, multi_tree *tp, int agn);
    void clear_all_vectors(multi_agent *map, monte_carlo *mcp, multi_tree *tp); //Clear all vectors for next stat run
    
    //Paramaters
    int x_dim;
    int y_dim;
    int learn_its; //Tracks the number of learning episodes
    bool goal_check; //Makes sure no two agents or goals start off in the same state
    int n_agents; //Number of agents and goals
    bool all_agents_at_goal;
    double g_reward; //Global Reward
    double d_reward; //Difference Reward
    double goal_reward;
    double penalty;
};

#endif /* sim_hpp */
