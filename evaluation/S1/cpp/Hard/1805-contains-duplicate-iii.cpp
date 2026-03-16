// Source: https://leetcode.com/problems/contains-duplicate-iii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and two integers indexDiff and valueDiff.
//
// Find a pair of indices (i, j) such that:
//
//
// 	i != j,
// 	abs(i - j) <= indexDiff.
// 	abs(nums[i] - nums[j]) <= valueDiff, and
//
//
// Return true if such pair exists or false otherwise.
//
// Example:
// Input: nums = [1,2,3,1], indexDiff = 3, valueDiff = 0
// Output: true
// Explanation: We can choose (i, j) = (0, 3).
// We satisfy the three conditions:
// i != j --> 0 != 3
// abs(i - j) <= indexDiff --> abs(0 - 3) <= 3
// abs(nums[i] - nums[j]) <= valueDiff --> abs(1 - 1) <= 0
//
// Constraints:
// 2 <= nums.length <= 105
// 	-109 <= nums[i] <= 109
// 	1 <= indexDiff <= nums.length
// 	0 <= valueDiff <= 109
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff, int valueDiff) {
        if (indexDiff <= 0 || valueDiff < 0 || nums.size() < 2) return false;

        multiset<long long> window; // Use long long to prevent overflow

        for (int i = 0; i < nums.size(); ++i) {
            if (i > indexDiff) {
                window.erase(window.find(static_cast<long long>(nums[i - indexDiff - 1])));
            }

            long long num = static_cast<long long>(nums[i]);
            auto lower = window.lower_bound(num - valueDiff);
            if (lower != window.end() && *lower <= num + valueDiff) {
                return true;
            }

            window.insert(num);
        }

        return false;           
    }
};
