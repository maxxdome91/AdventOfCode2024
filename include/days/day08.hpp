/**
 * @file day08.hpp
 * @brief Day 8: Resonant Collinearity
 *
 * PUZZLE CONTEXT:
 * ================
 * You discover a city map with antennas tuned to specific frequencies (indicated by
 * lowercase letters, uppercase letters, or digits). Each antenna frequency creates
 * "antinodes" at specific positions based on resonant frequencies.
 *
 * Part 1 - Basic Antinodes:
 *   An antinode occurs at any point that is perfectly in line with two antennas of
 *   the same frequency, but only when one antenna is TWICE as far away as the other.
 *   For each pair of same-frequency antennas, there are exactly TWO antinodes:
 *   - One antinode on one side of the pair (closer to the first antenna)
 *   - One antinode on the other side (closer to the second antenna)
 *   Antinodes can exist at antenna positions and must be within map bounds.
 *
 * Part 2 - Resonant Harmonics:
 *   An antinode occurs at ANY grid position exactly in line with at least two
 *   antennas of the same frequency, regardless of distance. This means:
 *   - All points on the line passing through each antenna pair are antinodes
 *   - Antennas themselves become antinodes (if there are 2+ of that frequency)
 *   - The line extends in both directions until hitting map boundaries
 *
 * EXPECTED OUTPUT:
 *   Part 1: Count of unique locations containing antinodes (within bounds)
 *   Part 2: Count of unique locations with updated harmonic rules
 *
 * ALGORITHMIC STRATEGY:
 * =====================
 *
 * Part 1 Approach:
 * 1. Parse the grid and group antenna positions by their frequency character
 *    - HINT: Use std::map<char, std::vector<Position>> or std::unordered_map
 *
 * 2. For each frequency that has 2+ antennas:
 *    a. Generate all unique pairs of antennas with that frequency
 *       - HINT: Use nested loops where j > i to avoid duplicates
 *
 *    b. For each pair (A, B), calculate the two antinode positions:
 *       - Antinode 1: Point on the line from A through B, at distance 2*(B-A) from A
 *         Formula: A + 2*(B - A) = 2*B - A
 *       - Antinode 2: Point on the line from B through A, at distance 2*(A-B) from B
 *         Formula: B + 2*(A - B) = 2*A - B
 *       - HINT: Think of this as vector math: delta = B - A, antinodes at A - delta and B + delta
 *
 *    c. Add valid antinodes (within bounds) to a set
 *       - HINT: Use std::set<Position> or std::unordered_set with custom hash
 *
 * 3. Return the size of the antinode set
 *
 * Part 2 Approach:
 * 1. Same parsing and grouping as Part 1
 *
 * 2. For each frequency with 2+ antennas, for each pair (A, B):
 *    a. Calculate the direction vector: delta = B - A
 *    b. Extend the line in BOTH directions from both antennas:
 *       - From A: go in direction -delta (opposite to B) until out of bounds
 *       - From B: go in direction +delta (towards and past B) until out of bounds
 *       - HINT: Use a while loop with bounds checking
 *
 *    c. Add all valid positions to the antinode set
 *       - HINT: The antennas themselves will be included automatically
 *
 * 3. Return the size of the antinode set
 *
 * KEY DATA STRUCTURES:
 * - Position struct with x, y coordinates (consider operator< for std::set)
 * - Map from char to vector of Positions for antenna grouping
 * - Set of Positions for tracking unique antinode locations
 *
 * EDGE CASES TO CONSIDER:
 * - Single antenna of a frequency (creates no antinodes)
 * - Antinodes at antenna positions (valid in both parts)
 * - Antinodes outside map bounds (must be excluded)
 * - Multiple antenna pairs creating antinodes at same location (use set to dedupe)
 */

#pragma once

#include <string>
#include <vector>

namespace aoc::day08 {

/**
 * @brief Solves part 1: Count unique antinode locations with basic rules
 * @param input Vector of strings representing the antenna map
 * @return String representation of the count of unique antinode locations
 *
 * For each pair of same-frequency antennas, calculate two antinodes where
 * one antenna is twice as far as the other. Count unique in-bounds positions.
 */
[[nodiscard]] std::string solve_part1(const std::vector<std::string>& input);

/**
 * @brief Solves part 2: Count unique antinode locations with harmonic rules
 * @param input Vector of strings representing the antenna map
 * @return String representation of the count of unique antinode locations
 *
 * For each pair of same-frequency antennas, all positions on the line through
 * them (within bounds) are antinodes, including the antenna positions themselves.
 */
[[nodiscard]] std::string solve_part2(const std::vector<std::string>& input);

} // namespace aoc::day08
