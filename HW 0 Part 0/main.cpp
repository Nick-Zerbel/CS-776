//
//  main.cpp
//  CS 776 HW 0 Part 0
//
//  Created by Nick Zerbel on 8/30/17.
//  Copyright © 2017 Nick Zerbel. All rights reserved.
//

#include <iostream>
#include "beach.hpp"
#include "breadth.hpp"
#include "tree.hpp"

using namespace std;

int main() {
    tree t; breadth_first br; beach b;
    tree *tp = &t;
    
    int decision;
    b.create_boat();
    b.create_s_vec();
    t.create_level(); //Root Node
    br.create_root_node(tp);
    
    while(tp->tree_vec.size() < 7){
        br.run_search(tp);
    }
    
    t.print_tree();
    
    
    for(int i = 0; i < tp->tree_vec.at(1).level_vec.size(); i++){
        decision = tp->tree_vec.at(1).level_vec.at(i).action;
        b.choose_boat_cap(decision);
        if(b.invalid_action == false){
            cout << "Boat Captain: " << b.boat_crew.at(0) << endl;
            br.parent_number = tp->tree_vec.at(1).level_vec.at(i).n_number;
            cout << endl;
            break;
        }
    }
    
    while(b.cl > 0 && b.ml > 0){
        for(int i = 2; i < tp->tree_vec.size(); i++){
            for(int j = 0; j < tp->tree_vec.at(i).level_vec.size(); j++){
                if(br.parent_number == tp->tree_vec.at(i).level_vec.at(j).p_number){
                    decision = tp->tree_vec.at(i).level_vec.at(j).action;
                    assert(decision > -1);
                    b.evaluate_action(decision);
                    if(b.invalid_action == false){
                        b.disembark();
                        br.parent_number = tp->tree_vec.at(i).level_vec.at(j).n_number;
                    }
                }
            }
        }
    }
    
    b.solution.at(5) = b.boat_crew.at(0); //Last one off the boat is the captain
    
    for(int i = 0; i < 6; i++){
        cout << b.solution.at(i) << endl;
    }
    
    return 0;
}
