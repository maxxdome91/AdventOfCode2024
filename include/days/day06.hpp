/**
 * @file day06.hpp
 * @brief Day 6: Guard Gallivant
 *
 * This puzzle involves simulating a guard's patrol path on a 2D grid and
 * analyzing the guard's movement patterns.
 *
 * Part 1: Predict the guard's patrol path and count distinct positions visited
 * before the guard leaves the mapped area.
 *
 * Part 2: Find all positions where placing a single new obstruction would cause
 * the guard to enter an infinite loop, never leaving the mapped area.
 */

#pragma once

#include <string>
#include <vector>

namespace aoc::day06 {

/**
 * @brief Solves part 1: Count distinct positions visited by the guard
 * @param input Vector of strings representing the puzzle input grid
 * @return String representation of the number of distinct positions visited
 *
 * The guard follows a strict protocol:
 * 1. If something is directly in front, turn right 90 degrees
 * 2. Otherwise, take a step forward
 *
 * Simulation continues until the guard steps outside the grid boundaries.
 */
[[nodiscard]] std::string solve_part1(const std::vector<std::string>& input);

/**
 * @brief Solves part 2: Count positions where adding an obstruction creates a loop
 * @param input Vector of strings representing the puzzle input grid
 * @return String representation of the number of valid obstruction positions
 *
 * A loop occurs when the guard revisits the same position with the same facing
 * direction. The new obstruction cannot be placed at the guard's starting position.
 */
[[nodiscard]] std::string solve_part2(const std::vector<std::string>& input);

} // namespace aoc::day06