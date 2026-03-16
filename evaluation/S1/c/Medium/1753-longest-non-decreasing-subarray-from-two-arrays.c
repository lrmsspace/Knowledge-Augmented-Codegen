// Source: https://leetcode.com/problems/longest-non-decreasing-subarray-from-two-arrays/   |   Difficulty: Medium
//
// Problem Description:
// You are given two 0-indexed integer arrays nums1 and nums2 of length n.
//
// Let's define another 0-indexed integer array, nums3, of length n. For each index i in the range [0, n - 1], you can assign either nums1[i] or nums2[i] to nums3[i].
//
// Your task is to maximize the length of the longest non-decreasing subarray in nums3 by choosing its values optimally.
//
// Return an integer representing the length of the longest non-decreasing subarray in nums3.
//
// Note: A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums1 = [2,3,1], nums2 = [1,2,1]
// Output: 2
// Explanation: One way to construct nums3 is: 
// nums3 = [nums1[0], nums2[1], nums2[2]] => [2,2,1]. 
// The subarray starting from index 0 and ending at index 1, [2,2], forms a non-decreasing subarray of length 2. 
// We can show that 2 is the maximum achievable length.
//
// Constraints:
// 1 <= nums1.length == nums2.length == n <= 105
// 	1 <= nums1[i], nums2[i] <= 109
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
// - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
//   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
//   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
//   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
//   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
//   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
// - Knapsack Problem (array, knapsack, dp-1d, enumeration)
//   • When to use: Use when selecting items from a set to maximize or minimize a value under a capacity constraint. It's also applicable for partitioning problems with a fixed budget.
//   • Idea: This algorithm finds the maximum value that can be obtained by selecting a subset of items, each with a weight and a value, such that their total weight does not exceed a given capacity. It typically uses dynamic programming with a time complexity of O(N*W), where N is the number of items and W is the capacity.
//   • Invariants: After processing item `i`, `dp[w]` stores the maximum value for capacity `w` using items up to `i`.; For each item, `dp[w]` is updated considering either including or excluding the current item.
//   • Tips: Use a 2D DP table `dp[i][w]` for item `i` and weight `w` for clarity, then optimize to 1D.; When optimizing to 1D, iterate weights downwards to avoid using an item multiple times.
//   • Pitfalls: Incorrectly initializing the DP table can lead to wrong results or infinite loops.; Forgetting to iterate weights downwards in 1D DP can lead to items being picked multiple times (unbounded knapsack).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maxNonDecreasingLength(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int dp1 = 1, dp2 = 1, res = 1;
    for (int i = 1; i < nums1Size; ++i) {
        int new_dp1 = 1, new_dp2 = 1;
        if (nums1[i] >= nums1[i - 1]) {
            new_dp1 = dp1 + 1;
        }
        if (nums1[i] >= nums2[i - 1]) {
            if (dp2 + 1 > new_dp1) {
                new_dp1 = dp2 + 1;
            }
        }
        if (nums2[i] >= nums2[i - 1]) {
            new_dp2 = dp2 + 1;
        }
        if (nums2[i] >= nums1[i - 1]) {
            if (dp1 + 1 > new_dp2) {
                new_dp2 = dp1 + 1;
            }
        }
        dp1 = new_dp1;
        dp2 = new_dp2;
        if (dp1 > res) {
            res = dp1;
        }
        if (dp2 > res) {
            res = dp2;
        }
    }
    return res;     
}
