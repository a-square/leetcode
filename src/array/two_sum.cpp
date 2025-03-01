#include <unordered_map>
#include <vector>

#include "leetcode.h"

std::vector<int> twoSum(const std::vector<int>& nums, int target) {
    int n = nums.size();

    std::unordered_map<int, int> valueToIndexMap;
    for (int i = 0; i < n; ++i) {
        valueToIndexMap[nums[i]] = i;
    }

    for (int i = 0; i < n; i++) {
        if (auto it = valueToIndexMap.find(target - nums[i]); it != valueToIndexMap.end()) {
            if (i != it->second) {
                return {i, it->second};
            }
        }
    }

    return {};
}

int main() {
    auto nums = lc::read<std::vector<int>>();
    auto target = lc::read<int>();
    auto result = twoSum(nums, target);
    lc::write(result);
}
