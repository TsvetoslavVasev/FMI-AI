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
#include <random>

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

std::pair<double, double> getMinMax(std::vector<Point>& dataset,int index)
{
    double max = (double)INT_MIN;
    double min = (double)INT_MAX;
    for(int i =0 ;i < dataset.size(); i++)
    {
        if(min > dataset[i].values[index]) min = dataset[i].values[index];
        if(max < dataset[i].values[index]) max = dataset[i].values[index];
    }
    std::pair<double, double> pair(min,max);
    return pair;
}

void normalzeNewPoint(std::vector<Point>& dataset, Point& point)
{
    std::pair<double,double> sepalLength = getMinMax(dataset, 0);
    std::pair<double,double> sepalWidth = getMinMax(dataset, 1);
    std::pair<double,double> petalLength = getMinMax(dataset, 2);
    std::pair<double,double> petalWidth = getMinMax(dataset, 3);
    
    point.values[0] = (point.values[0] - sepalLength.first)/(sepalLength.second - sepalLength.first);
    point.values[1] = (point.values[1] - sepalWidth.first)/(sepalWidth.second - sepalWidth.first);
    point.values[2] = (point.values[2] - petalLength.first)/(petalLength.second - petalLength.first);
    point.values[3] = (point.values[3] - petalWidth.first)/(petalWidth.second - petalWidth.first);
    
}

void normalize(std::vector<Point>& dataset)
{
    std::pair<double,double> sepalLength = getMinMax(dataset, 0);
    std::pair<double,double> sepalWidth = getMinMax(dataset, 1);
    std::pair<double,double> petalLength = getMinMax(dataset, 2);
    std::pair<double,double> petalWidth = getMinMax(dataset, 3);
    
    for(int i = 0 ;i < dataset.size(); i++)
    {
        dataset[i].values[0] = (dataset[i].values[0] - sepalLength.first)/(sepalLength.second - sepalLength.first);
        dataset[i].values[1] = (dataset[i].values[1] - sepalWidth.first)/(sepalWidth.second - sepalWidth.first);
        dataset[i].values[2] = (dataset[i].values[2] - petalLength.first)/(petalLength.second - petalLength.first);
        dataset[i].values[3] = (dataset[i].values[3] - petalWidth.first)/(petalWidth.second - petalWidth.first);
    }
}

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

int knn(Point& point, std::vector<Point>& dataset, int k)
{
    std::sort(dataset.begin(), dataset.end(), pointComparator(point));
    
    // first K-neighbours
    std::vector<int> classesCount(classes,0);
    for(int i = 0; i < k; i++)
    {
        classesCount[dataset[i].irisClass]++;
    }
    
    // if several with maxOccurrences, choose the class with the nearest entry
    std::vector<int> candidates(classes);
    int candidatesCount = 0;
    int maxOccurrences = -1;
    
    for(int i = 0; i < classes; i++)
    {
        if(classesCount[i] > maxOccurrences)
        {
            maxOccurrences = classesCount[i];
            candidatesCount = 0;
            candidates[candidatesCount++] = i;
        }
        else if (classesCount[i] == maxOccurrences) {
            candidates[candidatesCount++] = i;
        }
    }
    
    for(int i = 0; i < k; i++)
    {
        if(std::find(candidates.begin(), candidates.begin() + 1, dataset[i].irisClass) != candidates.end())
        {
            return dataset[i].irisClass;
        }
    }
    std::cout<<"Cant determine class \n";
    return -1;

}

int main() {

    std::vector<Point> data;
    readDataset(data, "iris.txt");
    
    std::random_shuffle(data.begin(), data.end());
    
    normalize(data);
    for(int i = 0; i<data.size();i++)
    {
        std::cout<<data[i]<<std::endl;
    }
    std::cout<<"\n \n";
    

    Point point(valuesCount);
    std::vector<double> vec{ 3.532,1.2340,1.23,3.56423};
    
    point.values = vec;
 
    normalzeNewPoint(data, point);
    
    
    int _class = knn(point,data, 10);
    std::cout<<classToString(_class)<<std::endl<<std::endl;
    
    

    return 0;
}
