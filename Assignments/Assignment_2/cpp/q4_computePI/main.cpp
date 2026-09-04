#include "generation\RandomInputGenerator.hpp"
#include <fstream>
#include <iostream>

// estimate the value of pi using monte carlo method
// class MonteCarloPiEstimator {
// private:
//     int numPoints;
//     int insideCircle;
// public:
//     MonteCarloPiEstimator(int numPoints) : numPoints(numPoints), insideCircle(0) {}

//     void estimate() {
//         for (int i = 0; i < numPoints; ++i) {
//             double x = static_cast<double>(rand()) / RAND_MAX; // Random x coordinate between 0 and 1
//             double y = static_cast<double>(rand()) / RAND_MAX; // Random y coordinate between 0 and 1

//             // Check if the point is inside the unit circle
//             if (x * x + y * y <= 1.0) {
//                 ++insideCircle;
//             }
//         }
//     }

//     double getPiEstimate() const {
//         return 4.0 * static_cast<double>(insideCircle) / numPoints;
//     }
// };
double getPiEstimate(int , int );
int main(){
    const double EXACT_PI = 3.14159265358979323846;
    std::ofstream outputFile("output.csv");
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file for writing." << "\n";
        return 1;
    }

    outputFile << "Iteration, Estimated value of pi,x coordinate,y coordinate,,Exact value of pi,Difference\n";
    int numPoints = 1'000'000'000; // Number of random points to generate : 1 billion
    // MonteCarloPiEstimator estimator(numPoints);
    // estimator.estimate();
    int insideCircle = 0;
    for (int i = 0; i < numPoints; ++i) {
        double x = static_cast<double>(rand()) / RAND_MAX; // Random x coordinate between 0 and 1
        double y = static_cast<double>(rand()) / RAND_MAX; // Random y coordinate between 0 and 1

        // Check if the point is inside the unit circle
        if (x * x + y * y <= 1.0) {
            ++insideCircle;
        }
        outputFile<< i+1 << "," <<getPiEstimate(i+1, insideCircle) << ",(" << x << "," << y << ")" << "," << EXACT_PI << "," << std::abs(getPiEstimate(i+1, insideCircle) - EXACT_PI) << "\n";
    }

    // Estimate pi using the ratio of points inside the circle to total points : 4 * (insideCircle / numPoints)
    // double piEstimate = 4.0 * static_cast<double>(estimator.insideCircle) / numPoints;


    return 0;
}
double getPiEstimate(int currentIteration, int insideCircle) {
    return 4.0 * static_cast<double>(insideCircle) / currentIteration;
}

// int main(){
//     const double EXACT_PI = 3.14159265358979323846;
//     std::ofstream outputFile("output.csv");
//     if (!outputFile.is_open()) {
//         std::cerr << "Error opening file for writing." << "\n";
//         return 1;
//     }

//     outputFile << "Iteration, Estimated value of pi,x coordinate,y coordinate,,Exact value of pi,Difference\n";
//     int numPoints = 1'000'000'000; // Number of random points to generate : 1 billion
//     MonteCarloPiEstimator estimator(numPoints);
//     estimator.estimate();

//     for (int i = 0; i < numPoints; ++i) {
//         double x = static_cast<double>(rand()) / RAND_MAX; // Random x coordinate between 0 and 1
//         double y = static_cast<double>(rand()) / RAND_MAX; // Random y coordinate between 0 and 1

//         // Check if the point is inside the unit circle
//         if (x * x + y * y <= 1.0) {
//             ++estimator.insideCircle;
//         }
//         outputFile<< i+1 << "," << estimator.getPiEstimate() << ",(" << x << "," << y << ")" << "," << EXACT_PI << "," << std::abs(estimator.getPiEstimate() - EXACT_PI) << "\n";
//     }

//     // Estimate pi using the ratio of points inside the circle to total points : 4 * (insideCircle / numPoints)
//     double piEstimate = 4.0 * static_cast<double>(estimator.insideCircle) / numPoints;

//     // outputFile << "Estimated value of pi: " << piEstimate << "\n";
//     // outputFile << "Exact value of pi: " << EXACT_PI << "\n";
//     // outputFile << "Difference: " << std::abs(piEstimate - EXACT_PI) << "\n";

//     outputFile.close();

//     return 0;
// }