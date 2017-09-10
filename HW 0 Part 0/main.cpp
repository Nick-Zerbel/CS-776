//
//  main.cpp
//  CS 776 HW 0 Part 0
//
//  Created by Nicholas Zerbel on 8/30/17.
//  Copyright © 2017 Nicholas Zerbel. All rights reserved.
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
    
    while(tp->tree_vec.size() < 7){ //Tree search examines all possible actions for 3 cannibals and 3 missionaries
        br.run_search(tp);
    }
    
    t.print_tree();
    
    //Boat that can only hold 2 People-------------------------------------------------------------------------------------------------------------
    cout << "2 Person Boat:" << endl;
    cout << endl;
    for(int i = 0; i < tp->tree_vec.at(1).level_vec.size(); i++){
        decision = tp->tree_vec.at(1).level_vec.at(i).action;
        b.choose_boat_cap(decision);
        if(b.invalid_action == false){ //Boat captain is the one who pilots the boat and ferries people across the river
            cout << "Boat Captain: " << b.boat_crew.at(0) << endl;
            br.parent_number = tp->tree_vec.at(1).level_vec.at(i).n_number;
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
    
    cout << "Passenger Order:" << endl;
    for(int i = 0; i < 6; i++){ //Display solution
        cout << b.solution.at(i) << endl;
    }
    cout << endl;
    
    //Boat that can hold 3 people---------------------------------------------------------------------------------------------------------------
    b.reset_s_vec();
    
    cout << "3 Person Boat:" << endl;
    cout << endl;
    for(int i = 0; i < tp->tree_vec.at(1).level_vec.size(); i++){
        decision = tp->tree_vec.at(1).level_vec.at(i).action;
        b.choose_boat_cap3(decision);
        if(b.invalid_action == false){
            cout << "Boat Captain: " << b.boat_crew3.at(0) << endl;
            br.parent_number = tp->tree_vec.at(1).level_vec.at(i).n_number;
            break;
        }
    }
    
    while(b.cl > 0 && b.ml > 0){
        for(int i = 2; i < tp->tree_vec.size(); i++){
            for(int j = 0; j < tp->tree_vec.at(i).level_vec.size(); j++){
                if(br.parent_number == tp->tree_vec.at(i).level_vec.at(j).p_number){
                    decision = tp->tree_vec.at(i).level_vec.at(j).action;
                    b.choose_two_passengers(decision);
                    if(b.invalid_action == false){
                        br.parent_number = tp->tree_vec.at(i).level_vec.at(j).n_number;
                    }
                    b.check_boat_cap();
                    if(b.boat_full == true){
                        b.disembark_3boat();
                    }
                }
            }
        }
    }
    
    assert(b.boat_crew3.at(0) == 0);
    b.solution.at(4) = b.boat_crew3.at(0);
    b.boat_crew3.at(0) = -1;
    for(int i = 0; i < 3; i++){
        if(b.boat_crew3.at(i) != -1){
            b.solution.at(5) = b.boat_crew3.at(i);
            break;
        }
    }
    
    cout << "Passenger Order:" << endl;
    for(int i = 0; i < 3; i++){ //Display solution
        cout << b.solution.at(2*i) << "\t";
        cout << b.solution.at(2*i+1) << "\n";
    }
    
    return 0;
}
