/**
 * @file math_utils.cpp
 * @brief Implementation of mathematical utilities
 */

#include "utils/math_utils.hpp"

namespace aoc::utils {

long long gcd(long long a, long long b) {
    while (b != 0) {
        const long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long lcm(const long long a, const long long b) {
    // Divide first to avoid potential overflow
    return a / gcd(a, b) * b;
}

long long gcd_multiple(const std::vector<long long>& numbers) {
    if (numbers.empty()) {
        return 0;
    }

    long long result = numbers[0];
    for (size_t i = 1; i < numbers.size(); ++i) {
        result = gcd(result, numbers[i]);
    }

    return result;
}

long long lcm_multiple(const std::vector<long long>& numbers) {
    if (numbers.empty()) {
        return 0;
    }

    long long result = numbers[0];
    for (size_t i = 1; i < numbers.size(); ++i) {
        result = lcm(result, numbers[i]);
    }

    return result;
}

long long abs_diff(const long long a, const long long b) {
    return (a > b) ? a - b : b - a;
}

} // namespace aoc::utils