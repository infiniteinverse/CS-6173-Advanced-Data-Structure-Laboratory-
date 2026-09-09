#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <random>
#include <string>

class MonteCarloIntegrator {
private:
    std::mt19937 rng;

public:
    MonteCarloIntegrator() : rng(std::random_device{}()) {}
    explicit MonteCarloIntegrator(unsigned int seed) : rng(seed) {}

    // 1. Sample Mean Method -> Writes to its own CSV file
    double sampleMean(
        const std::function<double(double)>& f,
        double a,
        double b,
        int n,
        const std::string& filename
    ) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open " << filename << "\n";
            return 0.0;
        }

        file.precision(10);
        file << "Iteration,X,F_X,Integral_Estimate\n";

        std::uniform_real_distribution<double> dist_x(a, b);
        double sum = 0.0;
        double width = b - a;

        for (int i = 1; i <= n; ++i) {
            double x = dist_x(rng);
            double fx = f(x);
            sum += fx;

            double estimate = width * (sum / i);

            file << i << ","
                 << x << ","
                 << fx << ","
                 << estimate << "\n";
        }

        file.close();
        return width * (sum / n);
    }

    // 2. Hit-or-Miss Method -> Writes to its own CSV file
    double hitOrMiss(
        const std::function<double(double)>& f,
        double a,
        double b,
        double y_max,
        int n,
        const std::string& filename
    ) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open " << filename << "\n";
            return 0.0;
        }

        file.precision(10);
        file << "Iteration,X,Y,F_X,Is_Hit,Integral_Estimate\n";

        std::uniform_real_distribution<double> dist_x(a, b);
        std::uniform_real_distribution<double> dist_y(0.0, y_max);

        int hits = 0;
        double box_area = (b - a) * y_max;

        for (int i = 1; i <= n; ++i) {
            double x = dist_x(rng);
            double y = dist_y(rng);
            double fx = f(x);

            bool is_hit = (y <= fx);
            if (is_hit) {
                hits++;
            }

            double estimate = box_area * (static_cast<double>(hits) / i);

            file << i << ","
                 << x << ","
                 << y << ","
                 << fx << ","
                 << (is_hit ? 1 : 0) << ","
                 << estimate << "\n";
        }

        file.close();
        return box_area * (static_cast<double>(hits) / n);
    }
};

int main() {
    const int N = 10000;
    const double a = 0.0;
    const double b = 2.0;
    const double y_max = 2.0;

    auto quarter_circle = [](double x) {
        return std::sqrt(4.0 - x * x);
    };

    MonteCarloIntegrator integrator;

    double est_sample = integrator.sampleMean(
        quarter_circle, a, b, N, "monte_carlo_sample_mean.csv"
    );

    double est_hit_miss = integrator.hitOrMiss(
        quarter_circle, a, b, y_max, N, "monte_carlo_hit_or_miss.csv"
    );

    double exact_pi = std::acos(-1.0);

    std::cout << "Exact Value (Pi)        = " << exact_pi << "\n";
    std::cout << "Sample Mean Estimate    = " << est_sample << "\n";
    std::cout << "Hit-or-Miss Estimate    = " << est_hit_miss << "\n";
    return 0;
}