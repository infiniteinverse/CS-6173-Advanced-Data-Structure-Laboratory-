#include <iostream>
#include <fstream>
#include <vector>
#include <random>

using namespace std;

int randomizedMajorityElement(
    const vector<int>& arr,
    int iterations,
    ofstream& file
)
{
    int n = arr.size();

    random_device rd;
    mt19937 generator(rd());

    uniform_int_distribution<int> distribution(0, n - 1);

    for (int i = 1; i <= iterations; i++)
    {
        // Randomly select an index
        int randomIndex = distribution(generator);

        // Candidate majority element
        int candidate = arr[randomIndex];

        // Count candidate
        int count = 0;

        for (int j = 0; j < n; j++)
        {
            if (arr[j] == candidate)
            {
                count++;
            }
        }

        bool isMajority = (count > n / 2);

        // Store result of this iteration
        file << i << ","
             << randomIndex << ","
             << candidate << ","
             << count << ","
             << (isMajority ? "Majority" : "Not Majority")
             << "\n";

        // Majority found
        if (isMajority)
        {
            return candidate;
        }
    }

    // Majority was not found
    return -1;
}


int main()
{
    // Example array
    vector<int> arr = {
        2, 1, 2, 2, 3,
        2, 2, 4, 2
    };

    const int iterations = 10;

    ofstream file("majority_element_results.csv");

    if (!file.is_open())
    {
        cerr << "Error: Could not open CSV file.\n";
        return 1;
    }

    // CSV header
    file << "Iteration,RandomIndex,Candidate,Count,Result\n";

    int majority = randomizedMajorityElement(
        arr,
        iterations,
        file
    );

    file.close();

    cout << "Array: ";

    for (int x : arr)
    {
        cout << x << " ";
    }

    cout << "\n";

    if (majority != -1)
    {
        cout << "Majority Element: "
             << majority << "\n";
    }
    else
    {
        cout << "Majority Element: Not Found\n";
    }

    cout << "Results stored in: "
         << "majority_element_results.csv\n";

    return 0;
}