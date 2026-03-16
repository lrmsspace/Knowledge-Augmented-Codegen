// Source: https://leetcode.com/problems/number-of-restricted-paths-from-first-to-last-node/   |   Difficulty: Medium
//
// Problem Description:
// There is an undirected weighted connected graph. You are given a positive integer n which denotes that the graph has n nodes labeled from 1 to n, and an array edges where each edges[i] = [ui, vi, weighti] denotes that there is an edge between nodes ui and vi with weight equal to weighti.
//
// A path from node start to node end is a sequence of nodes [z0, z1, z2, ..., zk] such that z0 = start and zk = end and there is an edge between zi and zi+1 where 0 <= i <= k-1.
//
// The distance of a path is the sum of the weights on the edges of the path. Let distanceToLastNode(x) denote the shortest distance of a path between node n and node x. A restricted path is a path that also satisfies that distanceToLastNode(zi) > distanceToLastNode(zi+1) where 0 <= i <= k-1.
//
// Return the number of restricted paths from node 1 to node n. Since that number may be too large, return it modulo 109 + 7.
//
// Example:
// Input: n = 5, edges = [[1,2,3],[1,3,3],[2,3,1],[1,4,2],[5,2,2],[3,5,1],[5,4,10]]
// Output: 3
// Explanation: Each circle contains the node number in black and its distanceToLastNode value in blue. The three restricted paths are:
// 1) 1 --> 2 --> 5
// 2) 1 --> 2 --> 3 --> 5
// 3) 1 --> 3 --> 5
//
// Constraints:
// 1 <= n <= 2 * 104
// 	n - 1 <= edges.length <= 4 * 104
// 	edges[i].length == 3
// 	1 <= ui, vi <= n
// 	ui != vi
// 	1 <= weighti <= 105
// 	There is at most one edge between any two nodes.
// 	There is at least one path between any two nodes.
//
// Helpful references (internal KB):
// - Dijkstra on sparse graphs (heap, queue, dijkstra)
//   • When to use: When you need to find the shortest paths from a single source vertex to all other vertices in a graph with non-negative edge weights, especially efficient for sparse graphs.
//   • Idea: Dijkstra's algorithm finds the shortest paths from a single source to all other vertices in a weighted graph with non-negative edge weights. It uses a priority queue to greedily explore vertices, achieving O(E log V) complexity with a binary heap.
//   • Invariants: At the start of each iteration, dist[u] holds the shortest distance found so far from the source to u.; All vertices already extracted from the priority queue have their final shortest distance determined.
//   • Tips: Use a priority queue (min-heap) to efficiently retrieve the unvisited vertex with the smallest distance.; Initialize all distances to infinity and the source distance to zero.
//   • Pitfalls: Does not work correctly with negative edge weights; Bellman-Ford or SPFA is needed.; Forgetting to mark vertices as visited or handle duplicate entries in the priority queue can lead to incorrectness or TLE.
// - Counting labeled graphs (number, dp-2d, counting, recursion)
//   • When to use: When counting the total number of labeled graphs with a specific number of vertices and connected components. Useful for problems requiring enumeration of graph structures based on their connectivity properties.
//   • Idea: This technique uses dynamic programming to count labeled graphs with a given number of vertices and connected components by building up solutions from smaller subproblems. It leverages a recurrence relation that considers the component containing a specific vertex, leading to an O(N^2 * K) time complexity for N vertices and K components.
//   • Invariants: D[i][j] correctly stores the number of labeled graphs with i vertices and j components.; All C_s values for s < n are correctly precomputed before calculating D[n][k].
//   • Tips: Precompute binomial coefficients for efficiency.; Precompute the number of connected graphs (C_s) for all relevant s.
//   • Pitfalls: Incorrectly defining base cases for the dynamic programming table.; Off-by-one errors in binomial coefficient calculations or array indexing.
// - Checking a graph for acyclicity and finding a cycle in O(M) (graph, array, dfs)
//   • When to use: Use when needing to determine if a graph contains any cycles or to identify one such cycle. It is applicable to both directed and undirected graphs.
//   • Idea: This algorithm uses Depth First Search to detect cycles in a graph by tracking visited states of nodes during traversal. It runs in O(V + E) time, where V is the number of vertices and E is the number of edges.
//   • Invariants: All nodes currently on the DFS recursion stack are marked as 'gray' (or equivalent).; All nodes fully explored and not part of the current path are marked as 'black' (or equivalent).
//   • Tips: For directed graphs, use a three-color scheme (white, gray, black) to distinguish states.; For undirected graphs, a simple visited array and checking against the immediate parent is sufficient.
//   • Pitfalls: Incorrectly handling the parent edge in undirected graphs can lead to false cycle detections.; Failing to distinguish between nodes currently in the recursion stack (gray) and fully processed nodes (black) in directed graphs.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int countRestrictedPaths(int n, vector<vector<int>>& edges) {
        const int MOD = 1e9 + 7;

        // Build graph
        vector<vector<pair<int, int>>> g(n);
        for (auto &e : edges) {
            int u = e[0] - 1, v = e[1] - 1, w = e[2];
            g[u].push_back({v, w});
            g[v].push_back({u, w});
        }

        // Dijkstra from node n-1 to find shortest distances to n-1
        vector<int> dist(n, INT32_MAX);
        dist[n-1] = 0;
        using PII = pair<int, int>;
        priority_queue<PII, vector<PII>, greater<PII>> pq;
        pq.push({0, n-1});
        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d > dist[u]) continue;
            for (auto &pr : g[u]) {
                int v = pr.first, w = pr.second;
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }

        // DP to count restricted paths from 0 to n-1
        vector<int> dp(n, -1);
        function<int(int)> dfs = [&](int u) -> int {
            if (u == n - 1) return 1;
            if (dp[u] != -1) return dp[u];
            long long res = 0;
            for (auto &pr : g[u]) {
                int v = pr.first;
                if (dist[u] > dist[v]) {
                    res = (res + dfs(v)) % MOD;
                }
            }
            dp[u] = (int)res;
            return dp[u];
        };

        return dfs(0);          
    }
};
