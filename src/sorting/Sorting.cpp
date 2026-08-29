#include "sorting/Sorting.hpp"
#include <vector>
#include <algorithm>


int BubbleSort::sort(std::vector<int>& data) {
        size_t n = data.size();
        int comparison = 0;
        for(int i = 1; i < n; i++) {

            bool swapped = false;

            for(int j = 1; j <= n-i; j++) {
                if(data[j] < data[j-1]) {
                    swapped = true;
                    std::swap(data[j], data[j-1]);
                }
                comparison++;
            }

            if(swapped == false) {
                break;
            }
        }
        return comparison;
    }


int InsertionSort::sort(std::vector<int>& data) {
    size_t n = data.size();
    int comparisons = 0;

    for (int i = 1; i < n; i++) {
        int key = data[i];
        int j = i - 1;

        while (j >= 0) {
            comparisons++;

            if (data[j] > key) {
                data[j + 1] = data[j];
                j--;
            } else {
                break;
            }
        }

        data[j + 1] = key;
    }

    return comparisons;
}

int InsertionSort::sort(std::vector<int>& data, int start, int end){
    int n = end + 1;
    int comparisons = 0;
    for(int i = start + 1; i < n; i++){
        int key = data[i];
        int j = i - 1;
        while(j>=start){
            if(data[j] > key){
                data[j+1] = data[j];
                j--;
            }
            else{
                break;
            }
        }
        data[j+1] = key;
    }
    return comparisons;
}

long long QuickSort::comparisons = 0;



int QuickSort::lomutoPartition(
    std::vector<int>& data,
    int start,
    int end
) {

    int pivot = data[end];

    int left = start - 1;

    for (int right = start; right < end; right++) {


        comparisons++;

        if (data[right] < pivot) {

            left++;

            std::swap(data[left], data[right]);
        }
    }

    std::swap(data[left + 1], data[end]);

    return left + 1;
}




int QuickSort::hoarePartition(
    std::vector<int>& data,
    int start,
    int end
) {

    int pivot = data[start + (end - start) / 2];

    int left = start - 1;
    int right = end + 1;

    while (true) {


        do {
            left++;

            comparisons++;

        } while (data[left] < pivot);


        do {
            right--;

            comparisons++;

        } while (data[right] > pivot);


        if (left >= right) {
            return right;
        }


        std::swap(data[left], data[right]);
    }
}




int QuickSort::median_of_three(
    std::vector<int>& data,
    int start,
    int end
) {

    int mid = start + (end - start) / 2;

    int a = data[start];
    int b = data[mid];
    int c = data[end];

    int pivot;




    if ((a <= b && b <= c) ||
        (c <= b && b <= a)) {
        comparisons+=2;
        
        pivot = b;
    }
    else if ((b <= a && a <= c) ||
    (c <= a && a <= b)) {
        
        comparisons+=2;
        pivot = a;
    }
    else {

        pivot = c;
    }



    int left = start - 1;
    int right = end + 1;

    while (true) {

  
        do {
            left++;

            comparisons++;

        } while (data[left] < pivot);



        do {
            right--;

            comparisons++;

        } while (data[right] > pivot);


        if (left >= right) {
            return right;
        }


        std::swap(data[left], data[right]);
    }
}



void QuickSort::sort(
    std::vector<int>& data,
    int start,
    int end,
    PartitionScheme scheme
) {

    if (start >= end) {
        return;
    }


    int p;


    switch (scheme) {



        case PartitionScheme::LOMUTO:

            p = lomutoPartition(data, start, end);

            sort(data, start, p - 1, scheme);
            sort(data, p + 1, end, scheme);

            break;



        case PartitionScheme::HOARE:

            p = hoarePartition(data, start, end);


            sort(data, start, p, scheme);
            sort(data, p + 1, end, scheme);

            break;




        case PartitionScheme::MEDIAN_OF_THREE:

            p = median_of_three(data, start, end);

            sort(data, start, p, scheme);
            sort(data, p + 1, end, scheme);

            break;
    }
}




void QuickSort::resetComparisons()
{
    comparisons = 0;
}


long long QuickSort::getComparisons()
{
    return comparisons;
}