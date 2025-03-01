#pragma once

// IWYU pragma: private, include "leetcode.h"

struct TreeNode {
    int val = 0;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;

    explicit TreeNode(int x) : val(x) {}
    explicit TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};
