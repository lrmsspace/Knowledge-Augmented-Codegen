// Source: https://leetcode.com/problems/minimum-sum-of-values-by-dividing-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given two arrays nums and andValues of length n and m respectively.
//
// The value of an array is equal to the last element of that array.
//
// You have to divide nums into m disjoint contiguous subarrays such that for the ith subarray [li, ri], the bitwise AND of the subarray elements is equal to andValues[i], in other words, nums[li] & nums[li + 1] & ... & nums[ri] == andValues[i] for all 1 <= i <= m, where & represents the bitwise AND operator.
//
// Return the minimum possible sum of the values of the m subarrays nums is divided into. If it is not possible to divide nums into m subarrays satisfying these conditions, return -1.
//
// Example:
// Input: nums = [1,4,3,3,2], andValues = [0,3,3,2]
//
// Output: 12
//
// Explanation:
//
// The only possible way to divide nums is:
//
//
// 	[1,4] as 1 & 4 == 0.
// 	[3] as the bitwise AND of a single element subarray is that element itself.
// 	[3] as the bitwise AND of a single element subarray is that element itself.
// 	[2] as the bitwise AND of a single element subarray is that element itself.
//
//
// The sum of the values for these subarrays is 4 + 3 + 3 + 2 = 12.
//
// Constraints:
// 1 <= n == nums.length <= 104
// 	1 <= m == andValues.length <= min(n, 10)
// 	1 <= nums[i] < 105
// 	0 <= andValues[j] < 105
//
// Helpful references (internal KB):
// - interval-dp (array, interval-dp)
//   • When to use: When a problem involves finding an optimal value for a contiguous range of elements, and solutions for larger ranges can be derived by merging optimal solutions of smaller sub-ranges.
//   • Idea: An extension of dynamic programming where subproblems are defined over contiguous intervals, solving for dp[i][j] by iterating through all possible split points k within [i, j]. This often results in O(N^3) time complexity.
//   • Invariants: dp[i][j] represents the optimal solution for the interval [i, j].; When computing dp[i][j], all subproblems dp[x][y] where y - x + 1 < j - i + 1 are already solved.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length, then by start index.
//   • Pitfalls: Off-by-one errors in interval boundaries or split points.; Incorrect iteration order, leading to uncomputed subproblems.
// - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
//   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
//   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
//   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
//   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
//   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minimumValueSum(int* nums, int numsSize, int* andValues, int andValuesSize) {
    const int INF = 0x3f3f3f3f;
    int dp[andValuesSize + 1];
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;

    for (int i = 0, andVal = 0; i < numsSize; ++i) {
        andVal = nums[i];
        for (int j = i; j < numsSize; ++j) {
            if (j > i) andVal &= nums[j];
            for (int k = andValuesSize - 1; k >= 0; --k) {
                if (andVal == andValues[k] && dp[k] != INF) {
                    int val = dp[k] + nums[j];
                    if (val < dp[k + 1]) dp[k + 1] = val;
                }
            }
        }
    }

    return dp[andValuesSize] == INF ? -1 : dp[andValuesSize];       
}
