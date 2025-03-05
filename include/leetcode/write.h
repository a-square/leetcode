#pragma once

// IWYU pragma: private, include "leetcode.h"

// A simple library for writing values to stdout in a LeetCode/ICM friendly
// format.

#include <deque>
#include <iostream>
#include <optional>
#include <ranges>

#include "detail/ios.h"
#include "structs.h"

namespace lc {

namespace detail {

template <typename T>
struct Writer {
    static void write(const T& value) { std::cout << value; }
};

template <typename T>
struct Writer<std::optional<T>> {
    static void write(const std::optional<T>& value) {
        if (value) {
            std::cout << *value;
        } else {
            std::cout << "null";
        }
    }
};

template <std::ranges::forward_range Range>
struct Writer<Range> {
    static void write(const Range& values) {
        std::cout << '[';
        bool first = true;
        for (const auto& value : values) {
            if (first) {
                first = false;
            } else {
                std::cout << ',';
            }
            Writer<std::decay_t<decltype(value)>>::write(value);
        }
        std::cout << ']';
    }
};

template <>
struct Writer<ListPtr> {
    void write(const ListPtr& values) {
        std::cout << '[';
        bool first = true;
        for (auto* node = values.get(); node; node = node->next) {
            if (first) {
                first = false;
            } else {
                std::cout << ',';
            }

            Writer<int>::write(node->val);
        }

        std::cout << ']';
    }
};

template <>
struct Writer<TreePtr> {
    static void write(const TreePtr& root) {
        std::deque<TreeNode*> bfsQueue;

        std::cout << '[';
        bool first = true;
        bfsQueue.push_back(root.get());
        while (!bfsQueue.empty()) {
            auto* node = bfsQueue.front();
            bfsQueue.pop_front();

            if (first) {
                first = false;
            } else {
                std::cout << ',';
            }

            if (node) {
                Writer<int>::write(node->val);
                bfsQueue.push_back(node->left);
                bfsQueue.push_back(node->right);
            } else {
                Writer<std::string_view>::write("null");
            }
        }
        std::cout << ']';
    }
};

template <typename T>
void write(const T& value) {
    Writer<T>::write(value);
}

} // namespace detail

template <typename T>
void write(const T& value) {
    detail::configureStreamsIfNeeded();
    detail::write(value);
    std::cout << std::endl;
}

} // namespace lc
