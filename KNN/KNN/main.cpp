//
//  main.cpp
//  KNN
//
//  Created by TsvetoslavVasev on 2.12.19.
//  Copyright © 2019 TsvetoslavVasev. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <ctime>

const int valuesCount = 4;
const int classes = 3;


int classToInt(std::string& _class) {
    if (_class == "Iris-setosa") {
        return 0;
    }
    else if (_class == "Iris-versicolor") {
        return 1;
    }
    else if (_class == "Iris-virginica") {
        return 2;
    }
    else {
        std::cout << "No such class!" << std::endl;
    }
    return -1;
}

std::string classToString(int& _class)
{
    switch (_class) {
        case 0:
            return std::string("Iris-setosa");
        case 1:
            return std::string("Iris-versicolor");
        case 2:
            return std::string("Iris-virginica");
        default:
            std::cout << "No such class!" << std::endl;
    }
    return nullptr;
}

struct Point
{
    std::vector<double> values;
    int irisClass;
    
    Point(int valuesCount) : values(std::vector<double>(valuesCount)){}
    
    friend std::istream& operator>>(std::istream& input, Point& point) {
        for (int i = 0; i < point.values.size(); i++) {
            char comma;
            input >> point.values[i] >> comma;
        }

        std::string inputClass;
        input >> inputClass;
        point.irisClass = classToInt(inputClass);

        return input;
    }

    friend std::ostream& operator<<(std::ostream& os, Point& point) {
        for (int i = 0; i < point.values.size(); i++) {
            os << point.values[i] << ",";
        }
        os << classToString(point.irisClass);
        return os;
    }
};

struct pointComparator
{
    Point& point;
    
    pointComparator(Point& other):point(other){}
    
    double euclidianDistance(Point& other)
    {
        double sum = 0;
        for(int i =0; i < point.values.size(); i++)
        {
            sum+= (this->point.values[i] - other.values[i])*(this->point.values[i] - other.values[i]);
        }
        return sqrt(sum);
    }
    bool operator() (Point& point1, Point& point2)
    {
        return euclidianDistance(point1) < euclidianDistance(point2);
    }
};

void readDataset(std::vector<Point>& dataset, const char* name) {
    
    std::ifstream inputFile;
    inputFile.open(name);
    
    if(inputFile.is_open())
    {
        while (!inputFile.eof()) {

            Point point(valuesCount);
            inputFile >> point;

            dataset.push_back(point);
        }

        inputFile.close();
    }
}


int main() {

    std::vector<Point> data;
    ///Users/tsvetoslavvasev/Developer/FMI-AI/KNN/KNN
    readDataset(data, "iris.txt");
    for(int i = 0; i<data.size();i++)
    {
        std::cout<<data[i]<<std::endl;
    }
    return 0;
}
