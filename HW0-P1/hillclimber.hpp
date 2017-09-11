//
//  hillclimber.hpp
//  CS 776 HW 0
//
//  Created by Nicholas Zerbel on 8/29/17.
//  Copyright © 2017 Nicholas Zerbel. All rights reserved.
//

#ifndef hillclimber_hpp
#define hillclimber_hpp

#include <iostream>
#include <cstdlib>

using namespace std;

class hillclimber{
public:
    int vec[100];
    int m_vec[100];
    
    void create_vec(); 
    void random_mutate3();
    void random_mutate1();
    void random_mutate2();
    void rand_revert3();
    void rand_revert1();
    void rand_revert2();

    bool zero_i;
    bool zero_j;
    bool zero_k;
    bool one_i;
    bool one_j;
    bool one_k;
    int pos1; //Used to track position of elements in the array
    int pos2;
    int pos3;
};

#endif /* hillclimber_hpp */
