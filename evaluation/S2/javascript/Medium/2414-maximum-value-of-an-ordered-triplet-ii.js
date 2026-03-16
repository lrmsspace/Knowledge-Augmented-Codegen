// Source: https://leetcode.com/problems/maximum-value-of-an-ordered-triplet-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums.
//
// Return the maximum value over all triplets of indices (i, j, k) such that i < j < k. If all such triplets have a negative value, return 0.
//
// The value of a triplet of indices (i, j, k) is equal to (nums[i] - nums[j]) * nums[k].
//
// Example:
// Input: nums = [12,6,1,2,7]
// Output: 77
// Explanation: The value of the triplet (0, 2, 4) is (nums[0] - nums[2]) * nums[4] = 77.
// It can be shown that there are no ordered triplets of indices with a value greater than 77.
//
// Constraints:
// 3 <= nums.length <= 105
// 	1 <= nums[i] <= 106
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - Convex hull trick and Li Chao tree (geometry, array, sweep-line, binary-search)
//   • When to use: When optimizing dynamic programming states that involve minimizing or maximizing linear functions, especially when slopes are monotonic or queries can be processed offline.
//   • Idea: Convex Hull Trick optimizes dynamic programming problems by maintaining a lower (or upper) convex hull of linear functions. It allows efficient querying of the minimum (or maximum) value of these functions at a given point, typically achieving O(N log N) or O(N) complexity.
//   • Invariants: The set of active lines always forms a lower (or upper) convex hull.; Lines within the hull are ordered by their slopes.
//   • Tips: Sort lines by slope for O(N) or O(N log N) insertion.; Use a deque for O(N) CHT when both slopes and query points are monotonic.
//   • Pitfalls: Incorrectly assuming monotonicity of slopes or query points.; Floating point precision issues when dealing with intersections.
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
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
var maximumTripletValue = function(nums) {
    let maxTripletValue = 0;
    let maxK = 0;
    let maxIK = 0;

    for (let j = nums.length - 2; j >= 1; j--) {
        maxK = Math.max(maxK, nums[j + 1]);
        maxIK = Math.max(maxIK, nums[j] * maxK);
        maxTripletValue = Math.max(maxTripletValue, maxIK - nums[j]);
    }
    return maxTripletValue;
};
