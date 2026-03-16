// Source: https://leetcode.com/problems/number-of-ways-to-assign-edge-weights-i/   |   Difficulty: Medium
//
// Problem Description:
// There is an undirected tree with n nodes labeled from 1 to n, rooted at node 1. The tree is represented by a 2D integer array edges of length n - 1, where edges[i] = [ui, vi] indicates that there is an edge between nodes ui and vi.
//
// Initially, all edges have a weight of 0. You must assign each edge a weight of either 1 or 2.
//
// The cost of a path between any two nodes u and v is the total weight of all edges in the path connecting them.
//
// Select any one node x at the maximum depth. Return the number of ways to assign edge weights in the path from node 1 to x such that its total cost is odd.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// Note: Ignore all edges not in the path from node 1 to x.
//
// Example:
// Input: edges = [[1,2]]
//
// Output: 1
//
// Explanation:
//
//
// 	The path from Node 1 to Node 2 consists of one edge (1 → 2).
// 	Assigning weight 1 makes the cost odd, while 2 makes it even. Thus, the number of valid assignments is 1.
//
// Constraints:
// 2 <= n <= 105
// 	edges.length == n - 1
// 	edges[i] == [ui, vi]
// 	1 <= ui, vi <= n
// 	edges represents a valid tree.
//

class Solution {
    public int assignEdgeWeights(int[][] edges) {
        int n = edges.length + 1;
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0] - 1).add(edge[1] - 1);
            graph.get(edge[1] - 1).add(edge[0] - 1);
        }

        int maxDepth = 0;
        Queue<int[]> queue = new LinkedList<>();
        boolean[] visited = new boolean[n];
        queue.offer(new int[]{0, 0}); // {node, depth}
        visited[0] = true;

        while (!queue.isEmpty()) {
            int[] curr = queue.poll();
            int node = curr[0];
            int depth = curr[1];
            maxDepth = Math.max(maxDepth, depth);

            for (int neighbor : graph.get(node)) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    queue.offer(new int[]{neighbor, depth + 1});
                }
            }
        }

        // The number of ways to assign weights to get an odd sum is 2^(maxDepth - 1)
        // because we need an odd number of edges with weight 1.
        long mod = 1_000_000_007;
        long result = modPow(2, maxDepth - 1, mod);
        return (int) result;            
    }
}
