//
//  beach.cpp
//  CS 776 HW 0 Part 0
//
//  Created by Nicholas Zerbel on 8/30/17.
//  Copyright © 2017 Nicholas Zerbel. All rights reserved.
//

#include "beach.hpp"

void beach::create_s_vec(){ //Initialize solution vector
    for(int i = 0; i < 6; i++){
        solution.push_back(-1);
    }
}

void beach::create_boat(){ //Initialize boat vectors for 2 person and 3 person boats
    for(int i = 0; i < 2; i++){ //2 Person Boat
        boat_crew.push_back(-1);
    }
    for(int i = 0; i < 3; i++){
        boat_crew3.push_back(-1); //3 Person Boat
    }
}

//2 Person Boat------------------------------------------------------------------------------------------------------------------
void beach::choose_boat_cap(int a){
    cl = 3; ml = 3; cr = 0; mr = 0;
    invalid_action = false;
    
    if(a == 0){ //0 = cannibals
        cl--;
    }
    
    if(a == 1){ //1 = missionaries
        ml--;
    }
    
    if(cl > ml){ //Cannibals cannot outnumber missionaries on the left beach
        invalid_action = true; //if actions is invalid, reset counters
        cl = 3;
        ml = 3;
    }
    
    if(invalid_action == false){ //If action is acceptable, have captain man the boat
        boat_crew.at(0) = a;
    }
}

void beach::evaluate_action(int a){
    invalid_action = false;
    
    if(a == 0){ //0 = cannibal
        cl--;
        cr++;
    }
    
    if(a == 1){ //1 = missionary
        ml--;
        mr++;
    }
    
    if(cl < 0 || ml < 0){ //There cannot be negative missionaries or cannibals
        invalid_action = true;
    }
    
    if(cl > ml){ //Cannibals cannot outnumber missionaries on the left
        invalid_action = true;
    }
    
    if(cr > mr){ //Cannibals cannot outnumber missionaries on the right
        invalid_action = true;
    }
    
    if(invalid_action == true){ //If the action is invalid, reset the counters
        if(a == 0){
            cl++;
            cr--;
        }
        if(a == 1){
            ml++;
            mr--;
        }
    }
    
    if(invalid_action == false){ //If action is acceptable, passenger boards the boat
        boat_crew.at(1) = a;
    }
}

void beach::disembark(){ //Passenger leaves the boat and leaves the captain in place
    for(int i = 0; i < 6; i++){
        if(solution.at(i) == -1){
            solution.at(i) = boat_crew.at(1);
            break;
        }
    }
}

//3 Person Boat-----------------------------------------------------------------------------------------------------------------
void beach::choose_boat_cap3(int a){
    cl = 3; ml = 3; cr = 0; mr = 0; cb = 0; mb = 0;
    invalid_action = false;
    
    if(a == 0){ //0 = cannibal
        cl--;
    }
    
    if(a == 1){ //1 = missionary
        ml--;
    }
    
    if(cl > ml){ //cannibals cannout outnumber missionaries on the left
        invalid_action = true;
        cl = 3;
        ml = 3;
    }
    
    if(invalid_action == false){ //If action is acceptable, have captain man the boat
        if(a == 0){
            cb++; //cannibal counter for boat
        }
        if(a == 1){
            mb++; //missionary counter for boat
        }
        boat_crew3.at(0) = a;
    }
}

void beach::choose_two_passengers(int a){
    invalid_action = false;
    
    if(a == 0){ //0 = cannibal
        cl--;
        cr++;
        cb++;
    }
    
    if(a == 1){ //1 = missionary
        ml--;
        mr++;
        mb++;
    }
    
    if(cl > ml){ //cannibals cannout outnumber missionaries on the left
        invalid_action = true;
    }
    
    if(mb > 0 && cb > mb){ //cannibals cannot outnumber missionaries on the boat
        invalid_action = true;
    }
    
    if(cl < 0 || ml < 0){ //there cannot be a negative amount of cannibals and missionaries
        invalid_action = true;
    }
    
    if(invalid_action == true){ //If action is invalid, reset counters
        if(a == 0){
            cl++;
            cr--;
            cb--;
        }
        if(a == 1){
            ml++;
            mr--;
            mb--;
        }
    }
    
    if(invalid_action == false){
        for(int i = 1; i < 3; i++){
            if(boat_crew3.at(i) == -1){
                boat_crew3.at(i) = a;
                break;
            }
        }
    }
}

void beach::check_boat_cap(){ //Check to see if the boat is full or not
    boat_full = true;
    for(int i = 0; i < 3; i++){
        if(boat_crew3.at(i) == -1){
            boat_full = false;
        }
    }
}

void beach::disembark_3boat(){ //The two boat passengers leave the boat
    int p1, p2;
    
    for(int i = 1; i < 3; i++){
        if(boat_crew3.at(i) == 0){
            cb--;
        }
        if(boat_crew3.at(i) == 1){
            mb--;
        }
    }
    
    p1 = boat_crew3.at(1);
    p2 = boat_crew3.at(2);
    boat_crew3.at(1) = -1; //-1 indicates an empty position in the boat
    boat_crew3.at(2) = -1;
    
    for(int i = 0; i < 6; i++){
        if(solution.at(i) == -1){
            solution.at(i) = p1;
            break;
        }
    }
    
    for(int i = 0; i < 6; i++){
        if(solution.at(i) == -1){
            solution.at(i) = p2;
            break;
        }
    }
}

void beach::reset_s_vec(){ //resets the solution vector between 2 and 3 person simulations
    for(int i = 0; i < 6; i++){
        solution.at(i) = -1;
    }
}




