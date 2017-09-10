//
//  breadth.hpp
//  CS 776 HW 0 Part 0
//
//  Created by Nicholas Zerbel on 8/30/17.
//  Copyright © 2017 Nicholas Zerbel. All rights reserved.
//

#ifndef breadth_hpp
#define breadth_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <assert.h>
#include "tree.hpp"

using namespace std;

class breadth_first{
public:
    
    
    //Actions
    void choose_cannibal(tree *tp);
    void choose_missionary(tree *tp);
    
    void create_root_node(tree *tp);
    void run_search(tree *tp);
    void expand(tree *tp);
    void prune(tree *tp, int a);
    
    int act;
    int lev;
    int node_number;
    int parent_number;
    bool valid_action;
};

#endif /* breadth_hpp */
