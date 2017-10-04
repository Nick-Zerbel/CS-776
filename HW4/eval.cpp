//
//  eval.cpp
//  HW4
//
//  Created by Nicholas Zerbel on 10/1/17.
//  Copyright © 2017 Nicholas Zerbel. All rights reserved.
//

#include "eval.hpp"

void domain::create_city_vec(string f){
    city c; int l;
    string s;
    ifstream data(f);
    l = 6;
    if(f == "burma14.tsp"){
        l = 8;
    }
    for(int i = 0; i < l; i++){
        getline(data, s);
    }
    for(int i = 0; i < n_cities; i++){
        city_vec.push_back(c);
        data >> city_vec.at(i).cn;
        data >> city_vec.at(i).cx;
        data >> city_vec.at(i).cy;
    }
    for(int i = 0; i < n_cities; i++){
        cout << city_vec.at(i).cn << "   " << city_vec.at(i).cx << "   " << city_vec.at(i).cy << endl;
    }
    
}

double domain::eval(vector <int> vec){
    double xd, x1, x2, yd, y1, y2;
    double dist; dist = 0;
    for(int i = 1; i < n_cities+1; i++){
        x1 = city_vec.at(vec.at(i-1)).cx;
        y1 = city_vec.at(vec.at(i-1)).cy;
        x2 = city_vec.at(vec.at(i)).cx;
        y2 = city_vec.at(vec.at(i)).cy;
        xd = x2 - x1;
        yd = y2 - y1;
        dist += round(sqrt((xd*xd) + (yd*yd)));
    }
    
    return dist;
}
