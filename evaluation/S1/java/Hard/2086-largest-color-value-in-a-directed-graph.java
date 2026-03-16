// Source: https://leetcode.com/problems/largest-color-value-in-a-directed-graph/   |   Difficulty: Hard
//
// Problem Description:
// There is a directed graph of n colored nodes and m edges. The nodes are numbered from 0 to n - 1.
//
// You are given a string colors where colors[i] is a lowercase English letter representing the color of the ith node in this graph (0-indexed). You are also given a 2D array edges where edges[j] = [aj, bj] indicates that there is a directed edge from node aj to node bj.
//
// A valid path in the graph is a sequence of nodes x1 -> x2 -> x3 -> ... -> xk such that there is a directed edge from xi to xi+1 for every 1 <= i < k. The color value of the path is the number of nodes that are colored the most frequently occurring color along that path.
//
// Return the largest color value of any valid path in the given graph, or -1 if the graph contains a cycle.
//
// Example:
// Input: colors = "abaca", edges = [[0,1],[0,2],[2,3],[3,4]]
// Output: 3
// Explanation: The path 0 -> 2 -> 3 -> 4 contains 3 nodes that are colored "a" (red in the above image).
//
// Constraints:
// n == colors.length
// 	m == edges.length
// 	1 <= n <= 105
// 	0 <= m <= 105
// 	colors consists of lowercase English letters.
// 	0 <= aj, bj < n
//
// Helpful references (internal KB):
// - Checking a graph for acyclicity and finding a cycle in O(M) (graph, array, dfs)
//   • When to use: Use when needing to determine if a graph contains any cycles or to identify one such cycle. It is applicable to both directed and undirected graphs.
//   • Idea: This algorithm uses Depth First Search to detect cycles in a graph by tracking visited states of nodes during traversal. It runs in O(V + E) time, where V is the number of vertices and E is the number of edges.
//   • Invariants: All nodes currently on the DFS recursion stack are marked as 'gray' (or equivalent).; All nodes fully explored and not part of the current path are marked as 'black' (or equivalent).
//   • Tips: For directed graphs, use a three-color scheme (white, gray, black) to distinguish states.; For undirected graphs, a simple visited array and checking against the immediate parent is sufficient.
//   • Pitfalls: Incorrectly handling the parent edge in undirected graphs can lead to false cycle detections.; Failing to distinguish between nodes currently in the recursion stack (gray) and fully processed nodes (black) in directed graphs.
// - Check whether a graph is bipartite (graph, queue, bfs)
//   • When to use: Use this when you need to determine if an undirected graph can be divided into two independent sets such that all edges connect vertices from different sets, or if it is two-colorable.
//   • Idea: This algorithm determines if an undirected graph is bipartite by attempting to 2-color it using BFS. It assigns alternating colors (or sets) to adjacent vertices, detecting non-bipartite conditions if an edge connects two vertices of the same color.
//   • Invariants: All visited vertices within the current BFS component are correctly 2-colored.; All edges processed so far connect vertices of different colors.
//   • Tips: Use two distinct colors (e.g., 0 and 1) to represent the two sets.; Iterate through all vertices and start a new BFS from any unvisited vertex to handle disconnected components.
//   • Pitfalls: Forgetting to handle disconnected graphs by ensuring all vertices are visited.; Incorrectly assigning colors, leading to false positives or negatives.
// - Shortest Paths (graph, queue, bellman-ford)
//   • When to use: Use when finding single-source shortest paths in edge-weighted digraphs that may contain negative edge weights, or to detect negative cycles. It can also be adapted for longest paths in DAGs.
//   • Idea: The Bellman-Ford algorithm solves the single-source shortest paths problem in edge-weighted digraphs, even with negative edge weights, or detects negative cycles. Its worst-case time complexity is O(V*E).
//   • Invariants: For any vertex v, distTo[v] is always an upper bound on the shortest path distance from the source s to v.; If distTo[v] is finite, there exists a path from s to v of length distTo[v].
//   • Tips: Use a queue-based optimization (SPFA) for better average-case performance.; It can detect the presence of negative cycles reachable from the source.
//   • Pitfalls: Shortest paths are undefined if a negative cycle is reachable from the source.; O(V*E) worst-case time complexity can be prohibitive for large, dense graphs.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int largestPathValue(String colors, int[][] edges) {
        int n = colors.length();
        List<List<Integer>> graph = new ArrayList<>();
        int[] inDegree = new int[n];

        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }

        for (int[] edge : edges) {
            graph.get(edge[0]).add(edge[1]);
            inDegree[edge[1]]++;
        }

        int[][] colorCount = new int[n][26];
        Queue<Integer> queue = new LinkedList<>();

        for (int i = 0; i < n; i++) {
            if (inDegree[i] == 0) {
                queue.offer(i);
                colorCount[i][colors.charAt(i) - 'a'] = 1;
            }
        }

        int visitedNodes = 0;
        int maxColorValue = 0;

        while (!queue.isEmpty()) {
            int node = queue.poll();
            visitedNodes++;

            for (int count : colorCount[node]) {
                maxColorValue = Math.max(maxColorValue, count);
            }

            for (int neighbor : graph.get(node)) {
                for (int c = 0; c < 26; c++) {
                    colorCount[neighbor][c] = Math.max(colorCount[neighbor][c],
                            colorCount[node][c] + (colors.charAt(neighbor) - 'a' == c ? 1 : 0));
                }

                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0) {
                    queue.offer(neighbor);
                }
            }
        }

        return visitedNodes == n ? maxColorValue : -1;          
    }
}
