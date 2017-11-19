//
//  agent.cpp
//  MAMCTS
//
//  Created by Nick Zerbel on 5/25/17.
//  Copyright © 2017 Nick Zerbel. All rights reserved.
//

#include "agent.hpp"

//AGENT FUNCTIONS-----------------------------------------------------------------------------------------------
void multi_agent::create_agent_vec(int n, int xd, int yd){
    double x, y;
    agent a;
    xdim = xd; ydim = yd;
    n_agents = n;
    
    for(int i = 0; i < n_agents; i++){
        agent_vec.push_back(a);
        agent_vec.at(i).agent_x = -1;
        agent_vec.at(i).agent_y = -1;
    }
    
    for(int i = 0; i < n_agents; i++){
        x = (double)(rand() % xdim);
        y = (double)(rand() % ydim);
        check_agent_coordinates(i, x, y);
        while(unique_pos == false){
            x = (double)(rand() % xdim);
            y = (double)(rand() % ydim);
            check_agent_coordinates(i, x, y);
        }
        agent_vec.at(i).agent_x = x;
        agent_vec.at(i).agent_y = y;
    }
    
    //Check to make sure no agents are stacked
    for(int i = 0; i < n_agents; i++){
        x = agent_vec.at(i).agent_x;
        y = agent_vec.at(i).agent_y;
        check_agent_coordinates(i, x ,y);
        assert(unique_pos == true);
    }
    
    ofstream ag; ag.open("Agent_Coordinates.txt");
    for(int i = 0; i < n_agents; i++){
        ag << agent_vec.at(i).agent_x << "\t" << agent_vec.at(i).agent_y << endl;
    }
    ag.close();
}

void multi_agent::assign_agent_coordinates(int n){
    agent a;
    n_agents = n;
    ifstream a_coords("agent_coordinates.txt");
    for(int i = 0; i < n_agents; i++){
        agent_vec.push_back(a);
        a_coords >> agent_vec.at(i).agent_x;
        a_coords >> agent_vec.at(i).agent_y;
    }
    a_coords.close();
}

void multi_agent::agent_move(int n, int a){ //Agent Number, Action
    double ax, ay;
    ax = agent_vec.at(n).agent_x;
    ay = agent_vec.at(n).agent_y;
    
    if(a == 0){
        ax--;
    }
    if(a == 1){
        ay++;
    }
    if(a == 2){
        ay--;
    }
    if(a == 3){
        ax++;
    }
    agent_vec.at(n).agent_x = ax;
    agent_vec.at(n).agent_y = ay;
}

void multi_agent::check_agent_coordinates(int n, double x, double y){
    already_taken = false;
    unique_pos = true;
    for(int i = 0; i < n_agents; i++){ //Check agent coordinates against other agent coordinates
        if(i != n){
            if(x == agent_vec.at(i).agent_x && y == agent_vec.at(i).agent_y){
                already_taken = true;
                unique_pos = false;
                break;
            }
        }
    }
}

void multi_agent::check_agent_status(int an){ //Checks if agent is at  goal
    double x, y;
    x = agent_vec.at(an).agent_x;
    y = agent_vec.at(an).agent_y;
    
    agent_in_play = true;
    for(int i = 0; i < n_agents; i++){
        if(x == goal_vec.at(i).goal_x && y == goal_vec.at(i).goal_y){
            agent_in_play = false;
            break;
        }
    }
}

//GOAL FUNCTIONS----------------------------------------------------------------------------------------------------
void multi_agent::create_goal_vec(){
    goal g;
    double x, y;
    
    for(int i = 0; i < n_agents; i++){
        goal_vec.push_back(g);
        goal_vec.at(i).goal_x = -1;
        goal_vec.at(i).goal_y = -1;
    }
    
    for(int i = 0; i < n_agents; i++){
        x = (double)(rand() % xdim);
        y = (double)(rand() % ydim);
        check_goal_coordinates(i, x, y);
        while(unique_pos == false){
            x = (double)(rand() % xdim);
            y = (double)(rand() % ydim);
            check_goal_coordinates(i, x ,y);
        }
        goal_vec.at(i).goal_x = x;
        goal_vec.at(i).goal_y = y;
    }
    
    //Check to make sure no goals are stacked
    for(int i = 0; i < n_agents; i++){
        x = goal_vec.at(i).goal_x;
        y = goal_vec.at(i).goal_y;
        check_goal_coordinates(i, x, y);
        assert(unique_pos == true);
    }
    
    ofstream gs; gs.open("Goal_Coordinates.txt");
    for(int i = 0; i < n_agents; i++){
        gs << goal_vec.at(i).goal_x << "\t" << goal_vec.at(i).goal_y << endl;
    }
    gs.close();
}

void multi_agent::assign_goal_coordinates(){
    goal g;
    ifstream g_coords("goal_coordinates.txt");
    for(int i = 0; i < n_agents; i++){
        goal_vec.push_back(g);
        g_coords >> goal_vec.at(i).goal_x;
        g_coords >> goal_vec.at(i).goal_y;
    }
    g_coords.close();
}

void multi_agent::check_goal_coordinates(int n, double xc, double yc){ //Goal number, goal_x, goal_y
    unique_pos = true;
    for(int i = 0; i < n_agents; i++){ //Check goal coordinates against other goal coordinates
        if(i != n){
            if(xc == goal_vec.at(i).goal_x && yc == goal_vec.at(i).goal_y){
                unique_pos = false;
                break;
            }
        }
    }
}

void multi_agent::check_goal_status(int gn){
    double gx, gy;
    gx = goal_vec.at(gn).goal_x;
    gy = goal_vec.at(gn).goal_y;
    goal_in_play = true;
    for(int i = 0; i < n_agents; i++){
        if(gx == agent_vec.at(i).agent_x && gy == agent_vec.at(i).agent_y){
            goal_in_play = false;
        }
    }
}

