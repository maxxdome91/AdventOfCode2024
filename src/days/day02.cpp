/**
 * @file day02.cpp
 * @brief Implementation of Day 2: [TODO - Beschreibung des Puzzles]
 */

#include "days/day02.hpp"

#include <sstream>
#include <string>
#include <vector>

namespace aoc::day02 {
    // Helper to check a single report line
    bool is_safe_report(const std::vector<int> &row) {
        if (row.size() < 2) return true; // Edge case: 1 number is technically sorted

        bool increasing = false;
        bool decreasing = false;

        for (size_t i = 0; i < row.size() - 1; ++i) {
            const int diff = row[i + 1] - row[i];

            // 1. Check magnitude constraint immediately
            if (std::abs(diff) < 1 || std::abs(diff) > 3) {
                return false;
            }

            // 2. Track direction
            if (diff > 0) increasing = true;
            if (diff < 0) decreasing = true;

            // 3. Conflict check: Can't be both increasing AND decreasing
            if (increasing && decreasing) {
                return false;
            }
        }
        return true;
    }

    std::string solve_part1(const std::vector<std::string> &input) {
        long num_valid_rows = 0;

        for (const auto &line: input) {
            std::vector<int> row;
            // Optimization: reserve memory if you know approx size to avoid reallocations
            row.reserve(8);

            std::stringstream ss(line);
            int num;
            while (ss >> num) {
                row.push_back(num);
            }

            if (is_safe_report(row)) {
                num_valid_rows++;
            }
        }
        return std::to_string(num_valid_rows);
    }

    std::string solve_part2(const std::vector<std::string> &input) {
        long num_valid_rows = 0;

        for (const auto &line: input) {
            std::vector<int> row;
            // Optimization: reserve memory if you know approx size to avoid reallocations
            row.reserve(8);

            std::stringstream ss(line);
            int num;
            while (ss >> num) {
                row.push_back(num);
            }

            if (is_safe_report(row)) {
                num_valid_rows++;
            } else {
                for (int i = 0; i < row.size(); ++i) {
                    auto adjusted_row = row;
                    adjusted_row.erase(adjusted_row.begin() + i);
                    if (is_safe_report(adjusted_row)) {
                        num_valid_rows++;
                        break;
                    }
                }
            }
        }
        return std::to_string(num_valid_rows);
    }
} // namespace aoc::day02
