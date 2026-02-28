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
#include <cmath>

namespace aoc::day07
{
    // ============================================================================
    // HELPER FUNCTION STUBS - Implement these first
    // ============================================================================

    std::vector<Equation> parse_input(const std::vector<std::string>& input)
    {
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

        for (const auto& line : input)
        {
            std::stringstream ss(line);
            std::string test_value_str, operands_str;
            std::getline(ss, test_value_str, ':');
            std::getline(ss, operands_str);

            std::int64_t test_value = std::stoll(test_value_str);
            std::vector<std::int64_t> operands;
            std::stringstream operands_ss(operands_str);
            std::string operand_str;
            while (operands_ss >> operand_str)
            {
                operands.push_back(std::stoll(operand_str));
            }
            Equation equation{test_value, operands};
            equations.push_back(equation);
        }
        return equations;
    }

    bool is_valid_equation(std::int64_t target, const std::vector<std::int64_t>& operands, int index, bool allow_concat)
    {
        if (index == 0)
        {
            return target == operands[0];
        }

        const std::int64_t current_operand = operands[index];

        // 1. Multiplication (Right-to-Left: target must be cleanly divisible by current_operand)
        if (target % current_operand == 0)
        {
            if (is_valid_equation(target / current_operand, operands, index - 1, allow_concat))
            {
                return true;
            }
        }

        // 2. Concatenation (Right-to-Left: target must "end with" current_operand)
        if (allow_concat)
        {
            std::int64_t temp = current_operand;
            std::int64_t multiplier = 1;
            while (temp > 0)
            {
                multiplier *= 10;
                temp /= 10;
            }

            if ((target - current_operand) % multiplier == 0 && target >= current_operand)
            {
                if (is_valid_equation((target - current_operand) / multiplier, operands, index - 1, allow_concat))
                {
                    return true;
                }
            }
        }

        // 3. Addition (Right-to-Left: target must be >= current_operand)
        if (target >= current_operand)
        {
            if (is_valid_equation(target - current_operand, operands, index - 1, allow_concat))
            {
                return true;
            }
        }

        return false;
    }

    // ============================================================================
    // MAIN SOLVING FUNCTIONS
    // ============================================================================

    std::string solve_part1(const std::vector<std::string>& input)
    {
        /**
         * TASK: Solve Part 1 of the Bridge Repair puzzle
         */
        auto equation_objects = parse_input(input);
        int64_t sum = 0;
        for (const auto& [test_value, operands] : equation_objects)
        {
            if (!operands.empty() && is_valid_equation(test_value, operands, static_cast<int>(operands.size() - 1),
                                                       false))
            {
                sum += test_value;
            }
        }
        return std::to_string(sum);
    }

    std::string solve_part2(const std::vector<std::string>& input)
    {
        /**
         * TASK: Solve Part 2 of the Bridge Repair puzzle
         */
        auto equation_objects = parse_input(input);
        int64_t sum = 0;
        for (const auto& [test_value, operands] : equation_objects)
        {
            if (!operands.empty() && is_valid_equation(test_value, operands, static_cast<int>(operands.size() - 1),
                                                       true))
            {
                sum += test_value;
            }
        }
        return std::to_string(sum);
    }
} // namespace aoc::day07
