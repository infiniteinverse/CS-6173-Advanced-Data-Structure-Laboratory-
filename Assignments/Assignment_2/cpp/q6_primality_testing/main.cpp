#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

// Fast modular multiplication to avoid 64-bit overflow: (a * b) % mod
unsigned long long mod_mul(unsigned long long a, unsigned long long b, unsigned long long mod) {
    unsigned long long res = 0;
    a %= mod;
    while (b > 0) {
        if (b & 1) res = (res + a) % mod;
        a = (a * 2) % mod;
        b >>= 1;
    }
    return res;
}

 

// Fast modular exponentiation: (base^exp) % mod
unsigned long long mod_pow(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    unsigned long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = mod_mul(res, base, mod);
        base = mod_mul(base, base, mod);
        exp >>= 1;
    }
    return res;
}

// Greatest Common Divisor
unsigned long long gcd(unsigned long long a, unsigned long long b) {
    while (b != 0) {
        unsigned long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Deterministic ground truth check for verification
bool isActuallyPrime(unsigned long long n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (unsigned long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

class PrimalityTester {
private:
    std::mt19937_64 rng;

public:
    PrimalityTester() : rng(std::random_device{}()) {}
    explicit PrimalityTester(unsigned long long seed) : rng(seed) {}

    // 1. Standard Monte Carlo Primality Test (Fermat Test)
    bool fermatTest(unsigned long long n, int k = 1) {
        if (n < 2) return false;
        if (n == 2 || n == 3) return true;
        if (n % 2 == 0) return false;

        std::uniform_int_distribution<unsigned long long> dist(2, n - 2);

        for (int i = 0; i < k; ++i) {
            unsigned long long a = dist(rng);

            if (gcd(a, n) > 1) {
                return false; // Composite
            }

            // Check Fermat's condition: a^(n-1) == 1 (mod n)
            if (mod_pow(a, n - 1, n) != 1) {
                return false; // Composite
            }
        }
        return true; // Probably prime
    }

    // 2. Miller-Rabin Primality Test
    bool millerRabinTest(unsigned long long n, int k = 1) {
        if (n < 2) return false;
        if (n == 2 || n == 3) return true;
        if (n % 2 == 0) return false;

        unsigned long long d = n - 1;
        int s = 0;
        while (d % 2 == 0) {
            d /= 2;
            s++;
        }

        std::uniform_int_distribution<unsigned long long> dist(2, n - 2);

        for (int i = 0; i < k; ++i) {
            unsigned long long a = dist(rng);
            unsigned long long x = mod_pow(a, d, n);

            if (x == 1 || x == n - 1) continue;

            bool composite = true;
            for (int r = 1; r < s; ++r) {
                x = mod_pow(x, 2, n);
                if (x == n - 1) {
                    composite = false;
                    break;
                }
            }
            if (composite) return false; // Composite
        }
        return true; // Probably prime
    }
};

// Helper struct to track classification metrics
struct TestMetrics {
    int tp = 0; // True Positive (Prime -> Prime)
    int tn = 0; // True Negative (Composite -> Composite)
    int fp = 0; // False Positive (Composite -> Prime) [False Detection]
    int fn = 0; // False Negative (Prime -> Composite)

    void update(bool actual, bool verdict, std::string& label) {
        if (actual && verdict) {
            tp++;
            label = "TP";
        } else if (!actual && !verdict) {
            tn++;
            label = "TN";
        } else if (!actual && verdict) {
            fp++;
            label = "FP (FALSE_DETECTION)";
        } else {
            fn++;
            label = "FN";
        }
    }
};

int main() {
    const std::string input_filename = "E:\\1st semester\\8 Advanced Data Structure Laboratory CS6173\\Assignments\\Assignment_2\\cpp\\q6_primality_testing\\numbers.txt"; // Use file containing both primes and composites
    const std::string output_filename = "primality_comparison_results.csv";
    
    // k = 1 exposes false positive rates for comparison
    const int ITERATIONS = 1; 

    std::ifstream input_file(input_filename);
    if (!input_file.is_open()) {
        std::cerr << "Error: Could not open " << input_filename << "\n";
        return 1;
    }

    std::vector<unsigned long long> numbers;
    unsigned long long val;
    while (input_file >> val) {
        numbers.push_back(val);
    }
    input_file.close();

    if (numbers.empty()) {
        std::cerr << "Error: No numbers found in " << input_filename << "\n";
        return 1;
    }

    std::ofstream csv(output_filename);
    if (!csv.is_open()) {
        std::cerr << "Error: Could not open " << output_filename << "\n";
        return 1;
    }

    csv << "Index,Number,Ground_Truth,Fermat_Verdict,Fermat_Type,Fermat_Correct,MR_Verdict,MR_Type,MR_Correct\n";

    PrimalityTester tester;
    TestMetrics fermat_m;
    TestMetrics mr_m;

    int total = static_cast<int>(numbers.size());
    int actual_primes = 0;
    int actual_composites = 0;

    for (int i = 0; i < total; ++i) {
        unsigned long long n = numbers[i];
        bool actual = isActuallyPrime(n);

        if (actual) actual_primes++;
        else actual_composites++;

        bool fermat_verdict = tester.fermatTest(n, ITERATIONS);
        bool mr_verdict = tester.millerRabinTest(n, ITERATIONS);

        std::string f_type, mr_type;
        fermat_m.update(actual, fermat_verdict, f_type);
        mr_m.update(actual, mr_verdict, mr_type);

        bool f_correct = (fermat_verdict == actual);
        bool mr_correct = (mr_verdict == actual);

        csv << (i + 1) << ","
            << n << ","
            << (actual ? "PRIME" : "COMPOSITE") << ","
            << (fermat_verdict ? "PRIME" : "COMPOSITE") << ","
            << f_type << ","
            << (f_correct ? "PASS" : "FAIL") << ","
            << (mr_verdict ? "PRIME" : "COMPOSITE") << ","
            << mr_type << ","
            << (mr_correct ? "PASS" : "FAIL") << "\n";
    }

    csv.close();

    // Summary calculations
    double f_acc = static_cast<double>(fermat_m.tp + fermat_m.tn) / total;
    double mr_acc = static_cast<double>(mr_m.tp + mr_m.tn) / total;

    double f_fp_rate = (actual_composites > 0) 
        ? static_cast<double>(fermat_m.fp) / actual_composites : 0.0;
    double mr_fp_rate = (actual_composites > 0) 
        ? static_cast<double>(mr_m.fp) / actual_composites : 0.0;

    std::cout << "--- Dataset Breakdown ---\n";
    std::cout << "Total Numbers Tested     : " << total << "\n";
    std::cout << "Actual Primes            : " << actual_primes << "\n";
    std::cout << "Actual Composites        : " << actual_composites << "\n";
    std::cout << "Iterations per test (k)  : " << ITERATIONS << "\n\n";

    std::cout << "--- Fermat Test Performance ---\n";
    std::cout << "True Positives (Primes)  : " << fermat_m.tp << "\n";
    std::cout << "True Negatives (Compos.) : " << fermat_m.tn << "\n";
    std::cout << "False Detections (FP)    : " << fermat_m.fp << "\n";
    std::cout << "Overall Accuracy Ratio   : " << f_acc << " (" << (f_acc * 100.0) << "%)\n";
    std::cout << "False Detection Rate     : " << f_fp_rate << " (" << (f_fp_rate * 100.0) << "% of composites)\n\n";

    std::cout << "--- Miller-Rabin Performance ---\n";
    std::cout << "True Positives (Primes)  : " << mr_m.tp << "\n";
    std::cout << "True Negatives (Compos.) : " << mr_m.tn << "\n";
    std::cout << "False Detections (FP)    : " << mr_m.fp << "\n";
    std::cout << "Overall Accuracy Ratio   : " << mr_acc << " (" << (mr_acc * 100.0) << "%)\n";
    std::cout << "False Detection Rate     : " << mr_fp_rate << " (" << (mr_fp_rate * 100.0) << "% of composites)\n\n";

    std::cout << "Detailed logs written to : " << output_filename << "\n";

    return 0;
}