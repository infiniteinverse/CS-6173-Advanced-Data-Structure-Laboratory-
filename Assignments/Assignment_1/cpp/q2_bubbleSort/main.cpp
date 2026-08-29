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
    std::fstream file1("comparisonHighlyRandom.csv", std::ios::in | std::ios::out | std::ios::trunc);
    if(!file1.is_open()) throw std::runtime_error("File not openeed!!");

    file1<< "InputSize, Comp(NES), Comp(ES)" << "\n";

    int cmpWithoutEarlyStopping = 0, cmpWithEarlyStopping = 0;
    for(int datasize = 1; datasize <= 100; datasize++){
        std::vector<int> b1Data = generator.generateInput(datasize, 1, 1000, InputType::HIGHLY_INVERSIONAL);
        std::vector<int> b2Data= b1Data;
        cmpWithEarlyStopping = bSortWithtEarlyStopping.sort(b1Data);
        cmpWithoutEarlyStopping = bSortWithoutEarlyStopping(b2Data);
        file1 << datasize << ", " << cmpWithoutEarlyStopping << ", " << cmpWithEarlyStopping << "\n";
    }

    file1.close();

    // nearly sorted data;
    std::fstream file2("comparisonNearlySorted.csv", std::ios::in | std::ios::out | std::ios::trunc);
    if(!file2.is_open()) throw std::runtime_error("File not openeed!!");

    file2<< "InputSize, Comp(NES), Comp(ES)" << "\n";

    cmpWithoutEarlyStopping = 0, cmpWithEarlyStopping = 0;
    for(int datasize = 1; datasize <= 100; datasize++){
        std::vector<int> b1Data = generator.generateInput(datasize, 1, 1000, InputType::NEARLY_SORTED, SortOrder::ASCENDING,0.08);
        std::vector<int> b2Data= b1Data;
        cmpWithEarlyStopping = bSortWithtEarlyStopping.sort(b1Data);
        cmpWithoutEarlyStopping = bSortWithoutEarlyStopping(b2Data);
        file2 << datasize << ", " << cmpWithoutEarlyStopping << ", " << cmpWithEarlyStopping << "\n";
    }

    file2.close();

    // sorted data;
    std::fstream file3("comparisonSorted.csv", std::ios::in | std::ios::out | std::ios::trunc);
    if(!file3.is_open()) throw std::runtime_error("File not openeed!!");

    file3<< "InputSize, Comp(NES), Comp(ES)" << "\n";

    cmpWithoutEarlyStopping = 0, cmpWithEarlyStopping = 0;
    for(int datasize = 1; datasize <= 100; datasize++){
        std::vector<int> b1Data = generator.generateInput(datasize, 1, 1000, InputType::SORTED);
        std::vector<int> b2Data= b1Data;
        cmpWithEarlyStopping = bSortWithtEarlyStopping.sort(b1Data);
        cmpWithoutEarlyStopping = bSortWithoutEarlyStopping(b2Data);
        file3 << datasize << ", " << cmpWithoutEarlyStopping << ", " << cmpWithEarlyStopping << "\n";
    }

    file3.close();
    
    return 0;
}