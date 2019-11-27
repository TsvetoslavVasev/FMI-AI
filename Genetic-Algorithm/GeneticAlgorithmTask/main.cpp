//
//  main.cpp
//  GeneticAlgorithm
//
//  Created by TsvetoslavVasev on 2.11.19.
//  Copyright © 2019 TsvetoslavVasev. All rights reserved.
//

#include <iostream>
#include <random>
#include "Population.h"



int main(int argc, const char * argv[]) {
    items.push_back(*new Item(0,100,150));
    items.push_back(*new Item(0,120,40));
    items.push_back(*new Item(0,1600,200));
    items.push_back(*new Item(0,700,160));
    items.push_back(*new Item(0,150,60));
    items.push_back(*new Item(0,680,45));
    items.push_back(*new Item(0,270,60));
    items.push_back(*new Item(0,385,48));
    items.push_back(*new Item(0,230,30));
    items.push_back(*new Item(0,520,10));
    items.push_back(*new Item(0,1700,400));
    items.push_back(*new Item(0,500,300));
    items.push_back(*new Item(0,240,15));
    items.push_back(*new Item(0,480,10));
    items.push_back(*new Item(0,730,40));
    items.push_back(*new Item(0,420,70));
    items.push_back(*new Item(0,430,75));
    items.push_back(*new Item(0,220,80));
    items.push_back(*new Item(0,70,20));
    items.push_back(*new Item(0,180,12));
    items.push_back(*new Item(0,40,50));
    items.push_back(*new Item(0,300,10));
    items.push_back(*new Item(0,900,20));
    items.push_back(*new Item(0,2000,150));
    
    Population population;
    for(int i=0 ; i < 5000; i++)
    {
        population.naturalSelection();
        
        population.generate();
        
        population.calcFitness();
        
        population.displayInfo();
    }
    population.evaluate();
    return 0;
}
