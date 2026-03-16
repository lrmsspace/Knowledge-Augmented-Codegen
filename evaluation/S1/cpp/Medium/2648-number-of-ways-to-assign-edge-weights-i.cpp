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
// Helpful references (internal KB):
// - Breadth-first search (graph, array, bfs)
//   • When to use: Use when finding the shortest path or minimum number of edges between nodes in an unweighted graph, or to explore a graph layer by layer. It is also suitable for finding shortest cycles or identifying all components of shortest paths.
//   • Idea: Breadth-first search systematically explores a graph level by level, ensuring the shortest path in terms of edges is found from a source node to all reachable nodes. It operates in O(V + E) time complexity for adjacency list representation.
//   • Invariants: All nodes currently in the queue are at depth `k` or `k+1` from the source.; The distance recorded for any visited node is its shortest path length from the source.
//   • Tips: Run multiple BFS from different sources to find global properties like shortest cycles.; Maintain a distance array to record the shortest path length from the source to each node.
//   • Pitfalls: Applying BFS directly to weighted graphs will not yield shortest paths.; Failing to mark visited nodes can lead to infinite loops in cyclic graphs or incorrect path lengths.
// - Chinese Remainder Theorem (number, mod-exp)
//   • When to use: Used to find an integer that satisfies a system of multiple congruence relations, particularly when the moduli are pairwise coprime. It's essential for reconstructing numbers from their remainders.
//   • Idea: The Chinese Remainder Theorem finds a unique integer solution to a system of linear congruences, modulo the product of their pairwise coprime moduli. It iteratively combines congruences, often using the Extended Euclidean Algorithm for modular inverses, with a complexity polynomial in the number of congruences.
//   • Invariants: The current combined solution satisfies all previously processed congruences.; The current combined modulus is the product of all previously processed pairwise coprime moduli.
//   • Tips: Ensure all moduli are pairwise coprime for a unique solution.; Use the Extended Euclidean Algorithm to find modular inverses.
//   • Pitfalls: Forgetting to check if moduli are pairwise coprime, leading to no unique solution or no solution.; Incorrectly calculating modular inverses, which is crucial for the algorithm.
// - Depth First Search (tree, graph, dfs)
//   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
//   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
//   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
//   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int assignEdgeWeights(vector<vector<int>>& edges) {
        const int MOD = 1e9 + 7;
        int n = edges.size() + 1;
        vector<vector<int>> graph(n + 1);
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        // BFS to find the maximum depth
        vector<int> depth(n + 1, -1);
        depth[1] = 0;
        queue<int> q;
        q.push(1);
        int maxDepth = 0;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            for (int neighbor : graph[node]) {
                if (depth[neighbor] == -1) {
                    depth[neighbor] = depth[node] + 1;
                    maxDepth = max(maxDepth, depth[neighbor]);
                    q.push(neighbor);
                }
            }
        }

        // Count number of nodes at maximum depth
        int countMaxDepth = 0;
        for (int i = 1; i <= n; ++i) {
            if (depth[i] == maxDepth) {
                countMaxDepth++;
            }
        }

        // Each edge in the path can be assigned weight 1 or 2
        // To get an odd total cost, we need an odd number of edges with weight 1
        // The number of ways to choose an odd number of edges from k edges is 2^(k-1)
        // Thus, the answer is countMaxDepth * 2^(maxDepth - 1) % MOD
        long long ways = 1;
        for (int i = 0; i < maxDepth - 1; ++i) {
            ways = (ways * 2) % MOD;
        }

        return (countMaxDepth * ways) % MOD;            
    }
};
