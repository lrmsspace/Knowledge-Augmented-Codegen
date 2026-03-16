// Source: https://leetcode.com/problems/shortest-path-with-alternating-colors/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n, the number of nodes in a directed graph where the nodes are labeled from 0 to n - 1. Each edge is red or blue in this graph, and there could be self-edges and parallel edges.
//
// You are given two arrays redEdges and blueEdges where:
//
//
// 	redEdges[i] = [ai, bi] indicates that there is a directed red edge from node ai to node bi in the graph, and
// 	blueEdges[j] = [uj, vj] indicates that there is a directed blue edge from node uj to node vj in the graph.
//
//
// Return an array answer of length n, where each answer[x] is the length of the shortest path from node 0 to node x such that the edge colors alternate along the path, or -1 if such a path does not exist.
//
// Example:
// Input: n = 3, redEdges = [[0,1],[1,2]], blueEdges = []
// Output: [0,1,-1]
//
// Constraints:
// 1 <= n <= 100
// 	0 <= redEdges.length, blueEdges.length <= 400
// 	redEdges[i].length == blueEdges[j].length == 2
// 	0 <= ai, bi, uj, vj < n
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
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] shortestAlternatingPaths(int n, int[][] redEdges, int[][] blueEdges) {
        // Create adjacency lists for red and blue edges
        List<List<Integer>> redAdj = new ArrayList<>();
        List<List<Integer>> blueAdj = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            redAdj.add(new ArrayList<>());
            blueAdj.add(new ArrayList<>());
        }
        for (int[] edge : redEdges) {
            redAdj.get(edge[0]).add(edge[1]);
        }
        for (int[] edge : blueEdges) {
            blueAdj.get(edge[0]).add(edge[1]);
        }

        // Result array initialized to -1
        int[] result = new int[n];
        Arrays.fill(result, -1);
        result[0] = 0;

        // BFS queue: each element is [node, color, distance]
        Queue<int[]> queue = new LinkedList<>();
        queue.offer(new int[]{0, 0, 0}); // Start with red edge
        queue.offer(new int[]{0, 1, 0}); // Start with blue edge

        // Visited array to avoid cycles: visited[node][color]
        boolean[][] visited = new boolean[n][2];
        visited[0][0] = true;
        visited[0][1] = true;

        while (!queue.isEmpty()) {
            int[] current = queue.poll();
            int node = current[0];
            int color = current[1];
            int distance = current[2];

            // Determine next edges based on current color
            List<List<Integer>> nextAdj = (color == 0) ? blueAdj : redAdj;
            int nextColor = 1 - color;

            for (int neighbor : nextAdj.get(node)) {
                if (!visited[neighbor][nextColor]) {
                    visited[neighbor][nextColor] = true;
                    queue.offer(new int[]{neighbor, nextColor, distance + 1});
                    if (result[neighbor] == -1) {
                        result[neighbor] = distance + 1;
                    }
                }
            }
        }

        return result;          
    }
}
