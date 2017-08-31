//
//  tree.cpp
//  CS 776 HW 0 Part 0
//
//  Created by Nick Zerbel on 8/30/17.
//  Copyright © 2017 Nick Zerbel. All rights reserved.
//

#include "tree.hpp"

void tree::create_level(){
    level l;
    tree_vec.push_back(l);
}

void tree::create_node(int lev, int n_nodes, int a, int n_n, int p_n){
    node n;
    tree_vec.at(lev).level_vec.push_back(n);
    
    tree_vec.at(lev).level_vec.at(n_nodes).action = a;
    tree_vec.at(lev).level_vec.at(n_nodes).n_number = n_n;
    tree_vec.at(lev).level_vec.at(n_nodes).p_number = p_n;
    
}

void tree::print_tree(){
    ofstream myfile;
    myfile.open("tree.txt");
    for(int i = 0; i < tree_vec.size(); i++){
        myfile << "level: " << i << "\n";
        for(int j = 0; j < tree_vec.at(i).level_vec.size(); j++){
            myfile << tree_vec.at(i).level_vec.at(j).action << "\t";
            myfile << tree_vec.at(i).level_vec.at(j).n_number << "\t";
            myfile << tree_vec.at(i).level_vec.at(j).p_number << "\t";
            myfile << "\n";
        }
        myfile << "\n";
    }
    myfile.close();
}
