//
//  sim.cpp
//  MAMCTS
//
//  Created by Nick Zerbel on 5/25/17.
//  Copyright © 2017 Nick Zerbel. All rights reserved.
//

#include "sim.hpp"

//GRIDWORLD PROBLEM---------------------------------------------------------------------------------------------------------
void gridworld::initialize_parameters(multi_agent *map, monte_carlo *mcp){
    for(int i = 0; i < n_agents; i++){
        mcp->n_num_vec.push_back(0);
        node_vec.push_back(0);
        ag_sim.push_back(true);
        dif_rewards.push_back(0);
        dif_nodes.push_back(0);
    }
    map->agent_vec.clear();
    map->goal_vec.clear();
    map->assign_agent_coordinates(n_agents);
    map->assign_goal_coordinates();
    mcp->node_number = 0;
    all_agents_at_goal = false;
    learn_its = 0;
    mcp->x_lim = x_dim;
    mcp->y_lim = y_dim;
}

void gridworld::check_goal_conditions(multi_agent *map){
    goal_check = true;
    bool check;
    
    for(int i = 0; i < map->n_agents; i++){ //Agent Number
        check = false;
        for(int j = 0; j < map->n_agents; j++){ //Goal Number
            if(map->agent_vec.at(i).agent_x == map->goal_vec.at(j).goal_x && map->agent_vec.at(i).agent_y == map->goal_vec.at(j).goal_y){
                check = true;
                break;
            }
        }
        if(check == false){ //If one agent's coordinates do not match a goal's coordinates, boolean is changed to false
            goal_check = false;
            break;
        }
    }
    if(goal_check == true){
        all_agents_at_goal = true;
    }
}

//Credit Evaluation Functions ---------------------------------------------------------------------------------------
void gridworld::cred_evals(multi_agent *map, multi_tree *tp, monte_carlo *mcp){
    vector <int> tree_sizes; int max_size;
    for(int i = 0; i < n_agents; i++){
        tree_sizes.push_back(tp->ag_tree.at(i).tree_vec.size());
    }
    max_size = *max_element(tree_sizes.begin(), tree_sizes.end());

    reset_all_agents(map, tp);
    calculate_global(map, mcp, tp, max_size);
    for(int a = 0; a < n_agents; a++){
        reset_all_agents(map, tp);
        calculate_difference(map, mcp, tp, max_size, a);
    }
    for(int i = 0; i < n_agents; i++){ //Agent
        for(int j = 0; j < tp->ag_tree.at(i).tree_vec.size(); j++){ //Level of Tree
            for(int k = 0; k < tp->ag_tree.at(i).tree_vec.at(j).level_vec.size(); k++){ //Node
                if(dif_nodes.at(i) == tp->ag_tree.at(i).tree_vec.at(j).level_vec.at(k).n_number){ //Final unexpanded node was set to parent node in vector
                    mcp->parent_number = tp->ag_tree.at(i).tree_vec.at(j).level_vec.at(k).p_number;
                    mcp->back_propagate_evals(map, tp, dif_rewards.at(i), i, j, dif_nodes.at(i));
                    goto next;
                }
            }
        }
    next:
        max_size = 0;
    }
    tree_sizes.clear();
}

void gridworld::reset_all_agents(multi_agent *map, multi_tree *tp){ //Resets all agents to initial positions
    for(int i = 0; i < n_agents; i++){ //Agent Number
        map->agent_vec.at(i).agent_x = tp->ag_tree.at(i).tree_vec.at(0).level_vec.at(0).x;
        map->agent_vec.at(i).agent_y = tp->ag_tree.at(i).tree_vec.at(0).level_vec.at(0).y;
        node_vec.at(i) = 0;
        ag_sim.at(i) = true;
    }
}

void gridworld::find_current_node(multi_agent *map, monte_carlo *mcp, multi_tree *tp, int agn, int l){ //agn = agent number, l = level
    double ax, ay;
    ax = map->agent_vec.at(agn).agent_x;
    ay = map->agent_vec.at(agn).agent_y;
    assert(l < tp->ag_tree.at(agn).tree_vec.size());
    mcp->action_check = false;
    mcp->current_node = node_vec.at(agn);
    for(int i = 0; i < tp->ag_tree.at(agn).tree_vec.at(l).level_vec.size(); i++){
        if(mcp->current_node == tp->ag_tree.at(agn).tree_vec.at(l).level_vec.at(i).n_number){
            if(ax == tp->ag_tree.at(agn).tree_vec.at(l).level_vec.at(i).x && ay == tp->ag_tree.at(agn).tree_vec.at(l).level_vec.at(i).y){
                mcp->parent_number = tp->ag_tree.at(agn).tree_vec.at(l).level_vec.at(i).n_number;
                mcp->action_check = true;
                break;
            }
        }
    }
    assert(mcp->action_check == true);
}

