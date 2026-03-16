// Source: https://leetcode.com/problems/minimum-increments-for-target-multiples-in-an-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given two arrays, nums and target.
//
// In a single operation, you may increment any element of nums by 1.
//
// Return the minimum number of operations required so that each element in target has at least one multiple in nums.
//
// Example:
// Input: nums = [1,2,3], target = [4]
//
// Output: 1
//
// Explanation:
//
// The minimum number of operations required to satisfy the condition is 1.
//
//
// 	Increment 3 to 4 with just one operation, making 4 a multiple of itself.
//
// Constraints:
// 1 <= nums.length <= 5 * 104
// 	1 <= target.length <= 4
// 	target.length <= nums.length
// 	1 <= nums[i], target[i] <= 104
//
// Helpful references (internal KB):
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
// - Range Minimum Query (array, ds, divide-and-conquer)
//   • When to use: Use when you need to find the minimum element within specified ranges of an array efficiently, especially for many queries after initial setup.
//   • Idea: A Range Minimum Query (RMQ) problem asks to find the minimum value in a specified range [L, R] of an array. It can be solved with various data structures, often achieving O(1) or O(log N) query time after O(N log N) or O(N) precomputation.
//   • Invariants: For any query range [L, R], the returned value is the minimum of elements A[i] where L <= i <= R.; The precomputed data structure correctly stores minimums for all relevant sub-intervals.
//   • Tips: For static arrays, Sparse Table offers O(1) query time after O(N log N) precomputation.; For dynamic arrays (with updates), Segment Tree provides O(log N) query and update times.
//   • Pitfalls: Incorrectly handling edge cases for range boundaries (L, R).; High memory usage for Sparse Table if N is very large (N log N space).
// - Euclidean algorithm for computing the greatest common divisor (number, gcd)
//   • When to use: Use this algorithm to efficiently find the greatest common divisor of two or more integers, or as a subroutine for tasks like simplifying fractions or finding the least common multiple.
//   • Idea: The Euclidean algorithm is an efficient method for computing the greatest common divisor (GCD) of two non-negative integers by repeatedly applying the division algorithm. It operates in logarithmic time complexity, O(log min(a, b)).
//   • Invariants: The greatest common divisor of the current pair (a, b) remains constant and equal to the GCD of the original inputs.; The second number (b) is always non-negative.
//   • Tips: Handle the base case where one of the numbers is zero; gcd(a, 0) = a.; The algorithm works for any order of inputs; if a < b, the first step swaps them effectively.
//   • Pitfalls: Forgetting to take absolute values if negative inputs are possible, as GCD is typically defined for non-negative integers.; Incorrectly handling the zero input case, which can lead to infinite loops or incorrect results.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minimumIncrements(vector<int>& nums, vector<int>& target) {
        const int MAX_VAL = 10000;
        vector<int> dp(1 << target.size(), INT_MAX);
        dp[0] = 0;

        for (int num : nums) {
            vector<int> new_dp = dp;
            for (int mask = 0; mask < (1 << target.size()); ++mask) {
                if (dp[mask] == INT_MAX) continue;
                for (int i = 0; i < target.size(); ++i) {
                    if (mask & (1 << i)) continue;
                    int t = target[i];
                    int increment = (num % t == 0) ? 0 : (t - (num % t));
                    if (num + increment <= MAX_VAL) {
                        int new_mask = mask | (1 << i);
                        new_dp[new_mask] = min(new_dp[new_mask], dp[mask] + increment);
                    }
                }
            }
            dp = move(new_dp);
        }

        return dp[(1 << target.size()) - 1] == INT_MAX ? -1 : dp[(1 << target.size()) - 1];         
    }
};
