#include <iostream>

using namespace std;

double fit;

double eval(int *vp){
    int solution[100];
    fit = 0;
    
    for(int i = 0; i < 100; i++){
        if(i % 2 == 0){
            solution[i] = 0;
        }
        if(i % 2 != 0){
            solution[i] = 1;
        }
    }
    
    for(int i = 0; i < 100; i++){
        if(vp[i] == solution[i]){
            fit = fit + 10;
        }
        if(vp[i] != solution[i]){
            fit = fit - 10;
        }
    }
    
    return fit;
}
