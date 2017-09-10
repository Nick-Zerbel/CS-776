//
//  beach.hpp
//  CS 776 HW 0 Part 0
//
//  Created by Nicholas Zerbel on 8/30/17.
//  Copyright © 2017 Nicholas Zerbel. All rights reserved.
//

#ifndef beach_hpp
#define beach_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

class beach{
public:
    vector <int> boat_crew;
    vector <int> boat_crew3;
    vector <int> solution;
    
    void create_s_vec();
    void reset_s_vec();
    void create_boat();
    
    //2 Person Boat
    void choose_boat_cap(int a);
    void evaluate_action(int a); //For two person boat
    void disembark();
    
    //3 Person Boat
    void choose_two_passengers(int a); //For three person boat
    void disembark_3boat();
    void choose_boat_cap3(int a);
    void check_boat_cap();
    
    bool invalid_action;
    bool boat_full;
    int cl; //counter for left beach cannibals
    int cr; //counter for right beach cannibals
    int ml; //counter for left beach missionaries
    int mr; //counter for right beach missionaries
    int cb; //counter for boat cannibals
    int mb; //counter for boat missionaries
};

#endif /* beach_hpp */
