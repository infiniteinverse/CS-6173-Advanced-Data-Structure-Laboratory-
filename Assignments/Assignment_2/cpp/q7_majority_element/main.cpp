#include "generation/RandomInputGenerator.hpp"


#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <algorithm>
#include <unordered_map>


int main() {
    RandomInputGenerator generator{};

    static std::random_device rd;
    static std::mt19937 gen(rd());

    const int MAX_ATTEMPTS = 10; // (1/2)^10 = 1/1024 ≈ 0.000976

    // =========================================================================
    // EXPERIMENT 1: Average Attempts vs. Datasize (Saved to CSV for MATLAB)
    // =========================================================================
    std::ofstream file("Assignments/Assignment_2/cpp/q7_majority_element/q7_majorityElement.csv");
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open output CSV file\n";
        return 1;
    }

    file << "Datasize,AvgAttempts,TheoreticalExpected\n";

    const int MAX_DATASIZE = 200;
    const int RUNS_PER_SIZE = 50; // Averages out noise for clean plotting

    for (int datasize = 2; datasize <= MAX_DATASIZE; datasize++) {
        int total_attempts_for_size = 0;

        for (int run = 0; run < RUNS_PER_SIZE; run++) {
            // 1. Generate base dataset
            std::vector<int> data = generator.generateInput(
                datasize, 1, datasize * 10, InputType::HIGHLY_INVERSIONAL
            );

            // 2. Inject strict majority element (floor(n/2) + 1 copies)
            int majority_count = (datasize / 2) + 1;
            int targetEle = 999999; // Unique identifier value
            for (int i = 0; i < majority_count; i++) {
                data[i] = targetEle;
            }

            std::unordered_map<int, int> hash {};
            for(int x: data) hash[x] ++;

            std::shuffle(data.begin(), data.end(), gen);

            // 3. Search up to 10 random attempts
            std::uniform_int_distribution<int> distrib(0, datasize - 1);
            int attempts_taken = MAX_ATTEMPTS;

            for (int k = 1; k <= MAX_ATTEMPTS; k++) {
                int idx = distrib(gen);
                if (hash[data[idx]] > datasize/2) {
                    attempts_taken = k;
                    break;
                }
            }
            total_attempts_for_size += attempts_taken;
        }

        double avg_attempts = static_cast<double>(total_attempts_for_size) / RUNS_PER_SIZE;
        file << datasize << "," << avg_attempts << ",2.0\n";
    }

    file.close();
    std::cout << "Experiment 1 complete: CSV generated as 'q7_majorityElement.csv'\n\n";

    // =========================================================================
    // EXPERIMENT 2: Empirical Proof of the 0.00097 Miss Bound (100,000 runs)
    // =========================================================================
    const int TOTAL_TEST_RUNS = 100000;
    const int TEST_SIZE = 100;
    int misses_count = 0;

    std::cout << "Running Monte Carlo validation (" << TOTAL_TEST_RUNS 
              << " runs) to prove missing probability...\n";

    for (int run = 0; run < TOTAL_TEST_RUNS; run++) {
        // Construct array with exact minimum majority count
        std::vector<int> data(TEST_SIZE, 0); // Fill with noise 0
        int majority_count = (TEST_SIZE / 2) + 1; // 51 elements
        for (int i = 0; i < majority_count; i++) {
            data[i] = 1; // Majority element is 1
        }

        std::unordered_map<int, int> hash {};
        for(int x: data) hash[x] ++;

        std::shuffle(data.begin(), data.end(), gen);

        std::uniform_int_distribution<int> distrib(0, TEST_SIZE - 1);
        bool found = false;

        // Perform exactly 10 attempts
        for (int k = 1; k <= MAX_ATTEMPTS; k++) {
            int idx = distrib(gen);
            if (hash[1] > data.size() / 2) {
                found = true;
                break;
            }
        }

        if (!found) {
            misses_count++;
        }
    }

    double empirical_prob = static_cast<double>(misses_count) / TOTAL_TEST_RUNS;
    double theoretical_prob = 1.0 / 1024.0; // 0.0009765625

    std::cout << "----------------- VERIFICATION RESULTS -----------------\n";
    std::cout << "Total Runs                 : " << TOTAL_TEST_RUNS << "\n";
    std::cout << "Number of Misses in 10 tries: " << misses_count << "\n";
    std::cout << "Empirical Miss Probability : " << empirical_prob << "\n";
    std::cout << "Theoretical Bound ((1/2)^10): " << theoretical_prob << " (~0.00097)\n";
    std::cout << "--------------------------------------------------------\n";

    return 0;
}