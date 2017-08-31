//
//  beach.hpp
//  CS 776 HW 0 Part 0
//
//  Created by Nick Zerbel on 8/30/17.
//  Copyright © 2017 Nick Zerbel. All rights reserved.
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
    vector <int> solution;
    
    void create_s_vec();
    void create_boat();
    
    void choose_boat_cap(int a);
    void evaluate_action(int a);
    void disembark();
    
    bool invalid_action;
    int cl; //counter for left beach cannibals
    int cr; //counter for right beach cannibals
    int ml; //counter for left beach missionaries
    int mr; //counter for right beach missionaries
};

#endif /* beach_hpp */
