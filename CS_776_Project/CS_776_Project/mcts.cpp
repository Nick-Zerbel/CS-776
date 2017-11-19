//
//  mcts.cpp
//  MAMCTS
//
//  Created by Nick Zerbel on 5/25/17.
//  Copyright © 2017 Nick Zerbel. All rights reserved.
//

#include "mcts.hpp"

void monte_carlo::set_mc_parameters(multi_tree *tp, int a){
    a_num = a;
    lev = 0;
    node_number = n_num_vec.at(a_num);
}

void monte_carlo::create_root_nodes(multi_tree *tp, multi_agent *map){
    for(int ag = 0; ag < map->n_agents; ag++){ //Create Root Nodes
        tp->create_tree(); //Create a tree for each agent
        tp->create_level(ag); //Create Root Level
        n_nodes = tp->ag_tree.at(ag).tree_vec.at(0).level_vec.size();
        tp->create_node(0, n_nodes, map->agent_vec.at(ag).agent_x, map->agent_vec.at(ag).agent_y, ag, node_number, 0, -1); //Root Node
    }
}

void monte_carlo::mc_search(multi_tree *tp, multi_agent *map){
    for(int j = 0; j < mc_iterations; j++){ //j = number of mcts simulations
        select(tp);
        expand(tp);
        for(int en = 0; en < tp->ag_tree.at(a_num).tree_vec.at(lev).level_vec.size(); en++){ //Rollout all newly expanded nodes
            if(parent_number == tp->ag_tree.at(a_num).tree_vec.at(lev).level_vec.at(en).p_number){
                rollout(tp, map, en);
            }
        }
        back_propagate(tp);
    }
}

int monte_carlo::select_move(multi_tree *tp, int agn, int l){ //(agent number, level)
    double best;
    action_check = false;
    assert(tp->ag_tree.at(agn).tree_vec.size() > l);
    
    reward_vec.clear();
    for(int i = 0; i < tp->ag_tree.at(agn).tree_vec.at(l).level_vec.size(); i++){
        if(parent_number == tp->ag_tree.at(agn).tree_vec.at(l).level_vec.at(i).p_number){
            reward_vec.push_back(tp->ag_tree.at(agn).tree_vec.at(l).level_vec.at(i).UCB1);
            action_check = true;
        }
    }
    
    best = *max_element(reward_vec.begin(), reward_vec.end());
    reward_vec.clear();
    
    for(int i = 0; i < tp->ag_tree.at(agn).tree_vec.at(l).level_vec.size(); i++){
        if(parent_number == tp->ag_tree.at(agn).tree_vec.at(l).level_vec.at(i).p_number && best == tp->ag_tree.at(agn).tree_vec.at(l).level_vec.at(i).UCB1){
            action = tp->ag_tree.at(agn).tree_vec.at(l).level_vec.at(i).action;
            current_node = tp->ag_tree.at(agn).tree_vec.at(l).level_vec.at(i).n_number; //Selected node becomes the new parent node for the next round
            break;
        }
    }
    
    assert(action >= 0);
    assert(action <= 4);
    return action;
}

