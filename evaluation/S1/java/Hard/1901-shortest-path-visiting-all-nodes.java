// Source: https://leetcode.com/problems/shortest-path-visiting-all-nodes/   |   Difficulty: Hard
//
// Problem Description:
// You have an undirected, connected graph of n nodes labeled from 0 to n - 1. You are given an array graph where graph[i] is a list of all the nodes connected with node i by an edge.
//
// Return the length of the shortest path that visits every node. You may start and stop at any node, you may revisit nodes multiple times, and you may reuse edges.
//
// Example:
// Input: graph = [[1,2,3],[0],[0],[0]]
// Output: 4
// Explanation: One possible path is [1,0,2,0,3]
//
// Constraints:
// n == graph.length
// 	1 <= n <= 12
// 	0 <= graph[i].length < n
// 	graph[i] does not contain i.
// 	If graph[a] contains b, then graph[b] contains a.
// 	The input graph is always connected.
//
// Helpful references (internal KB):
// - Breadth-first search (graph, queue, array, bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes level by level. It is also suitable for problems requiring traversal of all nodes at a specific distance from a source.
//   • Idea: Breadth-first search systematically explores a graph level by level, ensuring that all nodes at distance k are visited before any nodes at distance k+1. It finds the shortest path in terms of number of edges for unweighted graphs in O(V + E) time.
//   • Invariants: All nodes currently in the queue have been discovered and marked, but their adjacent nodes have not yet been fully explored.; For any node v marked as visited, distTo[v] stores the shortest path length from the source s to v.
//   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect paths.; Not handling disconnected graphs correctly.
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
    public int shortestPathLength(int[][] graph) {
        int n = graph.length;
        int endingMask = (1 << n) - 1;
        boolean[][] visited = new boolean[n][1 << n];
        Queue<int[]> queue = new LinkedList<>();

        for (int i = 0; i < n; i++) {
            int mask = 1 << i;
            queue.offer(new int[]{i, mask, 0});
            visited[i][mask] = true;
        }

        while (!queue.isEmpty()) {
            int[] curr = queue.poll();
            int node = curr[0];
            int mask = curr[1];
            int dist = curr[2];

            if (mask == endingMask) {
                return dist;
            }

            for (int neighbor : graph[node]) {
                int nextMask = mask | (1 << neighbor);
                if (!visited[neighbor][nextMask]) {
                    visited[neighbor][nextMask] = true;
                    queue.offer(new int[]{neighbor, nextMask, dist + 1});
                }
            }
        }

        return -1; // This line should never be reached since the graph is connected.           
    }
}
