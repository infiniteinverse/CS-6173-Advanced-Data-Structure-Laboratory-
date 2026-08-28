#include "generation/RandomInputGenerator.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <stdexcept>

// default constructor:
RandomInputGenerator::RandomInputGenerator()
    :generator(
        static_cast<unsigned int> (
            std::chrono::system_clock::now()
                .time_since_epoch()
                .count()
        )
    ){
}

// parameterized constructor:
RandomInputGenerator::RandomInputGenerator(
    unsigned int seed
)
    :generator(seed){
}

// Random input generation function:
std::vector<int> RandomInputGenerator::generateRandom(
            std:: size_t size,
            int min,
            int max
)
{
    if(min>max){
        throw std::invalid_argument("Minimum value cannot be greater than maximum value.");
    }
    std::vector<int> data(size);
    std::uniform_int_distribution<int> distribution(min, max);
    for(std::size_t i = 0; i < size; ++i){
        data[i] = distribution(generator);
    }
    return data;
}

// Sort data according to requested order:

void RandomInputGenerator::sortData(
    std::vector<int>& data,
    SortOrder order
){
    if(order == SortOrder::ASCENDING){
        std::sort(data.begin(), data.end());
    } else {
        std::sort(data.begin(), data.end(), std::greater<int>());
    }
}

void RandomInputGenerator::changeOrdering(
        std::vector<int>& data,
        double percentage,
        SortOrder order
)
{
    sortData(data, order);
    int no_of_swaps = static_cast<int>(std::round(data.size() * percentage));
    std::uniform_int_distribution<std::size_t> distribution(0, data.size() - 1);
    for(int i = 0; i < no_of_swaps; ++i){
        std::size_t index1 = distribution(generator);
        std::size_t index2 = distribution(generator);
        std::swap(data[index1], data[index2]);
    }
}

std::vector<int> RandomInputGenerator::generateInput(
        std::size_t size,
        int min,
        int max,
        InputType type,
        SortOrder order,
        double percentage
){
    std::vector<int> data = generateRandom(size, min, max);
    switch(type){
        case InputType::SORTED:
            sortData(data, order);
            break;
        case InputType::NEARLY_SORTED:
            changeOrdering(data, 0.15, order);
            break;
        case InputType::HIGHLY_INVERSIONAL:
            changeOrdering(data, 0.8, order == SortOrder::ASCENDING ? SortOrder::DESCENDING : SortOrder::ASCENDING);
            break;
        default:
            throw std::invalid_argument("Invalid input type.");
    }

    return data;
}

