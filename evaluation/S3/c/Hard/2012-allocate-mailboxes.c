// Source: https://leetcode.com/problems/allocate-mailboxes/   |   Difficulty: Hard
//
// Problem Description:
// Given the array houses where houses[i] is the location of the ith house along a street and an integer k, allocate k mailboxes in the street.
//
// Return the minimum total distance between each house and its nearest mailbox.
//
// The test cases are generated so that the answer fits in a 32-bit integer.
//
// Example:
// Input: houses = [1,4,8,10,20], k = 3
// Output: 5
// Explanation: Allocate mailboxes in position 3, 9 and 20.
// Minimum total distance from each houses to nearest mailboxes is |3-1| + |4-3| + |9-8| + |10-9| + |20-20| = 5
//
// Constraints:
// 1 <= k <= houses.length <= 100
// 	1 <= houses[i] <= 104
// 	All the integers of houses are unique.
//
// Helpful references (internal KB):
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
// - Sqrt Decomposition (array, enumeration, difference-array)
//   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
//   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
//   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
//   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
//   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
// - Finding the nearest pair of points (geometry, array, divide-and-conquer, merge-sort, two-pointers)
//   • When to use: Use this when finding the pair of points with the minimum Euclidean distance in a 2D plane. It efficiently handles large datasets by recursively dividing the problem and merging results.
//   • Idea: It finds the closest pair of points in a 2D plane by recursively dividing the set, solving subproblems, and merging results in O(N log N) time. The merge step efficiently handles cross-boundary pairs within a narrow strip.
//   • Invariants: The minimum distance returned by a recursive call is the true minimum for its input subset.; All points in the left subproblem have x-coordinates less than or equal to the median x-coordinate.
//   • Tips: Pre-sort points by x-coordinate to enable efficient splitting.; Maintain a y-sorted list of points for efficient merging of the strip.
//   • Pitfalls: An inefficient merge step can degrade complexity from O(N log N) to O(N^2).; Failing to correctly identify and process cross-boundary pairs.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minDistance(int* houses, int housesSize, int k) {
    int dp[101][101];
    for (int i = 0; i < housesSize; i++) {
        for (int j = i; j < housesSize; j++) {
            int mid = (i + j) / 2;
            dp[i][j] = 0;
            for (int m = i; m <= j; m++) {
                dp[i][j] += abs(houses[m] - houses[mid]);
            }
        }
    }

    int memo[101][101];
    for (int i = 0; i <= housesSize; i++) {
        for (int j = 0; j <= k; j++) {
            memo[i][j] = -1;
        }
    }

    int dfs(int start, int remaining) {
        if (remaining == 0) {
            return start == housesSize ? 0 : 1e9;
        }
        if (memo[start][remaining] != -1) {
            return memo[start][remaining];
        }
        int ans = 1e9;
        for (int end = start; end < housesSize; end++) {
            ans = fmin(ans, dp[start][end] + dfs(end + 1, remaining - 1));
        }
        return memo[start][remaining] = ans;
    }

    return dfs(0, k);       
}
