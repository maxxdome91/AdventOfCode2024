/**
 * @file day11.cpp
 * @brief Implementation of Day 11: Plutonian Pebbles
 */

#include "days/day11.hpp"

#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <numeric>
#include <ranges>
#include <sstream>

namespace aoc::day11
{
    /**
     * @brief Logic for transforming a single stone based on the puzzle rules.
     *
     * Rules:
     * 1. If the stone's number is 0, it is replaced by a stone with number 1.
     * 2. If the stone's number has an even number of digits, it is replaced by two stones:
     *    the left half and the right half of the digits respectively.
     * 3. If neither rule applies, the stone's number is multiplied by 2024.
     *
     * Tip: To split even digits, use `std::to_string` and `std::stoll`, or
     * mathematical operations like `log10` and `pow` for better performance.
     */
    std::vector<long long> transform_stone(long long value)
    {
        if (value == 0)
        {
            return {1ll};
        }

        int digits = static_cast<int>(std::log10(value)) + 1;
        if (digits % 2 == 0)
        {
            long long divisor = std::pow(10, digits / 2);
            return {value / divisor, value % divisor};
        }
        else
        {
            return {value * 2024};
        }
    }

    /**
     * @brief Simulates a single blink across all stones using a frequency map.
     *
     * Strategy:
     * - Observe that the order of stones doesn't matter, and many stones share the same value.
     * - Create a new `next_counts` map.
     * - For each `[value, count]` in `current_counts`:
     *    1. Transform the `value` into 1 or 2 `new_values`.
     *    2. Add the original `count` to `next_counts[new_value]`.
     */
    std::unordered_map<long long, long long> blink(const std::unordered_map<long long, long long>& current_counts)
    {
        std::unordered_map<long long, long long> next_counts;
        for (const auto& [value, count] : current_counts)
        {
            auto new_values = transform_stone(value);
            for (long long new_value : new_values)
            {
                next_counts[new_value] += count;
            }

        }
        return next_counts;
    }

    /**
     * @brief Part 1: How many stones after 25 blinks?
     */
    std::string solve_part1(const std::vector<std::string>& input)
    {
        // 1. Parse the input string into a `std::unordered_map<long long, long long>`
        std::stringstream ss(input[0]);
        std::unordered_map<long long, long long> current_counts;
        long long value;
        while (ss >> value)
        {
            current_counts[value]++;
        }
        // 2. Loop 25 times calling blink()
        for (int i = 0; i < 25; ++i)
        {
            current_counts = blink(current_counts);
        }
        // 3. Sum all values (the counts) in the final map.
        const auto result = std::ranges::fold_left(current_counts | std::views::values, 0LL, std::plus<>());

        return std::to_string(result);
    }

    /**
     * @brief Part 2: How many stones after 75 blinks?
     *
     * Note: Simple simulation (vector) will fail here due to exponential growth.
     * The frequency map approach (above) handles this efficiently.
     */
    std::string solve_part2(const std::vector<std::string>& input)
    {
        std::stringstream ss(input[0]);
        std::unordered_map<long long, long long> current_counts;
        while (ss.good())
        {
            long long value;
            ss >> value;
            current_counts[value] = 1;
        }
        // 2. Loop 75 times calling blink()
        for (int i = 0; i < 75; ++i)
        {
            current_counts = blink(current_counts);
        }
        // 3. Sum all values (the counts) in the final map.
        const auto result = std::ranges::fold_left(current_counts | std::views::values, 0LL, std::plus<>());

        return std::to_string(result);
    }
} // namespace aoc::day11
