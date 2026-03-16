// Source: https://leetcode.com/problems/find-the-count-of-monotonic-pairs-i/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of positive integers nums of length n.
//
// We call a pair of non-negative integer arrays (arr1, arr2) monotonic if:
//
//
// 	The lengths of both arrays are n.
// 	arr1 is monotonically non-decreasing, in other words, arr1[0] <= arr1[1] <= ... <= arr1[n - 1].
// 	arr2 is monotonically non-increasing, in other words, arr2[0] >= arr2[1] >= ... >= arr2[n - 1].
// 	arr1[i] + arr2[i] == nums[i] for all 0 <= i <= n - 1.
//
//
// Return the count of monotonic pairs.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [2,3,2]
//
// Output: 4
//
// Explanation:
//
// The good pairs are:
//
//
// 	([0, 1, 1], [2, 2, 1])
// 	([0, 1, 2], [2, 2, 0])
// 	([0, 2, 2], [2, 1, 0])
// 	([1, 2, 2], [1, 1, 0])
//
// Constraints:
// 1 <= n == nums.length <= 2000
// 	1 <= nums[i] <= 50
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
//   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
//   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
//   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
//   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
//   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
// - Disjoint Sparse Table tutorial (array, ds, sparse-table, prefix-sum)
//   • When to use: When you need O(1) query time for any associative operation (like sum, min, max, GCD) on a static array, after an O(N log N) preprocessing step.
//   • Idea: A Disjoint Sparse Table is a data structure that supports O(1) range queries for any associative operation on a static array. It achieves this by precomputing results for specific disjoint and overlapping ranges, with an O(N log N) construction time and space complexity.
//   • Invariants: table[k][i] stores the result of the operation for a range of length 2^k starting at index i.; For any query [L, R], the result is obtained by combining two precomputed values from blocks that cover [L, mid] and [mid+1, R].
//   • Tips: Understand the block decomposition based on powers of two for construction.; Queries combine results from two precomputed blocks that cover the query range.
//   • Pitfalls: Does not support point updates efficiently; any modification requires a full rebuild.; Higher space complexity of O(N log N) compared to some other range query structures.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @return {number}
 */
var countOfPairs = function(nums) {
    const mod = 1e9 + 7;
    const n = nums.length;
    const dp = Array.from({ length: n }, () => Array(n).fill(0));
    
    for (let i = 0; i < n; i++) {
        dp[i][i] = 1;
    }
    
    for (let length = 2; length <= n; length++) {
        for (let i = 0; i <= n - length; i++) {
            const j = i + length - 1;
            if (nums[i] + nums[j] === nums[i + j - (i + 1)]) {
                dp[i][j] = (dp[i][j] + dp[i + 1][j]) % mod;
                dp[i][j] = (dp[i][j] + dp[i][j - 1]) % mod;
                dp[i][j] = (dp[i][j] - dp[i + 1][j - 1] + mod) % mod;
            } else {
                dp[i][j] = (dp[i][j] + dp[i + 1][j]) % mod;
                dp[i][j] = (dp[i][j] + dp[i][j - 1]) % mod;
                dp[i][j] = (dp[i][j] - dp[i + 1][j - 1] + mod) % mod;
            }
        }
    }
    
    return dp[0][n - 1]; 
};
