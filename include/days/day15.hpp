#pragma once

/**
 * @file day15.hpp
 * @brief Day 15: Warehouse Woes - Robot Box Pushing Simulation
 *
 * A robot navigates a warehouse grid, pushing boxes. Input has two sections:
 * the initial map (walls #, robot @, boxes O, empty .) and movement instructions (< > ^ v).
 * Part 1: Push single-width boxes, calculate sum of GPS coordinates (100*y + x) for all boxes.
 * Part 2: Map is doubled horizontally; boxes become 2-wide ([]), requiring chain-push logic.
 */

#include <optional>
#include <string>
#include <vector>

namespace aoc::day15
{
    /**
     * @brief Represents a 2D position in the warehouse grid
     */
    struct Position
    {
        int x;
        int y;

        auto operator<=>(const Position&) const = default;
        Position operator+(const Position& delta) const;
        Position& operator+=(const Position& delta);
    };

    /**
     * @brief Represents a movement direction
     */
    enum class Direction { Up, Down, Left, Right };

    /**
     * @brief Parsed warehouse state containing the grid and robot position
     */
    struct Warehouse
    {
        std::vector<std::string> grid; ///< The warehouse layout
        Position robot_pos; ///< Current robot position
        int height; ///< Grid height
        int width; ///< Grid width
    };

    /**
     * @brief Parses the input into a warehouse state and instruction sequence
     * @param input Raw puzzle input (map + blank line + instructions)
     * @return Pair of (Warehouse, instruction string)
     */
    [[nodiscard]] std::pair<Warehouse, std::string> parse_input(const std::vector<std::string>& input);

    /**
     * @brief Converts a character direction to Direction enum
     * @param c Direction character (< > ^ v)
     * @return Direction enum value, or std::nullopt if invalid
     */
    [[nodiscard]] std::optional<Direction> char_to_direction(char c);

    /**
     * @brief Gets the position delta for a given direction
     * @param dir The direction
     * @return Position delta to add for movement
     */
    [[nodiscard]] Position get_delta(Direction dir);

    /**
     * @brief Attempts to move the robot and push boxes if necessary (Part 1)
     * @param warehouse The warehouse state (modified in place)
     * @param dir The direction to move
     * @return true if the move was successful, false if blocked
     */
    bool try_move_part1(Warehouse& warehouse, Direction dir);

    /**
     * @brief Attempts to move the robot and push 2-wide boxes (Part 2)
     * @param warehouse The warehouse state (modified in place)
     * @param dir The direction to move
     * @return true if the move was successful, false if blocked
     */
    bool try_move_part2(Warehouse& warehouse, Direction dir);

    /**
     * @brief Calculates the GPS sum of all boxes (100*y + x for each box)
     * @param warehouse The warehouse state
     * @return GPS coordinate sum
     */
    [[nodiscard]] long long calculate_gps_sum(const Warehouse& warehouse);

    /**
     * @brief Transforms a Part 1 warehouse to Part 2 (double width, boxes become [])
     * @param warehouse The original warehouse
     * @return Transformed warehouse for Part 2
     */
    [[nodiscard]] Warehouse expand_warehouse(const Warehouse& warehouse);

    /**
     * @brief Solves part 1 of day 15's puzzle
     * @param input Vector of strings representing the puzzle input
     * @return String representation of the GPS sum solution
     */
    std::string solve_part1(const std::vector<std::string>& input);

    /**
     * @brief Solves part 2 of day 15's puzzle
     * @param input Vector of strings representing the puzzle input
     * @return String representation of the GPS sum solution
     */
    std::string solve_part2(const std::vector<std::string>& input);
} // namespace aoc::day15
