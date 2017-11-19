//
//  mcts.hpp
//  MAMCTS
//
//  Created by Nick Zerbel on 5/25/17.
//  Copyright © 2017 Nick Zerbel. All rights reserved.
//

#ifndef mcts_hpp
#define mcts_hpp

#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
#include <assert.h>
#include <algorithm>
#include "tree.hpp"
#include "agent.hpp"


using namespace std;

class monte_carlo{
public:
    void set_mc_parameters(multi_tree *tp, int a);
    void create_root_nodes(multi_tree *tp, multi_agent *map);
    void mc_search(multi_tree *tp, multi_agent *map);
    
    //SELECTION
    void select(multi_tree *tp); //Choose an action
    int select_move(multi_tree *tp, int agn, int l); //Choose move which the agent will take after MCTS simulation
    void reset_q_roll(multi_tree *tp);
    
    //EXPANSION
    void expand(multi_tree *tp);
    void move_left(multi_tree *tp);
    void move_right(multi_tree *tp);
    void move_up(multi_tree *tp);
    void move_down(multi_tree *tp);
    void no_move(multi_tree *tp);
    void update_node_numbers(multi_tree *tp);
    void pruning(multi_tree *tp);
    void check_boundaries(double xx, double yy); //Agent cannot move outside Gridworld
    void prune(multi_tree *tp, int l); //Agent cannot re-visit a state when expanding the tree
    void reset_coordinates();
    
    //SIMULATION
    int select_node(multi_tree *tp); //Select an expanded node for rollout
    void rollout(multi_tree *tp, multi_agent *map, int n);
    void calculate_node_value(multi_tree *tp, int n);
    
    //BACK-PROPAGATION
    void back_propagate(multi_tree *tp);
    void back_propagate_evals(multi_agent *map, multi_tree *tp, double reward, int agn, int l, int nn);
    
    //Parameters
    vector <double> reward_vec;
    vector <int> n_num_vec;
    bool action_check; //Flags possible actions as valid or invalid
    int node_chosen;
    double parent_visit;
    double node_visit;
    int lev; //Current level of the tree
    int n_nodes; //Number of nodes currently in a level in the tree
    int node_number;
    int parent_number;
    int current_node;
    int a_num; //Designates which agent is currently simulating
    int n_agents; //Number of agents and goals
    int action;
    
    //Experimental Parameters
    int rollout_its; //Number of rollout iterations
    double obs_dist; //Observable Distance
    double epsilon; //Exploration vs Exploitation parameter for UCB1
    double gamma; //Discount factor for rollout value
    double alpha; //Discount factor for credit eval values
    int mc_iterations; //Number of expansion iterations MCTS does each episode
    int max_lev; //Cap on the maximum tree level
    double rollout_reward;
    
    //Coordinates
    double ax; //Current agent x coordinate
    double ay; //Current agent y coordinate
    double previous_x; //Previous agent x coordinate
    double previous_y; //Previous agent y coordinate
    double prune_x;
    double prune_y;
    int x_lim; //Maximum x dimension
    int y_lim; //Maximum y dimension
};

#endif /* mcts_hpp */
