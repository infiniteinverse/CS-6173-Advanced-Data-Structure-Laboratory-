#pragma once

#include <random>
#include <vector>
#include <cstddef>

enum class InputType {
    SORTED,
    REVERSE_SORTED,
    NEARLY_SORTED,
    HIGHLY_INVERSIONAL
};

enum class SortOrder{
    ASCENDING,
    DESCENDING  
};

class RandomInputGenerator {
    private:
        std::mt19937 generator;

        std::vector<int> generateRandom(
            std:: size_t size,
            int min,
            int max
        );
        
        void sortData(
            std::vector<int>& data,
            SortOrder order
        );

        // void makeNearlySorted(
        //     std::vector<int>& data,
        //     double percentage
        // );  

        void changeOrdering(
            std::vector<int>& data,
            double percentage,
            SortOrder order = SortOrder::ASCENDING
        );

    public:
        RandomInputGenerator();

        explicit RandomInputGenerator(
            unsigned int seed
        );

        std::vector<int> generateInput(
            std::size_t size,
            int min,
            int max,
            InputType type,
            SortOrder order = SortOrder::ASCENDING,
            double percentage = 0.1
        );
};