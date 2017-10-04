//
//  eval.hpp
//  HW4
//
//  Created by Nicholas Zerbel on 10/1/17.
//  Copyright © 2017 Nicholas Zerbel. All rights reserved.
//

#ifndef eval_hpp
#define eval_hpp

#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <cmath>

using namespace std;

class city{
public:
    int cn; //City number
    double cx; //City X Coordinate
    double cy; //City Y Coordinate
};

class domain{
    friend class city;
public:
    vector <city> city_vec;
    
    void create_city_vec(string f);
    double eval(vector <int> vec);
    
    
    int n_cities;
    double fitness;
};

#endif /* eval_hpp */
