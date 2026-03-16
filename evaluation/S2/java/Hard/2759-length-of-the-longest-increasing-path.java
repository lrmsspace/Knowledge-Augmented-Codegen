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
// - Longest increasing subsequence (array, dp-1d, counting, segment-tree)
//   • When to use: Use when seeking the longest possible sequence of elements from a given array such that each element is greater than the preceding one, preserving their original relative order.
//   • Idea: The Longest Increasing Subsequence (LIS) problem identifies the longest possible subsequence where elements are in strictly increasing order, preserving their original relative positions. It can be solved efficiently in O(N log N) time using dynamic programming with binary search or a segment tree.
//   • Invariants: The `tails` array elements are always strictly increasing.; For any index `k`, `tails[k]` holds the smallest possible ending element of an increasing subsequence of length `k+1`.
//   • Tips: Use a `tails` array to store the smallest ending element for LIS of each length.; Employ binary search on the `tails` array to update or extend subsequences.
//   • Pitfalls: Confusing subsequence (relative order) with contiguous subarray.; Incorrectly implementing strict vs. non-strict increasing conditions.
// - Manhattan Distance (geometry, graph, sweep-line, mst-kruskal, coordinate-compress)
//   • When to use: Use this when finding the Minimum Spanning Tree for points in a 2D plane where edge weights are Manhattan distances, or when a geometric problem can be simplified by transforming Manhattan to Chebyshev distance.
//   • Idea: This algorithm finds the Minimum Spanning Tree for points in a 2D plane using Manhattan distance. It leverages a sweep-line approach to efficiently find nearest neighbors in specific octants, reducing the number of candidate edges for Kruskal's algorithm, achieving O(N log N) complexity.
//   • Invariants: For any point 's' in the active set, its nearest neighbor in the current octant has not yet been processed.; Points are processed in non-decreasing order of 'x + y' (or transformed coordinate), ensuring local optimality for distances.
//   • Tips: Consider transforming Manhattan distance problems into Chebyshev distance problems using (x+y, y-x) coordinates.; Divide the plane into 8 octants around each point to simplify nearest neighbor searches.
//   • Pitfalls: Incorrectly defining or handling the 8 octants, especially near boundaries or for points with equal coordinates.; Inefficiently managing the 'active set' during the sweep-line, leading to higher than O(N log N) complexity.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
//   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
//   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
//   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
//   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
//   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
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
        int[][] points = new int[n][3];
        for (int i = 0; i < n; i++) {
            points[i][0] = coordinates[i][0];
            points[i][1] = coordinates[i][1];
            points[i][2] = i;
        }
        Arrays.sort(points, Comparator.comparingInt(a -> a[0]));

        TreeMap<Integer, Integer> activeSet = new TreeMap<>();
        int maxLength = 1;

        for (int[] point : points) {
            int x = point[0], y = point[1], index = point[2];
            if (index == k) {
                maxLength = Math.max(maxLength, 1);
            }
            Integer prevYKey = activeSet.lowerKey(y);
            if (prevYKey != null) {
                int lengthAtPrevY = activeSet.get(prevYKey);
                int currentLength = lengthAtPrevY + 1;
                maxLength = Math.max(maxLength, currentLength);
                activeSet.put(y, Math.max(activeSet.getOrDefault(y, 0), currentLength));
            } else {
                activeSet.put(y, Math.max(activeSet.getOrDefault(y, 0), 1));
            }
        }

        return maxLength;           
    }
}
