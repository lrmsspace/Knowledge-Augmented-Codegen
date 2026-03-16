// Source: https://leetcode.com/problems/minimum-array-changes-to-make-differences-equal/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums of size n where n is even, and an integer k.
//
// You can perform some changes on the array, where in one change you can replace any element in the array with any integer in the range from 0 to k.
//
// You need to perform some changes (possibly none) such that the final array satisfies the following condition:
//
//
// 	There exists an integer X such that abs(a[i] - a[n - i - 1]) = X for all (0 <= i < n).
//
//
// Return the minimum number of changes required to satisfy the above condition.
//
// Example:
// Input: nums = [1,0,1,2,4,3], k = 4
//
// Output: 2
//
// Explanation:
// We can perform the following changes:
//
//
// 	Replace nums[1] by 2. The resulting array is nums = [1,2,1,2,4,3].
// 	Replace nums[3] by 3. The resulting array is nums = [1,2,1,3,4,3].
//
//
// The integer X will be 2.
//
// Constraints:
// 2 <= n == nums.length <= 105
// 	n is even.
// 	0 <= nums[i] <= k <= 105
//
// Helpful references (internal KB):
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
// - Sqrt Decomposition (array, enumeration, difference-array)
//   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
//   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
//   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
//   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
//   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minChanges(int* nums, int numsSize, int k) {
    int* count = (int*)calloc(2 * k + 2, sizeof(int));
    for (int i = 0; i < numsSize / 2; i++) {
        int a = nums[i];
        int b = nums[numsSize - 1 - i];
        count[a + b]++;
        count[1 + min(a, b)]--;
        count[k + 1 + max(a, b)]--;
        count[k + 1 + a + b]++;
    }
    int changes = numsSize / 2;
    int minChanges = changes;
    for (int x = 2; x <= 2 * k; x++) {
        changes += count[x];
        if (changes < minChanges) {
            minChanges = changes;
        }
    }
    free(count);
    return minChanges;      
}
