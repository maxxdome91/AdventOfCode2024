#pragma once

/**
 * @file math_utils.hpp
 * @brief Mathematical utilities for puzzle solving
 *
 * Provides common mathematical operations like GCD, LCM,
 * and vector operations.
 */

#include <algorithm>
#include <numeric>
#include <vector>

namespace aoc::utils {

/**
 * @brief Calculates the greatest common divisor of two numbers
 *
 * Uses the Euclidean algorithm.
 *
 * @param a First number
 * @param b Second number
 * @return The greatest common divisor
 */
[[nodiscard]] long long gcd(long long a, long long b);

/**
 * @brief Calculates the least common multiple of two numbers
 *
 * Uses the formula: lcm(a, b) = a / gcd(a, b) * b
 * Division is done first to avoid potential overflow.
 *
 * @param a First number
 * @param b Second number
 * @return The least common multiple
 */
[[nodiscard]] long long lcm(long long a, long long b);

/**
 * @brief Calculates the greatest common divisor of multiple numbers
 *
 * @param numbers Vector of numbers
 * @return The greatest common divisor, or 0 if the vector is empty
 */
[[nodiscard]] long long gcd_multiple(const std::vector<long long>& numbers);

/**
 * @brief Calculates the least common multiple of multiple numbers
 *
 * @param numbers Vector of numbers
 * @return The least common multiple, or 0 if the vector is empty
 */
[[nodiscard]] long long lcm_multiple(const std::vector<long long>& numbers);

/**
 * @brief Calculates the absolute difference between two numbers
 *
 * @param a First number
 * @param b Second number
 * @return The absolute difference |a - b|
 */
[[nodiscard]] long long abs_diff(long long a, long long b);

/**
 * @brief Calculates the sum of a vector of numbers
 *
 * @tparam T Numeric type
 * @param numbers Vector of numbers to sum
 * @return The sum of all elements
 */
template<typename T>
[[nodiscard]] T sum(const std::vector<T>& numbers) {
    return std::accumulate(numbers.begin(), numbers.end(), T{});
}

/**
 * @brief Finds the minimum value in a vector
 *
 * @tparam T Comparable type
 * @param numbers Vector of numbers
 * @return The minimum value
 * @note Behavior is undefined if the vector is empty
 */
template<typename T>
[[nodiscard]] T min(const std::vector<T>& numbers) {
    return *std::min_element(numbers.begin(), numbers.end());
}

/**
 * @brief Finds the maximum value in a vector
 *
 * @tparam T Comparable type
 * @param numbers Vector of numbers
 * @return The maximum value
 * @note Behavior is undefined if the vector is empty
 */
template<typename T>
[[nodiscard]] T max(const std::vector<T>& numbers) {
    return *std::max_element(numbers.begin(), numbers.end());
}

} // namespace aoc::utils