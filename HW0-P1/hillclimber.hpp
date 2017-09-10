//
//  hillclimber.hpp
//  CS 776 HW 0
//
//  Created by Nick Zerbel on 8/29/17.
//  Copyright © 2017 Nick Zerbel. All rights reserved.
//

#ifndef hillclimber_hpp
#define hillclimber_hpp

#include <iostream>

using namespace std;

class hillclimber{
public:
    int vec[100];
    int m_vec[100];
    
    
    void create_vec(); 
    void mutate();
    void revert();
    
    bool zero;
    bool one;
    int pos;
};

#endif /* hillclimber_hpp */
