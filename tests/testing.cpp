#include "generation/RandomInputGenerator.hpp"

#include <iostream>


int main() {
    std::cout << "Running tests..." << std::endl;

    // Add your test cases here
    RandomInputGenerator generator;
    std::vector<int> data1 = generator.generateInput(10, 1, 100, InputType::SORTED, SortOrder::ASCENDING);
    std::vector<int> data2 = generator.generateInput(10, 1, 100, InputType::SORTED, SortOrder::DESCENDING);
    std::vector<int> data3 = generator.generateInput(25, 1, 100, InputType::NEARLY_SORTED, SortOrder::ASCENDING, 0.1);
    std::vector<int> data4 = generator.generateInput(10, 1, 100, InputType::NEARLY_SORTED, SortOrder::DESCENDING, 0.2);
    std::vector<int> data5 = generator.generateInput(10, 1, 100, InputType::HIGHLY_INVERSIONAL, SortOrder::ASCENDING, 0.8);
    std::vector<int> data6 = generator.generateInput(10, 1, 100, InputType::NEARLY_SORTED, SortOrder::DESCENDING, 0.8);


    for(int x: data1) std::cout << x << " ";
    std::cout << std::endl;
    for(int x: data2) std::cout << x << " ";
    std::cout << std::endl;
    for(int x: data3) std::cout << x << " ";
    std::cout << std::endl;
    for(int x: data4) std::cout << x << " ";
    std::cout << std::endl;
    for(int x: data5) std::cout << x << " ";
    std::cout << std::endl;
    for(int x: data6) std::cout << x << " ";
    std::cout << std::endl;

    std::cout << "All tests passed!" << std::endl;
    return 0;
}