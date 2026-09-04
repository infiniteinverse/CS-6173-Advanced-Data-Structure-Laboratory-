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
    std::fstream file1("Assignments/Assignment_1/cpp/q2_bubbleSort/comparisonHighlyRandom_trial_based.csv", std::ios::in | std::ios::out | std::ios::trunc);
    if(!file1.is_open()) throw std::runtime_error("File not openeed!!");

    file1<< "InputSize, Comp(NES), Comp(ES)" << "\n";
    int TRIALS = 25;

    for (int datasize = 1; datasize <= 100; datasize++) {

    long long totalWithoutES = 0;
    long long totalWithES = 0;

    for (int trial = 0; trial < TRIALS; trial++) {

        std::vector<int> data =
            generator.generateInput(
                datasize,
                1,
                1000,
                InputType::HIGHLY_INVERSIONAL
            );

        std::vector<int> b1Data = data;
        std::vector<int> b2Data = data;

        totalWithES += bSortWithtEarlyStopping.sort(b1Data);
        totalWithoutES += bSortWithoutEarlyStopping(b2Data);
    }

    double avgWithoutES =
        static_cast<double>(totalWithoutES) / TRIALS;

    double avgWithES =
        static_cast<double>(totalWithES) / TRIALS;

    file1 << datasize << ", "
          << avgWithoutES << ", "
          << avgWithES << "\n";

    }
    file1.close();

    // nearly sorted data;
    std::fstream file2("Assignments/Assignment_1/cpp/q2_bubbleSort/comparisonNearlySorted_trial_based.csv", std::ios::in | std::ios::out | std::ios::trunc);
    if(!file2.is_open()) throw std::runtime_error("File not openeed!!");

    file2<< "InputSize, Comp(NES), Comp(ES)" << "\n";
    // int TRIALS = 25;

    for (int datasize = 1; datasize <= 100; datasize++) {

    long long totalWithoutES = 0;
    long long totalWithES = 0;

    for (int trial = 0; trial < TRIALS; trial++) {

        std::vector<int> data =
            generator.generateInput(
                datasize,
                1,
                1000,
                InputType::NEARLY_SORTED
            );

        std::vector<int> b1Data = data;
        std::vector<int> b2Data = data;

        totalWithES += bSortWithtEarlyStopping.sort(b1Data);
        totalWithoutES += bSortWithoutEarlyStopping(b2Data);
    }

    double avgWithoutES =
        static_cast<double>(totalWithoutES) / TRIALS;

    double avgWithES =
        static_cast<double>(totalWithES) / TRIALS;

    file2 << datasize << ", "
          << avgWithoutES << ", "
          << avgWithES << "\n";
    }
    file2.close();

    // sorted data;
    std::fstream file3("Assignments/Assignment_1/cpp/q2_bubbleSort/comparisonSorted_trial_based.csv", std::ios::in | std::ios::out | std::ios::trunc);
    if(!file3.is_open()) throw std::runtime_error("File not openeed!!");

    file3<< "InputSize, Comp(NES), Comp(ES)" << "\n";
    
    // int TRIALS = 25;

    for (int datasize = 1; datasize <= 100; datasize++) {

    long long totalWithoutES = 0;
    long long totalWithES = 0;

    for (int trial = 0; trial < TRIALS; trial++) {

        std::vector<int> data =
            generator.generateInput(
                datasize,
                1,
                1000,
                InputType::SORTED
            );

        std::vector<int> b1Data = data;
        std::vector<int> b2Data = data;

        totalWithES += bSortWithtEarlyStopping.sort(b1Data);
        totalWithoutES += bSortWithoutEarlyStopping(b2Data);
    }

    double avgWithoutES =
        static_cast<double>(totalWithoutES) / TRIALS;

    double avgWithES =
        static_cast<double>(totalWithES) / TRIALS;

    file3 << datasize << ", "
          << avgWithoutES << ", "
          << avgWithES << "\n";
    }
    file3.close();
    
    return 0;
}