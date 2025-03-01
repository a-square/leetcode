#pragma once

// IWYU pragma: private, include "leetcode.h"

// A simple library for reading values from stdin in a LeetCode/ICM friendly format.

#include <format>
#include <iostream>

#include "detail/ios.h"

namespace lc {

namespace detail {

template <typename T>
struct Reader {
    static T read() {
        T value;
        if (std::cin >> value) {
            return value;
        }

        throw std::runtime_error("Couldn't parse a value");
    }
};

template <typename T>
struct Reader<std::vector<T>> {
    // Parses a collection of the form [t1, t2, t3, ...] into a vector.
    static std::vector<T> read() {
        // Set up a sentry, mostly in order to consume any preceding whitespace.
        std::istream::sentry s(std::cin);
        if (!s) {
            throw std::runtime_error("Expected a collection");
        }

        if (std::cin.get() != '[') {
            throw std::runtime_error(std::format("Expected a collection to start with '['"));
        }

        std::vector<T> result;
        bool first = true;
        while (true) {
            // ']' signals the end of the collection
            if (std::cin.peek() == ']') {
                std::cin.get();
                break;
            }

            // If the collection goes on, all items except the first one
            // must be preceeded by the ',' delimiter.
            if (first) {
                first = false;
            } else if (std::cin.get() != ',') {
                // The error message accounts for the fact that we haven't signaled
                // the result of the ']' check above.
                throw std::runtime_error(std::format(
                    "Expected either ']', or the ',' delimiter before the next item (#{})", result.size() + 1));
            }

            // Try to read the next item, check for anything unexpected (including EOF).
            T value;
            std::cin >> value;
            if (!std::cin.good()) {
                throw std::runtime_error(std::format("Couldn't parse item #{}", result.size() + 1));
            }

            result.push_back(std::move(value));
        }

        return result;
    }
};

} // namespace detail

template <typename T>
T read() {
    detail::configureStreamsIfNeeded();
    return detail::Reader<T>::read();
}

} // namespace lc
