//
//  agent.hpp
//  MAMCTS
//
//  Created by Nick Zerbel on 5/25/17.
//  Copyright © 2017 Nick Zerbel. All rights reserved.
//

#ifndef agent_hpp
#define agent_hpp

#include <cstdlib>
#include <iostream>
#include <vector>
#include <assert.h>
#include <fstream>

using namespace std;

class agent{
public:
    double agent_x;
    double agent_y;
    
};

class goal{
public:
    double goal_x;
    double goal_y;
};

class multi_agent{
    friend class agent;
    friend class goal;
public:
    vector <agent> agent_vec;
    vector <goal> goal_vec;
    
    //Goal Functions
    void create_goal_vec();
    void assign_goal_coordinates();
    void rand_goal_move(int gn); //Goals move randomly 50% of the time
    void check_goal_coordinates(int n, double xc, double yc);
    void check_goal_status(int gn); //Checks if goal is still in play
    
    //Agent Functions
    void create_agent_vec(int n, int xd, int yd);
    void assign_agent_coordinates(int n);
    void check_agent_coordinates(int n, double x, double y);
    void agent_move(int n, int a); //Agent moves based on information collects from MCTS and Reward Evaluation
    void check_agent_status(int an);
    
    //Parameters
    int n_agents; //Number of agents and goals
    int xdim;
    int ydim;
    bool unique_pos;
    bool already_taken; //Indicates if goal is already taken by another agent
    bool goal_in_play; //Indicates if a goal has been captured or not
    bool agent_in_play; //Indicates if agent has captrueed a goal or not
};

#endif /* agent_hpp */
