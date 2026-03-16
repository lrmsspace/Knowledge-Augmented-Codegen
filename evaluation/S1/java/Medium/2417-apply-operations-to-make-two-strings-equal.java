// Source: https://leetcode.com/problems/apply-operations-to-make-two-strings-equal/   |   Difficulty: Medium
//
// Problem Description:
// You are given two 0-indexed binary strings s1 and s2, both of length n, and a positive integer x.
//
// You can perform any of the following operations on the string s1 any number of times:
//
//
//  Choose two indices i and j, and flip both s1[i] and s1[j]. The cost of this operation is x.
//  Choose an index i such that i < n - 1 and flip both s1[i] and s1[i + 1]. The cost of this operation is 1.
//
//
// Return the minimum cost needed to make the strings s1 and s2 equal, or return -1 if it is impossible.
//
// Note that flipping a character means changing it from 0 to 1 or vice-versa.
//
// Example:
// Input: s1 = "1100011000", s2 = "0101001010", x = 2
// Output: 4
// Explanation: We can do the following operations:
// - Choose i = 3 and apply the second operation. The resulting string is s1 = "1101111000".
// - Choose i = 4 and apply the second operation. The resulting string is s1 = "1101001000".
// - Choose i = 0 and j = 8 and apply the first operation. The resulting string is s1 = "0101001010" = s2.
// The total cost is 1 + 1 + 2 = 4. It can be shown that it is the minimum cost possible.
//
// Constraints:
// n == s1.length == s2.length
//  1 <= n, x <= 500
//  s1 and s2 consist only of the characters '0' and '1'.
//
// Helpful references (internal KB):
// - interval-dp (array, interval-dp)
//   • When to use: When a problem involves finding an optimal value for a contiguous range of elements, and solutions for larger ranges can be derived by merging optimal solutions of smaller sub-ranges.
//   • Idea: An extension of dynamic programming where subproblems are defined over contiguous intervals, solving for dp[i][j] by iterating through all possible split points k within [i, j]. This often results in O(N^3) time complexity.
//   • Invariants: dp[i][j] represents the optimal solution for the interval [i, j].; When computing dp[i][j], all subproblems dp[x][y] where y - x + 1 < j - i + 1 are already solved.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length, then by start index.
//   • Pitfalls: Off-by-one errors in interval boundaries or split points.; Incorrect iteration order, leading to uncomputed subproblems.
// - 0-1 BFS (graph, array, dijkstra, bfs)
//   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently determines minimum costs without a full priority queue.
//   • Idea: A specialized Breadth-First Search variant that finds shortest paths in graphs with only 0 or 1 edge weights. It uses a deque to process 0-weight edges before 1-weight edges, achieving O(V+E) time complexity.
//   • Invariants: All nodes currently in the deque have a distance value of either `k` or `k+1` for some integer `k`.; Nodes pushed to the front of the deque always have a distance equal to the current node's distance.
//   • Tips: Utilize a deque to maintain the order of processing nodes.; Add nodes reached via 0-weight edges to the front of the deque.
//   • Pitfalls: Incorrectly using a standard queue instead of a deque.; Failing to initialize distances to infinity for all nodes except the source.
// - Shortest Paths (array, graph, dp-1d)
//   • When to use: To find the path with the minimum total weight or cost between two vertices, or from a single source to all other reachable vertices, in an edge-weighted graph.
//   • Idea: Shortest path algorithms determine the path with the least cumulative weight between nodes in a graph. This often involves a dynamic programming approach, iteratively updating minimum distances to achieve an optimal O(V*E) or O(E log V) complexity.
//   • Invariants: distTo[v] always stores the minimum path length from the source to v discovered so far.; For any edge u -> v, if distTo[u] is final, then distTo[v] will eventually be min(distTo[v], distTo[u] + weight(u,v)).
//   • Tips: Initialize the source distance to 0 and all other distances to infinity.; Use a `distTo` array to store the current shortest distances from the source.
//   • Pitfalls: Failing to detect or handle negative cycles, which can lead to infinite loops or incorrect results.; Incorrectly initializing distances or edge relaxation logic.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minOperations(String s1, String s2, int x) {
        int n = s1.length();
        List<Integer> diffIndices = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            if (s1.charAt(i) != s2.charAt(i)) {
                diffIndices.add(i);
            }
        }

        int m = diffIndices.size();
        if (m % 2 != 0) {
            return -1;
        }

        if (x >= 2) {
            int cost = 0;
            for (int i = 0; i < m; i += 2) {
                int dist = diffIndices.get(i + 1) - diffIndices.get(i);
                if (dist == 1) {
                    cost += 1;
                } else {
                    cost += Math.min(x, dist);
                }
            }
            return cost;
        } else {
            int[][] dp = new int[m + 1][m + 1];
            for (int i = 0; i <= m; i++) {
                Arrays.fill(dp[i], Integer.MAX_VALUE / 2);
            }
            dp[0][0] = 0;

            for (int i = 1; i <= m; i++) {
                for (int j = 0; j <= i; j++) {
                    if (j > 0) {
                        dp[i][j] = Math.min(dp[i][j], dp[i - 1][j - 1]);
                    }
                    if (j < i) {
                        int dist = (j > 0) ? diffIndices.get(i - 1) - diffIndices.get(i - 2) : Integer.MAX_VALUE;
                        dp[i][j] = Math.min(dp[i][j], dp[i - 1][j + 1] + Math.min(dist, x));
                    }
                }
            }

            return dp[m][0];
        }           
    }
}
