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
        end_lev.push_back(0);
    }
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
    reset_all_agents(map, tp);
    calculate_global(map, mcp, tp);
    for(int a = 0; a < n_agents; a++){
        reset_all_agents(map, tp);
        calculate_difference(map, mcp, tp, a);
    }
    
    for(int i = 0; i < n_agents; i++){ //Agent
        mcp->back_propagate_evals(map, tp, dif_rewards.at(i), i, end_lev.at(i), dif_node_vec.at(i));
    }
}

void gridworld::reset_all_agents(multi_agent *map, multi_tree *tp){ //Resets all agents to root positions
    for(int i = 0; i < n_agents; i++){ //Agent Number
        map->agent_vec.at(i).agent_x = tp->ag_tree.at(i).tree_vec.at(0).level_vec.at(0).x;
        map->agent_vec.at(i).agent_y = tp->ag_tree.at(i).tree_vec.at(0).level_vec.at(0).y;
        node_vec.at(i) = 0;
        ag_sim.at(i) = true;
    }
}

void gridworld::calculate_global(multi_agent *map, monte_carlo *mcp, multi_tree *tp){
    int act, count; g_reward = 0;
    
    for(int i = 1; i < (x_dim + y_dim); i++){ //Each Agent takes a step if able
        count = 0;
        for(int a = 0; a < n_agents; a++){
            if(ag_sim.at(a) == false){
                count++;
            }
        }
        if(count == n_agents){ //If all agents have no more moves left to make, finish eval
            break;
        }
        for(int a = 0; a < n_agents; a++){ //Agent Number
            if(i < tp->ag_tree.at(a).tree_vec.size()){ //If level exceeds the maximum size of tree, do not calculate
                mcp->parent_number = node_vec.at(a); //Parent is the node number of the previously selected node
                act = mcp->select_move(tp, a, i); //(agent_number, level) choose best child node
                node_vec.at(a) = mcp->current_node; //Node selected from select move
                if(mcp->action_check == false){
                    ag_sim.at(a) = false;
                }
                if(mcp->action_check == true){ //If a child node was found
                    end_lev.at(a) = i;
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
    dif_node_vec = node_vec;
}

void gridworld::calculate_difference(multi_agent *map, monte_carlo *mcp, multi_tree *tp, int agn){
    int act, count; double temp_reward; temp_reward = 0;
    for(int i = 1; i < (x_dim + y_dim); i++){
        count = 0;
        for(int a = 0; a < n_agents; a++){
            if(ag_sim.at(a) == false){
                count++;
            }
        }
        if(count == n_agents){ //If all agents have no more moves left to make, finish eval
            break;
        }
        for(int a = 0; a < n_agents; a++){ //Agent Number
            if(i < tp->ag_tree.at(a).tree_vec.size() && a != agn){ //Level cannot be greater than size of tree
                assert(a != agn);
                mcp->parent_number = node_vec.at(a); //Parent is the node number of the previously selected node
                act = mcp->select_move(tp, a, i); //(agent_number, level) choose best child node
                node_vec.at(a) = mcp->current_node; //Node selected from select move
                if(mcp->action_check == false){
                    ag_sim.at(a) = false;
                }
                if(mcp->action_check == true){ //If a child node was found
                    map->agent_move(a, act);
                    map->check_agent_status(a);
                    map->check_agent_coordinates(a, map->agent_vec.at(a).agent_x, map->agent_vec.at(a).agent_y);
                    if(map->agent_in_play == false && map->already_taken == false){
                        temp_reward += goal_reward;
                    }
                    if(map->agent_in_play == false && map->already_taken == true){
                        temp_reward -= penalty;
                    }
                    if(map->agent_in_play == true){
                        temp_reward--;
                    }
                }
            }
        }
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
    dif_rewards.clear();
    end_lev.clear();
}
