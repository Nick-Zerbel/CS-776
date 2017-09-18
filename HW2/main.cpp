//
//  main.cpp
//  CS-776-HW-2
//
//  Created by Nicholas Zerbel on 9/17/17.
//  Copyright © 2017 Nicholas Zerbel. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "hillclimber.hpp"

double eval(int *v);

int main() {
    hillclimber h;
    srand( time(NULL) );
    int iterations = 1000000000;
    
    ofstream myfile;
    myfile.open("best-fitness.txt");
    
    h.create_vec();
    h.best_fit = eval(h.best_vec); //assign initial fitness
    for(int i = 0; i < iterations; i++){
        h.mutate();
        h.fitness = eval(h.vec);
        h.evaluate();
        myfile << h.best_fit << "\n";
    }
    
    myfile.close();
    
    ofstream sol;
    sol.open("best-solution.txt");
    for(int i = 0; i < 150; i++){
        sol << h.best_vec[i] << "\t";
    }
    sol.close();
    
	cout << "Best Fitness: " << h.best_fit << endl;
    
    return 0;
}
