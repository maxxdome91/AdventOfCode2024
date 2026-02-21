/**
 * @file day07.cpp
 * @brief Implementation of Day 7: Bridge Repair
 *
 * This file contains the skeleton implementation for the Bridge Repair puzzle.
 * Students should implement the helper functions and main solving functions
 * following the detailed comments provided.
 */

#include "days/day07.hpp"

#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
#include <cstdint>
#include <cmath>
#include <complex>

namespace aoc::day07 {
    // ============================================================================
    // HELPER FUNCTION STUBS - Implement these first
    // ============================================================================

    std::vector<Equation> parse_input(const std::vector<std::string> &input) {
        /**
         * TASK: Parse each line of input into Equation structures
         *
         * INPUT FORMAT: "test_value: operand1 operand2 operand3 ..."
         * EXAMPLE: "9738: 7 89 52 75 8 1"
         *
         * STEPS:
         * 1. Create an empty vector to store Equation objects
         * 2. For each line in input:
         *    a. Find the position of ": " to split test_value from operands
         *    b. Extract and parse the test_value as an int64_t
         *    c. Extract the operands string (everything after ": ")
         *    d. Split the operands string by spaces
         *    e. Parse each operand as an int64_t and add to a vector
         *    f. Create an Equation struct with test_value and operands vector
         *    g. Add the Equation to the result vector
         * 3. Return the vector of Equation objects
         *
         * HINTS:
         * - Use std::stringstream to parse strings
         * - Use std::stoll() to convert strings to int64_t
         * - Handle the colon and space separator carefully
         */

        std::vector<Equation> equations;

        for (const auto &line: input) {
            std::stringstream ss(line);
            std::string test_value_str, operands_str;
            std::getline(ss, test_value_str, ':');
            std::getline(ss, operands_str);

            std::int64_t test_value = std::stoll(test_value_str);
            std::vector<std::int64_t> operands;
            std::stringstream operands_ss(operands_str);
            std::string operand_str;
            while (operands_ss >> operand_str) {
                operands.push_back(std::stoll(operand_str));
            }
            equations.push_back({test_value, operands});
        }
        return equations;
    }

    std::int64_t concatenate(std::int64_t a, std::int64_t b) {
        /**
         * TASK: Concatenate two numbers by combining their digits
         *
         * EXAMPLES:
         * - concatenate(12, 34) = 1234
         * - concatenate(5, 6) = 56
         * - concatenate(100, 200) = 100200
         *
         * STEPS:
         * 1. Convert both numbers to strings
         * 2. Concatenate the strings
         * 3. Convert the result back to int64_t
         * 4. Return the result
         *
         * HINTS:
         * - Use std::to_string() to convert numbers to strings
         * - Use std::stoll() to convert strings back to int64_t
         * - String concatenation in C++ uses the + operator
         */


        const std::string a_str = std::to_string(a);
        const std::string b_str = std::to_string(b);
        const std::string concatenated_str = a_str + b_str;
        return std::stoll(concatenated_str);
    }

    std::int64_t evaluate_equation(const std::vector<std::int64_t> &operands,
                                   const std::vector<int> &operators) {
        /**
         * TASK: Evaluate an equation with given operators (Part 1)
         *
         * PARAMETERS:
         * - operands: vector of numbers to combine (e.g., [7, 89, 52])
         * - operators: vector of operators where 0 = +, 1 = *
         *
         * EXAMPLE:
         * - operands = [7, 89, 52], operators = [0, 1]
         * - Evaluation: ((7 + 89) * 52) = (96 * 52) = 4992
         *
         * STEPS:
         * 1. Start with result = first operand
         * 2. For each operator and corresponding next operand:
         *    a. If operator is 0 (addition): result = result + operand
         *    b. If operator is 1 (multiplication): result = result * operand
         * 3. Return the final result
         *
         * IMPORTANT: Evaluate strictly left-to-right, no operator precedence!
         *
         * HINTS:
         * - Use a loop to iterate through operators and operands
         * - operators.size() should equal operands.size() - 1
         * - Start the loop from index 1 of operands
         */

        std::int64_t result = operands[0];
        for (size_t i = 0; i < operators.size(); ++i) {
            if (operators[i] == 0) {
                result += operands[i + 1];
            } else if (operators[i] == 1) {
                result *= operands[i + 1];
            }
        }
        return result;
    }

