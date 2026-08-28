#include "sorting/Sorting.hpp"
#include <vector>
#include <algorithm>


void BubbleSort::sort(std::vector<int>& data) {
        size_t n = data.size();

        for(int i = 1; i < n; i++) {

            bool swapped = false;

            for(int j = 1; j <= n-i; j++) {
                if(data[j] < data[j-1]) {
                    swapped = true;
                    std::swap(data[j], data[j-1]);
                }
            }

            if(swapped == false) {
                break;
            }
        }
    }


void InsertionSort::sort(std::vector<int>& data) {
        size_t n = data.size();

        for(int i = 1; i < n; i++) {
            int key = data[i];
            int j = i - 1;

            while(j >= 0 && data[j] > key) {
                data[j + 1] = data[j];
                j--;
            }
            data[j + 1] = key;
        }
    }





int QuickSort::lomutoPartition(std::vector<int>& data, int start, int end) {
        int pivot = data[end];

        int left = start-1;
        
        for(int right = start; right < end; right++) {
            if(data[right] < pivot) {
                left++;
                std::swap(data[left], data[right]);
            }
        }

        std::swap(data[left+1], data[end]);

        return left+1;
    }
int QuickSort::hoarePartition(std::vector<int>& data, int start, int end) {
        int pivot = data[start + ((end - start) >> 1)];

        int left = start - 1;
        int right = end + 1;

        while(true) {
            do {
                left++;
            } while(data[left] < pivot);

            do {
                right--;
            } while(data[right] > pivot);

            if(left >= right) return right;

            std::swap(data[left], data[right]);
        }

        return right;
    }

int QuickSort::median_of_three(std::vector<int>& data, int start, int end) {
        int a = data[start];
        int b = data[end];
        int c = data[start + ((end - start) >> 1)];

        int pivot = c;

        if((a <= b && b <= c) || (c <= b && b <= a)) pivot = b;
        else if((b <= a && a <= c) || (c <= a) && a <= b) pivot = a;

        int left = start - 1;
        int right = end + 1;

        while(true) {
            do {
                left++;
            } while(data[left] < pivot);

            do {
                right--;
            } while(data[right] > pivot);

            if(left >= right) return right;

            std::swap(data[left], data[right]);
        }

        return right;
    }

void QuickSort::sort(std::vector<int>& data, int start, int end, PartitionScheme scheme) {
        if(start >= end) return;

        int p = 0;

        switch(scheme) {
            case PartitionScheme::LOMUTO:
                p = lomutoPartition(data, start, end);
                break;

            case PartitionScheme::HOARE:
                p = hoarePartition(data, start, end);
                break;

        }

        sort(data, start, p-1, scheme);
    }
