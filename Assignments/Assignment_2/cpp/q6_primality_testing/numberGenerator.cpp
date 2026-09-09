#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    std::vector<int> numbers;

    // 1. Collect the first 100 prime numbers
    int candidate = 2;
    while (numbers.size() < 100) {
        if (isPrime(candidate)) {
            numbers.push_back(candidate);
        }
        candidate++;
    }

    // 2. Collect 900 composite numbers
    candidate = 4;
    int composite_count = 0;
    while (composite_count < 900) {
        if (!isPrime(candidate)) {
            numbers.push_back(candidate);
            composite_count++;
        }
        candidate++;
    }

    // 3. Shuffle to interleave primes and composites
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(numbers.begin(), numbers.end(), g);

    // 4. Write all 1000 numbers to numbers.txt
    std::ofstream out("numbers.txt");
    if (!out.is_open()) {
        std::cerr << "Error creating numbers.txt\n";
        return 1;
    }

    for (int num : numbers) {
        out << num << "\n";
    }
    out.close();

    std::cout << "Successfully generated numbers.txt with 1000 numbers (100 primes + 900 composites).\n";
    return 0;
}
