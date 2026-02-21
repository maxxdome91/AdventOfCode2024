/**
 * @file day01.cpp
 * @brief Implementation of Day 1: [TODO - Beschreibung des Puzzles]
 */

#include "days/day01.hpp"

#include <algorithm>
#include <ranges>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>

namespace aoc::day01 {
    std::string solve_part1(const std::vector<std::string> &input) {
        std::vector<int> left_list{};
        std::vector<int> right_list{};
        for (const auto &line: input) {
            std::istringstream iss(line);
            int left_num, right_num;
            if (iss >> left_num >> right_num) {
                left_list.push_back(left_num);
                right_list.push_back(right_num);
            }
        }
        std::ranges::sort(left_list);
        std::ranges::sort(right_list);
        size_t total_distance = 0;
        for (auto [left, right]: std::views::zip(left_list, right_list)) {
            total_distance += std::abs(left - right);
        }
        return std::to_string(total_distance);
    }

    std::string solve_part2(const std::vector<std::string> &input) {
        std::vector<int> left_list{};
        std::vector<int> right_list{};
        for (const auto &line: input) {
            std::istringstream iss(line);
            int left_num, right_num;
            if (iss >> left_num >> right_num) {
                left_list.push_back(left_num);
                right_list.push_back(right_num);
            }
        }
        std::unordered_map<int, int> right_list_counts{};
        for (const auto &right_num: right_list) {
            right_list_counts[right_num]++;
        }
        size_t similarity_score = 0;
        for (int element: left_list) {
            auto count = right_list_counts[element];
            similarity_score += static_cast<size_t>(element) * count;
        }
        return std::to_string(similarity_score);
    }
} // namespace aoc::day01
