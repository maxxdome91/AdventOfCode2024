#pragma once

/**
 * @file day17.hpp
 * @brief Day 17: Chronospatial Computer
 *
 * PUZZLE SUMMARY:
 * ---------------
 * Simulate a 3-bit computer with three registers (A, B, C) and eight instructions.
 *
 * Computer Basics:
 * - Program is a list of 3-bit numbers (0-7)
 * - Three registers: A, B, C (can hold any integer, not limited to 3 bits)
 * - Instruction pointer starts at 0
 * - Each instruction has an opcode (3-bit number) followed by an operand
 * - Instruction pointer increases by 2 after each instruction (opcode + operand)
 *
 * Operand Types:
 * - Literal: value is the operand itself (0-7)
 * - Combo: 0-3 represent literal 0-3, 4=A, 5=B, 6=C, 7=reserved
 *
 * Instructions (8 total):
 * - adv (0): A = A / 2^combo(operand), result truncated
 * - bxl (1): B = B XOR literal(operand)
 * - bst (2): B = combo(operand) mod 8
 * - jnz (3): if A != 0, jump to literal(operand)
 * - bxc (4): B = B XOR C (operand ignored)
 * - out (5): output combo(operand) mod 8
 * - bdv (6): B = A / 2^combo(operand)
 * - cdv (7): C = A / 2^combo(operand)
 *
 * Part 1: Run the program with given initial register values, collect output
 * Part 2: [TODO - Usually involves finding input that produces specific output]
 *
 * Approach: Build a simple VM/interpreter that executes instructions step by step
 */

#include <string>
#include <vector>
#include <cstdint>

namespace aoc::day17
{
    // ============================================================================
    // CUSTOM DATA TYPES
    // ============================================================================

    /**
     * @brief Opcode enum for the 8 instructions.
     *
     * Each opcode identifies a specific instruction type.
     */
    enum class Opcode
    {
        Adv = 0, // Division into A
        Bxl = 1, // XOR into B
        Bst = 2, // Modulo 8 into B
        Jnz = 3, // Jump if A != 0
        Bxc = 4, // XOR B and C into B
        Out = 5, // Output value
        Bdv = 6, // Division into B
        Cdv = 7 // Division into C
    };

    /**
     * @brief Operand type discriminator.
     *
     * Instructions specify whether their operand is literal or combo.
     */
    enum class OperandType
    {
        Literal,
        Combo
    };

    /**
     * @brief Computer state containing registers and instruction pointer.
     *
     * HINT: Registers can hold large integers, use int64_t.
     */
    struct ComputerState
    {
        int64_t A;
        int64_t B;
        int64_t C;
        size_t instructionPointer;


        // TODO: Add constructor or factory method for easy initialization
        ComputerState(int64_t a, int64_t b, int64_t c, size_t instruction_pointer)
            : A(a),
              B(b),
              C(c),
              instructionPointer(instruction_pointer)
        {
        }
        ComputerState() = default;
    };

    /**
     * @brief Parsed program representation.
     *
     * HINT: Store as vector of integers (0-7).
     */
    struct Program
    {
        std::vector<int> instructions;

        // TODO: Add method to check if instruction pointer is within bounds
        [[nodiscard]] bool isInBounds(size_t index) const
        {
            return index + 1 < instructions.size();
        }
    };

    /**
     * @brief Computer class that executes the program.
     *
     * RESPONSIBILITIES:
     *   - Store program and current state
     *   - Resolve combo operands
     *   - Execute individual instructions
     *   - Run until halt
     *   - Collect output values
     */
    class Computer
    {
    public:
        // TODO: Add member variables:
        //   - Program program_
        //   - ComputerState state_
        //   - std::vector<int> output_
        Program program_;
        ComputerState state_;
        std::vector<int> output_;

        /**
         * @brief Initialize computer with program and register values.
         */
        Computer(const Program& program, int64_t A, int64_t B, int64_t C);

        /**
         * @brief Resolve a combo operand to its actual value.
         *
         * HINTS:
         *   - 0-3: return the value directly
         *   - 4: return register A
         *   - 5: return register B
         *   - 6: return register C
         *   - 7: reserved (should not occur)
         */
        int64_t resolveCombo(int operand) const;

        /**
         * @brief Execute a single instruction.
         *
         * HINTS:
         *   - Read opcode and operand from current instruction pointer
         *   - Perform the operation based on opcode
         *   - Update instruction pointer (usually +2, or jump target for jnz)
         *   - For 'out', store the output value
         */
        void executeInstruction();

        /**
         * @brief Check if the computer has halted.
         *
         * HINT: Halted when instruction pointer is past the end of the program.
         */
        bool isHalted() const;

        /**
         * @brief Run the program until it halts.
         *
         * HINT: Loop executeInstruction() until isHalted() returns true.
         */
        void run();

        /**
         * @brief Get the collected output values.
         */
        const std::vector<int>& getOutput() const;

        /**
         * @brief Get the current state (for debugging).
         */
        ComputerState getState() const;
    };

    // ============================================================================
    // PARSING
    // ============================================================================

    /**
     * @brief Parse the puzzle input into program and initial register values.
     *
     * INPUT FORMAT:
     *   Register A: <number>
     *   Register B: <number>
     *   Register C: <number>
     *
     *   Program: <comma-separated numbers>
     *
     * HINTS:
     *   - Parse lines to extract register values
     *   - Parse comma-separated program string into vector of ints
     *   - Return as a struct or tuple
     */
    struct ParsedInput
    {
        int64_t A;
        int64_t B;
        int64_t C;
        std::vector<int> program;
    };

    ParsedInput parseInput(const std::vector<std::string>& input);

    // ============================================================================
    // SOLVER
    // ============================================================================

    /**
     * @brief Run the program and return the output as comma-separated string.
     *
     * ALGORITHM OVERVIEW:
     *
     *   1. Parse input to get initial registers and program
     *   2. Create Computer with parsed values
     *   3. Run the computer until halt
     *   4. Join output values with commas
     *   5. Return as string
     */
    std::string runProgram(const std::vector<std::string>& input);

    /**
     * @brief Solves part 1 of day 17's puzzle
     * @param input Vector of strings representing the puzzle input
     * @return Comma-separated output values produced by the program
     */
    std::string solve_part1(const std::vector<std::string>& input);

    /**
     * @brief Solves part 2 of day 17's puzzle
     * @param input Vector of strings representing the puzzle input
     * @return String representation of the solution
     *
     * NOTE: Part 2 typically involves finding an input value (for register A)
     * that causes the program to output a specific sequence (often the program
     * itself). This may require:
     *   - Understanding the program's behavior
     *   - Working backwards from desired output
     *   - Bit manipulation insights
     */
    std::string solve_part2(const std::vector<std::string>& input);
} // namespace aoc::day17
