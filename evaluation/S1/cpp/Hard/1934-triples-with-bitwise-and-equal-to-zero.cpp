// Source: https://leetcode.com/problems/triples-with-bitwise-and-equal-to-zero/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums, return the number of AND triples.
//
// An AND triple is a triple of indices (i, j, k) such that:
//
//
// 	0 <= i < nums.length
// 	0 <= j < nums.length
// 	0 <= k < nums.length
// 	nums[i] & nums[j] & nums[k] == 0, where & represents the bitwise-AND operator.
//
// Example:
// Input: nums = [2,1,3]
// Output: 12
// Explanation: We could choose the following i, j, k triples:
// (i=0, j=0, k=1) : 2 & 2 & 1
// (i=0, j=1, k=0) : 2 & 1 & 2
// (i=0, j=1, k=1) : 2 & 1 & 1
// (i=0, j=1, k=2) : 2 & 1 & 3
// (i=0, j=2, k=1) : 2 & 3 & 1
// (i=1, j=0, k=0) : 1 & 2 & 2
// (i=1, j=0, k=1) : 1 & 2 & 1
// (i=1, j=0, k=2) : 1 & 2 & 3
// (i=1, j=1, k=0) : 1 & 1 & 2
// (i=1, j=2, k=0) : 1 & 3 & 2
// (i=2, j=0, k=1) : 3 & 2 & 1
// (i=2, j=1, k=0) : 3 & 1 & 2
//
// Constraints:
// 1 <= nums.length <= 1000
// 	0 <= nums[i] < 216
//
// Helpful references (internal KB):
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Sparse Table (array, sparse-table, enumeration)
//   • When to use: Use when you need to perform many range queries on a static array, especially when the query operation is associative and idempotent, allowing for O(1) query time after O(N log N) precomputation.
//   • Idea: A Sparse Table is a data structure that precomputes answers for all possible range queries of power-of-two lengths. It allows O(1) query time for idempotent operations like min/max/gcd and O(log N) for non-idempotent associative operations, after an O(N log N) build time.
//   • Invariants: After precomputation, dp[k][i] stores the result for the range [i, i + 2^k - 1].; For any k > 0, dp[k][i] is the result of combining dp[k-1][i] and dp[k-1][i + 2^(k-1)].
//   • Tips: Precompute log2 values for faster range length calculations.; Store dp[k][i] as the result for range [i, i + 2^k - 1].
//   • Pitfalls: Does not support updates to array elements efficiently.; Requires O(N log N) space, which can be significant for large N.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int countTriplets(vector<int>& nums) {
        const int MAX_MASK = 1 << 16;
        vector<int> freq(MAX_MASK, 0);

        // Count frequency of each number in nums
        for (int num : nums) {
            freq[num]++;
        }

        // Precompute the number of pairs (a, b) such that a & b == mask
        vector<int> pairCount(MAX_MASK, 0);
        for (int i = 0; i < MAX_MASK; ++i) {
            for (int j = 0; j < MAX_MASK; ++j) {
                int andResult = i & j;
                pairCount[andResult] += freq[i] * freq[j];
            }
        }

        // Calculate the total number of triplets (i, j, k) such that nums[i] & nums[j] & nums[k] == 0
        int totalTriplets = 0;
        for (int num : nums) {
            totalTriplets += pairCount[~num & (MAX_MASK - 1)];
        }

        return totalTriplets;           
    }
};
