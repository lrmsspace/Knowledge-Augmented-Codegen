// Source: https://leetcode.com/problems/visit-array-positions-to-maximize-score/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums and a positive integer x.
//
// You are initially at position 0 in the array and you can visit other positions according to the following rules:
//
//
// 	If you are currently in position i, then you can move to any position j such that i < j.
// 	For each position i that you visit, you get a score of nums[i].
// 	If you move from a position i to a position j and the parities of nums[i] and nums[j] differ, then you lose a score of x.
//
//
// Return the maximum total score you can get.
//
// Note that initially you have nums[0] points.
//
// Example:
// Input: nums = [2,3,6,1,9,2], x = 5
// Output: 13
// Explanation: We can visit the following positions in the array: 0 -> 2 -> 3 -> 4.
// The corresponding values are 2, 6, 1 and 9. Since the integers 6 and 1 have different parities, the move 2 -> 3 will make you lose a score of x = 5.
// The total score will be: 2 + 6 + 1 + 9 - 5 = 13.
//
// Constraints:
// 2 <= nums.length <= 105
// 	1 <= nums[i], x <= 106
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public long maxScore(int[] nums, int x) {
        long evenMax = nums[0] % 2 == 0 ? nums[0] : Long.MIN_VALUE;
        long oddMax = nums[0] % 2 == 1 ? nums[0] : Long.MIN_VALUE;

        for (int i = 1; i < nums.length; i++) {
            if (nums[i] % 2 == 0) {
                evenMax = Math.max(evenMax, oddMax - x + nums[i]);
                oddMax = Math.max(oddMax, evenMax - x + nums[i]);
            } else {
                oddMax = Math.max(oddMax, evenMax - x + nums[i]);
                evenMax = Math.max(evenMax, oddMax - x + nums[i]);
            }
        }

        return Math.max(evenMax, oddMax);           
    }
}
