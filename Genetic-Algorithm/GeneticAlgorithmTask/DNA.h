//
//  DNA.h
//  GeneticAlgorithm
//
//  Created by TsvetoslavVasev on 2.11.19.
//  Copyright © 2019 TsvetoslavVasev. All rights reserved.
//

#ifndef DNA_h
#define DNA_h
#include "Item.h"
#include <vector>

std::vector<Item> items;

int newInt()
{
   return rand() % 2;
}
struct DNA
{
    std::vector<int> genes;
    double fitness_score;
    
    void getItems()
    {
        for(int i = 0; i < 25; i++)
        {
            if(this->genes[i] == 1) std::cout<<i<< " ";
        }
    }
    DNA()
    {
        this->genes.resize(25);
        for(int i = 0; i < 25; i++)
        {
            this->genes[i]= newInt();
        }
    }
    DNA(size_t num)
    {
        this->genes.resize(num);
    }
    DNA& operator=(DNA& other)
    {
        this->genes = other.genes;
        this->fitness_score = other.fitness_score;
        return *this;
    }
    
    double fitness()
    {
        double score = 0;
        double priceSoFar = 0;
        for(int i = 0; i < 25; i++)
        {
            score += items[i].value * genes[i];
            priceSoFar += items[i].price * genes[i];
        }
        if(priceSoFar > 5000) score = 1;
        this->fitness_score = score;
        return score;
    }
    
    DNA* crossover(DNA*& partner)
    {
        DNA* child = new DNA(this->genes.size());
        
        std::random_device rd;
        std::mt19937 eng(rd());
        std::uniform_int_distribution<> distr(1, 23);
        
        int midpoint = distr(eng);
        
        for (int i = 0; i < 25; i++)
        {
            if(i > midpoint) child->genes[i] = this->genes[i];
            else child->genes[i] = partner->genes[i];
        }
        return child;
    }
    
    void mutate(double mutationRate)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0, 1);// distribution between 0 and 1
        
        for(int i = 0; i < 25; i++)
        {
            if(dis(gen) < mutationRate)
                this->genes[i] = newInt();
        }
    }
};



#endif /* DNA_h */

