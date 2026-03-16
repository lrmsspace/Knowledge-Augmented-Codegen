// Source: https://leetcode.com/problems/maximum-score-from-performing-multiplication-operations/   |   Difficulty: Hard
//
// Problem Description:
// You are given two 0-indexed integer arrays nums and multipliers of size n and m respectively, where n >= m.
//
// You begin with a score of 0. You want to perform exactly m operations. On the ith operation (0-indexed) you will:
//
//
//     Choose one integer x from either the start or the end of the array nums.
//     Add multipliers[i] * x to your score.
//     
//         Note that multipliers[0] corresponds to the first operation, multipliers[1] to the second operation, and so on.
//     
//     
//     Remove x from nums.
//
//
// Return the maximum score after performing m operations.
//
// Example:
// Input: nums = [1,2,3], multipliers = [3,2,1]
// Output: 14
// Explanation: An optimal solution is as follows:
// - Choose from the end, [1,2,3], adding 3 * 3 = 9 to the score.
// - Choose from the end, [1,2], adding 2 * 2 = 4 to the score.
// - Choose from the end, [1], adding 1 * 1 = 1 to the score.
// The total score is 9 + 4 + 1 = 14.
//
// Constraints:
// n == nums.length
// 	m == multipliers.length
// 	1 <= m <= 300
// 	m <= n <= 105 
// 	-1000 <= nums[i], multipliers[i] <= 1000
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
//   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
//   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
//   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
//   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
//   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
// - Operations on polynomials and series (array, recursion)
//   • When to use: Apply when multiplying polynomials or combining two sequences where the resulting element's index is the sum of indices from the original sequences. This is typically for enumerative counting problems.
//   • Idea: Convolution computes the coefficients of the product of two polynomials or series by summing products of coefficients whose indices add up to the target index. A direct computation has a time complexity of O(N*M).
//   • Invariants: For any k, c_k correctly represents the coefficient of x^k in the product polynomial.; The sum i + (k-i) always equals k for each term contributing to c_k.
//   • Tips: Understand the index relationship: c_k = sum(a_i * b_{k-i}) for all valid i.; Handle array bounds carefully for both input sequences and the result.
//   • Pitfalls: Off-by-one errors in loop bounds for indices i and k-i.; Incorrectly determining the size of the result array (should be n+m+1 elements for degrees n and m).
// - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
//   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
//   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
//   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
//   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
//   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maximumScore(int* nums, int numsSize, int* multipliers, int multipliersSize) {
    int m = multipliersSize;
    int n = numsSize;
    int dp[m + 1][m + 1]; // dp[i][j] - max score using i from the start and j from the end
    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= m; ++j) {
            dp[i][j] = 0;
        }
    }

    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (j > 0) {
                dp[i][j] = dp[i - 1][j - 1] + multipliers[i - 1] * nums[j - 1];
            }
            if (i - j > 0) {
                int scoreFromEnd = dp[i - 1][j] + multipliers[i - 1] * nums[n - (i - j)];
                if (scoreFromEnd > dp[i][j]) {
                    dp[i][j] = scoreFromEnd;
                }
            }
        }
    }

    int maxScore = dp[m][0];
    for (int j = 1; j <= m; ++j) {
        if (dp[m][j] > maxScore) {
            maxScore = dp[m][j];
        }
    }
    
    return maxScore;        
}
