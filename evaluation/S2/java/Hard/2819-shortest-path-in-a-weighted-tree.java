// Source: https://leetcode.com/problems/shortest-path-in-a-weighted-tree/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n and an undirected, weighted tree rooted at node 1 with n nodes numbered from 1 to n. This is represented by a 2D array edges of length n - 1, where edges[i] = [ui, vi, wi] indicates an undirected edge from node ui to vi with weight wi.
//
// You are also given a 2D integer array queries of length q, where each queries[i] is either:
//
//
// 	[1, u, v, w'] – Update the weight of the edge between nodes u and v to w', where (u, v) is guaranteed to be an edge present in edges.
// 	[2, x] – Compute the shortest path distance from the root node 1 to node x.
//
//
// Return an integer array answer, where answer[i] is the shortest path distance from node 1 to x for the ith query of [2, x].
//
// Example:
// Input: n = 2, edges = [[1,2,7]], queries = [[2,2],[1,1,2,4],[2,2]]
//
// Output: [7,4]
//
// Explanation:
//
//
//
//
// 	Query [2,2]: The shortest path from root node 1 to node 2 is 7.
// 	Query [1,1,2,4]: The weight of edge (1,2) changes from 7 to 4.
// 	Query [2,2]: The shortest path from root node 1 to node 2 is 4.
//
// Constraints:
// 1 <= n <= 105
// 	edges.length == n - 1
// 	edges[i] == [ui, vi, wi]
// 	1 <= ui, vi <= n
// 	1 <= wi <= 104
// 	The input is generated such that edges represents a valid tree.
// 	1 <= queries.length == q <= 105
// 	queries[i].length == 2 or 4
// 	
// 		queries[i] == [1, u, v, w'] or,
// 		queries[i] == [2, x]
// 		1 <= u, v, x <= n
// 		(u, v) is always an edge from edges.
// 		1 <= w' <= 104
//
// Helpful references (internal KB):
// - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
//   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
//   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
//   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
//   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
//   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
// - Second Best Minimum Spanning Tree (graph, tree, mst-kruskal, lca, binary-lifting, enumeration)
//   • When to use: When you need to find a spanning tree with the second smallest total edge weight, typically after finding the primary Minimum Spanning Tree.
//   • Idea: This algorithm finds the second best Minimum Spanning Tree by iterating through non-MST edges, adding each to the MST to form a cycle, and then removing the maximum weight edge on that cycle (excluding the added edge). It leverages Kruskal's for the initial MST and LCA with binary lifting for efficient path maximum queries, achieving an overall time complexity of O(E log E + E log V).
//   • Invariants: The initial MST is always a valid spanning tree with minimum total weight.; For any non-MST edge (u, v) added, a unique cycle is formed in the current graph.
//   • Tips: Precompute LCA and maximum edge weights on paths using binary lifting for efficiency.; The initial MST can be found using Kruskal's or Prim's algorithm.
//   • Pitfalls: Incorrectly identifying the maximum weight edge on the cycle when adding a non-MST edge.; Forgetting to exclude the newly added edge itself when finding the maximum edge on the cycle.
// - Range Minimum Query (array, ds, union-find)
//   • When to use: Use when range minimum queries are needed on an array where elements can be dynamically removed or merged, and Union-Find is employed to manage the active state or connectivity of indices.
//   • Idea: Union-Find can be adapted to assist in range minimum queries, particularly when elements are dynamically removed or merged. It helps maintain connectivity of active elements or segments, allowing efficient traversal to find the minimum among available items, often with near-constant amortized time per Union-Find operation.
//   • Invariants: The `find` operation correctly returns the canonical representative for any element `i`.; Each set in the Union-Find structure maintains a property (e.g., minimum value, next available index) relevant to its merged elements.
//   • Tips: Utilize path compression and union by rank/size for optimal Union-Find performance.; Store relevant properties (e.g., minimum value, next available index) within the representative of each set.
//   • Pitfalls: Union-Find alone does not directly provide range minimums; it typically manages connectivity or availability.; Naive iteration through active elements found by Union-Find can be too slow for large ranges.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] treeQueries(int n, int[][] edges, int[][] queries) {
        // Step 1: Build the tree and compute initial distances from the root
        List<List<int[]>> graph = new ArrayList<>();
        for (int i = 0; i <= n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            graph.get(u).add(new int[]{v, w});
            graph.get(v).add(new int[]{u, w});
        }

        int[] dist = new int[n + 1];
        boolean[] visited = new boolean[n + 1];
        dfs(1, 0, graph, dist, visited);

        // Step 2: Process queries
        int[] answer = new int[queries.length];
        for (int i = 0; i < queries.length; i++) {
            if (queries[i][0] == 1) {
                // Update query
                int u = queries[i][1], v = queries[i][2], w = queries[i][3];
                updateEdgeWeight(graph, u, v, w);
                // Recompute distances from root after the update
                Arrays.fill(visited, false);
                dfs(1, 0, graph, dist, visited);
            } else {
                // Distance query
                int x = queries[i][1];
                answer[i] = dist[x];
            }
        }
        return answer;          
    }
}