//SELECTION------------------------------------------------------------------------------------------------------------
void monte_carlo::select(multi_tree *tp){
    double best, q_val;
    bool no_nodes;
    previous_x = tp->ag_tree.at(a_num).tree_vec.at(0).level_vec.at(0).x;
    previous_y = tp->ag_tree.at(a_num).tree_vec.at(0).level_vec.at(0).y;
    parent_number = tp->ag_tree.at(a_num).tree_vec.at(0).level_vec.at(0).n_number;
    parent_visit = tp->ag_tree.at(a_num).tree_vec.at(0).level_vec.at(0).visit_count;
    
    if(tp->ag_tree.at(a_num).tree_vec.size() == 1){ //If there is only the root level, go immediately to expansion
        lev = 1;
        goto expansion_phase;
    }
    
    reward_vec.clear();
    for(int i = 1; i < tp->ag_tree.at(a_num).tree_vec.size(); i++){
        no_nodes = true;
        for(int j = 0; j < tp->ag_tree.at(a_num).tree_vec.at(i).level_vec.size(); j++){
            if(parent_number == tp->ag_tree.at(a_num).tree_vec.at(i).level_vec.at(j).p_number){
                node_visit = tp->ag_tree.at(a_num).tree_vec.at(i).level_vec.at(j).visit_count;
                q_val = tp->ag_tree.at(a_num).tree_vec.at(i).level_vec.at(j).q_node;
                tp->ag_tree.at(a_num).tree_vec.at(i).level_vec.at(j).UCB1 = q_val + epsilon*sqrt(log(parent_visit)/node_visit); //UCB1 Formula
                reward_vec.push_back(tp->ag_tree.at(a_num).tree_vec.at(i).level_vec.at(j).UCB1);
                no_nodes = false;
            }
        }
        
        if(no_nodes == true){
            lev = i;
            goto expansion_phase;
        }
        
        best = *max_element(reward_vec.begin(), reward_vec.end());
        reward_vec.clear();
        for(int k = 0; k < tp->ag_tree.at(a_num).tree_vec.at(i).level_vec.size(); k++){
            if(best == tp->ag_tree.at(a_num).tree_vec.at(i).level_vec.at(k).UCB1 && parent_number == tp->ag_tree.at(a_num).tree_vec.at(i).level_vec.at(k).p_number){
                parent_visit = tp->ag_tree.at(a_num).tree_vec.at(i).level_vec.at(k).visit_count;
                parent_number = tp->ag_tree.at(a_num).tree_vec.at(i).level_vec.at(k).n_number;
                previous_x = tp->ag_tree.at(a_num).tree_vec.at(i).level_vec.at(k).x;
                previous_y = tp->ag_tree.at(a_num).tree_vec.at(i).level_vec.at(k).y;
                lev = i + 1;
                break;
            }
        }
    }
    
expansion_phase:
    assert(lev <= tp->ag_tree.at(a_num).tree_vec.size());
}

//EXPANSION---------------------------------------------------------------------------------------------------------------
void monte_carlo::expand(multi_tree *tp){
    if(lev == tp->ag_tree.at(a_num).tree_vec.size()){
        tp->create_level(a_num);
    }
    move_left(tp); //Explores Left Action (x--)
    move_up(tp); //Explores Up Action (y++)
    move_down(tp); //Explores Down Action (y--)
    move_right(tp); //Explores Right Action (x++)
    no_move(tp);
}

void monte_carlo::move_left(multi_tree *tp){
    reset_coordinates();
    ax--;
    pruning(tp);
    if(action_check == true){
        update_node_numbers(tp);
        tp->create_node(lev, n_nodes, ax, ay, a_num, node_number, parent_number, 0);
    }
}

void monte_carlo::move_up(multi_tree *tp){
    reset_coordinates();
    ay++;
    pruning(tp);
    if(action_check == true){
        update_node_numbers(tp);
        tp->create_node(lev, n_nodes, ax, ay, a_num, node_number, parent_number, 1);
    }
}

void monte_carlo::move_down(multi_tree *tp){
    reset_coordinates();
    ay--;
    pruning(tp);
    if(action_check == true){
        update_node_numbers(tp);
        tp->create_node(lev, n_nodes, ax, ay, a_num, node_number, parent_number, 2);
    }
}

void monte_carlo::move_right(multi_tree *tp){
    reset_coordinates();
    ax++;
    pruning(tp);
    if(action_check == true){
        update_node_numbers(tp);
        tp->create_node(lev, n_nodes, ax, ay, a_num, node_number, parent_number, 3);
    }
}

void monte_carlo::no_move(multi_tree *tp){
    reset_coordinates();
    check_boundaries(ax, ay);
    if(lev > max_lev){
        action_check = false;
    }
    if(action_check == true){
        prune(tp, lev-5);
    }
    if(action_check == true){
        update_node_numbers(tp);
        tp->create_node(lev, n_nodes, ax, ay, a_num, node_number, parent_number, 4);
    }
}

void monte_carlo::pruning(multi_tree *tp){
    check_boundaries(ax, ay); //Agent cannot go out of bounds
    if(lev > max_lev){
        action_check = false;
    }
    if(action_check == true){
        prune(tp, lev); //Agent cannot revisit a previous state during a MCTS simulation
    }
}

