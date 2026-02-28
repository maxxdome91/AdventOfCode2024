#pragma once

/**
 * @file day14.hpp
 * @brief Day 14: [TODO - Beschreibung des Puzzles]
 *
 * [TODO - Detaillierte Beschreibung des Puzzles]
 * Part 1: [TODO - Beschreibung von Teil 1]
 * Part 2: [TODO - Beschreibung von Teil 2]
 */

#include <string>
#include <vector>

namespace aoc::day14 {

/**
 * @brief Represents a robot with a position and velocity.
 */
struct Robot {
    int px, py;
    int vx, vy;
};

/**
 * @brief Parses the input strings into a vector of Robot objects.
 * @param input The raw input lines from the puzzle.
 * @return A vector of parsed Robots.
 */
std::vector<Robot> parse_input(const std::vector<std::string>& input);

/**
 * @brief Simulates the movement of a robot over a given time period.
 * @param robot The robot to move.
 * @param seconds The duration of the movement in seconds.
 * @param width The width of the grid.
 * @param height The height of the grid.
 * @return The new position of the robot as a pair (x, y).
 */
std::pair<int, int> simulate_movement(const Robot& robot, int seconds, int width, int height);

/**
 * @brief Calculates the safety factor by counting robots in quadrants.
 * @param positions The final positions of all robots.
 * @param width The width of the grid.
 * @param height The height of the grid.
 * @return The product of robot counts in the four quadrants.
 */
long long calculate_safety_factor(const std::vector<std::pair<int, int>>& positions, int width, int height);

/**
 * @brief Solves part 1 of day 14's puzzle
 * @param input Vector of strings representing the puzzle input
 * @return String representation of the solution
 */
std::string solve_part1(const std::vector<std::string>& input);

/**
 * @brief Solves part 2 of day 14's puzzle
 * @param input Vector of strings representing the puzzle input
 * @return String representation of the solution
 */
std::string solve_part2(const std::vector<std::string>& input);

} // namespace aoc::day14