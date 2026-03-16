// Source: https://leetcode.com/problems/k-closest-points-to-origin/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane and an integer k, return the k closest points to the origin (0, 0).
//
// The distance between two points on the X-Y plane is the Euclidean distance (i.e., √(x1 - x2)2 + (y1 - y2)2).
//
// You may return the answer in any order. The answer is guaranteed to be unique (except for the order that it is in).
//
// Example:
// Input: points = [[1,3],[-2,2]], k = 1
// Output: [[-2,2]]
// Explanation:
// The distance between (1, 3) and the origin is sqrt(10).
// The distance between (-2, 2) and the origin is sqrt(8).
// Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
// We only want the closest k = 1 points from the origin, so the answer is just [[-2,2]].
//
// Constraints:
// 1 <= k <= points.length <= 104
// 	-104 <= xi, yi <= 104
//
// Helpful references (internal KB):
// - kth-largest-element-in-an-array (heap, array, heap-select)
//   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
//   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
//   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
//   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
//   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
// - Finding the nearest pair of points (geometry, array, divide-and-conquer)
//   • When to use: Use this algorithm to efficiently find the pair of points with the minimum Euclidean distance among a given set of N points in a 2D plane. It is particularly effective for large datasets where an O(N^2) approach is too slow.
//   • Idea: This divide-and-conquer algorithm finds the closest pair of points in a 2D plane by recursively splitting the set of points and merging results. It achieves an optimal time complexity of O(N log N).
//   • Invariants: At the start of any recursive call, the input point set is sorted by X-coordinate.; The returned minimum distance 'd' for a subproblem is the true minimum distance among its points.
//   • Tips: Initial sorting by X-coordinate is crucial for efficient division of the point set.; Handle base cases (e.g., 2 or 3 points) with a simple brute-force distance calculation.
//   • Pitfalls: Forgetting to sort points by Y-coordinate within the central strip can degrade performance to O(N^2).; Incorrectly defining the strip width or comparison range in the merge step can lead to incorrect results.
// - Finding the Eulerian path in O(M) (graph, enumeration, bfs)
//   • When to use: Use when the problem requires visiting every edge in a graph exactly once, either starting and ending at the same vertex (cycle) or at two different vertices (path).
//   • Idea: An Eulerian path is a trail in a graph which visits every edge exactly once. An Eulerian cycle is an Eulerian path that starts and ends on the same vertex.
//   • Invariants: Every edge in the graph is considered exactly once for inclusion in the path.; The current path segment always forms a valid trail in the graph.
//   • Tips: Check vertex degrees to determine path/cycle existence before attempting to find it.; For an Eulerian path, start traversal from one of the two odd-degree vertices.
//   • Pitfalls: Incorrectly handling multi-edges or self-loops can lead to errors in degree calculation or traversal.; Failing to check graph connectivity can result in incomplete paths or infinite loops.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private int distanceSquared(int[] point) {
        return point[0] * point[0] + point[1] * point[1];
    }
    public int[][] kClosest(int[][] points, int k) {
        java.util.PriorityQueue<int[]> maxHeap = new java.util.PriorityQueue<>(
            (a, b) -> Integer.compare(distanceSquared(b), distanceSquared(a))
        );

        for (int[] point : points) {
            maxHeap.offer(point);
            if (maxHeap.size() > k) {
                maxHeap.poll();
            }
        }

        int[][] result = new int[k][2];
        for (int i = 0; i < k; i++) {
            result[i] = maxHeap.poll();
        }

        return result;          
    }
}
