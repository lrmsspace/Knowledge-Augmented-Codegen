// Source: https://leetcode.com/problems/k-th-nearest-obstacle-queries/   |   Difficulty: Medium
//
// Problem Description:
// There is an infinite 2D plane.
//
// You are given a positive integer k. You are also given a 2D array queries, which contains the following queries:
//
//
// 	queries[i] = [x, y]: Build an obstacle at coordinate (x, y) in the plane. It is guaranteed that there is no obstacle at this coordinate when this query is made.
//
//
// After each query, you need to find the distance of the kth nearest obstacle from the origin.
//
// Return an integer array results where results[i] denotes the kth nearest obstacle after query i, or results[i] == -1 if there are less than k obstacles.
//
// Note that initially there are no obstacles anywhere.
//
// The distance of an obstacle at coordinate (x, y) from the origin is given by |x| + |y|.
//
// Example:
// Input: queries = [[1,2],[3,4],[2,3],[-3,0]], k = 2
//
// Output: [-1,7,5,3]
//
// Explanation:
//
//
// 	Initially, there are 0 obstacles.
// 	After queries[0], there are less than 2 obstacles.
// 	After queries[1], there are obstacles at distances 3 and 7.
// 	After queries[2], there are obstacles at distances 3, 5, and 7.
// 	After queries[3], there are obstacles at distances 3, 3, 5, and 7.
//
// Constraints:
// 1 <= queries.length <= 2 * 105
// 	All queries[i] are unique.
// 	-109 <= queries[i][0], queries[i][1] <= 109
// 	1 <= k <= 105
//
// Helpful references (internal KB):
// - kth-largest-element-in-an-array (heap, array, heap-select)
//   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
//   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
//   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
//   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
//   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
// - Point location in O(logn) (geometry, ds, simulation)
//   • When to use: Use when needing to efficiently determine which region (face or edge) of a planar subdivision a given query point lies within, especially for multiple online queries.
//   • Idea: This algorithm preprocesses a planar subdivision to answer point location queries in logarithmic time. It typically involves building a specialized data structure, possibly persistent, to quickly identify the containing face or edge for any given point.
//   • Invariants: The search process always maintains the invariant that the query point is within the current candidate region.; After each step, the search space for the point's location is reduced by a constant factor.
//   • Tips: Use a suitable geometric data structure like a trapezoidal map or persistent segment tree.; Carefully handle points lying exactly on edges or vertices.
//   • Pitfalls: Degenerate cases (vertical edges, collinear points) require careful handling.; Floating-point precision errors can lead to incorrect classifications.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} queries
 * @param {number} k
 * @return {number[]}
 */
var resultsArray = function(queries, k) {
    const maxHeap = new MaxPriorityQueue();
    const results = [];

    for (const [x, y] of queries) {
        const distance = Math.abs(x) + Math.abs(y);
        maxHeap.enqueue(distance);

        if (maxHeap.size() < k) {
            results.push(-1);
        } else {
            while (maxHeap.size() > k) {
                maxHeap.dequeue();
            }
            results.push(maxHeap.front().element);
        }
    }

    return results;
};
