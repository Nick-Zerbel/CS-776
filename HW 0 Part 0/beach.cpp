//
//  beach.cpp
//  CS 776 HW 0 Part 0
//
//  Created by Nick Zerbel on 8/30/17.
//  Copyright © 2017 Nick Zerbel. All rights reserved.
//

#include "beach.hpp"

void beach::create_s_vec(){
    for(int i = 0; i < 6; i++){
        solution.push_back(-1);
    }
}

void beach::create_boat(){
    for(int i = 0; i < 2; i++){
        boat_crew.push_back(-1);
    }
}

void beach::choose_boat_cap(int a){
    cl = 3; ml = 3; cr = 0; mr = 0;
    invalid_action = false;
    
    if(a == 0){
        cl--;
    }
    
    if(a == 1){
        ml--;
    }
    
    if(cl > ml){
        invalid_action = true;
        cl = 3;
        ml = 3;
    }
    
    if(invalid_action == false){
        boat_crew.at(0) = a;
    }
}

void beach::evaluate_action(int a){
    invalid_action = false;
    
    if(a == 0){
        cl--;
        cr++;
    }
    
    if(a == 1){
        ml--;
        mr++;
    }
    
    if(cl < 0){
        invalid_action = true;
        if(a == 0){
            cl++;
            cr--;
        }
        if(a == 1){
            ml++;
            mr--;
        }
        goto done;
    }
    
    if(ml < 0){
        invalid_action = true;
        if(a == 0){
            cl++;
            cr--;
        }
        if(a == 1){
            ml++;
            mr--;
        }
        goto done;
    }
    
    if(cl > ml){
        invalid_action = true;
        if(a == 0){
            cl++;
            cr--;
        }
        if(a == 1){
            ml++;
            mr--;
        }
        goto done;
    }
    
    if(cr > mr){
        invalid_action = true;
        if(a == 0){
            cl++;
            cr--;
        }
        if(a == 1){
            ml++;
            mr--;
        }
        goto done;
    }
    
    if(invalid_action == false){
        boat_crew.at(1) = a;
    }
    
done:
    assert(cl > -1);
    assert(ml > -1);
    
}

void beach::disembark(){
    for(int i = 0; i < 6; i++){
        if(solution.at(i) == -1){
            solution.at(i) = boat_crew.at(1);
            break;
        }
    }
}



