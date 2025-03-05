#pragma once

// IWYU pragma: private, include "leetcode.h"

#include <deque>
#include <iostream>
#include <memory>
#include <unordered_set>

namespace lc {

struct ListNode {
    int val = 0;
    ListNode* next = 0;

    ListNode(int x) : val(x) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

struct TreeNode {
    int val = 0;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;

    explicit TreeNode(int x) : val(x) {}
    explicit TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

namespace detail {

struct ListDeleter {
    void operator()(ListNode* head) {
        bool issuedWarning = false;
        std::unordered_set<ListNode*> deleted;

        while (head) {
            if (auto [_, inserted] = deleted.insert(head); !inserted) {
                if (!issuedWarning) {
                    issuedWarning = true;
                    std::cerr << "Warning: Deleting a list that contains a cycle!" << std::endl;
                }
                return;
            }

            auto* newHead = head->next;
            delete head;
            head = newHead;
        }
    }
};

struct TreeDeleter {
    void operator()(TreeNode* root) {
        if (!root) {
            return;
        }

        bool issuedWarning = false;
        std::unordered_set<TreeNode*> deleted;

        std::deque<TreeNode*> toDelete;
        toDelete.push_back(root);
        while (!toDelete.empty()) {
            auto* node = toDelete.back();
            toDelete.pop_back();

            if (auto [_, inserted] = deleted.insert(node); !inserted) {
                if (!issuedWarning) {
                    issuedWarning = true;
                    std::cerr << "Warning: Deleting a tree that contains a cycle!" << std::endl;
                }
                return;
            }

            if (node->right) {
                toDelete.push_back(node->right);
            }
            if (node->left) {
                toDelete.push_back(node->left);
            }

            delete node;
        }
    }
};

} // namespace detail

using ListPtr = std::unique_ptr<ListNode, detail::ListDeleter>;
using TreePtr = std::unique_ptr<TreeNode, detail::TreeDeleter>;

} // namespace lc
