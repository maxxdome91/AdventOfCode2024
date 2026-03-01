/**
 * @file day17.cpp
 * @brief Implementation of Day 17: Chronospatial Computer
 */

#include "days/day17.hpp"

#include <ranges>
#include <string>
#include <vector>
#include <sstream>

namespace aoc::day17
{
    // ============================================================================
    // COMPUTER STATE IMPLEMENTATION
    // ============================================================================

    // TODO: Add constructor for ComputerState if needed


    // ============================================================================
    // PROGRAM IMPLEMENTATION
    // ============================================================================

    // TODO: Add method to check if instruction pointer is within program bounds

    // ============================================================================
    // COMPUTER IMPLEMENTATION
    // ============================================================================

    Computer::Computer(const Program& program, int64_t A, int64_t B, int64_t C)
    {
        // TODO: Initialize program_, state_, and output_
        this->program_ = program;
        this->state_ = {A, B, C, 0};
        this->output_ = {};
    }

    int64_t Computer::resolveCombo(int operand) const
    {
        switch (operand)
        {
        case 0:
        case 1:
        case 2:
        case 3: return operand;
        case 4: return state_.A;
        case 5: return state_.B;
        case 6: return state_.C;
        default: return 0; // Should not occur
        }
    }

    void Computer::executeInstruction()
    {
        if (isHalted()) return;

        auto opcode = program_.instructions.at(state_.instructionPointer);
        auto operand = program_.instructions.at(state_.instructionPointer + 1);
        
        bool jumped = false;
        switch (opcode)
        {
        case 0: // adv
            state_.A >>= resolveCombo(operand);
            break;
        case 1: // bxl
            state_.B ^= operand;
            break;
        case 2: // bst
            state_.B = resolveCombo(operand) % 8;
            break;
        case 3: // jnz
            if (state_.A != 0) {
                state_.instructionPointer = static_cast<size_t>(operand);
                jumped = true;
            }
            break;
        case 4: // bxc
            state_.B ^= state_.C;
            break;
        case 5: // out
            output_.push_back(static_cast<int>(resolveCombo(operand) % 8));
            break;
        case 6: // bdv
            state_.B = state_.A >> resolveCombo(operand);
            break;
        case 7: // cdv
            state_.C = state_.A >> resolveCombo(operand);
            break;
        default: ;
        }

        if (!jumped)
        {
            state_.instructionPointer += 2;
        }
    }

    bool Computer::isHalted() const
    {
        return state_.instructionPointer >= program_.instructions.size();
    }

    void Computer::run()
    {
        while (!isHalted()) { executeInstruction(); }
    }

    const std::vector<int>& Computer::getOutput() const
    {
        return output_;
    }

    ComputerState Computer::getState() const
    {
        return state_;
    }

    // ============================================================================
    // PARSING IMPLEMENTATION
    // ============================================================================

    ParsedInput parseInput(const std::vector<std::string>& input)
    {
        ParsedInput result;

        for (const auto& line : input)
        {
            if (line.starts_with("Register A:"))
            {
                result.A = std::stoll(line.substr(11));
            }
            else if (line.starts_with("Register B:"))
            {
                result.B = std::stoll(line.substr(11));
            }
            else if (line.starts_with("Register C:"))
            {
                result.C = std::stoll(line.substr(11));
            }
            else if (line.starts_with("Program:"))
            {
                std::string program_str = line.substr(9);
                std::stringstream ss(program_str);
                std::string token;
                while (std::getline(ss, token, ','))
                {
                    result.program.push_back(std::stoi(token));
                }
            }
        }

        return result;
    }

    // ============================================================================
    // SOLVER IMPLEMENTATION
    // ============================================================================

    std::string runProgram(const std::vector<std::string>& input)
    {
        auto parsed = parseInput(input);
        Program program{parsed.program};
        Computer computer{program, parsed.A, parsed.B, parsed.C};
        computer.run();
        
        const auto& output = computer.getOutput();
        std::string result;
        for (size_t i = 0; i < output.size(); ++i)
        {
            if (i > 0) result += ',';
            result += std::to_string(output[i]);
        }
        return result;
    }

    std::string solve_part1(const std::vector<std::string>& input)
    {
        return runProgram(input);
    }

    std::string solve_part2(const std::vector<std::string>& input)
    {
        // TODO: Implement part 2 solution
        //
        // EXPECTED REQUIREMENT:
        // Find the value for register A that causes the program to output
        // a specific sequence (often the program itself).
        //
        // APPROACH HINTS:
        // - The program likely processes A in chunks of 3 bits at a time
        // - Each iteration outputs one 3-bit value and shifts A right
        // - Work backwards from the desired output to find valid A values
        // - May need to try candidates and verify
        // - Consider the relationship between A, B, C during execution

        return "Not implemented";
    }
} // namespace aoc::day17
