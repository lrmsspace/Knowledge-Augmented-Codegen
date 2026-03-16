// Source: https://leetcode.com/problems/zero-array-transformation-iii/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums of length n and a 2D array queries where queries[i] = [li, ri].
//
// Each queries[i] represents the following action on nums:
//
//
// 	Decrement the value at each index in the range [li, ri] in nums by at most 1.
// 	The amount by which the value is decremented can be chosen independently for each index.
//
//
// A Zero Array is an array with all its elements equal to 0.
//
// Return the maximum number of elements that can be removed from queries, such that nums can still be converted to a zero array using the remaining queries. If it is not possible to convert nums to a zero array, return -1.
//
// Example:
// Input: nums = [2,0,2], queries = [[0,2],[0,2],[1,1]]
//
// Output: 1
//
// Explanation:
//
// After removing queries[2], nums can still be converted to a zero array.
//
//
// 	Using queries[0], decrement nums[0] and nums[2] by 1 and nums[1] by 0.
// 	Using queries[1], decrement nums[0] and nums[2] by 1 and nums[1] by 0.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 105
// 	1 <= queries.length <= 105
// 	queries[i].length == 2
// 	0 <= li <= ri < nums.length
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Sparse Table (array, sparse-table, enumeration)
//   • When to use: Use when performing many range queries on a static array where the query operation is idempotent (e.g., min, max, GCD) to achieve O(1) query time after O(N log N) precomputation.
//   • Idea: A data structure that precomputes answers for all possible range queries of power-of-two lengths, allowing O(1) query time for idempotent operations like range minimum/maximum queries. Precomputation takes O(N log N) time and space.
//   • Invariants: The `st[k][i]` entry stores the result of the operation for the range `[i, i + 2^k - 1]`.; All ranges of length `2^k` starting at `i` are correctly computed in `st[k][i]` during precomputation.
//   • Tips: Precompute logarithms for O(1) lookup of `floor(log2(length))` during queries.; Sparse tables are most efficient for idempotent operations (min, max, GCD, OR, AND) due to overlapping segments.
//   • Pitfalls: Not suitable for dynamic arrays or scenarios requiring updates, as modifications invalidate the precomputed table.; High memory usage: requires O(N log N) space, which can be significant for large N.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @param {number[][]} queries
 * @return {number}
 */
var maxRemoval = function(nums, queries) {
    const n = nums.length;
    const m = queries.length;
    const prefix = new Array(n + 1).fill(0);
    for (const [l, r] of queries) {
        prefix[l]++;
        prefix[r + 1]--;
    }
    for (let i = 1; i <= n; i++) {
        prefix[i] += prefix[i - 1];
    }
    const freq = new Array(m + 1).fill(0);
    for (let i = 0; i < n; i++) {
        if (prefix[i] > m) return -1;
        freq[prefix[i]]++;
    }
    let removed = 0;
    for (let i = m; i >= 0; i--) {
        removed += freq[i];
        if (removed >= freq[i]) {
            removed -= freq[i];
        } else {
            return m - i;
        }
    }
    return m;
};
