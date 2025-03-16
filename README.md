# LeetCode Solutions

This repository contains my solutions to various LeetCode problems implemented in C++, organized by category.

## Purpose

The main goals of this repository are (according to Claude 3.7 Sonnet):

- Document my problem-solving approach for LeetCode problems
- Provide optimized and well-commented solutions
- Create a reference for interview preparation
- Track my progress in mastering algorithms and data structures

## Project Structure

```
.
├── include/             # Header files and utilities
│   └── leetcode.h       # Common utilities and helper functions
├── src/                 # Source files grouped by problem category
│   ├── array/           # Array problems (e.g. Two Sum)
│   ├── string/          # String problems
│   ├── linked_list/     # Linked List problems
│   └── ...              # Other problem categories
├── Makefile             # Build system configuration
├── run                  # Script to execute compiled solutions
└── test                 # Script to run the tests
```

## How to Use

### Prerequisites

- GNU Make
- C++ compiler with C++23 support (Currently `clang++` is hardcoded)

### Compiling and Running Solutions

Example:
```bash
./run src/array/2sum.cpp
```

Currently, the build flags are hardcoded with `-O3` and ASAN enabled.

## Testing the solutions

Each solution's source file may include one or more test cases of the form:
`// TEST: [STDIN] -> [STDOUT]`. The command `./test` collects and runs
all these these tests and reports the results (requires Python 3).

You can optionally specify which tests to run using substring matching against
the source path, e.g. `./test -k src/array/two_sum.cpp`, or add any other
command line arguments of `pytest`.

## License

This project is open-source and available under the MIT License.
