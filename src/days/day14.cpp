/**
 * @file day14.cpp
 * @brief Implementation of Day 14: Restroom Redoubt
 *
 * --- Day 14: Restroom Redoubt ---
 * One of the EHQ's North Pole Restrooms is in need of some maintenance.
 * Inside, a large group of robots is roaming the room.
 * Each robot has a position (p) and a velocity (v).
 *
 * The robots are in a 101x103 space. (Example space is 11x7).
 * When a robot would run into a wall, it instead teleports to the other side of the room.
 *
 * After 100 seconds, count the robots in each of the four quadrants.
 * The quadrants are separated by a middle vertical line and a middle horizontal line.
 * Robots on these lines are not counted in any quadrant.
 * Multiply the number of robots in each quadrant together to get the safety factor.
 *
 * --- Part Two ---
 * During the scan, you discover that most of the robots seem to be forming a 
 * picture of a Christmas tree!
 *
 * What is the fewest number of seconds that must elapse for the robots to 
 * display the Christmas tree?
 */

#include "days/day14.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <cstdio>
#include <array>
#include <regex>
#include <limits>

namespace aoc::day14
{
    std::vector<Robot> parse_input(const std::vector<std::string>& input)
    {
        std::vector<Robot> result;
        for (const auto& line : input)
        {
            if (line.empty()) continue;
            Robot r{};
            if (sscanf(line.c_str(), "p=%d,%d v=%d,%d", &r.px, &r.py, &r.vx, &r.vy) == 4)
            {
                result.push_back(r);
            }
        }
        return result;
    }

    std::pair<int, int> simulate_movement(const Robot& robot, int seconds, int width, int height)
    {
        /**
         * HINT: The position at time T is (p + v * T).
         * Because of the "teleportation" (wrapping), use modulo.
         * CRITICAL: In C++, -5 % 103 is -5. To wrap correctly: (val % mod + mod) % mod.
         */
        auto nx = robot.px + robot.vx * seconds;
        auto ny = robot.py + robot.vy * seconds;
        nx = (nx % width + width) % width;
        ny = (ny % height + height) % height;
        return {nx, ny};
    }

    long long calculate_safety_factor(const std::vector<std::pair<int, int>>& positions, int width, int height)
    {
        /**
         * HINT: Use std::array<int, 4> quadrants = {0, 0, 0, 0};
         * Mid-lines: mid_x = width / 2, mid_y = height / 2.
         * Quadrant mapping:
         *   Q0: x < mid_x, y < mid_y
         *   Q1: x > mid_x, y < mid_y
         *   Q2: x < mid_x, y > mid_y
         *   Q3: x > mid_x, y > mid_y
         * Return the product of all 4 counts using 1LL to ensure long long multiplication.
         */
        std::vector<int> quadrants(4, 0);
        const auto mid_x = width / 2;
        const auto mid_y = height / 2;

        for (auto [x, y] : positions)
        {
            if (x < mid_x)
            {
                if (y < mid_y)
                {
                    quadrants[0]++;
                }
                if (y > mid_y)
                {
                    quadrants[2]++;
                }
            }
            if (x > mid_x)
            {
                if (y < mid_y)
                {
                    quadrants[1]++;
                }
                if (y > mid_y)
                {
                    quadrants[3]++;
                }
            }
        }
        return std::ranges::fold_left(quadrants, 1LL, std::multiplies<>());
    }

    std::string solve_part1(const std::vector<std::string>& input)
    {
        const int width = 101;
        const int height = 103;

        // 1. Parse all robots.
        const auto robots = parse_input(input);
        // 2. For each robot, simulate its position at T=100.
        std::vector<std::pair<int, int>> positions{};
        for (auto robot : robots)
        {
            auto position = simulate_movement(robot, 100, width, height);
            positions.push_back(position);
        }
        // 3. Collect all positions and pass to calculate_safety_factor.
        const auto result = calculate_safety_factor(positions, width, height);

        return std::to_string(result);
    }

    std::string solve_part2(const std::vector<std::string>& input)
    {
        const int width = 101;
        const int height = 103;
        const auto robots = parse_input(input);

        long long lowest_sf = std::numeric_limits<long long>::max();
        int best_time = 0;

        for (int t = 1; t <= width * height; ++t)
        {
            std::vector<std::pair<int, int>> positions;
            positions.reserve(robots.size());
            for (const auto& robot : robots)
            {
                positions.push_back(simulate_movement(robot, t, width, height));
            }

            auto sf = calculate_safety_factor(positions, width, height);
            if (sf < lowest_sf)
            {
                lowest_sf = sf;
                best_time = t;
            }
        }

        return std::to_string(best_time);
    }
} // namespace aoc::day14
