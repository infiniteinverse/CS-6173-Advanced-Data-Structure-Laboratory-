#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>

int main() {
    const int N = 10000;

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> distribution(0.0, 2.0);

    std::ofstream file("monte_carlo_numerical_integration.csv");

    if (!file.is_open()) {
        std::cerr << "Error: Could not open CSV file.\n";
        return 1;
    }

    file << "Iteration,X,F_X,Integral_Estimate\n";
    file << std::fixed << std::setprecision(10);

    double sum = 0.0;

    for (int i = 1; i <= N; ++i) {

        // Generate random x in [0, 2]
        double x = distribution(generator);

        // f(x) = sqrt(4 - x^2)
        double fx = std::sqrt(4.0 - x * x);

        sum += fx;

        // Monte Carlo estimate:
        // I = (b-a) * average(f(x))
        double estimate = 2.0 * sum / i;

        // Store every iteration
        file << i << ","
             << x << ","
             << fx << ","
             << estimate << "\n";
    }

    file.close();

    double final_estimate = 2.0 * sum / N;

    std::cout << "Monte Carlo estimate = "
              << std::setprecision(10)
              << final_estimate << "\n";

    std::cout << "Exact value = "
              << std::acos(-1.0) << "\n";

    std::cout << "Results written to "
              << "monte_carlo_numerical_integration.csv\n";

    return 0;
}