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
    gridworld_finished = false;
    learn_its = 0;
    mcp->x_lim = x_dim;
    mcp->y_lim = y_dim;
}

void gridworld::check_goal_conditions(multi_agent *map){
    double x, y; int count; count = 0;
    goal_check = true;
    
    for(int i = 0; i < n_agents; i++){
        x = map->agent_vec.at(i).agent_x;
        y = map->agent_vec.at(i).agent_y;
        for(int j = 0; j < n_agents; j++){
            if(i != j){
                if(x == map->agent_vec.at(j).agent_x && y == map->agent_vec.at(j).agent_y){
                    goal_check = false;
                    break;
                }
            }
            if(x == map->goal_vec.at(j).goal_x && y == map->goal_vec.at(j).goal_y){
                count++;
            }
        }
    }
    if(count < n_agents){
        goal_check = false;
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
    int act, count; g_reward = 0; double dist;
    
    for(int i = 1; i < 100; i++){ //Each Agent takes a step if able
        count = 0;
        for(int aa = 0; aa < n_agents; aa++){
            if(ag_sim.at(aa) == false){
                count++;
            }
        }
        if(count == n_agents){ //If all agents have no more moves left to make, finish eval
            break;
        }
        for(int a = 0; a < n_agents; a++){ //Agent Number
            if(i < tp->ag_tree.at(a).tree_vec.size()){ //If level exceeds the maximum size of tree, do not calculate
                mcp->parent_number = node_vec.at(a); //Parent is the node number of the previously selected node
                if(i == 1){
                    assert(mcp->parent_number == 0);
                }
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
                    if(map->agent_in_play == false && map->unique_pos == true){
                        g_reward += goal_reward;
                        for(int oa = 0; oa < n_agents; oa++){ //Penalty for being close to other agents
                            if(oa != a){
                                dist = abs(map->agent_vec.at(a).agent_x - map->agent_vec.at(oa).agent_x);
                                dist += abs(map->agent_vec.at(a).agent_y - map->agent_vec.at(oa).agent_y);
                                if(dist <= mcp->obs_dist){
                                    g_reward -= prox_penalty;
                                }
                            }
                        }
                        ag_sim.at(a) = false;
                        assert(i == end_lev.at(a));
                    }
                    if(map->agent_in_play == false && map->unique_pos == false){
                        g_reward -= penalty;
                        for(int oa = 0; oa < n_agents; oa++){ //Penalty for being close to other agents
                            if(oa != a){
                                dist = abs(map->agent_vec.at(a).agent_x - map->agent_vec.at(oa).agent_x);
                                dist += abs(map->agent_vec.at(a).agent_y - map->agent_vec.at(oa).agent_y);
                                if(dist <= mcp->obs_dist){
                                    g_reward -= prox_penalty;
                                }
                            }
                        }
                        ag_sim.at(a) = false;
                        assert(i == end_lev.at(a));
                    }
                    if(map->agent_in_play == true){
                        g_reward -= step_penalty;
                        for(int oa = 0; oa < n_agents; oa++){ //Penalty for being close to other agents
                            if(oa != a){
                                dist = abs(map->agent_vec.at(a).agent_x - map->agent_vec.at(oa).agent_x);
                                dist += abs(map->agent_vec.at(a).agent_y - map->agent_vec.at(oa).agent_y);
                                if(dist <= mcp->obs_dist){
                                    g_reward -= prox_penalty;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    dif_node_vec = node_vec;
}

void gridworld::calculate_difference(multi_agent *map, monte_carlo *mcp, multi_tree *tp, int agn){
    int act, count; double temp_reward, dist; temp_reward = 0;
    for(int i = 1; i < 100; i++){ //Each Agent takes a step if able
        count = 0;
        for(int aa = 0; aa < n_agents; aa++){
            if(ag_sim.at(aa) == false){
                count++;
            }
        }
        if(count == n_agents){ //If all agents have no more moves left to make, finish eval
            break;
        }
        for(int a = 0; a < n_agents; a++){ //Agent Number
            if(i < tp->ag_tree.at(a).tree_vec.size()){ //If level exceeds the maximum size of tree, do not calculate
                mcp->parent_number = node_vec.at(a); //Parent is the node number of the previously selected node
                if(i == 1){
                    assert(mcp->parent_number == 0);
                }
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
                    if(map->agent_in_play == false && map->unique_pos == true){ //Agent is first to a goal
                        temp_reward += goal_reward;
                        for(int oa = 0; oa < n_agents; oa++){ //Penalty for being close to other agents
                            if(oa != a && oa != agn){
                                dist = abs(map->agent_vec.at(a).agent_x - map->agent_vec.at(oa).agent_x);
                                dist += abs(map->agent_vec.at(a).agent_y - map->agent_vec.at(oa).agent_y);
                                if(dist <= mcp->obs_dist){
                                    temp_reward -= prox_penalty;
                                }
                            }
                        }
                        ag_sim.at(a) = false;
                        assert(i == end_lev.at(a));
                    }
                    if(map->agent_in_play == false && map->unique_pos == false){ //Agent arrives at goal occupied by another
                        temp_reward -= penalty;
                        for(int oa = 0; oa < n_agents; oa++){ //Penalty for being close to other agents
                            if(oa != a && oa != agn){
                                dist = abs(map->agent_vec.at(a).agent_x - map->agent_vec.at(oa).agent_x);
                                dist += abs(map->agent_vec.at(a).agent_y - map->agent_vec.at(oa).agent_y);
                                if(dist <= mcp->obs_dist){
                                    temp_reward -= prox_penalty;
                                }
                            }
                        }
                        ag_sim.at(a) = false;
                        assert(i == end_lev.at(a));
                    }
                    if(map->agent_in_play == true){ //Agent did not land in a goal state
                        temp_reward -= step_penalty;
                        for(int oa = 0; oa < n_agents; oa++){ //Penalty for being close to other agents
                            if(oa != a && oa != agn){
                                dist = abs(map->agent_vec.at(a).agent_x - map->agent_vec.at(oa).agent_x);
                                dist += abs(map->agent_vec.at(a).agent_y - map->agent_vec.at(oa).agent_y);
                                if(dist <= mcp->obs_dist){
                                    temp_reward -= prox_penalty;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    dif_node_vec = node_vec;
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
