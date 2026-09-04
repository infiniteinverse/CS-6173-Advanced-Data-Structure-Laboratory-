#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>

boost::multiprecision::int256_t multiply(
    boost::multiprecision::int256_t a,
    boost::multiprecision::int256_t b
) {
    return a * b;
}

int main() {

    boost::multiprecision::int256_t a(
        "1234567890123456789012345678901234567890"
    );

    boost::multiprecision::int256_t b(
        "9876543210987654321098765432109876543210"
    );

    boost::multiprecision::int256_t result = multiply(a, b);

    std::cout << "Result: " << result << std::endl;

    return 0;
}