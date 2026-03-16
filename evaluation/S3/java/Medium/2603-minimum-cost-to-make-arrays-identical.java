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
// - Sqrt Decomposition (array, enumeration, difference-array)
//   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
//   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
//   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
//   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
//   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
// - Sqrt Decomposition (array, enumeration, prefix-sum)
//   • When to use: Use when frequent range queries and point/range updates are needed on an array, offering a balanced O(sqrt(N)) time complexity for both operations. It's a good alternative when a segment tree is too complex or overkill.
//   • Idea: Sqrt decomposition divides an array into blocks of size approximately sqrt(N) to optimize range queries and updates. It achieves an O(sqrt(N)) time complexity for both query and update operations.
//   • Invariants: Each block maintains an up-to-date aggregate of its elements.; For any query, fully contained blocks are processed using their precomputed aggregates.
//   • Tips: Choose block size carefully, typically sqrt(N) for optimal balance.; Precompute block aggregates (sum, min, max) for efficient queries.
//   • Pitfalls: Incorrectly handling partial blocks or boundary conditions.; Off-by-one errors in block indices or element indices within blocks.
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
        long totalCost = 0;

        // Calculate the cost of making arr identical to brr without any splits
        for (int i = 0; i < n; i++) {
            totalCost += Math.abs(arr[i] - brr[i]);
        }

        // If the cost of rearranging is less than the cost of adjustments, consider rearranging
        if (k < totalCost) {
            // Sort both arrays to minimize the cost of adjustments after rearrangement
            Arrays.sort(arr);
            Arrays.sort(brr);

            long rearrangementCost = k;
            for (int i = 0; i < n; i++) {
                rearrangementCost += Math.abs(arr[i] - brr[i]);
            }

            // Choose the minimum cost between rearrangement and direct adjustments
            return Math.min(totalCost, rearrangementCost);
        }

        return totalCost;           
    }
}
