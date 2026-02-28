/**
 * @file day13.cpp
 * @brief Implementation of Day 13: Claw Contraption
 */

#include "days/day13.hpp"

#include <string>
#include <vector>
#include <optional>
#include <cstdio>
#include <regex>
#include <ranges>

namespace aoc::day13
{
    struct Machine
    {
        long long ax, ay; // Button A movement
        long long bx, by; // Button B movement
        long long px, py; // Prize location
    };

    /**
     * @brief Parses the input into a list of claw machines.
     *
     * Tip: The input is grouped in blocks of 3 lines separated by an empty line.
     * Use `std::sscanf(line.c_str(), "Button A: X+%lld, Y+%lld", ...)`
     * or regular expressions to extract numbers.
     */
    std::vector<Machine> parse_machines(const std::vector<std::string>& input)
    {
        std::vector<Machine> result;
        const std::regex num_regex(R"(\d+)");
        auto get_nums = [&](const std::string& s)
        {
            std::vector<long long> nums;
            auto begin = std::sregex_iterator(s.begin(), s.end(), num_regex);
            for (auto it = begin; it != std::sregex_iterator(); ++it)
            {
                nums.push_back(std::stoll(it->str()));
            }
            return nums;
        };
        for (auto const& block : input | std::views::chunk(4))
        {
            auto a = get_nums(block[0]);
            auto b = get_nums(block[1]);
            auto p = get_nums(block[2]);

            result.push_back({a[0], a[1], b[0], b[1], p[0], p[1]});
        }
        return result;
    }

    /**
     * @brief Solves for minimum tokens using Cramer's Rule.
     *
     * System of Equations:
     * 1) a * AX + b * BX = PX
     * 2) a * AY + b * BY = PY
     *
     * Cramer's Rule Formulas:
     * - Determinant (D) = (AX * BY) - (AY * BX)
     * - Da = (PX * BY) - (PY * BX)
     * - Db = (AX * PY) - (AY * PX)
     *
     * A solution exists if D != 0, Da%D == 0, and Db%D == 0.
     * Cost = 3*a + b
     */
    std::optional<long long> solve_machine(const Machine& m)
    {
        // TODO: Implement Cramer's Rule with integer division checks
        auto D = (m.ax * m.by) - (m.ay * m.bx);
        auto Da = (m.px * m.by) - (m.py * m.bx);
        auto Db = (m.ax * m.py) - (m.ay * m.px);

        if (D == 0 || Da % D != 0 || Db % D != 0)
        {
            return std::nullopt;
        }

        auto a = Da / D;
        auto b = Db / D;

        if (a < 0 || b < 0)
        {
            return std::nullopt;
        }

        return 3 * a + b;
    }

    std::string solve_part1(const std::vector<std::string>& input)
    {
        long long result = 0;
        // 1. Parse machines
        auto machines = parse_machines(input);
        // 2. Solve each machine
        for (const auto& machine : machines)
        {
            result += solve_machine(machine).value_or(0);
        }
        // 3. Sum costs
        return std::to_string(result);
    }

    /**
     * @brief Part 2: Large Prize Coordinates.
     *
     * Important:
     * - Add 10,000,000,000,000 to both `px` and `py` for each machine.
     * - Use `long long` for all calculations to prevent overflow.
     */
    std::string solve_part2(const std::vector<std::string>& input)
    {
        // 1. Parse machines
        long long result = 0;
        auto machines = parse_machines(input);
        // 2. Apply offset to prize coordinates
        for (auto& machine : machines)
        {
            machine.px += 10000000000000ll;
            machine.py += 10000000000000ll;
            result += solve_machine(machine).value_or(0);
        }
        // 3. Solve and sum
        return std::to_string(result);
    }
} // namespace aoc::day13
