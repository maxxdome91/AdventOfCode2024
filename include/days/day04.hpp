#pragma once

/**
 * @file day04.hpp
 * @brief Day 4: Ceres Search
 *
 * Word search puzzle where you need to find occurrences of "XMAS" in a grid.
 * Part 1: Count all occurrences of "XMAS" in horizontal, vertical, and diagonal directions
 * Part 2: Count "X-MAS" patterns where two "MAS" words intersect in an X shape around an 'A'
 */

#include <string>
#include <vector>

namespace aoc::day04 {

/**
 * @brief Solves part 1 of day 4's puzzle - Count XMAS occurrences
 * @param input Vector of strings representing the puzzle input grid
 * @return String representation of the count of XMAS occurrences
 */
std::string solve_part1(const std::vector<std::string>& input);

/**
 * @brief Solves part 2 of day 4's puzzle - Count X-MAS patterns
 * @param input Vector of strings representing the puzzle input grid
 * @return String representation of the count of X-MAS patterns
 */
std::string solve_part2(const std::vector<std::string>& input);

} // namespace aoc::day04
