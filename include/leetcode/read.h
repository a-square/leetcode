#pragma once

// IWYU pragma: private, include "leetcode.h"

// A simple library for reading values from stdin in a LeetCode/ICM friendly format.

#include <concepts>
#include <format>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <utility>

#include "detail/ios.h"
#include "structs.h"

namespace lc {

namespace detail {

template <typename T>
struct Reader {
    static T read() {
        T value;
        std::cin >> value;

        if (std::cin.eof()) {
            throw std::runtime_error("Expected a value, got EOF");
        }

        if (!std::cin.good()) {
            throw std::runtime_error("Failed to parse a value");
        }

        return value;
    }
};

template <typename T>
struct Reader<std::optional<T>> {
    static std::optional<T> read() {
        std::istream::sentry s(std::cin);
        if (!s) {
            throw std::runtime_error("Expected a value or null");
        }

        if (std::cin.peek() == 'n') {
            std::string nullStr;
            std::cin >> nullStr;
            if (!std::cin.good()) {
                throw std::runtime_error("Expected a value or null");
            }
            if (nullStr != "null") {
                throw std::runtime_error(std::format("Expected a value or null, got {}", nullStr));
            }
            return std::nullopt;
        }

        T value;
        std::cin >> value;
        if (!std::cin.good()) {
            throw std::runtime_error("Expected a value or null");
        }
        return value;
    }
};

template <typename Container>
class ReaderAdapter;

template <typename T>
class ReaderAdapter<std::vector<T>> {
  public:
    using ContainerType = std::vector<T>;
    using ValueType = T;

    explicit ReaderAdapter(ContainerType& container) : container_(container) {}

    size_t size() const { return container_.size(); }

    void add(ValueType&& value) { container_.push_back(std::move(value)); }

  private:
    ContainerType& container_;
};

template <>
class ReaderAdapter<ListPtr> {
  public:
    using ContainerType = ListPtr;
    using ValueType = int;

    explicit ReaderAdapter(ContainerType& container) : container_(container) {
        if (container) {
            throw std::invalid_argument("List reader adapter can only be constructed with an initially empty list");
        }
    }

    size_t size() const { return size_; }

    void add(ValueType&& value) {
        if (!container_) {
            container_ = ListPtr(new ListNode(std::move(value)));
            tail_ = container_.get();
        } else {
            auto* newTail = new ListNode(std::move(value));
            tail_->next = newTail;
            tail_ = newTail;
        }
        size_++;
    }

  private:
    ContainerType& container_;
    ListNode* tail_ = nullptr;
    size_t size_ = 0;
};

template <>
class ReaderAdapter<TreePtr> {
  public:
    using ContainerType = TreePtr;
    using ValueType = std::optional<int>;

    explicit ReaderAdapter(ContainerType& container) : container_(container) {
        if (container) {
            throw std::invalid_argument("List reader adapter can only be constructed with an initially empty tree");
        }

        // Nullptr is the special value which means put the result into the root pointer.
        readQueue_.push_back(nullptr);
    }

    size_t size() const { return size_; }

    void add(ValueType&& value) {
        if (readQueue_.empty()) {
            throw std::runtime_error("Invalid binary tree input");
        }

        auto** nodePtr = readQueue_.front();
        readQueue_.pop_front();

        if (!value.has_value()) {
            return;
        }

        auto* node = new TreeNode(std::move(*value));
        if (nodePtr) {
            *nodePtr = node;
        } else {
            container_.reset(node);
        }

        readQueue_.push_back(&node->left);
        readQueue_.push_back(&node->right);

        size_++;
    }

  private:
    ContainerType& container_;
    std::deque<TreeNode**> readQueue_;
    size_t size_ = 0;
};

template <typename Container>
concept ReaderAdapterAware =
    requires(ReaderAdapter<Container> adapter, typename ReaderAdapter<Container>::ValueType value) {
        std::is_default_constructible_v<Container>;
        std::is_constructible_v<ReaderAdapter<Container>, Container&>;
        { std::as_const(adapter).size() } -> std::convertible_to<size_t>;
        { adapter.add(std::move(value)) };
    };

template <ReaderAdapterAware Container>
struct Reader<Container> {
    using AdapterType = ReaderAdapter<Container>;
    using ContainerType = ReaderAdapter<Container>::ContainerType;
    using ValueType = AdapterType::ValueType;

    // Parses a collection of the form [t1, t2, t3, ...] into a container.
    static ContainerType read() {
        // Set up a sentry, mostly in order to consume any preceding whitespace.
        std::istream::sentry s(std::cin);
        if (!s) {
            throw std::runtime_error("Expected a collection");
        }

        if (std::cin.get() != '[') {
            throw std::runtime_error(std::format("Expected a collection to start with '['"));
        }

        ContainerType result;
        AdapterType adapter(result);

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
                    "Expected either ']', or the ',' delimiter before the next item (#{})", adapter.size() + 1));
            }

            // Try to read the next item, check for anything unexpected (including EOF).
            try {
                auto value = Reader<ValueType>::read();
                adapter.add(std::move(value));
            } catch (const std::exception& ex) {
                throw std::runtime_error(std::format("Couldn't parse item #{}: {}", adapter.size() + 1, ex.what()));
            }
        }

        return result;
    }
};

template <typename T>
T read() {
    return Reader<T>::read();
}

} // namespace detail

template <typename T>
T read() {
    detail::configureStreamsIfNeeded();
    return detail::read<T>();
}

} // namespace lc