void monte_carlo::check_boundaries(double xx, double yy){
    action_check = true;
    if(xx >= x_lim){
        action_check = false;
    }
    if(xx < 0){
        action_check = false;
    }
    if(yy >= y_lim){
        action_check = false;
    }
    if(yy < 0){
        action_check = false;
    }
}

void monte_carlo::prune(multi_tree *tp, int l){
    for(int i = l-1; i >= 0; i--){
        for(int j = 0; j < tp->ag_tree.at(a_num).tree_vec.at(i).level_vec.size(); j++){
            prune_x = tp->ag_tree.at(a_num).tree_vec.at(i).level_vec.at(j).x;
            prune_y = tp->ag_tree.at(a_num).tree_vec.at(i).level_vec.at(j).y;
            if(ax == prune_x && ay == prune_y){
                action_check = false;
                break;
            }
        }
        if(action_check == false){
            break;
        }
    }
}

void monte_carlo::update_node_numbers(multi_tree *tp){
    node_number++;
    n_nodes = tp->ag_tree.at(a_num).tree_vec.at(lev).level_vec.size();
}

void monte_carlo::reset_coordinates(){
    ax = previous_x;
    ay = previous_y;
}

//SIMULATION------------------------------------------------------------------------------------------------------------------
void monte_carlo::rollout(multi_tree *tp, multi_agent *map, int n){
    int act; double steps, dist, q_val; steps = 0; q_val = 0;
    double x, y;
    x = tp->ag_tree.at(a_num).tree_vec.at(lev).level_vec.at(n).x;
    y = tp->ag_tree.at(a_num).tree_vec.at(lev).level_vec.at(n).y;
    
    for(int i = 0; i < rollout_its; i++){
        act = rand() % 5;
        if(act == 0){
            x--;
            steps++;
            check_boundaries(x, y);
            dist = abs(x-ax) + abs(y-ay);
            if(action_check == false || dist > obs_dist){
                x++;
                steps--;
            }
        }
        if(act == 1){
            y++;
            steps++;
            check_boundaries(x, y);
            dist = abs(x-ax) + abs(y-ay);
            if(action_check == false || dist > obs_dist){
                y--;
                steps--;
            }
        }
        if(act == 2){
            y--;
            steps++;
            check_boundaries(x, y);
            dist = abs(x-ax) + abs(y-ay);
            if(action_check == false || dist > obs_dist){
                y++;
                steps--;
            }
        }
        if(act == 3){
            x++;
            steps++;
            check_boundaries(x, y);
            dist = abs(x-ax) + abs(y-ay);
            if(action_check == false || dist > obs_dist){
                x--;
                steps--;
            }
        }
        if(act == 4){
            steps++;
        }
        
        for(int j = 0; j < map->n_agents; j++){
            if(x == map->goal_vec.at(j).goal_x && y == map->goal_vec.at(j).goal_y){ //If a goal is reached, +100
                q_val += rollout_reward;
                x = tp->ag_tree.at(a_num).tree_vec.at(lev).level_vec.at(n).x;
                y = tp->ag_tree.at(a_num).tree_vec.at(lev).level_vec.at(n).y;
            }
        }
    }
    tp->ag_tree.at(a_num).tree_vec.at(lev).level_vec.at(n).q_node = q_val;
}

