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
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minChanges(int[] nums, int k) {
        int n = nums.length;
        int[] diff = new int[k * 2 + 2];
        int[] count = new int[k + 1];
        int pairs = n / 2;

        for (int i = 0; i < n / 2; i++) {
            int a = nums[i];
            int b = nums[n - i - 1];
            int low = Math.min(a, b) + 1;
            int high = Math.max(a, b) + k + 1;

            diff[0] += 2; // assume we change both
            diff[low] -= 1; // one change is enough from low
            diff[high] -= 1; // one change is enough up to high
            diff[k * 2 + 1] += 1; // revert back after k*2

            count[a + b]++; // count existing sums
        }

        int minChanges = Integer.MAX_VALUE;
        int currentChanges = 0;

        for (int targetSum = 0; targetSum <= k * 2; targetSum++) {
            currentChanges += diff[targetSum];
            int totalChanges = currentChanges - count[targetSum];
            minChanges = Math.min(minChanges, totalChanges);
        }

        return minChanges;          
    }
}
