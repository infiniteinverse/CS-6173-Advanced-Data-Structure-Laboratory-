#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

// Deterministic ground truth
bool isActuallyPrime(unsigned long long n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (unsigned long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

class NaiveMonteCarloTester {
private:
    std::mt19937_64 rng;

public:
    NaiveMonteCarloTester() : rng(std::random_device{}()) {}
    explicit NaiveMonteCarloTester(unsigned long long seed) : rng(seed) {}

    // Naive Monte Carlo: probes k random candidate divisors in [2, sqrt(n)]
    bool isPrime(unsigned long long n, int k) {
        if (n < 2) return false;
        if (n == 2 || n == 3) return true;

        unsigned long long limit = static_cast<unsigned long long>(std::sqrt(n));
        if (limit < 2) {
            return true;
        }

        std::uniform_int_distribution<unsigned long long> dist(2, limit);

        for (int i = 0; i < k; ++i) {
            unsigned long long d = dist(rng);
            if (n % d == 0) {
                return false; // Found a factor: definitely composite
            }
        }

        return true; // No factor discovered: guessed prime
    }
};

int main() {
    const std::string input_filename = "numbers.txt";
    const std::string output_filename = "naive_monte_carlo_results.csv";
    
    // Low value of k exposes false detections clearly
    const int TEST_ROUNDS = 5;

    std::ifstream input_file(input_filename);
    if (!input_file.is_open()) {
        std::cerr << "Error: Could not open " << input_filename << "\n";
        return 1;
    }

    std::vector<unsigned long long> numbers;
    unsigned long long num;
    while (input_file >> num) {
        numbers.push_back(num);
    }
    input_file.close();

    if (numbers.empty()) {
        std::cerr << "Error: No numbers read from " << input_filename << "\n";
        return 1;
    }

    std::ofstream csv_file(output_filename);
    if (!csv_file.is_open()) {
        std::cerr << "Error: Could not open " << output_filename << "\n";
        return 1;
    }

    csv_file << "Index,Number,Ground_Truth,Naive_MC_Verdict,Error_Type,Is_Correct\n";

    NaiveMonteCarloTester tester;
    int true_positives = 0;   // Prime -> Prime
    int true_negatives = 0;   // Composite -> Composite
    int false_positives = 0;  // Composite -> Prime (False Detection)
    int false_negatives = 0;  // Prime -> Composite (Should be 0)

    int total_tested = static_cast<int>(numbers.size());

    for (int i = 0; i < total_tested; ++i) {
        unsigned long long candidate = numbers[i];
        bool expected = isActuallyPrime(candidate);
        bool verdict = tester.isPrime(candidate, TEST_ROUNDS);

        std::string error_type = "NONE";
        bool is_correct = false;

        if (expected && verdict) {
            true_positives++;
            error_type = "TRUE_POSITIVE";
            is_correct = true;
        } else if (!expected && !verdict) {
            true_negatives++;
            error_type = "TRUE_NEGATIVE";
            is_correct = true;
        } else if (!expected && verdict) {
            false_positives++;
            error_type = "FALSE_POSITIVE (FALSE_DETECTION)";
            is_correct = false;
        } else if (expected && !verdict) {
            false_negatives++;
            error_type = "FALSE_NEGATIVE";
            is_correct = false;
        }

        csv_file << (i + 1) << ","
                 << candidate << ","
                 << (expected ? "PRIME" : "COMPOSITE") << ","
                 << (verdict ? "PRIME" : "COMPOSITE") << ","
                 << error_type << ","
                 << (is_correct ? "PASS" : "FAIL") << "\n";
    }

    csv_file.close();

    int total_composites = false_positives + true_negatives;
    double overall_accuracy = static_cast<double>(true_positives + true_negatives) / total_tested;
    double false_detection_rate = (total_composites > 0) 
        ? static_cast<double>(false_positives) / total_composites 
        : 0.0;

    std::cout << "--- Monte Carlo False Detection Analysis ---\n";
    std::cout << "Numbers Tested            : " << total_tested << "\n";
    std::cout << "Divisor Probes (k)        : " << TEST_ROUNDS << "\n";
    std::cout << "True Positives (Primes)   : " << true_positives << "\n";
    std::cout << "True Negatives (Correct C): " << true_negatives << "\n";
    std::cout << "False Detections (FP)     : " << false_positives << "\n";
    std::cout << "False Negatives (FN)      : " << false_negatives << "\n";
    std::cout << "Overall Accuracy Ratio    : " << overall_accuracy << " (" << (overall_accuracy * 100.0) << "%)\n";
    std::cout << "False Detection Rate (FP) : " << false_detection_rate << " (" << (false_detection_rate * 100.0) << "% of composites)\n";
    std::cout << "Results written to        : " << output_filename << "\n";

    return 0;
} 