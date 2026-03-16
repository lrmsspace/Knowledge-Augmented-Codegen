// Source: https://leetcode.com/problems/minimum-incompatibility/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums​​​ and an integer k. You are asked to distribute this array into k subsets of equal size such that there are no two equal elements in the same subset.
//
// A subset's incompatibility is the difference between the maximum and minimum elements in that array.
//
// Return the minimum possible sum of incompatibilities of the k subsets after distributing the array optimally, or return -1 if it is not possible.
//
// A subset is a group integers that appear in the array with no particular order.
//
// Example:
// Input: nums = [1,2,1,4], k = 2
// Output: 4
// Explanation: The optimal distribution of subsets is [1,2] and [1,4].
// The incompatibility is (2-1) + (4-1) = 4.
// Note that [1,1] and [2,4] would result in a smaller sum, but the first subset contains 2 equal elements.
//
// Constraints:
// 1 <= k <= nums.length <= 16
// 	nums.length is divisible by k
// 	1 <= nums[i] <= nums.length
//
// Helpful references (internal KB):
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
// - Generating all K-combinations (bitset, enumeration)
//   • When to use: When all subsets of a fixed size K need to be generated, either in lexicographical order or such that successive combinations differ by exactly one element.
//   • Idea: This algorithm enumerates all K-combinations from a set, either in lexicographical order or using a Gray code approach where adjacent combinations differ by a single element. It typically runs in O(N choose K) time, generating each combination in O(K) or O(1) amortized time.
//   • Invariants: Each generated combination contains exactly K distinct elements.; All elements within a combination are unique and from the original set.
//   • Tips: For lexicographical generation, find the rightmost element that can be incremented without exceeding its maximum possible value.; After incrementing an element, set all subsequent elements to their minimum valid values.
//   • Pitfalls: Incorrectly handling boundary conditions for the rightmost element or its maximum value.; Off-by-one errors when assigning subsequent elements after an increment.
// - Knapsack Problem (array, knapsack, dp-1d, enumeration)
//   • When to use: Use when selecting items from a set to maximize or minimize a value under a capacity constraint. It's also applicable for partitioning problems with a fixed budget.
//   • Idea: This algorithm finds the maximum value that can be obtained by selecting a subset of items, each with a weight and a value, such that their total weight does not exceed a given capacity. It typically uses dynamic programming with a time complexity of O(N*W), where N is the number of items and W is the capacity.
//   • Invariants: After processing item `i`, `dp[w]` stores the maximum value for capacity `w` using items up to `i`.; For each item, `dp[w]` is updated considering either including or excluding the current item.
//   • Tips: Use a 2D DP table `dp[i][w]` for item `i` and weight `w` for clarity, then optimize to 1D.; When optimizing to 1D, iterate weights downwards to avoid using an item multiple times.
//   • Pitfalls: Incorrectly initializing the DP table can lead to wrong results or infinite loops.; Forgetting to iterate weights downwards in 1D DP can lead to items being picked multiple times (unbounded knapsack).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minimumIncompatibility(vector<int>& nums, int k) {
        const int n = nums.size();
        const int subsetSize = n / k;
        const int fullMask = (1 << n) - 1;

        // Precompute valid subsets and their incompatibilities
        unordered_map<int, int> subsetIncompatibility;
        for (int mask = 0; mask <= fullMask; ++mask) {
            if (__builtin_popcount(mask) != subsetSize) continue;

            unordered_set<int> seen;
            int minVal = INT_MAX, maxVal = INT_MIN;
            bool valid = true;

            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) {
                    if (seen.count(nums[i])) {
                        valid = false;
                        break;
                    }
                    seen.insert(nums[i]);
                    minVal = min(minVal, nums[i]);
                    maxVal = max(maxVal, nums[i]);
                }
            }

            if (valid) {
                subsetIncompatibility[mask] = maxVal - minVal;
            }
        }

        // DP array to store minimum incompatibility sum for each mask
        vector<int> dp(1 << n, INT_MAX);
        dp[0] = 0;

        for (int mask = 0; mask <= fullMask; ++mask) {
            if (dp[mask] == INT_MAX) continue;

            // Try to add a new valid subset
            for (const auto& [subsetMask, incompatibility] : subsetIncompatibility) {
                if ((mask & subsetMask) == 0) { // No overlap
                    int newMask = mask | subsetMask;
                    dp[newMask] = min(dp[newMask], dp[mask] + incompatibility);
                }
            }
        }

        return dp[fullMask] == INT_MAX ? -1 : dp[fullMask];         
    }
};
