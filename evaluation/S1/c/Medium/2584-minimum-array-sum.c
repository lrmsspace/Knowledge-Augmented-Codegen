// Source: https://leetcode.com/problems/minimum-array-sum/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and three integers k, op1, and op2.
//
// You can perform the following operations on nums:
//
//
// 	Operation 1: Choose an index i and divide nums[i] by 2, rounding up to the nearest whole number. You can perform this operation at most op1 times, and not more than once per index.
// 	Operation 2: Choose an index i and subtract k from nums[i], but only if nums[i] is greater than or equal to k. You can perform this operation at most op2 times, and not more than once per index.
//
//
// Note: Both operations can be applied to the same index, but at most once each.
//
// Return the minimum possible sum of all elements in nums after performing any number of operations.
//
// Example:
// Input: nums = [2,8,3,19,3], k = 3, op1 = 1, op2 = 1
//
// Output: 23
//
// Explanation:
//
//
// 	Apply Operation 2 to nums[1] = 8, making nums[1] = 5.
// 	Apply Operation 1 to nums[3] = 19, making nums[3] = 10.
// 	The resulting array becomes [2, 5, 3, 10, 3], which has the minimum possible sum of 23 after applying the operations.
//
// Constraints:
// 1 <= nums.length <= 100
// 	0 <= nums[i] <= 105
// 	0 <= k <= 105
// 	0 <= op1, op2 <= nums.length
//
// Helpful references (internal KB):
// - Knapsack Problem (array, knapsack, dp-1d, dp-2d)
//   • When to use: Use when selecting a subset of items, each with a weight and value, to maximize total value without exceeding a given capacity. It is applicable for resource allocation problems with discrete choices.
//   • Idea: The Knapsack Problem aims to choose items with maximum total value such that their total weight does not exceed a given capacity. It is typically solved using dynamic programming, achieving a time complexity of O(nW) for n items and capacity W.
//   • Invariants: `dp[j]` (in 1D DP) represents the maximum value achievable with capacity `j` using items considered so far.; When processing item `i` and capacity `j` (decreasing `j`), `dp[j-weight_i]` holds the value from previous items for that reduced capacity.
//   • Tips: Initialize DP table with zeros for capacity 0 and unreachable states.; For 0-1 knapsack with 1D DP, iterate capacity `j` in decreasing order.
//   • Pitfalls: Incorrect iteration order for 1D DP in 0-1 knapsack (using increasing `j`).; Off-by-one errors in item indices or capacity calculations.
// - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
//   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
//   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
//   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
//   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
//   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
// - Generating all K-combinations (bitset, enumeration)
//   • When to use: When all subsets of a fixed size K need to be generated, either in lexicographical order or such that successive combinations differ by exactly one element.
//   • Idea: This algorithm enumerates all K-combinations from a set, either in lexicographical order or using a Gray code approach where adjacent combinations differ by a single element. It typically runs in O(N choose K) time, generating each combination in O(K) or O(1) amortized time.
//   • Invariants: Each generated combination contains exactly K distinct elements.; All elements within a combination are unique and from the original set.
//   • Tips: For lexicographical generation, find the rightmost element that can be incremented without exceeding its maximum possible value.; After incrementing an element, set all subsequent elements to their minimum valid values.
//   • Pitfalls: Incorrectly handling boundary conditions for the rightmost element or its maximum value.; Off-by-one errors when assigning subsequent elements after an increment.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minArraySum(int* nums, int numsSize, int k, int op1, int op2) {
    int n = numsSize;
    int max_ops = op1 + op2;
    int dp[n + 1][max_ops + 1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= max_ops; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = 1; i <= n; i++) {
        int original = nums[i - 1];
        int op1_result = (original + 1) / 2;
        int op2_result = (original >= k) ? (original - k) : original;
        int both_result = (original >= k) ? ((original - k + 1) / 2) : op1_result;

        for (int j = 0; j <= max_ops; j++) {
            dp[i][j] = dp[i - 1][j] + original;

            if (j >= 1) {
                dp[i][j] = (dp[i][j] < dp[i - 1][j - 1] + op1_result) ? dp[i][j] : (dp[i - 1][j - 1] + op1_result);
                dp[i][j] = (dp[i][j] < dp[i - 1][j - 1] + op2_result) ? dp[i][j] : (dp[i - 1][j - 1] + op2_result);
            }
            if (j >= 2) {
                dp[i][j] = (dp[i][j] < dp[i - 1][j - 2] + both_result) ? dp[i][j] : (dp[i - 1][j - 2] + both_result);
            }
        }
    }

    return dp[n][max_ops];      
}