//BACK-PROPAGATION------------------------------------------------------------------------------------------------------------
void monte_carlo::back_propagate(multi_tree *tp){
    double n; n = 0;
    double q_val, q_prev, nv; q_val = 0;
    
    for(int i = 0; i < tp->ag_tree.at(a_num).tree_vec.at(lev).level_vec.size(); i++){
        if(parent_number == tp->ag_tree.at(a_num).tree_vec.at(lev).level_vec.at(i).p_number){
            q_val += tp->ag_tree.at(a_num).tree_vec.at(lev).level_vec.at(i).q_node;
            n++;
        }
    }
    
    if(n > 0){
        q_val /= n; //Average across all newly expanded nodes
    }
    if(n == 0){
        q_val = 0;
    }
    
    reward_vec.clear();
    //Back-Propagate
    for(int i = lev-1; i >= 0; i--){ //i = level
        for(int j = 0; j < tp->ag_tree.at(a_num).tree_vec.at(i).level_vec.size(); j++){ //j = node
            if(parent_number == tp->ag_tree.at(a_num).tree_vec.at(i).level_vec.at(j).n_number){
                tp->ag_tree.at(a_num).tree_vec.at(i).level_vec.at(j).visit_count++;
                
                //Calculate MC Q-Value
                q_prev = tp->ag_tree.at(a_num).tree_vec.at(i).level_vec.at(j).q_node; //Previous q value
                nv = tp->ag_tree.at(a_num).tree_vec.at(i).level_vec.at(j).visit_count; //Number of visits to this node
                tp->ag_tree.at(a_num).tree_vec.at(i).level_vec.at(j).q_node = q_prev + ((q_val - q_prev)/nv); //MCTS Q-value
                parent_number = tp->ag_tree.at(a_num).tree_vec.at(i).level_vec.at(j).p_number;
                break;
            }
        }
        
        n = 0;
        q_val = 0;
        for(int tn = 0; tn < tp->ag_tree.at(a_num).tree_vec.at(i).level_vec.size(); tn++){
            if(parent_number == tp->ag_tree.at(a_num).tree_vec.at(i).level_vec.at(tn).p_number){
                q_val += tp->ag_tree.at(a_num).tree_vec.at(i).level_vec.at(tn).q_node;
                n++;
            }
        }
        assert(n > 0);
        q_val /= n; //A parent's value is the average of its children's action values
    }
}

void monte_carlo::back_propagate_evals(multi_agent *map, multi_tree *tp, double reward, int agn, int l, int nn){
    double q_val, q_prev, count, nv;
    //count = count for number of nodes, nv = node visit count
    
    count = 0;
    for(int i = 0; i < tp->ag_tree.at(agn).tree_vec.at(l).level_vec.size(); i++){ //Update current node value
        if(parent_number == tp->ag_tree.at(agn).tree_vec.at(l).level_vec.at(i).p_number){
            if(nn == tp->ag_tree.at(agn).tree_vec.at(l).level_vec.at(i).n_number){
                q_val = reward;
                q_prev = tp->ag_tree.at(agn).tree_vec.at(l).level_vec.at(i).q_node;
                nv = tp->ag_tree.at(agn).tree_vec.at(l).level_vec.at(i).visit_count;
                tp->ag_tree.at(agn).tree_vec.at(l).level_vec.at(i).q_node = q_prev + ((q_val-q_prev)/nv);
                count++;
                break;
            }
        }
    }
    
    assert(count > 0);

    count = 0;
    q_val = 0;
    for(int tn = 0; tn < tp->ag_tree.at(agn).tree_vec.at(l).level_vec.size(); tn++){
        if(parent_number == tp->ag_tree.at(agn).tree_vec.at(l).level_vec.at(tn).p_number){
            q_val += tp->ag_tree.at(agn).tree_vec.at(l).level_vec.at(tn).q_node;
            count++;
        }
    }
    assert(count > 0);
    q_val /= count; //A parent's value is the average of its children's action values
    
    for(int i = l-1; i >= 0; i--){ //i = level
        for(int j = 0; j < tp->ag_tree.at(agn).tree_vec.at(i).level_vec.size(); j++){ //j = node
            if(parent_number == tp->ag_tree.at(agn).tree_vec.at(i).level_vec.at(j).n_number){
                //Calculate MC Q-Value
                q_prev = tp->ag_tree.at(agn).tree_vec.at(i).level_vec.at(j).q_node; //Previous q value
                nv = tp->ag_tree.at(agn).tree_vec.at(i).level_vec.at(j).visit_count; //Number of visits to this node
                tp->ag_tree.at(agn).tree_vec.at(i).level_vec.at(j).q_node = q_prev + ((q_val - q_prev)/nv); //MCTS Q-value
                parent_number = tp->ag_tree.at(agn).tree_vec.at(i).level_vec.at(j).p_number;
                break;
            }
        }
        
        count = 0;
        q_val = 0;
        for(int tn = 0; tn < tp->ag_tree.at(agn).tree_vec.at(i).level_vec.size(); tn++){
            if(parent_number == tp->ag_tree.at(agn).tree_vec.at(i).level_vec.at(tn).p_number){
                q_val += tp->ag_tree.at(agn).tree_vec.at(i).level_vec.at(tn).q_node;
                count++;
            }
        }
        assert(count > 0);
        q_val /= count; //A parent's value is the average of its children's action values
    }
}
