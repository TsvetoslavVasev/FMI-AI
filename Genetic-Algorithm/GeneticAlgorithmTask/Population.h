//
//  Population.h
//  GeneticAlgorithm
//
//  Created by TsvetoslavVasev on 2.11.19.
//  Copyright © 2019 TsvetoslavVasev. All rights reserved.
//

#ifndef Population_h
#define Population_h
#include "DNA.h"
#include <map>

struct Population {
    
    std::vector<DNA*> population;
    std::vector<DNA*> matingPool;
    size_t generations;
    double mutationRate;
    DNA* bestSoFar;
    
    
    Population()
    {
        this->population.resize(100);
        for(int i = 0; i <100; i++)
        {
            DNA* toADD = new DNA();
            this->population[i] = toADD;
        }
        this->generations = 0;
        this->mutationRate = 0.3;
        this->calcFitness();
        this->bestSoFar = new DNA(25);
    }
    void calcFitness()
    {
        for(int i = 0; i< 100; i++)
        {
            this->population[i]->fitness();
        }
    }
    // Based on fitness, each member will get added to the mating pool a certain number of times
    // a higher fitness = more entries to mating pool = more likely to be picked as a parent
    // a lower fitness = fewer entries to mating pool = less likely to be picked as a parent
    void naturalSelection()
    {
        this->matingPool.clear();
        double maxFitness = 0;
        double fitnessSUM = 0;
        
        for(int i = 0; i < 100; i++)
        {
            fitnessSUM += this->population[i]->fitness_score;
            
            if(this->population[i]->fitness_score > maxFitness)
                maxFitness = this->population[i]->fitness_score;
        }
        for(int i = 0; i < 100; i++)
        {
            if(this->population[i]->fitness_score == maxFitness)
                this->bestSoFar = population[i];
        }
        for(int i = 0; i < 100; i++)
        {
            //normalize to %
            double fitness = (this->population[i]->fitness_score )/fitnessSUM;//maxFitness;
            //std::cout<<fitness<<"   ";
            int n = std::floor(fitness*100);
            for( int j = 0; j < n; j++)
            {
                this->matingPool.push_back(this->population[i]);
            }
        }
        //std::cout<<std::endl<<this->matingPool.size()<<std::endl;
    }
    
    //generate new generation
    void generate()
    {
        
        std::random_device rd;
        std::mt19937 eng(rd());
        std::uniform_int_distribution<> distr(0, this->matingPool.size()-1);
        this->sort();
        //refill 20% of the population with children from the mating pool
        for(int i = 0; i < 20 ; i++)
        {
            int a = std::floor(distr(eng));
            int b = std::floor(distr(eng));
            DNA* partnerA = this->matingPool[a];
            DNA* partnerB = this->matingPool[b];
            DNA* child = partnerA->crossover(partnerB);
            child->mutate(this->mutationRate);
            this->population[i] = child;
        }
        this->generations++;
    }
    DNA* getBest()const
    {
        return this->bestSoFar;
    }
    
    
    // current "most fit" member of the population
    void evaluate()
    {
        for(int i = 0; i < 25; i++)
        {
        std::cout<<this->bestSoFar->genes[i]<<" ";
        }
        std::cout<<std::endl;
    }
    int getGeneration()const
    {
        return this->generations;
    }
    
    double getAverageFitness()const
    {
        double total = 0;
        for(int i = 0; i < 100; i++)
        {
            total += this->population[i]->fitness_score;
        }
        total = total/this->population.size();
        return total;
    }
    void sort()
    {
        int n = 100;
       int i, j;
       bool swapped;
       for (i = 0; i < n-1; i++)
       {
         swapped = false;
         for (j = 0; j < n-i-1; j++)
         {
            if (this->population[j]->fitness_score > this->population[j+1]->fitness_score)
            {
               std::swap(this->population[j], this->population[j+1]);
               swapped = true;
            }
         }
         if (swapped == false)
            break;
       }
    }
    void displayInfo()
    {
        int fitnessSum = 0;
        for(int i = 0; i < 100; i++)
        {
            fitnessSum += this->population[i]->fitness_score;
        }
        //DNA* best = this->getBest();
        std::cout<<"Generation: "<<this->getGeneration()<<std::endl;
        std::cout<<"bestFitness: "<<this->bestSoFar->fitness_score<<std::endl;
        std::cout<<"average fitness: "<<this->getAverageFitness()<<std::endl;
        std::cout<<'\n';
    }
};
#endif /* Population_h */

