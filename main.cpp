/**
 * @file main.cpp
 * @brief Main entry point for Advent of Code 2024 solutions
 *
 * This program runs solutions for the Advent of Code 2024 puzzles.
 * It supports running individual days/parts or all days at once.
 *
 * Usage:
 *   ./aoc2024              - Run all days
 *   ./aoc2024 <day>        - Run both parts of a specific day
 *   ./aoc2024 <day> <part> - Run a specific part of a specific day
 */

#include <chrono>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "utils/input_handler.hpp"

// Include all day headers
#include "days/day01.hpp"
#include "days/day02.hpp"
#include "days/day03.hpp"
#include "days/day04.hpp"
#include "days/day05.hpp"
#include "days/day06.hpp"
#include "days/day07.hpp"
#include "days/day08.hpp"
#include "days/day09.hpp"
#include "days/day10.hpp"
#include "days/day11.hpp"
#include "days/day12.hpp"
#include "days/day13.hpp"
#include "days/day14.hpp"
#include "days/day15.hpp"
#include "days/day16.hpp"
#include "days/day17.hpp"
#include "days/day18.hpp"
#include "days/day19.hpp"
#include "days/day20.hpp"
#include "days/day21.hpp"
#include "days/day22.hpp"
#include "days/day23.hpp"
#include "days/day24.hpp"
#include "days/day25.hpp"

/// Type alias for solution functions
using SolutionFunc = std::function<std::string(const std::vector<std::string>&)>;

/**
 * @brief Constructs the input file path for a given day
 * @param day Day number (1-25)
 * @return Path to the input file
 */
std::string get_input_path(int day) {
    return "inputs/day" + std::string(day < 10 ? "0" : "") + std::to_string(day) + ".txt";
}

/**
 * @brief Prints usage information
 * @param program_name Name of the executable
 */
void print_usage(const char* program_name) {
    std::cout << "Usage: " << program_name << " <day_number> [part_number]" << std::endl;
    std::cout << "  day_number: 1-25 (which day to run)" << std::endl;
    std::cout << "  part_number: 1 or 2 (which part to run, default: both)" << std::endl;
    std::cout << std::endl;
    std::cout << "Examples:" << std::endl;
    std::cout << "  " << program_name << " 1      # Run both parts of day 1" << std::endl;
    std::cout << "  " << program_name << " 1 1    # Run only part 1 of day 1" << std::endl;
    std::cout << "  " << program_name << " 1 2    # Run only part 2 of day 1" << std::endl;
    std::cout << std::endl;
}

/**
 * @brief Runs all days and prints results with timing
 * @param day_solutions Map of day numbers to solution function pairs
 */
