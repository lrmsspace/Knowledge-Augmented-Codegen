// Source: https://leetcode.com/problems/number-of-operations-to-make-network-connected/   |   Difficulty: Medium
//
// Problem Description:
// There are n computers numbered from 0 to n - 1 connected by ethernet cables connections forming a network where connections[i] = [ai, bi] represents a connection between computers ai and bi. Any computer can reach any other computer directly or indirectly through the network.
//
// You are given an initial computer network connections. You can extract certain cables between two directly connected computers, and place them between any pair of disconnected computers to make them directly connected.
//
// Return the minimum number of times you need to do this in order to make all the computers connected. If it is not possible, return -1.
//
// Example:
// Input: n = 4, connections = [[0,1],[0,2],[1,2]]
// Output: 1
// Explanation: Remove cable between computer 1 and 2 and place between computers 1 and 3.
//
// Constraints:
// 1 <= n <= 105
// 	1 <= connections.length <= min(n * (n - 1) / 2, 105)
// 	connections[i].length == 2
// 	0 <= ai, bi < n
// 	ai != bi
// 	There are no repeated connections.
// 	No two computers are connected by more than one cable.
//
// Helpful references (internal KB):
// - Search for connected components in a graph (graph, dfs, bfs, enumeration)
//   • When to use: Use when you need to partition an undirected graph into maximal connected subgraphs where every node is reachable from every other node within its subgraph.
//   • Idea: This algorithm identifies all connected components in an undirected graph by iteratively performing graph traversals (DFS or BFS) from unvisited nodes. It has a time complexity of O(V + E) for adjacency list representation.
//   • Invariants: All nodes visited so far belong to an identified connected component.; Any node currently being visited is part of the current connected component being explored.
//   • Tips: Maintain a visited array or set to track processed nodes.; Iterate through all nodes, starting a new traversal if a node is unvisited.
//   • Pitfalls: Failing to iterate through all nodes to find all components in a disconnected graph.; Not correctly marking nodes as visited during traversal, leading to infinite loops or re-processing.
// - Minimum-cost flow - Successive shortest path algorithm (graph, array, greedy, dijkstra, bellman-ford)
//   • When to use: This algorithm finds a minimum-cost flow of a given amount from a source to a sink in a flow network. It is suitable when both flow capacity and edge costs are present.
//   • Idea: The successive shortest path algorithm iteratively finds augmenting paths with minimum cost in a residual graph, using shortest path algorithms like Bellman-Ford or Dijkstra with potentials, until the desired flow is achieved. Its complexity depends on the shortest path algorithm used and the number of augmentations.
//   • Invariants: The total flow pushed from source to sink never exceeds the sum of capacities of edges leaving the source.; For any edge (u, v) with flow f_uv, 0 <= f_uv <= capacity_uv.
//   • Tips: Use potentials with Dijkstra for non-negative edge costs in the residual graph.; Bellman-Ford is necessary if initial edge costs can be negative or if potentials are not used.
//   • Pitfalls: Incorrectly updating potentials can lead to wrong shortest paths.; Forgetting to add reverse edges with negative costs in the residual graph.
// - Counting labeled graphs (number, recursion, counting, dp-1d)
//   • When to use: When the problem requires enumerating distinct labeled graphs with specific properties, such as connectivity, on a given number of vertices. It is suitable for combinatorial counting problems involving graph structures.
//   • Idea: This technique determines the number of connected labeled graphs by subtracting the count of disconnected graphs from the total. It typically employs a recursive or dynamic programming approach, often involving combinatorial terms like binomial coefficients, with a polynomial time complexity.
//   • Invariants: The total number of labeled graphs $G_n$ for $n$ vertices is always $2^{n(n-1)/2}$.; For any $n$, the sum of connected and disconnected labeled graphs equals the total number of labeled graphs.
//   • Tips: Start with the total number of labeled graphs $G_n = 2^{n(n-1)/2}$.; Use complementary counting: total graphs minus disconnected graphs.
//   • Pitfalls: Forgetting to divide by $n$ when converting from rooted to unrooted disconnected graphs.; Incorrectly handling base cases for recursive definitions or DP states.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        if (connections.size() < n - 1) return -1;

        vector<vector<int>> adj(n);
        for (const auto& conn : connections) {
            adj[conn[0]].push_back(conn[1]);
            adj[conn[1]].push_back(conn[0]);
        }

        vector<bool> visited(n, false);
        int components = 0;

        function<void(int)> dfs = [&](int node) {
            visited[node] = true;
            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    dfs(neighbor);
                }
            }
        };

        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                ++components;
                dfs(i);
            }
        }

        return components - 1;          
    }
};
