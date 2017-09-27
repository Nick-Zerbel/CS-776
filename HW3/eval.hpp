//
//  eval.hpp
//  HW3
//
//  Created by Nicholas Zerbel on 9/21/17.
//  Copyright © 2017 Nicholas Zerbel. All rights reserved.
//

#ifndef eval_hpp
#define eval_hpp

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

class eval{
public:
    void set_parameters(int v, int s);
    void decode(vector <int> vec, int s);
    double function1(vector <int> vec);
    double function2(vector <int> vec);
    double function3(vector <int> vec);
    double function4(vector <int> vec);
    double gauss(int mu, int sigma);
    
    double fit; //fitness value returned by functions
    int vec_size; //size of the array
    int string_size;
    double num;
    const double pi = 3.14159265358979323846;
};

#endif /* eval_hpp */
