#pragma once

/**
 * @file day11.hpp
 * @brief Day 11: Plutonian Pebbles
 *
 * This puzzle involves a line of stones with numbers that change according to specific rules 
 * every time you blink.
 * 
 * Rules:
 * 1. If the stone's number is 0, it is replaced by a stone with number 1.
 * 2. If the stone's number has an even number of digits, it is replaced by two stones:
 *    the left half and the right half of the digits respectively.
 * 3. If neither rule applies, the stone's number is multiplied by 2024.
 *
 * Part 1: How many stones will you have after blinking 25 times?
 * Part 2: How many stones will you have after blinking 75 times?
 */

#include <string>
#include <vector>

namespace aoc::day11 {

/**
 * @brief Solves part 1 of day 11's puzzle
 * @param input Vector of strings representing the puzzle input
 * @return String representation of the solution
 */
std::string solve_part1(const std::vector<std::string>& input);

/**
 * @brief Solves part 2 of day 11's puzzle
 * @param input Vector of strings representing the puzzle input
 * @return String representation of the solution
 */
std::string solve_part2(const std::vector<std::string>& input);

} // namespace aoc::day11