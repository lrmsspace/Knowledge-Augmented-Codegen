// Source: https://leetcode.com/problems/maximal-network-rank/   |   Difficulty: Medium
//
// Problem Description:
// There is an infrastructure of n cities with some number of roads connecting these cities. Each roads[i] = [ai, bi] indicates that there is a bidirectional road between cities ai and bi.
//
// The network rank of two different cities is defined as the total number of directly connected roads to either city. If a road is directly connected to both cities, it is only counted once.
//
// The maximal network rank of the infrastructure is the maximum network rank of all pairs of different cities.
//
// Given the integer n and the array roads, return the maximal network rank of the entire infrastructure.
//
// Example:
// Input: n = 4, roads = [[0,1],[0,3],[1,2],[1,3]]
// Output: 4
// Explanation: The network rank of cities 0 and 1 is 4 as there are 4 roads that are connected to either 0 or 1. The road between 0 and 1 is only counted once.
//
// Constraints:
// 2 <= n <= 100
// 	0 <= roads.length <= n * (n - 1) / 2
// 	roads[i].length == 2
// 	0 <= ai, bi <= n-1
// 	ai != bi
// 	Each pair of cities has at most one road connecting them.
//
// Helpful references (internal KB):
// - Undirected Graphs (graph, array, simulation)
//   • When to use: When modeling symmetric relationships between entities and needing to explore, analyze connectivity, or find paths within the network. Useful for problems involving reachability or structural properties.
//   • Idea: Undirected graphs represent symmetric relationships between pairs of vertices. Simulation on them involves systematically exploring or processing these connections, often with O(V+E) complexity for basic traversals.
//   • Invariants: All vertices reachable from the source within 'k' edges have been processed by the 'k'-th step of BFS.; Each edge in the graph is traversed at most twice (once for each direction) during a full graph traversal.
//   • Tips: Use an adjacency list for sparse graphs to optimize space and traversal time.; Use an adjacency matrix for dense graphs or when O(1) edge existence checks are critical.
//   • Pitfalls: Forgetting to handle disconnected components, leading to incomplete graph processing.; Incorrectly representing undirected edges (e.g., only adding one direction to an adjacency list).
// - Undirected Graphs (graph, matrix, simulation)
//   • When to use: Use when modeling symmetric relationships between entities, analyzing graph properties like connectivity or degrees, or simulating processes on a network where connections are bidirectional.
//   • Idea: An undirected graph consists of a set of vertices and a set of edges, where each edge connects two vertices symmetrically. Basic operations often have a time complexity of O(V+E) or O(V^2) depending on representation.
//   • Invariants: For every edge (u, v) in the graph, the edge (v, u) also exists.; The sum of degrees of all vertices equals twice the number of edges.
//   • Tips: Choose adjacency list for sparse graphs, adjacency matrix for dense graphs.; Degrees of vertices are easily calculated from adjacency representations.
//   • Pitfalls: Forgetting to add both (u,v) and (v,u) when using an adjacency matrix or list.; Not handling disconnected components during full graph traversals.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
//   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
//   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
//   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
//   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
//   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int maximalNetworkRank(int n, vector<vector<int>>& roads) {
        vector<int> degree(n, 0);
        vector<vector<bool>> connected(n, vector<bool>(n, false));

        for (const auto& road : roads) {
            int a = road[0], b = road[1];
            degree[a]++;
            degree[b]++;
            connected[a][b] = connected[b][a] = true;
        }

        int maxRank = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int rank = degree[i] + degree[j] - (connected[i][j] ? 1 : 0);
                maxRank = max(maxRank, rank);
            }
        }

        return maxRank;         
    }
};
