//
//  eval.cpp
//  HW3
//
//  Created by Nicholas Zerbel on 9/21/17.
//  Copyright © 2017 Nicholas Zerbel. All rights reserved.
//

#include "eval.hpp"

void eval::set_parameters(int v, int s){
    vec_size = v;
    string_size = s;
}

void eval::decode(vector<int> vec, int s){
    num = 0;
    for(int i = 0; i < string_size; i++){
        num += vec.at(i+s*string_size)*pow(2,i);
    }
}

double eval::function1(vector <int> vec){ //f(x) = sum(x^2) [1,3] for -5.12 <= x <= 5.12
    double x;
    
    fit = 0;
    for(int i = 0; i < 3; i++){
        decode(vec, i);
        x = -5.12 + num*(10/(pow(2,10)-1));
        fit += pow(x, 2);
    }
    
    return fit;
}

double eval::function2(vector<int> vec){ //f(x) = 100*(x1^2-x2)^2 + (1-x1)^2
    double x1, x2;
    
    decode(vec, 0);
    x1 = -2.048 + num*(12/(pow(2,12) - 1));
    
    decode(vec, 1);
    x2 = -2.048 + num*(12/(pow(2,12) -1));
    
    fit = 100*pow(pow(x1, 2)-x2, 2) + pow(1-x1, 2);
    
    return fit;
}

double eval::function3(vector<int> vec){ //f(x) = sum(integer(x)) [1,5]
    double x; int xi;
    
    fit = 0;
    for(int i = 0; i < 5; i++){
        decode(vec, i);
        x = -5.12 + num*(10/(pow(2, 10)-1));
        xi = round(x);
        fit += xi;
    }
    
    fit = abs(fit);
    
    return fit;
}

double eval::function4(vector<int> vec){ //f(x) = sum(i*x^4) [1,30] + gauss(0,1)
    double x;
    
    fit = 0;
    for(int i = 0; i < 30; i++){
        decode(vec, i);
        x = -1.28 + num*(8/(pow(2, 8) -1));
        fit += i*pow(x,4) + gauss(0, 1); //Add gausian val
    }
    
    return fit;
}

//Box-Muller Transform
double eval::gauss(int mu, int sigma){ //mu = mean and sigma = standard deviation
    double y1, y2, x1, x2;
    
    x1 = (double)rand()/RAND_MAX;
    x2 = (double)rand()/RAND_MAX;
    
    y1 = sqrt(-2*log(x1)) * cos(2*pi*x2);
    y2 = sqrt(-2*log(x1)) * sin(2*pi*x2);
    
    y1 = y1*sigma + mu;
    y2 = y2*sigma + mu;
    
    return y2;
}
