//
//  main.cpp
//  CS 776 HW 0
//
//  Created by Nicholas Zerbel on 8/29/17.
//  Copyright © 2017 Nicholas Zerbel. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include "hillclimber.hpp"

using namespace std;

double eval(int *vp);

int main() {
    hillclimber h;
    double fitness, new_fitness, best;
    int count, iterations; count = 0;
    srand( time(NULL) );
    
    h.create_vec(); 
    fitness = eval(h.vec); //Assign initial fitness

    bool best_fitness_known; best_fitness_known = true;

    if(best_fitness_known == true){
        cout << "Enter maximum fitness value:" << endl;
        cin >> best;
    }

    iterations = 1000000000;
    
    for(int i = 0; i < iterations; i++){ //Number of iterations
        if(count < 400){
            h.random_mutate1();
            new_fitness = eval(h.vec);
            if(new_fitness < fitness){
                h.rand_revert1();
            }
            if(new_fitness >= fitness){
                fitness = new_fitness;
            }
        }
        if(count >= 400 || count < 700){
            h.random_mutate2();
            new_fitness = eval(h.vec);
            if(new_fitness < fitness){
                h.rand_revert2();
            }
            if(new_fitness >= fitness){
                fitness = new_fitness;
            }
        }
        if(count >= 700 || count < 1000){
            h.random_mutate3();
            new_fitness = eval(h.vec);
            if(new_fitness < fitness){
                h.rand_revert3();
            }
            if(new_fitness >= fitness){
                fitness = new_fitness;
            }
        }
        if(fitness == best && best_fitness_known == true){
            break;
        }
        count++;
        if(count > 999){
            count = 100;
        }
    }
    
    for(int i = 0; i < 100; i++){
        cout << h.vec[i] << "\t";
    }
    cout << endl;
    cout << "Final Fitness = " << fitness << endl;
    
    return 0;
}