void gridworld::calculate_global(multi_agent *map, monte_carlo *mcp, multi_tree *tp, int s){
    int act, l; l = 1; g_reward = 0;
    while(l < s){ //l = tree level
        if(l >= s){ //If level is equal to or greater than max tree size, quit
            break;
        }
        
        //Each Agent takes a step if able
        for(int a = 0; a < n_agents; a++){ //Agent Number
            if(l < tp->ag_tree.at(a).tree_vec.size()){ //If level exceeds the maximum size of tree, do not calculate
                map->check_agent_status(a); //Check if agent is at a goal
                
                if(map->agent_in_play == true && ag_sim.at(a) == true){ //If agent has not reached a goal, continue
                    find_current_node(map, mcp, tp, a, (l-1)); //(agent_number, level) find current parent node
                    act = mcp->select_move(tp, a, l); //(agent_number, level) choose best child node
                    if(mcp->action_check == false){
                        ag_sim.at(a) = false;
                    }
                    if(mcp->action_check == true){ //If a child node was found
                        node_vec.at(a) = mcp->current_node;
                        dif_nodes.at(a) = mcp->current_node;
                        map->agent_move(a, act);
                        map->check_agent_status(a);
                        map->check_agent_coordinates(a, map->agent_vec.at(a).agent_x, map->agent_vec.at(a).agent_y);
                        if(map->agent_in_play == false && map->already_taken == false){
                            g_reward += goal_reward;
                        }
                        if(map->agent_in_play == false && map->already_taken == true){
                            g_reward -= penalty;
                        }
                        if(map->agent_in_play == true){
                            g_reward--;
                        }
                    }
                }
            }
        }
        l++; //Increase level
    }
}

void gridworld::calculate_difference(multi_agent *map, monte_carlo *mcp, multi_tree *tp, int s, int agn){
    int act, l; l = 1; double temp_reward; temp_reward = 0;
    while(l < s){ //l = tree level
        if(l >= s){ //If level is equal to or greater than max tree size, quit
            break;
        }
        //Each Agent takes a step if able
        for(int a = 0; a < n_agents; a++){ //Agent Number
            if(l < tp->ag_tree.at(a).tree_vec.size()){ //If level exceeds the maximum size of tree, do not calculate
                map->check_agent_status(a); //Check if agent is at a goal
                
                if(map->agent_in_play == true && ag_sim.at(a) == true){ //If agent has not reached a goal, continue
                    find_current_node(map, mcp, tp, a, (l-1)); //(agent_number, level) find current parent node
                    act = mcp->select_move(tp, a, l); //(agent_number, level) choose best child node
                    if(mcp->action_check == false){
                        ag_sim.at(a) = false;
                    }
                    if(mcp->action_check == true){ //If a child node was found
                        node_vec.at(a) = mcp->current_node;
                        map->agent_move(a, act);
                        map->check_agent_status(a);
                        map->check_agent_coordinates(a, map->agent_vec.at(a).agent_x, map->agent_vec.at(a).agent_y);
                        if(map->agent_in_play == false && map->already_taken == false){
                            if(a != agn){
                                temp_reward += goal_reward;
                            }
                        }
                        if(map->agent_in_play == false && map->already_taken == true){
                            if(a != agn){
                                temp_reward -= penalty;
                            }
                        }
                        if(map->agent_in_play == true){
                            if(a != agn){
                                temp_reward--;
                            }
                        }
                    }
                }
            }
        }
        l++; //Increase level
    }
    
    d_reward = g_reward - temp_reward;
    dif_rewards.at(agn) = d_reward;
}

void gridworld::clear_all_vectors(multi_agent *map, monte_carlo *mcp, multi_tree *tp){
    tp->ag_tree.clear();
    mcp->reward_vec.clear();
    map->agent_vec.clear();
    map->goal_vec.clear();
    mcp->n_num_vec.clear();
    node_vec.clear();
    ag_sim.clear();
    dif_nodes.clear();
    dif_rewards.clear();
}
