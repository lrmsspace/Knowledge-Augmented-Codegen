// Source: https://leetcode.com/problems/find-weighted-median-node-in-tree/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n and an undirected, weighted tree rooted at node 0 with n nodes numbered from 0 to n - 1. This is represented by a 2D array edges of length n - 1, where edges[i] = [ui, vi, wi] indicates an edge from node ui to vi with weight wi.
//
// The weighted median node is defined as the first node x on the path from ui to vi such that the sum of edge weights from ui to x is greater than or equal to half of the total path weight.
//
// You are given a 2D integer array queries. For each queries[j] = [uj, vj], determine the weighted median node along the path from uj to vj.
//
// Return an array ans, where ans[j] is the node index of the weighted median for queries[j].
//
// Example:
// Input: n = 2, edges = [[0,1,7]], queries = [[1,0],[0,1]]
//
// Output: [0,1]
//
// Explanation:
//
//
//
//
// 	
// 		
// 			Query
// 			Path
// 			Edge
// 			Weights
// 			Total
// 			Path
// 			Weight
// 			Half
// 			Explanation
// 			Answer
// 		
// 	
// 	
// 		
// 			[1, 0]
// 			1 → 0
// 			[7]
// 			7
// 			3.5
// 			Sum from 1 → 0 = 7 >= 3.5, median is node 0.
// 			0
// 		
// 		
// 			[0, 1]
// 			0 → 1
// 			[7]
// 			7
// 			3.5
// 			Sum from 0 → 1 = 7 >= 3.5, median is node 1.
// 			1
//
// Constraints:
// 2 <= n <= 105
// 	edges.length == n - 1
// 	edges[i] == [ui, vi, wi]
// 	0 <= ui, vi < n
// 	1 <= wi <= 109
// 	1 <= queries.length <= 105
// 	queries[j] == [uj, vj]
// 	0 <= uj, vj < n
// 	The input is generated such that edges represents a valid tree.
//
// Helpful references (internal KB):
// - Lowest Common Ancestor - Binary Lifting (tree, array, binary-lifting, dfs)
//   • When to use: Use binary lifting when you need to answer multiple Lowest Common Ancestor (LCA) queries or ancestor relationship checks efficiently on a static tree.
//   • Idea: Binary lifting precomputes ancestor pointers using DFS to answer Lowest Common Ancestor (LCA) queries and ancestor checks in O(log N) time per query, after O(N log N) preprocessing.
//   • Invariants: For any node `u` and power `k`, `up[u][k]` is the 2^k-th ancestor of `u`.; `depth[u]` correctly represents the distance from the root to node `u`.
//   • Tips: Precompute `up[u][k]` as the 2^k-th ancestor of `u`.; Use DFS to fill the `up` array and node depths.
//   • Pitfalls: Incorrectly calculating `log N` for array dimensions.; Failing to handle the root node's ancestors (e.g., `up[root][k]` should be itself or an invalid node).
// - Lowest Common Ancestor - Binary Lifting (tree, array, dfs, binary-lifting)
//   • When to use: When you need to find the lowest common ancestor of multiple pairs of nodes in a static tree efficiently. It's suitable for scenarios requiring fast query times after initial preprocessing.
//   • Idea: Binary lifting precomputes ancestors at powers of two distances for each node, enabling O(log N) LCA queries after O(N log N) preprocessing. It finds the LCA by lifting nodes to the same depth and then simultaneously upwards.
//   • Invariants: `up[u][j]` stores the `2^j`-th ancestor of node `u`.; For any node `u`, `depth[u]` is its distance from the root.
//   • Tips: Precompute depths of all nodes using DFS from the root.; Initialize `up[u][0]` as the direct parent of `u` for all nodes.
//   • Pitfalls: Incorrectly handling the root's parent or depth calculation.; Off-by-one errors in `logN` calculation for array dimensions.
// - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
//   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
//   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
//   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
//   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
//   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] findMedian(int n, int[][] edges, int[][] queries) {
        // Step 1: Build the tree from edges
        List<List<int[]>> tree = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            tree.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            tree.get(u).add(new int[]{v, w});
            tree.get(v).add(new int[]{u, w});
        }

        // Step 2: Precompute depth and parent using DFS
        int LOG = 17; // log2(10^5) ~ 16.6
        int[][] up = new int[n][LOG];
        long[] distToRoot = new long[n];
        dfs(0, -1, 0, tree, up, distToRoot);

        // Step 3: Process each query to find the weighted median node
        int[] ans = new int[queries.length];
        for (int j = 0; j < queries.length; j++) {
            int uj = queries[j][0], vj = queries[j][1];
            ans[j] = findWeightedMedian(uj, vj, up, distToRoot);
        }
        return ans;         
    }
}
