// Source: https://leetcode.com/problems/minimum-cost-to-make-arrays-identical/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integer arrays arr and brr of length n, and an integer k. You can perform the following operations on arr any number of times:
//
//
// 	Split arr into any number of contiguous subarrays and rearrange these subarrays in any order. This operation has a fixed cost of k.
// 	
// 	Choose any element in arr and add or subtract a positive integer x to it. The cost of this operation is x.
// 	
//
//
// Return the minimum total cost to make arr equal to brr.
//
// Example:
// Input: arr = [-7,9,5], brr = [7,-2,-5], k = 2
//
// Output: 13
//
// Explanation:
//
//
// 	Split arr into two contiguous subarrays: [-7] and [9, 5] and rearrange them as [9, 5, -7], with a cost of 2.
// 	Subtract 2 from element arr[0]. The array becomes [7, 5, -7]. The cost of this operation is 2.
// 	Subtract 7 from element arr[1]. The array becomes [7, -2, -7]. The cost of this operation is 7.
// 	Add 2 to element arr[2]. The array becomes [7, -2, -5]. The cost of this operation is 2.
//
//
// The total cost to make the arrays equal is 2 + 2 + 7 + 2 = 13.
//
// Constraints:
// 1 <= arr.length == brr.length <= 105
// 	0 <= k <= 2 * 1010
// 	-105 <= arr[i] <= 105
// 	-105 <= brr[i] <= 105
//
// Helpful references (internal KB):
// - Knuth's Optimization (array, interval, dp-2d)
//   • When to use: Used to optimize certain 2D dynamic programming problems, typically interval DP, where the cost function satisfies the quadrangle inequality and the optimal split points exhibit monotonicity.
//   • Idea: Knuth's Optimization reduces the time complexity of certain 2D DP problems from O(N^3) to O(N^2) by restricting the search range for the optimal split point. This is applicable when the cost function satisfies the quadrangle inequality and the optimal split points are monotonic.
//   • Invariants: dp[i][j] stores the minimum cost for the interval [i, j].; opt[i][j] stores the optimal split point k for dp[i][j].
//   • Tips: Verify the quadrangle inequality for the cost function C(a,c) + C(b,d) <= C(a,d) + C(b,c).; Ensure the optimal split points opt[i][j] are monotonic: opt[i][j-1] <= opt[i][j] <= opt[i+1][j].
//   • Pitfalls: Incorrectly assuming quadrangle inequality holds for the cost function.; Improper iteration order for DP states, which breaks the opt dependency.
// - kth-largest-element-in-an-array (array, merge-sort)
//   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
//   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
//   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
//   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
//   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
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
    public long minCost(int[] arr, int[] brr, long k) {
        int n = arr.length;
        long cost = 0;
        for (int i = 0; i < n; i++) {
            cost += Math.abs(arr[i] - brr[i]);
        }
        return Math.min(cost, k);           
    }
}
