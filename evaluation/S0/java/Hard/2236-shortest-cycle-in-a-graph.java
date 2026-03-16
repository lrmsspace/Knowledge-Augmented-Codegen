// Source: https://leetcode.com/problems/shortest-cycle-in-a-graph/   |   Difficulty: Hard
//
// Problem Description:
// There is a bi-directional graph with n vertices, where each vertex is labeled from 0 to n - 1. The edges in the graph are represented by a given 2D integer array edges, where edges[i] = [ui, vi] denotes an edge between vertex ui and vertex vi. Every vertex pair is connected by at most one edge, and no vertex has an edge to itself.
//
// Return the length of the shortest cycle in the graph. If no cycle exists, return -1.
//
// A cycle is a path that starts and ends at the same node, and each edge in the path is used only once.
//
// Example:
// Input: n = 7, edges = [[0,1],[1,2],[2,0],[3,4],[4,5],[5,6],[6,3]]
// Output: 3
// Explanation: The cycle with the smallest length is : 0 -> 1 -> 2 -> 0
//
// Constraints:
// 2 <= n <= 1000
// 	1 <= edges.length <= 1000
// 	edges[i].length == 2
// 	0 <= ui, vi < n
// 	ui != vi
// 	There are no repeated edges.
//

class Solution {
    public int findShortestCycle(int n, int[][] edges) {
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0]).add(edge[1]);
            graph.get(edge[1]).add(edge[0]);
        }

        int shortestCycle = Integer.MAX_VALUE;

        for (int start = 0; start < n; start++) {
            Queue<int[]> queue = new LinkedList<>();
            queue.offer(new int[]{start, -1});
            int[] distance = new int[n];
            Arrays.fill(distance, Integer.MAX_VALUE);
            distance[start] = 0;

            while (!queue.isEmpty()) {
                int[] current = queue.poll();
                int node = current[0];
                int parent = current[1];

                for (int neighbor : graph.get(node)) {
                    if (distance[neighbor] == Integer.MAX_VALUE) {
                        distance[neighbor] = distance[node] + 1;
                        queue.offer(new int[]{neighbor, node});
                    } else if (neighbor != parent) {
                        shortestCycle = Math.min(shortestCycle, distance[node] + distance[neighbor] + 1);
                    }
                }
            }
        }

        return shortestCycle == Integer.MAX_VALUE ? -1 : shortestCycle;         
    }
}
