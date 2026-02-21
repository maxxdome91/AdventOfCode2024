/**
 * @file day05.cpp
 * @brief Implementation of Day 5: Print Queue
 * 
 * This solution implements a topological sorting algorithm to handle page ordering constraints.
 * The problem involves validating and correcting sequences based on ordering rules of the form X|Y,
 * where X must come before Y in the sequence.
 */

#include "days/day05.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <algorithm>
#include <queue>
#include <ranges>

namespace aoc::day05 {
    /**
     * @brief Parse the input into ordering rules and update sequences
     * @param input Vector of strings representing the puzzle input
     * @return Pair containing: first = rules map, second = update sequences
     *
     * The input consists of two sections separated by an empty line:
     * - Section 1: Ordering rules in format "X|Y" where X must come before Y
     * - Section 2: Page update sequences in format "page1,page2,page3,..."
     */
    std::pair<std::unordered_map<int, std::unordered_set<int> >, std::vector<std::vector<int> > >
    parse_input(const std::vector<std::string> &input) {
        size_t separator_pos = 0;
        for (size_t i = 0; i < input.size(); ++i) {
            if (input[i].empty()) {
                separator_pos = i;
                break;
            }
        }

        std::unordered_map<int, std::unordered_set<int> > rules;
        for (size_t i = 0; i < separator_pos; ++i) {
            const auto pos = input[i].find('|');
            int x = std::stoi(input[i].substr(0, pos));
            int y = std::stoi(input[i].substr(pos + 1));
            rules[x].insert(y);
        }

        std::vector<std::vector<int> > updates;
        for (size_t i = separator_pos + 1; i < input.size(); ++i) {
            std::vector<int> sequence;
            std::stringstream ss(input[i]);
            std::string item;
            while (std::getline(ss, item, ',')) {
                sequence.push_back(std::stoi(item));
            }
            updates.push_back(sequence);
        }

        return {rules, updates};
    }


    /**
     * @brief Check if a sequence respects the ordering rules
     * @param sequence Vector of page numbers in order
     * @param rules Map of ordering constraints (page -> set of pages that must come after)
     * @return True if sequence is valid, false otherwise
     *
     * For each page in the sequence, this function checks if any pages that must come after it
     * according to the rules appear before it in the sequence. Only considers rules that involve
     * pages actually present in the current sequence.
     */
    bool is_valid_sequence(const std::vector<int> &sequence,
                           const std::unordered_map<int, std::unordered_set<int> > &rules) {
        std::unordered_set<int> pages_in_sequence(sequence.begin(), sequence.end());

        for (size_t i = 0; i < sequence.size(); ++i) {
            if (int current_page = sequence[i]; rules.contains(current_page)) {
                for (const auto &must_come_after = rules.at(current_page); int page: must_come_after) {
                    if (auto found_pos = std::ranges::find(sequence, page);
                        pages_in_sequence.contains(page) &&
                        found_pos != sequence.end() &&
                        found_pos < sequence.begin() + static_cast<long>(i)) {
                        return false;
                    }
                }
            }
        }

        return true;
    }


    /**
     * @brief Sort a sequence according to the ordering rules using Kahn's algorithm for topological sorting
     * @param sequence Vector of page numbers to sort
     * @param rules Map of ordering constraints
     * @return Sorted vector respecting all rules
     *
     * Implements Kahn's algorithm for topological sorting:
     * 1. Build a subgraph containing only pages from the current sequence and relevant rules
     * 2. Calculate in-degrees for each node (number of incoming edges)
     * 3. Process nodes with in-degree 0 (no dependencies) first
     * 4. For each processed node, reduce in-degree of its neighbors
     * 5. Add newly 0-in-degree nodes to the processing queue
     *
     * This ensures that all ordering constraints are satisfied in the final sequence.
     */
    std::vector<int> sort_sequence_according_to_rules(
        const std::vector<int> &sequence,
        const std::unordered_map<int, std::unordered_set<int> > &rules) {
        // Build adjacency list for pages in a sequence based on rules
        // Only include edges between pages that are both present in this sequence
        std::unordered_map<int, std::unordered_set<int> > adjacency_list;
        for (int page: sequence) {
            if (rules.contains(page)) {
                for (int next_page: rules.at(page)) {
                    if (std::ranges::find(sequence, next_page) != sequence.end()) {
                        adjacency_list[page].insert(next_page);
                    }
                }
            }
        }

        // Calculate in-degrees for each page in the sequence
        // In degree represents the number of pages that must come before this page
        std::unordered_map<int, int> in_degree;
        for (int page: sequence) {
            in_degree[page] = 0;
        }
        for (const auto &neighbors: adjacency_list | std::views::values) {
            for (int neighbor: neighbors) {
                in_degree[neighbor]++;
            }
        }

        // Initialize queue with pages having 0 in-degrees (no dependencies)
        std::queue<int> queue;
        for (int page: sequence) {
            if (in_degree[page] == 0) {
                queue.push(page);
            }
        }

        // Perform topological sort using Kahn's algorithm
        std::vector<int> sorted_sequence;
        while (!queue.empty()) {
            int current_page = queue.front();
            queue.pop();
            sorted_sequence.push_back(current_page);

            // Process all neighbors of the current page
            for (int neighbor: adjacency_list[current_page]) {
                in_degree[neighbor]--;
                // If the neighbor now has 0 in-degree, add it to the queue
                if (in_degree[neighbor] == 0) {
                    queue.push(neighbor);
                }
            }
        }

        return sorted_sequence;
    }


    /**
     * @brief Get the middle element of a sequence
     * @param sequence Vector of integers (assumed to have an odd length)
     * @return Middle element
     */
    int get_middle_element(const std::vector<int> &sequence) {
        return sequence[sequence.size() / 2];
    }

    /**
     * @brief Solve Part 1: Sum middle elements of valid sequences
     * @param input Vector of strings representing the puzzle input
     * @return String representation of the solution
     *
     * Part 1 requires identifying sequences that already satisfy all ordering rules
     * and summing their middle elements.
     */
    std::string solve_part1(const std::vector<std::string> &input) {
        auto [rules, updates] = parse_input(input);

        std::vector<std::vector<int> > valid_updates;
        for (const auto &update: updates) {
            if (is_valid_sequence(update, rules)) {
                valid_updates.push_back(update);
            }
        }

        int total = 0;
        for (const auto &update: valid_updates) {
            total += get_middle_element(update);
        }

        return std::to_string(total);
    }

    /**
     * @brief Solve Part 2: Sum middle elements of corrected invalid sequences
     * @param input Vector of strings representing the puzzle input
     * @return String representation of the solution
     *
     * Part 2 requires finding sequences that violate ordering rules, applying topological
     * sorting to correct them, and summing the middle elements of the corrected sequences.
     */
    std::string solve_part2(const std::vector<std::string> &input) {
        auto [rules, updates] = parse_input(input);

        std::vector<std::vector<int> > fixed_updates;
        for (const auto &update: updates) {
            if (!is_valid_sequence(update, rules)) {
                fixed_updates.push_back(sort_sequence_according_to_rules(update, rules));
            }
        }

        int total = 0;
        for (const auto &update: fixed_updates) {
            total += get_middle_element(update);
        }

        return std::to_string(total);
    }
} // namespace aoc::day05
