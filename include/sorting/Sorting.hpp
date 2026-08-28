#pragma once

#include <vector>
#include <algorithm>

class BubbleSort {
private:

public:
    static int sort(std::vector<int>& data) ;

    
};

class InsertionSort {
private:
public:
    static void sort(std::vector<int>& data); 
};


enum class PartitionScheme {
    LOMUTO,
    HOARE,
    MEDIAN_OF_THREE,
    RANDOMIZED
};


class QuickSort {
private:
public:
    static int lomutoPartition(std::vector<int>& data, int start, int end); 

    static int hoarePartition(std::vector<int>& data, int start, int end);

    static int median_of_three(std::vector<int>& data, int start, int end);


    static void sort(std::vector<int>& data, int start, int end, PartitionScheme scheme);
};