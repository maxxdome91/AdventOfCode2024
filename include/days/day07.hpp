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
 * This is a brute-force problem that requires:
 * 1. Parsing each equation into a test value and a list of operands
 * 2. Generating all possible combinations of operators
 * 3. Evaluating each combination left-to-right
 * 4. Checking if any combination equals the test value
 * 5. Summing all valid test values
 *
 * Part 1: Use only two operators: + (addition) and * (multiplication)
 *         For n operands, there are 2^(n-1) possible operator combinations
 *
 * Part 2: Use three operators: + (addition), * (multiplication), and || (concatenation)
 *         For n operands, there are 3^(n-1) possible operator combinations
 *         Concatenation combines two numbers: 12 || 34 = 1234
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
 *
 * IMPLEMENTATION NOTES:
 * - Split each line by ": " to separate test_value from operands
 * - Parse test_value as an integer
 * - Split operands by spaces and parse each as an integer
 * - Store in Equation struct
 */
std::vector<Equation> parse_input(const std::vector<std::string>& input);

/**
 * @brief Evaluates an equation given a sequence of operators (Part 1)
 * @param operands Vector of numbers to combine
 * @param operators Vector of operators (0 = +, 1 = *)
 * @return The result of evaluating left-to-right with given operators
 *
 * IMPLEMENTATION NOTES:
 * - Start with the first operand as the result
 * - For each operator and next operand, apply the operator to result and operand
 * - Operators: 0 = addition, 1 = multiplication
 * - Evaluate strictly left-to-right (no operator precedence)
 * - Example: 1 + 2 * 3 with operators [0, 1] = ((1 + 2) * 3) = 9
 */
std::int64_t evaluate_equation(const std::vector<std::int64_t>& operands,
                               const std::vector<int>& operators);

/**
 * @brief Evaluates an equation given a sequence of operators (Part 2)
 * @param operands Vector of numbers to combine
 * @param operators Vector of operators (0 = +, 1 = *, 2 = ||)
 * @return The result of evaluating left-to-right with given operators
 *
 * IMPLEMENTATION NOTES:
 * - Start with the first operand as the result
 * - For each operator and next operand, apply the operator to result and operand
 * - Operators: 0 = addition, 1 = multiplication, 2 = concatenation
 * - Evaluate strictly left-to-right (no operator precedence)
 * - Concatenation: combine digits (e.g., 12 || 34 = 1234)
 * - Example: 1 + 2 || 3 with operators [0, 2] = ((1 + 2) || 3) = 23
 */
std::int64_t evaluate_equation_part2(const std::vector<std::int64_t>& operands,
                                     const std::vector<int>& operators);

/**
 * @brief Concatenates two numbers by combining their digits
 * @param a First number
 * @param b Second number
 * @return Result of concatenating a and b (e.g., 12 || 34 = 1234)
 *
 * IMPLEMENTATION NOTES:
 * - Convert both numbers to strings
 * - Concatenate the strings
 * - Convert back to integer
 * - Handle negative numbers appropriately
 */
std::int64_t concatenate(std::int64_t a, std::int64_t b);

/**
 * @brief Generates all possible operator combinations for Part 1
 * @param num_operators Number of operators needed (n-1 for n operands)
 * @return Vector of all possible operator sequences (each sequence is a vector of 0s and 1s)
 *
 * IMPLEMENTATION NOTES:
 * - For num_operators = k, generate 2^k combinations
 * - Each combination is a vector of k integers (0 or 1)
 * - Can use binary counting: for i from 0 to 2^k-1, extract bits to form operator sequence
 * - Example: for k=2, generate: [0,0], [0,1], [1,0], [1,1]
 */
std::vector<std::vector<int>> generate_operator_combinations(int num_operators);

/**
 * @brief Generates all possible operator combinations for Part 2
 * @param num_operators Number of operators needed (n-1 for n operands)
 * @return Vector of all possible operator sequences (each sequence is a vector of 0s, 1s, and 2s)
 *
 * IMPLEMENTATION NOTES:
 * - For num_operators = k, generate 3^k combinations
 * - Each combination is a vector of k integers (0, 1, or 2)
 * - Can use base-3 counting: for i from 0 to 3^k-1, extract base-3 digits to form operator sequence
 * - Example: for k=2, generate: [0,0], [0,1], [0,2], [1,0], [1,1], [1,2], [2,0], [2,1], [2,2]
 */
std::vector<std::vector<int>> generate_operator_combinations_part2(int num_operators);

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