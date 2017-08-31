//
//  breadth.cpp
//  CS 776 HW 0 Part 0
//
//  Created by Nick Zerbel on 8/30/17.
//  Copyright © 2017 Nick Zerbel. All rights reserved.
//

#include "breadth.hpp"

void breadth_first::create_root_node(tree *tp){
    tp->create_level();
    tp->create_node(0, 0, -1, 0, 0);
    lev = 1;
    node_number = 0;
}

void breadth_first::run_search(tree *tp){
    if(lev == tp->tree_vec.size()){
        tp->create_level();
    }
    for(int i = 0; i < tp->tree_vec.at(lev-1).level_vec.size(); i++){
        parent_number = tp->tree_vec.at(lev-1).level_vec.at(i).n_number;
        expand(tp);
    }
    lev++;
}

void breadth_first::expand(tree *tp){
    choose_cannibal(tp);
    choose_missionary(tp);
}

void breadth_first::choose_cannibal(tree *tp){
    act = 0;
    prune(tp, act);
    
    if(valid_action == true){
        node_number++;
        tp->create_node(lev, tp->tree_vec.at(lev).level_vec.size(), act, node_number, parent_number);
    }
}

void breadth_first::choose_missionary(tree *tp){
    act = 1;
    prune(tp, act);
    
    if(valid_action == true){
        node_number++;
        tp->create_node(lev, tp->tree_vec.at(lev).level_vec.size(), act, node_number, parent_number);
    }
    
}

void breadth_first::prune(tree *tp, int a){
    int c, m, p_num;
    assert(a == 0 || a == 1);
    c = 0;
    m = 0;
    p_num = parent_number;
    valid_action = true;
    
    if(a == 0){
        c++;
    }
    if(a == 1){
        m++;
    }
    
    for(int i = lev-1; i > -1; i--){ //Starting at the previous fully expanded level
        for(int j = 0; j < tp->tree_vec.at(i).level_vec.size(); j++){ //For all nodes in level
            
            if(p_num == tp->tree_vec.at(i).level_vec.at(j).n_number){ //Count the number of c's and m'c along decision path
                if(tp->tree_vec.at(i).level_vec.at(j).action == 0){
                    c++;
                }
                if(tp->tree_vec.at(i).level_vec.at(j).action == 1){
                    m++;
                }
                p_num = tp->tree_vec.at(i).level_vec.at(j).p_number;
            }
        }
    }
    
    
    if(c > 3){
        valid_action = false;
    }
    if(m > 3){
        valid_action = false;
    }
}
