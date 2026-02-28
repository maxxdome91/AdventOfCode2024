#pragma once

/**
 * @file day12.hpp
 * @brief Day 12: Garden Groups
 *
 * This puzzle involves a grid of garden plots represented by letters. Plots with the 
 * same letter that are connected horizontally or vertically form a "region".
 * 
 * Your goal is to calculate the total price of fencing all regions.
 *
 * Part 1: Price = Sum of (Area * Perimeter) for all regions.
 * Part 2: Price = Sum of (Area * Number of Sides) for all regions.
 */

#include <string>
#include <vector>

namespace aoc::day12 {

/**
 * @brief Solves part 1 of day 12's puzzle
 * @param input Vector of strings representing the puzzle input
 * @return String representation of the solution
 */
std::string solve_part1(const std::vector<std::string>& input);

/**
 * @brief Solves part 2 of day 12's puzzle
 * @param input Vector of strings representing the puzzle input
 * @return String representation of the solution
 */
std::string solve_part2(const std::vector<std::string>& input);

} // namespace aoc::day12