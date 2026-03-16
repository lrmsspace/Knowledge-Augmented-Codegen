// Source: https://leetcode.com/problems/minimum-score-by-changing-two-elements/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums.
//
//
// 	The low score of nums is the minimum absolute difference between any two integers.
// 	The high score of nums is the maximum absolute difference between any two integers.
// 	The score of nums is the sum of the high and low scores.
//
//
// Return the minimum score after changing two elements of nums.
//
// Example:
// Input: nums = [1,4,7,8,5]
//
// Output: 3
//
// Explanation:
//
//
// 	Change nums[0] and nums[1] to be 6 so that nums becomes [6,6,7,8,5].
// 	The low score is the minimum absolute difference: |6 - 6| = 0.
// 	The high score is the maximum absolute difference: |8 - 5| = 3.
// 	The sum of high and low score is 3.
//
// Constraints:
// 3 <= nums.length <= 105
// 	1 <= nums[i] <= 109
//
// Helpful references (internal KB):
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
// - Range Minimum Query (array, bitset, bit-fenwick)
//   • When to use: When you need to efficiently query the minimum value within a range and perform point updates on an array. It's suitable for scenarios requiring logarithmic time complexity for both operations.
//   • Idea: A Fenwick tree (BIT) can be adapted to answer Range Minimum Queries and perform point updates in O(log N) time. It achieves this by storing prefix minimums in a tree-like structure, allowing efficient aggregation.
//   • Invariants: Each node `tree[i]` stores the minimum of a specific range `[i - (i & -i) + 1, i]`.; An update to `arr[idx]` correctly propagates the new minimum to all relevant `tree` nodes.
//   • Tips: Adapt standard BIT operations for minimums instead of sums.; Use `min(current_value, new_value)` for updates and queries.
//   • Pitfalls: Standard BIT operations are for sums; direct application for minimums is incorrect.; Querying a range `[L, R]` for minimum is not a simple `query(R) - query(L-1)`.
// - Finding the nearest pair of points (geometry, array, divide-and-conquer, merge-sort, two-pointers)
//   • When to use: Use this when finding the pair of points with the minimum Euclidean distance in a 2D plane. It efficiently handles large datasets by recursively dividing the problem and merging results.
//   • Idea: It finds the closest pair of points in a 2D plane by recursively dividing the set, solving subproblems, and merging results in O(N log N) time. The merge step efficiently handles cross-boundary pairs within a narrow strip.
//   • Invariants: The minimum distance returned by a recursive call is the true minimum for its input subset.; All points in the left subproblem have x-coordinates less than or equal to the median x-coordinate.
//   • Tips: Pre-sort points by x-coordinate to enable efficient splitting.; Maintain a y-sorted list of points for efficient merging of the strip.
//   • Pitfalls: An inefficient merge step can degrade complexity from O(N log N) to O(N^2).; Failing to correctly identify and process cross-boundary pairs.
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
var minimizeSum = function(nums) {
    nums.sort((a, b) => a - b);
    const n = nums.length;
    const option1 = nums[n - 1] - nums[2]; // Change the two smallest elements to the third smallest
    const option2 = nums[n - 3] - nums[0]; // Change the two largest elements to the third largest
    const option3 = nums[n - 2] - nums[1]; // Change the smallest and largest elements to the second smallest and second largest
    return Math.min(option1, option2, option3);
};
