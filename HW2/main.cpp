//
//  main.cpp
//  CS-776-HW-2
//
//  Created by Nicholas Zerbel on 9/17/17.
//  Copyright © 2017 Nicholas Zerbel. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "hillclimber.hpp"

double eval(int *v);

int main() {
    hillclimber h;
    srand( time(NULL) );
    int iterations = 1000000;
    
    ofstream myfile;
    myfile.open("best-fitness.txt"); //Records best fitness found

	ofstream sol;
	sol.open("array.txt"); //Records initial array and best array at the end
    
    h.create_vec();

	sol << "Initial Array:" << "\n";
	for(int i = 0; i < 150; i++){
		sol << h.best_vec[i] << "\t";
	}
	sol << endl;

    h.best_fit = eval(h.best_vec); //assign initial fitness
    for(int i = 0; i < iterations; i++){
		if(i % 100000 == 0){
			cout << "iteration: " << i << endl;
		}
        h.mutate();
        h.fitness = eval(h.vec); //Fitness for mutating vector
		h.r_fitness = eval(h.r_vec); //Fitness for completely random vector
        h.evaluate();
        myfile << h.best_fit << "\n";
    }
    
    myfile.close();
    
	sol << "Final Array:" << "\n";
    for(int i = 0; i < 150; i++){
        sol << h.best_vec[i] << "\t";
    }
    sol.close();
    
	cout << "Best Fitness: " << h.best_fit << endl;
    
    return 0;
}
