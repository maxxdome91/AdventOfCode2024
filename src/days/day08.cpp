/**
 * @file day08.cpp
 * @brief Implementation of Day 8: Resonant Collinearity
 *
 * See day08.hpp for detailed puzzle description and algorithmic strategy.
 */

#include "days/day08.hpp"

#include <set>
#include <string>
#include <unordered_map>
#include <vector>
#include <ranges>
#include <cctype>

namespace aoc::day08
{
    // ============================================================================
    // TYPES AND CONSTANTS
    // ============================================================================

    /**
     * @brief Represents a 2D position on the grid
     *
     * HINT: This struct needs operator< for use with std::set
     * Consider also implementing operator== for completeness
     */
    struct Position
    {
        int x;
        int y;

        bool operator<(const Position& other) const
        {
            if (x == other.x) return y < other.y;
            return x < other.x;
        }

        bool operator==(const Position& other) const
        {
            return x == other.x && y == other.y;
        }
    };

    // ============================================================================
    // HELPER FUNCTIONS
    // ============================================================================

    /**
     * @brief Check if a position is within the grid boundaries
     * @param x X coordinate to check
     * @param y Y coordinate to check
     * @param width Grid width
     * @param height Grid height
     * @return true if position is within bounds
     *
     * HINT: Remember that valid coordinates are 0 <= x < width and 0 <= y < height
     */
    [[nodiscard]] bool is_in_bounds(const int x, const int y, const int width, const int height)
    {
        return x >= 0 && x < width && y >= 0 && y < height;
    }

    /**
     * @brief Parse the grid and extract all antenna positions grouped by frequency
     * @param grid The input grid as vector of strings
     * @return Map from frequency character to vector of antenna positions
     *
     * HINT: Iterate through each cell, if it's alphanumeric (not '.'), add to map
     * HINT: Use std::map<char, std::vector<Position>> or std::unordered_map
     * HINT: isalnum() from <cctype> can help identify antenna characters
     */
    [[nodiscard]] std::unordered_map<char, std::vector<Position>> parse_antennas(
        const std::vector<std::string>& grid)
    {
        std::unordered_map<char, std::vector<Position>> antennas{};
        for (auto [i, line] : std::views::enumerate(grid))
        {
            for (auto [j, c] : std::views::enumerate(line))
            {
                if (isalnum(c))
                {
                    antennas[c].push_back(Position{static_cast<int>(j), static_cast<int>(i)});
                }
            }
        }
        return antennas;
    }

    /**
     * @brief Calculate antinode positions for a pair of antennas (Part 1)
     * @param a First antenna position
     * @param b Second antenna position
     * @param width Grid width for bounds checking
     * @param height Grid height for bounds checking
     * @return Vector of valid antinode positions (0, 1, or 2 positions)
     *
     * HINT: Calculate the delta vector: dx = b.x - a.x, dy = b.y - a.y
     * HINT: Antinode 1 is at (a.x - dx, a.y - dy) - opposite direction from a
     * HINT: Antinode 2 is at (b.x + dx, b.y + dy) - same direction past b
     * HINT: Only include positions that are within bounds
     */
    [[nodiscard]] std::vector<Position> calculate_antinodes_part1(
        const Position& a, const Position& b, const int width, const int height)
    {
        const auto dx = b.x - a.x;
        const auto dy = b.y - a.y;
        const auto ax = a.x - dx;
        const auto ay = a.y - dy;
        const auto bx = b.x + dx;
        const auto by = b.y + dy;
        std::vector<Position> antinodes{{ax, ay}, {bx, by}};
        std::erase_if(antinodes, [&](const auto& p)
        {
            return !is_in_bounds(p.x, p.y, width, height);
        });
        return antinodes;
    }

