// Source: https://leetcode.com/problems/minimum-increments-to-equalize-leaf-paths/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n and an undirected tree rooted at node 0 with n nodes numbered from 0 to n - 1. This is represented by a 2D array edges of length n - 1, where edges[i] = [ui, vi] indicates an edge from node ui to vi .
//
// Each node i has an associated cost given by cost[i], representing the cost to traverse that node.
//
// The score of a path is defined as the sum of the costs of all nodes along the path.
//
// Your goal is to make the scores of all root-to-leaf paths equal by increasing the cost of any number of nodes by any non-negative amount.
//
// Return the minimum number of nodes whose cost must be increased to make all root-to-leaf path scores equal.
//
// Example:
// Input: n = 3, edges = [[0,1],[0,2]], cost = [2,1,3]
//
// Output: 1
//
// Explanation:
//
//
//
// There are two root-to-leaf paths:
//
//
// 	Path 0 → 1 has a score of 2 + 1 = 3.
// 	Path 0 → 2 has a score of 2 + 3 = 5.
//
//
// To make all root-to-leaf path scores equal to 5, increase the cost of node 1 by 2.
// Only one node is increased, so the output is 1.
//
// Constraints:
// 2 <= n <= 105
// 	edges.length == n - 1
// 	edges[i] == [ui, vi]
// 	0 <= ui, vi < n
// 	cost.length == n
// 	1 <= cost[i] <= 109
// 	The input is generated such that edges represents a valid tree.
//
// Helpful references (internal KB):
// - Depth First Search (tree, graph, dfs)
//   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
//   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
//   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
//   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
// - Undirected Graphs (graph, array, simulation)
//   • When to use: When modeling symmetric relationships between entities and needing to explore, analyze connectivity, or find paths within the network. Useful for problems involving reachability or structural properties.
//   • Idea: Undirected graphs represent symmetric relationships between pairs of vertices. Simulation on them involves systematically exploring or processing these connections, often with O(V+E) complexity for basic traversals.
//   • Invariants: All vertices reachable from the source within 'k' edges have been processed by the 'k'-th step of BFS.; Each edge in the graph is traversed at most twice (once for each direction) during a full graph traversal.
//   • Tips: Use an adjacency list for sparse graphs to optimize space and traversal time.; Use an adjacency matrix for dense graphs or when O(1) edge existence checks are critical.
//   • Pitfalls: Forgetting to handle disconnected components, leading to incomplete graph processing.; Incorrectly representing undirected edges (e.g., only adding one direction to an adjacency list).
// - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
//   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
//   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
//   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
//   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
//   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minIncrease(int n, vector<vector<int>>& edges, vector<int>& cost) {
        vector<vector<int>> graph(n);
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1];
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        int maxPathSum = 0;
        function<int(int, int)> dfs = [&](int node, int parent) -> int {
            if (graph[node].size() == 1 && parent != -1) {
                // Leaf node
                return cost[node];
            }
            int maxChildPath = 0;
            for (int neighbor : graph[node]) {
                if (neighbor == parent) continue;
                int childPathSum = dfs(neighbor, node);
                maxChildPath = max(maxChildPath, childPathSum);
            }
            return cost[node] + maxChildPath;
        };

        maxPathSum = dfs(0, -1);

        int increments = 0;
        function<void(int, int, int)> dfsCount = [&](int node, int parent, int currentSum) {
            if (graph[node].size() == 1 && parent != -1) {
                // Leaf node
                increments += (maxPathSum - currentSum);
                return;
            }
            for (int neighbor : graph[node]) {
                if (neighbor == parent) continue;
                dfsCount(neighbor, node, currentSum + cost[neighbor]);
            }
        };

        dfsCount(0, -1, cost[0]);

        return increments;          
    }
};
