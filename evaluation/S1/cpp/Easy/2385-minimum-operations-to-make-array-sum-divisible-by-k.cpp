// Source: https://leetcode.com/problems/minimum-operations-to-make-array-sum-divisible-by-k/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums and an integer k. You can perform the following operation any number of times:
//
//
// 	Select an index i and replace nums[i] with nums[i] - 1.
//
//
// Return the minimum number of operations required to make the sum of the array divisible by k.
//
// Example:
// Input: nums = [3,9,7], k = 5
//
// Output: 4
//
// Explanation:
//
//
// 	Perform 4 operations on nums[1] = 9. Now, nums = [3, 5, 7].
// 	The sum is 15, which is divisible by 5.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i] <= 1000
// 	1 <= k <= 100
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Garner's algorithm
//  (number, array, enumeration)
//   • When to use: Use when reconstructing a large integer from a system of congruences with pairwise coprime moduli, offering an alternative to the direct Chinese Remainder Theorem approach.
//   • Idea: Garner's algorithm efficiently reconstructs an integer from its remainders modulo a set of pairwise coprime numbers, by computing its mixed radix representation coefficients. It typically runs in O(k^2 log M) time, where k is the number of moduli and M is the maximum modulus, assuming modular inverse takes log M time.
//   • Invariants: At the start of iteration j, the partial sum $V_{j-1}$ satisfies $V_{j-1} \equiv a_i \pmod{p_i}$ for all $i < j$.; For each iteration j, the coefficient $x_j$ is uniquely determined in the range $[0, p_j - 1]$.
//   • Tips: Ensure all moduli are pairwise coprime for a unique solution.; Precompute modular inverses for efficiency, especially if many are needed.
//   • Pitfalls: Incorrectly calculating modular inverses, leading to wrong coefficients.; Not handling large intermediate products, which can cause integer overflow.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        int total_mod = 0;
        for (int num : nums) {
            total_mod = (total_mod + num) % k;
        }
        if (total_mod == 0) return 0;

        int n = nums.size();
        int left = 0, curr_mod = 0;
        int min_length = n + 1;

        for (int right = 0; right < n; ++right) {
            curr_mod = (curr_mod + nums[right]) % k;

            while (left <= right && curr_mod == total_mod) {
                min_length = min(min_length, right - left + 1);
                curr_mod = (curr_mod - nums[left] % k + k) % k;
                left++;
            }
        }

        return (min_length == n + 1 || min_length == n) ? -1 : min_length;          
    }
};
