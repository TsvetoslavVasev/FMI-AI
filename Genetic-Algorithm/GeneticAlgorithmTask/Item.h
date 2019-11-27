//
//  Item.h
//  GeneticAlgorithm
//
//  Created by TsvetoslavVasev on 2.11.19.
//  Copyright © 2019 TsvetoslavVasev. All rights reserved.
//

#ifndef Item_h
#define Item_h

struct Item
{
    int bought;
    int value;
    int price;
    Item (){}
    Item(int bought, int price, int value)
    {
        this->bought = bought;
        this->value = value;
        this->price = price;
    }
};

#endif /* Item_h */