    /**
     * @brief Calculate all antinode positions on the line through two antennas (Part 2)
     * @param a First antenna position
     * @param b Second antenna position
     * @param width Grid width for bounds checking
     * @param height Grid height for bounds checking
     * @return Vector of all valid antinode positions on the line
     *
     * HINT: Calculate the delta vector: dx = b.x - a.x, dy = b.y - a.y
     * HINT: Start from position a and go in direction -delta until out of bounds
     * HINT: Start from position b and go in direction +delta until out of bounds
     * HINT: Use a while loop to extend the line in both directions
     * HINT: All positions on the line (including a and b) are antinodes
     */
    [[nodiscard]] std::vector<Position> calculate_antinodes_part2(
        const Position& a, const Position& b, const int width, const int height)
    {
        std::vector<Position> antinodes{};
        antinodes.push_back(a);
        antinodes.push_back(b);

        const auto dx = b.x - a.x;
        const auto dy = b.y - a.y;

        // Extend in negative direction from a
        Position position{a.x - dx, a.y - dy};
        while (is_in_bounds(position.x, position.y, width, height))
        {
            antinodes.push_back(position);
            position.x -= dx;
            position.y -= dy;
        }
        // Extend in positive direction from b
        position = {b.x + dx, b.y + dy};
        while (is_in_bounds(position.x, position.y, width, height))
        {
            antinodes.push_back(position);
            position.x += dx;
            position.y += dy;
        }

        return antinodes;
    }

    // ============================================================================
    // PART 1 IMPLEMENTATION
    // ============================================================================

    std::string solve_part1(const std::vector<std::string>& input)
    {
        // TODO: Implement Part 1 solution
        //
        // Algorithm outline:
        // 1. Get grid dimensions (width, height)
        // 2. Parse antennas into frequency groups
        // 3. Create an empty set for unique antinode positions
        // 4. For each frequency with 2+ antennas:
        //    a. For each unique pair of antennas (i, j where j > i):
        //       - Calculate antinodes using calculate_antinodes_part1()
        //       - Add valid antinodes to the set
        // 5. Return the size of the antinode set as a string
        //
        // HINT: Use nested loops for pair generation:
        //   for (size_t i = 0; i < positions.size(); ++i)
        //     for (size_t j = i + 1; j < positions.size(); ++j)

        const int width = static_cast<int>(input.size());
        const int height = static_cast<int>(input[0].size());
        auto groups = parse_antennas(input);
        std::set<Position> unique_antennas;
        for (auto position : groups | std::views::values)
        {
            if (position.size() > 1)
            {
                for (size_t i = 0; i < position.size() - 1; ++i)
                {
                    for (size_t j = i + 1; j < position.size(); ++j)
                    {
                        auto antinodes = calculate_antinodes_part1(position[i], position[j], width, height);
                        unique_antennas.insert_range(antinodes);
                    }
                }
            }
        }

        return std::to_string(unique_antennas.size());
    }

    // ============================================================================
    // PART 2 IMPLEMENTATION
    // ============================================================================

    std::string solve_part2(const std::vector<std::string>& input)
    {
        // TODO: Implement Part 2 solution
        //
        // Algorithm outline:
        // 1. Get grid dimensions (width, height)
        // 2. Parse antennas into frequency groups
        // 3. Create an empty set for unique antinode positions
        // 4. For each frequency with 2+ antennas:
        //    a. For each unique pair of antennas (i, j where j > i):
        //       - Calculate all line positions using calculate_antinodes_part2()
        //       - Add all valid positions to the set
        // 5. Return the size of the antinode set as a string
        //
        // HINT: The algorithm structure is similar to Part 1
        // HINT: The difference is in how antinodes are calculated (all line positions)
        // HINT: Antennas themselves will be included as antinodes

        const int width = static_cast<int>(input.size());
        const int height = static_cast<int>(input[0].size());
        auto groups = parse_antennas(input);
        std::set<Position> unique_antennas;
        for (auto position : groups | std::views::values)
        {
            if (position.size() > 1)
            {
                for (size_t i = 0; i < position.size() - 1; ++i)
                {
                    for (size_t j = i + 1; j < position.size(); ++j)
                    {
                        auto antinodes = calculate_antinodes_part2(position[i], position[j], width, height);
                        unique_antennas.insert_range(antinodes);
                    }
                }
            }
        }

        return std::to_string(unique_antennas.size());
    }
} // namespace aoc::day08
