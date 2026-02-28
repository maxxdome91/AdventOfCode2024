#pragma once

/**
 * @file day13.hpp
 * @brief Day 13: Claw Contraption
 *
 * This puzzle involves claw machines with two buttons (A and B) and a prize at specific 
 * coordinates. Each button moves the claw a specific amount in X and Y.
 * 
 * - Button A: Moves (AX, AY), costs 3 tokens.
 * - Button B: Moves (BX, BY), costs 1 token.
 * 
 * Part 1: Find the minimum tokens needed to reach the prize for each machine, 
 *         with a maximum of 100 presses per button.
 * Part 2: The prize coordinates are actually 10,000,000,000,000 higher in both X and Y. 
 *         There is no limit on button presses.
 */

#include <string>
#include <vector>

namespace aoc::day13 {

/**
 * @brief Solves part 1 of day 13's puzzle
 * @param input Vector of strings representing the puzzle input
 * @return String representation of the solution
 */
std::string solve_part1(const std::vector<std::string>& input);

/**
 * @brief Solves part 2 of day 13's puzzle
 * @param input Vector of strings representing the puzzle input
 * @return String representation of the solution
 */
std::string solve_part2(const std::vector<std::string>& input);

} // namespace aoc::day13