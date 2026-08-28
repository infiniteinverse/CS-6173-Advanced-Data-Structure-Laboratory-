#include "generation/RandomInputGenerator.hpp"
#include "sorting/Sorting.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>

int bSortWithoutEarlyStopping(std::vector<int>& data){
    size_t size = data.size();
    int comp = 0;
    for(int i = 1; i < size; i++){
        for(int j = 0; j < size - i; j++){
            if(data[j] > data[j+1]){
                std::swap(data[j], data[j+1]);
            }
            comp++;
        }
    }
    return comp;
}
int main(){
    RandomInputGenerator generator;
    BubbleSort bSortWithtEarlyStopping;
    // highly randomly ordered data;
    std::fstream file("comparisonHighlyRandom.csv", std::ios::in | std::ios::out | std::ios::trunc);
    if(!file.is_open()) throw std::runtime_error("File not openeed!!");

    file<< "InputSize, Comp(NES), Comp(ES)" << "\n";

    int cmpWithoutEarlyStopping = 0, cmpWithEarlyStopping = 0;
    for(int datasize = 1; datasize <= 100; datasize++){
        std::vector<int> data = generator.generateInput(datasize, 1, 1000, InputType::HIGHLY_INVERSIONAL);
        cmpWithEarlyStopping = bSortWithtEarlyStopping.sort(data);
        cmpWithoutEarlyStopping = bSortWithoutEarlyStopping(data);
        file << datasize << ", " << cmpWithoutEarlyStopping << ", " << cmpWithEarlyStopping << "\n";
    }

    file.close();
    
}