void run_all_days(const std::map<int, std::pair<SolutionFunc, SolutionFunc>>& day_solutions) {
    std::cout << "Running all days:" << std::endl;

    for (int day = 1; day <= 25; ++day) {
        std::cout << "Day " << day << ": ";

        try {
            const std::string input_path = get_input_path(day);
            const auto input = aoc::utils::read_input(input_path);

            // Run and time part 1
            const auto start = std::chrono::high_resolution_clock::now();
            const auto part1_result = day_solutions.at(day).first(input);
            const auto mid = std::chrono::high_resolution_clock::now();
            const auto part1_time = std::chrono::duration_cast<std::chrono::microseconds>(mid - start);

            std::cout << "Part 1: " << part1_result << " (" << part1_time.count() << "μs)";

            // Run and time part 2 if available
            if (day_solutions.at(day).second) {
                const auto part2_result = day_solutions.at(day).second(input);
                const auto end = std::chrono::high_resolution_clock::now();
                const auto part2_time = std::chrono::duration_cast<std::chrono::microseconds>(end - mid);
                std::cout << " | Part 2: " << part2_result << " (" << part2_time.count() << "μs)";
            }

            std::cout << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
}

/**
 * @brief Runs a specific day and prints results with timing
 * @param day Day number to run
 * @param part Part number (0 = both, 1 = part 1 only, 2 = part 2 only)
 * @param day_solutions Map of day numbers to solution function pairs
 * @return Exit code (0 = success, 1 = error)
 */
int run_specific_day(int day, int part,
                     const std::map<int, std::pair<SolutionFunc, SolutionFunc>>& day_solutions) {
    const std::string input_path = get_input_path(day);

    try {
        const auto input = aoc::utils::read_input(input_path);

        std::cout << "Advent of Code 2024 - Day " << day << std::endl;
        std::cout << "=========================================" << std::endl;

        // Run part 1 if requested
        if (part == 0 || part == 1) {
            const auto start = std::chrono::high_resolution_clock::now();
            const auto result = day_solutions.at(day).first(input);
            const auto end = std::chrono::high_resolution_clock::now();
            const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            std::cout << "Part 1: " << result << " (" << duration.count() << " μs)" << std::endl;
        }

        // Run part 2 if requested and available
        if (part == 0 || part == 2) {
            if (day_solutions.at(day).second) {
                const auto start = std::chrono::high_resolution_clock::now();
                const auto result = day_solutions.at(day).second(input);
                const auto end = std::chrono::high_resolution_clock::now();
                const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                std::cout << "Part 2: " << result << " (" << duration.count() << " μs)" << std::endl;
            } else if (part == 2) {
                std::cout << "Part 2: Not available for this day" << std::endl;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error reading input file '" << input_path << "': " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

int main(int argc, char* argv[]) {
    // Map day numbers to their solution functions
    // Note: Days with only one part have nullptr for part 2
    const std::map<int, std::pair<SolutionFunc, SolutionFunc>> day_solutions = {
        {1,  {aoc::day01::solve_part1, aoc::day01::solve_part2}},
        {2,  {aoc::day02::solve_part1, aoc::day02::solve_part2}},
        {3,  {aoc::day03::solve_part1, aoc::day03::solve_part2}},
        {4,  {aoc::day04::solve_part1, aoc::day04::solve_part2}},
        {5,  {aoc::day05::solve_part1, aoc::day05::solve_part2}},
        {6,  {aoc::day06::solve_part1, aoc::day06::solve_part2}},
        {7,  {aoc::day07::solve_part1, aoc::day07::solve_part2}},
        {8,  {aoc::day08::solve_part1, aoc::day08::solve_part2}},
        {9,  {aoc::day09::solve_part1, aoc::day09::solve_part2}},
        {10, {aoc::day10::solve_part1, aoc::day10::solve_part2}},
        {11, {aoc::day11::solve_part1, aoc::day11::solve_part2}},
        {12, {aoc::day12::solve_part1, aoc::day12::solve_part2}},
        {13, {aoc::day13::solve_part1, aoc::day13::solve_part2}},
        {14, {aoc::day14::solve_part1, aoc::day14::solve_part2}},
        {15, {aoc::day15::solve_part1, aoc::day15::solve_part2}},
        {16, {aoc::day16::solve_part1, aoc::day16::solve_part2}},
        {17, {aoc::day17::solve_part1, aoc::day17::solve_part2}},
        {18, {aoc::day18::solve_part1, aoc::day18::solve_part2}},
        {19, {aoc::day19::solve_part1, aoc::day19::solve_part2}},
        {20, {aoc::day20::solve_part1, aoc::day20::solve_part2}},
        {21, {aoc::day21::solve_part1, aoc::day21::solve_part2}},
        {22, {aoc::day22::solve_part1, aoc::day22::solve_part2}},
        {23, {aoc::day23::solve_part1, aoc::day23::solve_part2}},
        {24, {aoc::day24::solve_part1, aoc::day24::solve_part2}},
        {25, {aoc::day25::solve_part1, aoc::day25::solve_part2}}
    };

    // No arguments: print usage and run all days
    if (argc < 2) {
        print_usage(argv[0]);
        run_all_days(day_solutions);
        return 0;
    }

    // Parse day number
    const int day = std::stoi(argv[1]);
    if (day < 1 || day > 25) {
        std::cerr << "Error: Day must be between 1 and 25" << std::endl;
        return 1;
    }

    // Parse optional part number (0 = both parts)
    int part = 0;
    if (argc >= 3) {
        part = std::stoi(argv[2]);
        if (part != 1 && part != 2) {
            std::cerr << "Error: Part must be 1 or 2" << std::endl;
            return 1;
        }
    }

    return run_specific_day(day, part, day_solutions);
}