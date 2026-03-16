// Source: https://leetcode.com/problems/length-of-the-longest-increasing-path/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D array of integers coordinates of length n and an integer k, where 0 <= k < n.
//
// coordinates[i] = [xi, yi] indicates the point (xi, yi) in a 2D plane.
//
// An increasing path of length m is defined as a list of points (x1, y1), (x2, y2), (x3, y3), ..., (xm, ym) such that:
//
//
// 	xi < xi + 1 and yi < yi + 1 for all i where 1 <= i < m.
// 	(xi, yi) is in the given coordinates for all i where 1 <= i <= m.
//
//
// Return the maximum length of an increasing path that contains coordinates[k].
//
// Example:
// Input: coordinates = [[3,1],[2,2],[4,1],[0,0],[5,3]], k = 1
//
// Output: 3
//
// Explanation:
//
// (0, 0), (2, 2), (5, 3) is the longest increasing path that contains (2, 2).
//
// Constraints:
// 1 <= n == coordinates.length <= 105
// 	coordinates[i].length == 2
// 	0 <= coordinates[i][0], coordinates[i][1] <= 109
// 	All elements in coordinates are distinct.
// 	0 <= k <= n - 1
//
// Helpful references (internal KB):
// - Longest Increasing Subsequence (array, coordinate-compress, segment-tree, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements must be strictly increasing. It is applicable for problems requiring optimal substructure on sequences with an increasing property.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of a given sequence such that all elements of the subsequence are in increasing order. It can be solved in O(N log N) time using dynamic programming with binary search or a segment tree with coordinate compression.
//   • Invariants: The `dp` array (or segment tree) stores information about the smallest ending element for increasing subsequences of various lengths.; The `dp` array, if used, remains sorted in strictly increasing order.
//   • Tips: The O(N log N) solution uses a `dp` array storing the smallest ending element for all increasing subsequences of a given length.; Binary search (`lower_bound`) efficiently finds the correct position to update in the `dp` array.
//   • Pitfalls: Confusing subsequence with subarray, which requires contiguous elements.; Incorrectly handling duplicates; LIS typically requires strictly increasing elements.
// - Finding the Eulerian path in O(M) (graph, enumeration, bfs)
//   • When to use: Use when the problem requires visiting every edge in a graph exactly once, either starting and ending at the same vertex (cycle) or at two different vertices (path).
//   • Idea: An Eulerian path is a trail in a graph which visits every edge exactly once. An Eulerian cycle is an Eulerian path that starts and ends on the same vertex.
//   • Invariants: Every edge in the graph is considered exactly once for inclusion in the path.; The current path segment always forms a valid trail in the graph.
//   • Tips: Check vertex degrees to determine path/cycle existence before attempting to find it.; For an Eulerian path, start traversal from one of the two odd-degree vertices.
//   • Pitfalls: Incorrectly handling multi-edges or self-loops can lead to errors in degree calculation or traversal.; Failing to check graph connectivity can result in incomplete paths or infinite loops.
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
    public int maxPathLength(int[][] coordinates, int k) {
        int n = coordinates.length;
        int targetX = coordinates[k][0];
        int targetY = coordinates[k][1];

        // Separate points into four quadrants relative to the target point
        List<int[]> lowerLeft = new ArrayList<>();
        List<int[]> lowerRight = new ArrayList<>();
        List<int[]> upperLeft = new ArrayList<>();
        List<int[]> upperRight = new ArrayList<>();

        for (int i = 0; i < n; i++) {
            if (i == k) continue;
            int x = coordinates[i][0];
            int y = coordinates[i][1];
            if (x < targetX && y < targetY) {
                lowerLeft.add(new int[]{x, y});
            } else if (x < targetX && y > targetY) {
                upperLeft.add(new int[]{x, y});
            } else if (x > targetX && y < targetY) {
                lowerRight.add(new int[]{x, y});
            } else {
                upperRight.add(new int[]{x, y});
            }
        }

        // Sort each quadrant appropriately
        Comparator<int[]> comparator = Comparator.<int[]>comparingInt(p -> p[0])
                .thenComparingInt(p -> p[1]);

        lowerLeft.sort(comparator.reversed());
        upperLeft.sort((a, b) -> a[0] != b[0] ? Integer.compare(b[0], a[0]) : Integer.compare(a[1], b[1]));
        lowerRight.sort((a, b) -> a[0] != b[0] ? Integer.compare(a[0], b[0]) : Integer.compare(b[1], a[1]));
        upperRight.sort(comparator);

        // Function to compute LIS in one direction
        Function<List<int[]>, int[]> computeLIS = (points) -> {
            int m = points.size();
            int[] dp = new int[m];
            Arrays.fill(dp, 1);
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < i; j++) {
                    if (points.get(j)[1] < points.get(i)[1]) {
                        dp[i] = Math.max(dp[i], dp[j] + 1);
                    }
                }
            }
            return dp;
        };

        int[] lisLowerLeft = computeLIS.apply(lowerLeft);
        int[] lisUpperLeft = computeLIS.apply(upperLeft);
        int[] lisLowerRight = computeLIS.apply(lowerRight);
        int[] lisUpperRight = computeLIS.apply(upperRight);
        int maxLength = 1; // At least the target point itself
        for (int len : lisLowerLeft) {
            maxLength = Math.max(maxLength, len + 1);
        }
        for (int len : lisUpperLeft) {
            maxLength = Math.max(maxLength, len + 1);
        }
        for (int len : lisLowerRight) {
            maxLength = Math.max(maxLength, len + 1);
        }
        for (int len : lisUpperRight) {
            maxLength = Math.max(maxLength, len + 1);
        }
        return maxLength;
    }
}