    std::int64_t evaluate_equation_part2(const std::vector<std::int64_t> &operands,
                                         const std::vector<int> &operators) {
        /**
         * TASK: Evaluate an equation with given operators (Part 2)
         *
         * PARAMETERS:
         * - operands: vector of numbers to combine (e.g., [7, 89, 52])
         * - operators: vector of operators where 0 = +, 1 = *, 2 = ||
         *
         * EXAMPLE:
         * - operands = [1, 2, 3], operators = [0, 2]
         * - Evaluation: ((1 + 2) || 3) = (3 || 3) = 33
         *
         * STEPS:
         * 1. Start with result = first operand
         * 2. For each operator and corresponding next operand:
         *    a. If operator is 0 (addition): result = result + operand
         *    b. If operator is 1 (multiplication): result = result * operand
         *    c. If operator is 2 (concatenation): result = concatenate(result, operand)
         * 3. Return the final result
         *
         * IMPORTANT: Evaluate strictly left-to-right, no operator precedence!
         *
         * HINTS:
         * - Similar to evaluate_equation, but with an additional case for concatenation
         * - Use the concatenate() helper function for operator 2
         */

        std::int64_t result = operands[0];
        for (size_t i = 0; i < operators.size(); ++i) {
            if (operators[i] == 0) {
                result += operands[i + 1];
            } else if (operators[i] == 1) {
                result *= operands[i + 1];
            } else if (operators[i] == 2) {
                result = concatenate(result, operands[i + 1]);
            }
        }
        return result;
    }


    std::vector<std::vector<int> > generate_operator_combinations(int num_operators) {
        /**
         * TASK: Generate all possible operator combinations for Part 1
         *
         * PARAMETERS:
         * - num_operators: number of operators needed (n-1 for n operands)
         *
         * RETURNS: Vector of all possible operator sequences
         * Each sequence is a vector of integers (0 or 1)
         *
         * EXAMPLE:
         * - num_operators = 2
         * - Returns: [[0,0], [0,1], [1,0], [1,1]]
         * - Total combinations: 2^2 = 4
         *
         * STEPS:
         * 1. Calculate total combinations: 2^num_operators
         * 2. Create an empty result vector
         * 3. For each combination from 0 to (2^num_operators - 1):
         *    a. Create a new operator sequence vector
         *    b. For each bit position (0 to num_operators-1):
         *       - Extract the bit at that position from the combination number
         *       - Add the bit (0 or 1) to the operator sequence
         *    c. Add the operator sequence to the result vector
         * 4. Return the result vector
         *
         * HINTS:
         * - Use bit shifting and bitwise AND to extract bits
         * - (combination >> bit_position) & 1 extracts bit at position
         * - Total combinations = 1 << num_operators (left shift by num_operators)
         * - This is essentially counting in binary from 0 to 2^num_operators - 1
         */

        std::vector<std::vector<int> > combinations;
        size_t total_combinations = 1 << num_operators;
        for (size_t i = 0; i < total_combinations; ++i) {
            std::vector<int> operators;
            for (size_t bit = 0; bit < num_operators; ++bit) {
                operators.push_back((i >> bit) & 1);
            }
            combinations.push_back(operators);
        }
        return combinations;
    }

    std::vector<std::vector<int> > generate_operator_combinations_part2(int num_operators) {
        /**
         * TASK: Generate all possible operator combinations for Part 2
         *
         * PARAMETERS:
         * - num_operators: number of operators needed (n-1 for n operands)
         *
         * RETURNS: Vector of all possible operator sequences
         * Each sequence is a vector of integers (0, 1, or 2)
         *
         * EXAMPLE:
         * - num_operators = 2
         * - Returns: [[0,0], [0,1], [0,2], [1,0], [1,1], [1,2], [2,0], [2,1], [2,2]]
         * - Total combinations: 3^2 = 9
         *
         * STEPS:
         * 1. Calculate total combinations: 3^num_operators
         * 2. Create an empty result vector
         * 3. For each combination from 0 to (3^num_operators - 1):
         *    a. Create a new operator sequence vector
         *    b. For each digit position (0 to num_operators-1):
         *       - Extract the base-3 digit at that position from the combination number
         *       - Add the digit (0, 1, or 2) to the operator sequence
         *    c. Add the operator sequence to the result vector
         * 4. Return the result vector
         *
         * HINTS:
         * - This is similar to generate_operator_combinations but uses base-3 instead of binary
         * - To extract base-3 digits: (combination / (3^position)) % 3
         * - Total combinations = 3^num_operators
         * - You can calculate 3^num_operators using a loop or std::pow
         */
        const int total_combinations = std::pow(3, num_operators);
        std::vector<std::vector<int> > combinations;
        for (int i = 0; i < total_combinations; ++i) {
            std::vector<int> operators{};
            for (int j = 0; j < num_operators; ++j) {
                auto base_digit = static_cast<int>(i / (std::pow(3, j))) % 3;
                operators.push_back(base_digit);
            }
            std::ranges::reverse(operators);
            combinations.push_back(operators);
        }
        return combinations;
    }

    // ============================================================================
    // MAIN SOLVING FUNCTIONS
    // ============================================================================

