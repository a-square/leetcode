#pragma once

// IWYU pragma: private, include "leetcode.h"

// A simple library for writing values to stdout in a LeetCode/ICM friendly
// format.

#include <iostream>
#include <vector>

#include "detail/ios.h"

namespace lc {

namespace detail {

template <typename T>
struct Writer {
    static void write(const T& value) { std::cout << value; }
};

template <typename T>
struct Writer<std::vector<T>> {
    static void write(const std::vector<T>& values) {
        std::cout << '[';
        bool first = true;
        for (const auto& value : values) {
            if (first) {
                first = false;
            } else {
                std::cout << ',';
            }
            std::cout << value;
        }
        std::cout << ']';
        std::cout << std::endl;
    }
};

} // namespace detail

template <typename T>
void write(const T& value) {
    detail::configureStreamsIfNeeded();
    detail::Writer<T>::write(value);
}

} // namespace lc
