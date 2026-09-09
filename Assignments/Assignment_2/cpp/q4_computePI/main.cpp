// #include "generation\RandomInputGenerator.hpp"
#include <random>
#include <fstream>
#include <iostream>

static constexpr double EXACT_PI = 3.14159265358979323846;
using  ll = long long;
class MonteCarloPiEstimator{
private:
    ll numPoints;
    ll insideCircle;
    std:: mt19937 generator; 

public:
    MonteCarloPiEstimator(int numPoints): numPoints(numPoints), insideCircle(0) {}

    void estimate() {
        std::random_device rd; 
        generator.seed(rd()); 
        std::uniform_real_distribution<double> distribution(0.0, 1.0);
        std::ofstream outputFile("PIEstimation.csv", std::ios::out | std::ios::in | std::ios::trunc);
        if (!outputFile.is_open()) {
            throw std::runtime_error("Error opening file for writing.");
        }

        outputFile << "Iteration, Estimated value of pi, x coordinate,y coordinate, Exact value of pi, Difference\n";
   
        for (ll i = 0; i < numPoints; ++i) {
            double x = distribution(generator); 
            double y = distribution(generator); 

            // Check if the point is inside the unit circle
            if (x * x + y * y <= 1.0) {
                ++insideCircle;
            }
            if(i % 10000 == 0){
                std ::cout << "Iteration: " << i << ", Estimated value of pi: " << 4.0 * static_cast<double>(insideCircle) / (i + 1) << "\n";
            }
            double piEstimate = 4.0 * static_cast<double>(insideCircle) / (i + 1);
            outputFile << i + 1 << "," << piEstimate << ",(" << x << "," << y << ")," << EXACT_PI << "," << std::abs(piEstimate - EXACT_PI) << "\n";    
        }
        outputFile.close();
    }

    double getPiEstimate() const {
        return 4.0 * static_cast<double>(insideCircle) / numPoints;
    }
};


int main() {
    ll numPoints = 10'000'000;  // we get more precision as we increase the number of points
    MonteCarloPiEstimator estimator(numPoints);
    estimator.estimate();
    std::cout << "Estimated PI value: " << estimator.getPiEstimate() << "\n";
    return 0;
}