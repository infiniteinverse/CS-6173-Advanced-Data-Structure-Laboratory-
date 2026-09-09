#include "generation/RandomInputGenerator.hpp"
#include "sorting/Sorting.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>


class RandomisedQuickSort {
private:
    static int comparison;
    static std::random_device rd;
    static std::mt19937 gen;

    static int hoare(std::vector<int>& data, int start, int end) {
        
        std::uniform_int_distribution<int> distrib(start, end-1); // to make sure that it is not loop infinitely

        int pivot = data[distrib(gen)];

        int left = start-1;
        int right = end+1;

        while(true) {
            do {
                left++;
                comparison++;
            } while(data[left] < pivot);

            do {
                right--;
                comparison++;
            } while(data[right] > pivot);

            if(left >= right) return right;

            std::swap(data[left], data[right]);
        }

        return right;

    }

    static int lomuto(std::vector<int>& data, int start, int end) {
        std::uniform_int_distribution<int> distrib(start, end);

        int p = distrib(gen);
        int pivot = data[p];

        std::swap(data[end], data[p]);

        int left = start-1;
        for(int right = start; right < end; right++) {
            comparison++;
            if(data[right] < pivot) {
                left++;
                std::swap(data[left], data[right]);
            }
        }

        std::swap(data[left+1], data[end]);
        return left+1;
    }


    static void sorting(std::vector<int>& data, int start, int end, PartitionScheme scheme) {
        if(start >= end) return;

        int p = 0;
        switch(scheme) {
            case PartitionScheme::LOMUTO:
                p = lomuto(data, start, end);
                sorting(data, start, p-1, scheme);
                sorting(data, p+1, end, scheme);
                break;

            case PartitionScheme::HOARE:
                p = hoare(data, start, end);
                sorting(data, start, p, scheme);
                sorting(data, p+1, end, scheme);
                break;
        }
        
    }

public:

    static int sort(std::vector<int>& data, PartitionScheme scheme) {
        reset_comparison();
        sorting(data, 0, data.size()-1, scheme);
        return comparison;
    }

    static void reset_comparison() {
        comparison = 0;
    }

    static int get_comparison() {
        return comparison;
    }

};

int RandomisedQuickSort::comparison {};
std::random_device RandomisedQuickSort::rd{};
std::mt19937 RandomisedQuickSort::gen(rd());


int main() {
    RandomInputGenerator generator {};

    // highly inversional data set
    std::fstream file("Assignments/Assignment_2/cpp/q8_randomized_quick_sort/q8_RandQuickVSQuickLomuto.csv", std::ios::in | std::ios::out | std::ios::trunc);
    if(!file.is_open()) throw std::runtime_error("File does not exist or cannot be open");

    file << "Datasize,RandQuickComp,QuickComp\n";

    int MAX_SIZE = 1e3;
    int TRAILS = 30;

    for(int datasize = 1; datasize <= MAX_SIZE; datasize++) {
        int total_comp_randquick = 0;
        int total_comp_quick = 0;

        for(int t = 1; t <= TRAILS; t++) {
            std::vector<int> data1 = generator.generateInput(datasize, 1, 1e3, InputType::HIGHLY_INVERSIONAL, SortOrder::ASCENDING, 0.1);
            std::vector<int> data2 = data1;

            total_comp_randquick += RandomisedQuickSort::sort(data1, PartitionScheme::LOMUTO);
            QuickSort::sort(data2, 0, data2.size()-1, PartitionScheme::LOMUTO);
            total_comp_quick += QuickSort::getComparisons();
            QuickSort::resetComparisons();
        }

        file << datasize << "," << total_comp_randquick / TRAILS << "," << total_comp_quick / TRAILS << "\n";
    }

    // sorted data set

    std::fstream file2("Assignments/Assignment_2/cpp/q8_randomized_quick_sort/q8_RandQuickVSQuickHoare.csv", std::ios::in | std::ios::out | std::ios::trunc);
    if(!file2.is_open()) throw std::runtime_error("File does not exist or cannot be open");

    file2 << "Datasize,RandQuickComp,QuickComp\n";

    for(int datasize = 1; datasize <= MAX_SIZE; datasize++) {
        int total_comp_randquick = 0;
        int total_comp_quick = 0;

        for(int t = 1; t <= TRAILS; t++) {
            std::vector<int> data1 = generator.generateInput(datasize, 1, 1e3, InputType::HIGHLY_INVERSIONAL, SortOrder::ASCENDING, 0.1);
            std::vector<int> data2 = data1;

            total_comp_randquick += RandomisedQuickSort::sort(data1, PartitionScheme::HOARE);
            QuickSort::sort(data2, 0, data2.size()-1, PartitionScheme::HOARE);
            total_comp_quick += QuickSort::getComparisons();
            QuickSort::resetComparisons();
        }

        file2 << datasize << "," << total_comp_randquick / TRAILS << "," << total_comp_quick / TRAILS << "\n";
    }

    return 0;
}