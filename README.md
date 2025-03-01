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
└── run                  # Script to execute compiled solutions
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

## License

This project is open-source and available under the MIT License.
