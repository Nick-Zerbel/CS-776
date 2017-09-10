//
//  main.cpp
//  CS 776 HW 0
//
//  Created by Nick Zerbel on 8/29/17.
//  Copyright © 2017 Nick Zerbel. All rights reserved.
//

#include <iostream>
#include "hillclimber.hpp"

using namespace std;

double eval(int *vp);

int main() {
    hillclimber h;
    double fitness, new_fitness;
    
    h.create_vec();
    fitness = eval(h.vec);
    
    for(int i = 0; i < 100000000; i++){
        h.mutate();
        new_fitness = eval(h.vec);
        if(new_fitness < fitness){
            h.revert();
        }
        if(new_fitness >= fitness){
            fitness = new_fitness;
        }
        h.pos++;
    }
    
    for(int i = 0; i < 100; i++){
        cout << h.vec[i] << "\t";
    }
    cout << endl;
    cout << "Final Fitness = " << fitness << endl;
    
    
    return 0;
}
