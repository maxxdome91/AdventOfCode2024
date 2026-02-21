# Advent of Code 2024

This project contains solutions for Advent of Code 2024, which consists of 25 days of programming puzzles.

## Project Structure

```
AdventOfCode2024/
├── CMakeLists.txt              # Main build configuration
├── main.cpp                    # Entry point with CLI interface
├── include/                    # Header files
│   ├── utils/                  # Utility headers
│   │   ├── input_handler.hpp
│   │   ├── string_utils.hpp
│   │   └── math_utils.hpp
│   └── days/                   # Day-specific headers (day01-day25)
├── src/                        # Source files
│   ├── utils/                  # Utility implementations
│   │   ├── input_handler.cpp
│   │   ├── string_utils.cpp
│   │   └── math_utils.cpp
│   └── days/                   # Day-specific implementations (day01-day25)
├── inputs/                     # Input files for each day
│   ├── day01.txt
│   ├── day02.txt
│   ...
│   └── day25.txt
├── tests/                      # Unit tests
│   ├── CMakeLists.txt
│   ├── test_main.cpp
│   ├── test_utils.cpp
│   └── test_days.cpp
├── docs/                       # Documentation
│   └── architecture.md
└── README.md                   # This file
```

## Build Instructions

### Prerequisites
- C++23 compatible compiler (GCC 11+, Clang 12+, or MSVC 19.29+)
- CMake 3.20 or higher
- Google Test (for running tests)

### Building the Project

1. Create a build directory:
```bash
mkdir build && cd build
```

2. Configure the project:
```bash
cmake ..
```

3. Build the executable:
```bash
make
```

### Running Solutions

The executable supports several ways to run solutions:

- Run all days:
```bash
./aoc2024
```

- Run a specific day (both parts):
```bash
./aoc2024 1    # Run day 1, both parts
```

- Run a specific day and part:
```bash
./aoc2024 1 1  # Run day 1, part 1 only
./aoc2024 1 2  # Run day 1, part 2 only
```

### Running Tests

To build and run tests:

1. Build tests:
```bash
make aoc2024_tests
```

2. Run tests:
```bash
./tests/aoc2024_tests
```

## Utilities

The project includes several utility functions:

- **Input Handler**: Functions for reading input files
- **String Utils**: Common string operations (split, trim, etc.)
- **Math Utils**: Mathematical functions (GCD, LCM, etc.)

## Adding New Solutions

To implement a solution for a day:

1. Place the input file in `inputs/dayXX.txt`
2. Implement the functions in `src/days/dayXX.cpp`
3. The solution functions are already declared in `include/days/dayXX.hpp`

Each day should implement:
- `solve_part1(const std::vector<std::string>& input)` - Solve part 1
- `solve_part2(const std::vector<std::string>& input)` - Solve part 2

## License

This project is created for educational purposes to solve Advent of Code puzzles.