/**
 * @file day15.cpp
 * @brief Day 15: Warehouse Woes - Robot Box Pushing Simulation
 *
 * C++ Toolbox:
 * - std::vector<std::string> for the grid (mutable, row-based access)
 * - std::optional<Direction> for safe direction parsing
 * - std::pair<Warehouse, std::string> for separating map from instructions
 * - std::set<Position> for tracking boxes to move (Part 2 chain detection)
 */

#include "days/day15.hpp"

#include <algorithm>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace aoc::day15
{
    // Position implementation
    Position Position::operator+(const Position& delta) const
    {
        return {x + delta.x, y + delta.y};
    }

    Position& Position::operator+=(const Position& delta)
    {
        x += delta.x;
        y += delta.y;
        return *this;
    }

    // Direction character mapping
    std::optional<Direction> char_to_direction(char c)
    {
        switch (c)
        {
        case '^': return Direction::Up;
        case 'v': return Direction::Down;
        case '<': return Direction::Left;
        case '>': return Direction::Right;
        default: return std::nullopt;
        }
    }

    Position get_delta(Direction dir)
    {
        // Up: {0, -1}, Down: {0, 1}, Left: {-1, 0}, Right: {1, 0}
        switch (dir)
        {
        case Direction::Up:
            return Position{0, -1};
        case Direction::Down:
            return Position{0, 1};
        case Direction::Left:
            return Position{-1, 0};
        case Direction::Right:
            return Position{1, 0};
        }
        return {-1, -1};
    }

    std::pair<Warehouse, std::string> parse_input(const std::vector<std::string>& input)
    {
        if (input.empty())
            throw std::runtime_error("Empty input");

        // Find the blank line separating map from instructions
        auto it = std::ranges::find(input, "");

        Warehouse warehouse{};
        warehouse.grid = std::vector<std::string>(input.begin(), it);

        if (warehouse.grid.empty())
            throw std::runtime_error("Map section is empty");

        warehouse.width = static_cast<int>(warehouse.grid[0].size());
        warehouse.height = static_cast<int>(warehouse.grid.size());

        bool found_robot = false;
        for (size_t y = 0; y < warehouse.grid.size(); ++y)
        {
            const auto& row = warehouse.grid[y];
            for (size_t x = 0; x < row.size(); ++x)
            {
                if (row[x] == '@')
                {
                    warehouse.robot_pos = Position{static_cast<int>(x), static_cast<int>(y)};
                    found_robot = true;
                    break;
                }
            }
            if (found_robot) break;
        }

        if (!found_robot)
            throw std::runtime_error("Robot (@) not found in warehouse map");

        std::string instructions;
        if (it != input.end())
        {
            for (auto it2 = std::next(it); it2 != input.end(); ++it2)
            {
                instructions += *it2;
            }
        }

        return {warehouse, instructions};
    }

    bool try_move_part1(Warehouse& warehouse, Direction dir)
    {
        const auto delta = get_delta(dir);
        const auto target = warehouse.robot_pos + delta;

        // 1. Check if the target cell is a wall
        if (warehouse.grid[target.y][target.x] == '#') return false;

        // 2. If it's a box, find if there's an empty space to push the chain into
        if (warehouse.grid[target.y][target.x] == 'O')
        {
            auto scan = target + delta;
            while (warehouse.grid[scan.y][scan.x] == 'O')
            {
                scan += delta;
            }

            // If the chain ends at a wall, we can't push
            if (warehouse.grid[scan.y][scan.x] == '#') return false;

            // Otherwise, we found a '.', so we push the entire chain:
            // In Part 1, this is equivalent to moving the first box to the empty spot.
            warehouse.grid[scan.y][scan.x] = 'O';
        }

        // 3. Move the robot in the grid
        warehouse.grid[warehouse.robot_pos.y][warehouse.robot_pos.x] = '.';
        warehouse.robot_pos = target;
        warehouse.grid[warehouse.robot_pos.y][warehouse.robot_pos.x] = '@';

        return true;
    }

    bool try_move_part2(Warehouse& warehouse, Direction dir)
    {
        const auto delta = get_delta(dir);
        const auto target = warehouse.robot_pos + delta;

        // --- Horizontal Movement ---
        if (dir == Direction::Left || dir == Direction::Right)
        {
            Position scan = target;
            while (warehouse.grid[scan.y][scan.x] == '[' || warehouse.grid[scan.y][scan.x] == ']')
            {
                scan += delta;
            }

            if (warehouse.grid[scan.y][scan.x] == '#') return false;

            if (warehouse.grid[scan.y][scan.x] == '.')
            {
                warehouse.grid[scan.y].erase(scan.x, 1);
                warehouse.grid[scan.y].insert(warehouse.robot_pos.x, 1, '.');
                warehouse.robot_pos += delta;
                return true;
            }
        }

        // --- Vertical Movement ---
        std::queue<Position> q;
        std::set<Position> seen;
        std::vector<Position> to_move;

        q.push(target);

        while (!q.empty())
        {
            auto current = q.front();
            q.pop();

            if (seen.contains(current)) continue;
            seen.insert(current);

            char tile = warehouse.grid[current.y][current.x];

            if (tile == '#') return false; // Blocked!

            if (tile == '[' || tile == ']')
            {
                to_move.push_back(current);
                q.push(current + delta);
                if (tile == '[') q.push(Position{current.x + 1, current.y});
                else q.push(Position{current.x - 1, current.y});
            }
        }

        // If we get here, the move is possible!
        // Store box characters and clear their old positions
        std::vector<std::pair<Position, char>> box_states;
        for (const auto& pos : to_move)
        {
            box_states.push_back({pos, warehouse.grid[pos.y][pos.x]});
            warehouse.grid[pos.y][pos.x] = '.';
        }

        // Place boxes in their new positions
        for (const auto& [pos, ch] : box_states)
        {
            Position next = pos + delta;
            warehouse.grid[next.y][next.x] = ch;
        }

        // Finally, move the robot
        warehouse.grid[warehouse.robot_pos.y][warehouse.robot_pos.x] = '.';
        warehouse.robot_pos += delta;
        warehouse.grid[warehouse.robot_pos.y][warehouse.robot_pos.x] = '@';

        return true;
    }

    Warehouse expand_warehouse(const Warehouse& warehouse)
    {
        Warehouse result;
        for (const auto& line : warehouse.grid)
        {
            std::string to_add{};
            to_add.reserve(line.size() * 2);
            for (auto col : line)
            {
                switch (col)
                {
                case 'O':
                    to_add.append("[]");
                    break;
                case '@':
                    to_add.append("@.");
                    break;
                default:
                    to_add.append(std::string(2, col));
                    break;
                }
            }
            result.grid.emplace_back(std::move(to_add));
        }

        result.height = warehouse.height;
        result.width = warehouse.width * 2;
        result.robot_pos = Position{warehouse.robot_pos.x * 2, warehouse.robot_pos.y};
        return result;
    }

    long long calculate_gps_sum(const Warehouse& warehouse)
    {
        long long result = 0;
        for (size_t y = 0; y < warehouse.grid.size(); ++y)
        {
            const auto& row = warehouse.grid[y];
            for (size_t x = 0; x < row.size(); ++x)
            {
                char c = row[x];
                if (c == 'O' || c == '[')
                {
                    result += 100 * y + x;
                }
            }
        }
        return result;
    }

    std::string solve_part1(const std::vector<std::string>& input)
    {
        // TODO: Orchestrate Part 1 solution.
        //
        auto [warehouse, instructions] = parse_input(input);
        // 1. {warehouse, instructions} = parse_input(input).
        // 2. For each char in instructions:
        for (char c : instructions)
        {
            if (auto dir = char_to_direction(c))
            {
                try_move_part1(warehouse, dir.value());
            }
        }
        //    - if (dir = char_to_direction(char)) try_move_part1(warehouse, *dir).
        // 3. return std::to_string(calculate_gps_sum(warehouse)).
        return std::to_string(calculate_gps_sum(warehouse));
    }

    std::string solve_part2(const std::vector<std::string>& input)
    {
        // TODO: Orchestrate Part 2 solution.
        // 
        // 1. {raw_warehouse, instructions} = parse_input(input).
        auto [raw_warehouse, instructions] = parse_input(input);
        // 2. warehouse = expand_warehouse(raw_warehouse).
        auto warehouse = expand_warehouse(raw_warehouse);
        // 3. For each char in instructions:
        for (char c : instructions)
        {
            if (auto dir = char_to_direction(c))
            {
                try_move_part2(warehouse, dir.value());
            }
        }
        //    - if (dir = char_to_direction(char)) try_move_part2(warehouse, *dir).
        // 4. return std::to_string(calculate_gps_sum(warehouse)).
        return std::to_string(calculate_gps_sum(warehouse));
    }
} // namespace aoc::day15
