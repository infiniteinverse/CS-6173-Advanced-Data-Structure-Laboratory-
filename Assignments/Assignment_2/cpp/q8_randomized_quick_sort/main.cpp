#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <algorithm>

using namespace std;
using namespace chrono;


// ============================================================
// Conventional Quick Sort
// ============================================================

int partitionNormal(
    vector<int>& arr,
    int low,
    int high,
    long long& comparisons
)
{
    int pivot = arr[high];

    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        comparisons++;

        if (arr[j] <= pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);

    return i + 1;
}


void quickSortNormal(
    vector<int>& arr,
    int low,
    int high,
    long long& comparisons
)
{
    if (low < high)
    {
        int pivotIndex =
            partitionNormal(
                arr,
                low,
                high,
                comparisons
            );

        quickSortNormal(
            arr,
            low,
            pivotIndex - 1,
            comparisons
        );

        quickSortNormal(
            arr,
            pivotIndex + 1,
            high,
            comparisons
        );
    }
}


// ============================================================
// Randomized Quick Sort
// ============================================================

int partitionRandomized(
    vector<int>& arr,
    int low,
    int high,
    long long& comparisons,
    mt19937& generator
)
{
    // Choose random pivot index
    uniform_int_distribution<int> distribution(
        low,
        high
    );

    int randomIndex = distribution(generator);

    // Move random pivot to the end
    swap(arr[randomIndex], arr[high]);

    int pivot = arr[high];

    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        comparisons++;

        if (arr[j] <= pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);

    return i + 1;
}


void quickSortRandomized(
    vector<int>& arr,
    int low,
    int high,
    long long& comparisons,
    mt19937& generator
)
{
    if (low < high)
    {
        int pivotIndex =
            partitionRandomized(
                arr,
                low,
                high,
                comparisons,
                generator
            );

        quickSortRandomized(
            arr,
            low,
            pivotIndex - 1,
            comparisons,
            generator
        );

        quickSortRandomized(
            arr,
            pivotIndex + 1,
            high,
            comparisons,
            generator
        );
    }
}


// ============================================================
// Main
// ============================================================

int main()
{
    // Random number generator
    random_device rd;
    mt19937 generator(rd());

    // Random values for input array
    uniform_int_distribution<int> valueDistribution(
        1,
        100000
    );

    // Output CSV
    ofstream file(
        "quicksort_comparison.csv"
    );

    if (!file.is_open())
    {
        cerr << "Error: Could not open CSV file.\n";
        return 1;
    }

    // CSV header
    file << "InputSize,"
         << "NormalComparisons,"
         << "RandomizedComparisons,"
         << "NormalTime_us,"
         << "RandomizedTime_us\n";


    // Test different input sizes
    for (int size = 100; size <= 10000; size += 100)
    {
        // ----------------------------------------------------
        // Generate random input
        // ----------------------------------------------------

        vector<int> original(size);

        for (int i = 0; i < size; i++)
        {
            original[i] =
                valueDistribution(generator);
        }


        // ----------------------------------------------------
        // Conventional Quick Sort
        // ----------------------------------------------------

        vector<int> normalArray = original;

        long long normalComparisons = 0;

        auto startNormal =
            high_resolution_clock::now();

        quickSortNormal(
            normalArray,
            0,
            size - 1,
            normalComparisons
        );

        auto endNormal =
            high_resolution_clock::now();

        auto normalTime =
            duration_cast<microseconds>(
                endNormal - startNormal
            ).count();


        // ----------------------------------------------------
        // Randomized Quick Sort
        // ----------------------------------------------------

        vector<int> randomizedArray = original;

        long long randomizedComparisons = 0;

        auto startRandom =
            high_resolution_clock::now();

        quickSortRandomized(
            randomizedArray,
            0,
            size - 1,
            randomizedComparisons,
            generator
        );

        auto endRandom =
            high_resolution_clock::now();

        auto randomizedTime =
            duration_cast<microseconds>(
                endRandom - startRandom
            ).count();


        // ----------------------------------------------------
        // Verify that both arrays are sorted
        // ----------------------------------------------------

        if (!is_sorted(normalArray.begin(),
                       normalArray.end()))
        {
            cerr << "Normal Quick Sort failed!\n";
            return 1;
        }

        if (!is_sorted(randomizedArray.begin(),
                       randomizedArray.end()))
        {
            cerr << "Randomized Quick Sort failed!\n";
            return 1;
        }


        // ----------------------------------------------------
        // Write result to CSV
        // ----------------------------------------------------

        file << size << ","
             << normalComparisons << ","
             << randomizedComparisons << ","
             << normalTime << ","
             << randomizedTime
             << "\n";


        cout << "Input size: "
             << size
             << " | Normal comparisons: "
             << normalComparisons
             << " | Randomized comparisons: "
             << randomizedComparisons
             << "\n";
    }


    file.close();

    cout << "\n-------------------------------------\n";
    cout << "Comparison completed.\n";
    cout << "Results stored in:\n";
    cout << "quicksort_comparison.csv\n";
    cout << "-------------------------------------\n";

    return 0;
}