    std::string solve_part1(const std::vector<std::string> &input) {
        /**
         * TASK: Solve Part 1 of the Bridge Repair puzzle
         *
         * PROBLEM:
         * Find all equations where the test value can be achieved by inserting
         * + or * operators between operands. Sum the test values of all valid equations.
         *
         * ALGORITHM:
         * 1. Parse the input into Equation structures
         * 2. For each equation:
         *    a. Generate all 2^(n-1) possible operator combinations (n = number of operands)
         *    b. For each operator combination:
         *       - Evaluate the equation with those operators
         *       - If the result equals the test value, mark this equation as valid
         *    c. If any combination was valid, add the test value to the sum
         * 3. Return the sum as a string
         *
         * STEPS:
         * 1. Call parse_input() to get vector of Equation objects
         * 2. Initialize sum = 0
         * 3. For each equation in the parsed input:
         *    a. Get the number of operators needed: operands.size() - 1
         *    b. Generate all operator combinations using generate_operator_combinations()
         *    c. Initialize found_valid = false
         *    d. For each operator combination:
         *       - Evaluate the equation using evaluate_equation()
         *       - If result equals test_value:
         *         * Set found_valid = true
         *         * Break out of the loop (we only need one valid combination)
         *    e. If found_valid is true, add test_value to sum
         * 4. Convert sum to string and return
         *
         * HINTS:
         * - Use std::to_string() to convert the final sum to a string
         * - Break early once you find a valid operator combination for an equation
         * - The sum might be very large, so use int64_t
         */

        auto equation_objects = parse_input(input);
        int64_t sum = 0;
        for (auto equation_object: equation_objects) {
            auto num_operators = equation_object.operands.size() - 1;
            auto operator_combinations = generate_operator_combinations(num_operators);
            auto found_valid = false;
            for (auto operator_combination: operator_combinations) {
                auto evaluation = evaluate_equation(equation_object.operands, operator_combination);
                if (evaluation == equation_object.test_value) {
                    found_valid = true;
                    break;
                }
            }
            if (found_valid) {
                sum += equation_object.test_value;
            }
        }

        // TODO: Implement Part 1 solution here
        // std::vector<Equation> equations = parse_input(input);
        // std::int64_t sum = 0;
        //
        // for (const auto& equation : equations) {
        //     int num_operators = equation.operands.size() - 1;
        //     auto combinations = generate_operator_combinations(num_operators);
        //
        //     bool found_valid = false;
        //     for (const auto& operators : combinations) {
        //         std::int64_t result = evaluate_equation(equation.operands, operators);
        //         if (result == equation.test_value) {
        //             found_valid = true;
        //             break;
        //         }
        //     }
        //
        //     if (found_valid) {
        //         sum += equation.test_value;
        //     }
        // }
        //
        return std::to_string(sum);
    }

    std::string solve_part2(const std::vector<std::string> &input) {
        /**
         * TASK: Solve Part 2 of the Bridge Repair puzzle
         *
         * PROBLEM:
         * Find all equations where the test value can be achieved by inserting
         * +, *, or || (concatenation) operators between operands.
         * Sum the test values of all valid equations.
         *
         * ALGORITHM:
         * 1. Parse the input into Equation structures
         * 2. For each equation:
         *    a. Generate all 3^(n-1) possible operator combinations (n = number of operands)
         *    b. For each operator combination:
         *       - Evaluate the equation with those operators (using Part 2 evaluation)
         *       - If the result equals the test value, mark this equation as valid
         *    c. If any combination was valid, add the test value to the sum
         * 3. Return the sum as a string
         *
         * STEPS:
         * 1. Call parse_input() to get vector of Equation objects
         * 2. Initialize sum = 0
         * 3. For each equation in the parsed input:
         *    a. Get the number of operators needed: operands.size() - 1
         *    b. Generate all operator combinations using generate_operator_combinations_part2()
         *    c. Initialize found_valid = false
         *    d. For each operator combination:
         *       - Evaluate the equation using evaluate_equation_part2()
         *       - If result equals test_value:
         *         * Set found_valid = true
         *         * Break out of the loop (we only need one valid combination)
         *    e. If found_valid is true, add test_value to sum
         * 4. Convert sum to string and return
         *
         * HINTS:
         * - Very similar to solve_part1, but uses Part 2 functions
         * - Use generate_operator_combinations_part2() instead of generate_operator_combinations()
         * - Use evaluate_equation_part2() instead of evaluate_equation()
         * - Break early once you find a valid operator combination for an equation
         * - The sum might be very large, so use int64_t
         */

        // TODO: Implement Part 2 solution here
        // std::vector<Equation> equations = parse_input(input);
        // std::int64_t sum = 0;
        //
        // for (const auto& equation : equations) {
        //     int num_operators = equation.operands.size() - 1;
        //     auto combinations = generate_operator_combinations_part2(num_operators);
        //
        //     bool found_valid = false;
        //     for (const auto& operators : combinations) {
        //         std::int64_t result = evaluate_equation_part2(equation.operands, operators);
        //         if (result == equation.test_value) {
        //             found_valid = true;
        //             break;
        //         }
        //     }
        //
        //     if (found_valid) {
        //         sum += equation.test_value;
        //     }
        // }
        //
        // return std::to_string(sum);

        return "Not implemented";
    }
} // namespace aoc::day07
