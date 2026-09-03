#include "generation\RandomInputGenerator.hpp"
#include <fstream>
#include <iostream>

// estimate the value of pi using monte carlo method

int main(){
    const double EXACT_PI = 3.14159265358979323846;
    std::ofstream outputFile("output.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file for writing." << std::endl;
        return 1;
    }

    int numPoints = 1'000'000'000; // Number of random points to generate
    int insideCircle = 0;

    for (int i = 0; i < numPoints; ++i) {
        double x = static_cast<double>(rand()) / RAND_MAX; // Random x coordinate between 0 and 1
        double y = static_cast<double>(rand()) / RAND_MAX; // Random y coordinate between 0 and 1

        // Check if the point is inside the unit circle
        if (x * x + y * y <= 1.0) {
            ++insideCircle;
        }
    }

    // Estimate pi using the ratio of points inside the circle to total points
    double piEstimate = 4.0 * static_cast<double>(insideCircle) / numPoints;

    outputFile << "Estimated value of pi: " << piEstimate << "\n";
    outputFile << "Exact value of pi: " << EXACT_PI << "\n";
    outputFile << "Difference: " << std::abs(piEstimate - EXACT_PI) << "\n";

    outputFile.close();

    return 0;
}