#pragma once

/**
 * @file day07.hpp
 * @brief Day 7: Bridge Repair
 *
 * PROBLEM OVERVIEW:
 * The problem involves equations where we need to determine if a test value can be
 * achieved by inserting operators between operands. Each line has the format:
 *   test_value: operand1 operand2 operand3 ...
 *
 * ALGORITHMIC APPROACH:
 * This uses a highly optimized recursive right-to-left evaluation with early pruning.
 * By working backward from the test_value, we can mathematically eliminate massive
 * numbers of invalid operator combinations early, vastly outperforming pre-computing
 * sequences left-to-right.
 *
 * Part 1: Use only two operators: + (addition) and * (multiplication)
 * Part 2: Use three operators: + (addition), * (multiplication), and || (concatenation)
 */

#include <string>
#include <vector>
#include <cstdint>

namespace aoc::day07 {

/**
 * @struct Equation
 * @brief Represents a single equation from the input
 * @member test_value The target value that must be achieved
 * @member operands Vector of numbers to combine with operators
 */
struct Equation {
    std::int64_t test_value;
    std::vector<std::int64_t> operands;
};

/**
 * @brief Parses the input data into Equation structures
 * @param input Vector of strings in format "test_value: operand1 operand2 ..."
 * @return Vector of parsed Equation structures
 */
std::vector<Equation> parse_input(const std::vector<std::string>& input);

/**
 * @brief Solves part 1 of day 7's puzzle
 * @param input Vector of strings representing the puzzle input
 * @return String representation of the solution (sum of valid test values)
 */
std::string solve_part1(const std::vector<std::string>& input);

/**
 * @brief Solves part 2 of day 7's puzzle
 * @param input Vector of strings representing the puzzle input
 * @return String representation of the solution (sum of valid test values with concatenation)
 */
std::string solve_part2(const std::vector<std::string>& input);

} // namespace aoc::day07
