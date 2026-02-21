/**
 * @file day03.cpp
 * @brief Implementation of Day 3: [TODO - Beschreibung des Puzzles]
 */

#include "days/day03.hpp"

#include <regex>
#include <string>
#include <vector>

namespace aoc::day03 {
    std::regex pattern_mul(R"(mul\((\d{1,3}),(\d{1,3})\))");
    std::regex pattern_part2(R"(mul\((\d{1,3}),(\d{1,3})\)|do\(\)|don't\(\))");

    std::string solve_part1(const std::vector<std::string> &input) {
        size_t result = 0;
        for (auto line: input) {
            auto begin = std::sregex_iterator(line.begin(), line.end(), pattern_mul);
            auto end = std::sregex_iterator();
            for (auto it = begin; it != end; ++it) {
                const std::smatch &match = *it;
                result += std::stoi(match[1]) * std::stoi(match[2]);
            }
        }
        return std::to_string(result);
    }

    std::string solve_part2(const std::vector<std::string> &input) {
        size_t result = 0;
        bool mul_enabled = true;
        for (auto line: input) {
            auto begin = std::sregex_iterator(line.begin(), line.end(), pattern_part2);
            auto end = std::sregex_iterator();
            for (auto it = begin; it != end; ++it) {
                const std::smatch &match = *it;
                if (match[0].str() == "do()") {
                    mul_enabled = true;
                } else if (match[0].str() == "don't()") {
                    mul_enabled = false;
                } else if (mul_enabled) {
                    result += std::stoi(match[1]) * std::stoi(match[2]);
                }
            }
        }
        return std::to_string(result);
    }
} // namespace aoc::day03
