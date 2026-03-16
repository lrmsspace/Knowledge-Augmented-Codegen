// Source: https://leetcode.com/problems/add-edges-to-make-degrees-of-all-nodes-even/   |   Difficulty: Hard
//
// Problem Description:
// There is an undirected graph consisting of n nodes numbered from 1 to n. You are given the integer n and a 2D array edges where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi. The graph can be disconnected.
//
// You can add at most two additional edges (possibly none) to this graph so that there are no repeated edges and no self-loops.
//
// Return true if it is possible to make the degree of each node in the graph even, otherwise return false.
//
// The degree of a node is the number of edges connected to it.
//
// Example:
// Input: n = 5, edges = [[1,2],[2,3],[3,4],[4,2],[1,4],[2,5]]
// Output: true
// Explanation: The above diagram shows a valid way of adding an edge.
// Every node in the resulting graph is connected to an even number of edges.
//
// Constraints:
// 3 <= n <= 105
// 	2 <= edges.length <= 105
// 	edges[i].length == 2
// 	1 <= ai, bi <= n
// 	ai != bi
// 	There are no repeated edges.
//
// Helpful references (internal KB):
// - Finding faces of a planar graph (graph, array, dfs, enumeration)
//   • When to use: Used to identify and enumerate all faces (regions) of a given planar graph, typically when its geometric embedding is known or can be derived.
//   • Idea: This algorithm finds all faces of a planar graph by traversing edges in a specific angular order around each vertex. It achieves a time complexity of O(N log N) due to sorting, or O(N) if edges are pre-sorted.
//   • Invariants: Every directed edge is part of exactly one face boundary traversal.; At any vertex u, the next edge (u, w) is chosen such that it is immediately counter-clockwise to the incoming edge (v, u) in u's adjacency list.
//   • Tips: Sort adjacent edges by polar angle for each vertex.; Mark directed edges as visited to ensure each face is found once.
//   • Pitfalls: Errors in polar angle sorting, especially for collinear edges.; Failing to correctly mark directed edges as visited, leading to infinite loops or duplicate faces.
// - Undirected Graphs (graph, matrix, simulation)
//   • When to use: Use when modeling symmetric relationships between entities, analyzing graph properties like connectivity or degrees, or simulating processes on a network where connections are bidirectional.
//   • Idea: An undirected graph consists of a set of vertices and a set of edges, where each edge connects two vertices symmetrically. Basic operations often have a time complexity of O(V+E) or O(V^2) depending on representation.
//   • Invariants: For every edge (u, v) in the graph, the edge (v, u) also exists.; The sum of degrees of all vertices equals twice the number of edges.
//   • Tips: Choose adjacency list for sparse graphs, adjacency matrix for dense graphs.; Degrees of vertices are easily calculated from adjacency representations.
//   • Pitfalls: Forgetting to add both (u,v) and (v,u) when using an adjacency matrix or list.; Not handling disconnected components during full graph traversals.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, matrix, matrix-exp, counting)
//   • When to use: Use when needing to count the number of paths of a specific length between all pairs of vertices in a graph, or to find reachability in a fixed number of steps.
//   • Idea: This algorithm leverages matrix exponentiation to find the number of paths of a fixed length `k` between all pairs of vertices in a graph. Each matrix multiplication step extends path lengths by one, resulting in an O(N^3 log K) time complexity for an N-vertex graph.
//   • Invariants: After `m` matrix multiplications, `C_m[i][j]` stores the number of paths of length `m` from `i` to `j`.; The initial adjacency matrix `G` remains constant throughout the exponentiation process.
//   • Tips: Represent the graph as an adjacency matrix where `G[i][j]` is the number of direct edges.; Matrix multiplication `C_k * G` yields `C_{k+1}` for path counts.
//   • Pitfalls: Standard matrix multiplication is O(N^3), leading to O(N^3 log K) overall time complexity.; Memory usage is O(N^2) for storing matrices, which can be prohibitive for very large graphs.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    bool isPossible(int n, vector<vector<int>>& edges) {
        vector<int> degree(n + 1, 0);
        for (const auto& edge : edges) {
            degree[edge[0]]++;
            degree[edge[1]]++;
        }

        vector<int> oddNodes;
        for (int i = 1; i <= n; ++i) {
            if (degree[i] % 2 != 0) {
                oddNodes.push_back(i);
            }
        }

        int oddCount = oddNodes.size();
        if (oddCount == 0) {
            return true;
        } else if (oddCount == 2) {
            int u = oddNodes[0];
            int v = oddNodes[1];
            // Check if we can connect u and v directly
            bool canConnectDirectly = true;
            for (const auto& edge : edges) {
                if ((edge[0] == u && edge[1] == v) || (edge[0] == v && edge[1] == u)) {
                    canConnectDirectly = false;
                    break;
                }
            }
            if (canConnectDirectly) {
                return true;
            }
            // Check if there exists a node w that can connect to both u and v
            for (int w = 1; w <= n; ++w) {
                if (w != u && w != v) {
                    bool canConnectU = true;
                    bool canConnectV = true;
                    for (const auto& edge : edges) {
                        if ((edge[0] == u && edge[1] == w) || (edge[0] == w && edge[1] == u)) {
                            canConnectU = false;
                        }
                        if ((edge[0] == v && edge[1] == w) || (edge[0] == w && edge[1] == v)) {
                            canConnectV = false;
                        }
                    }
                    if (canConnectU && canConnectV) {
                        return true;
                    }
                }
            }
            return false;
        } else if (oddCount == 4) {
            // Check all pairings of the four odd degree nodes
            for (int i = 0; i < 4; ++i) {
                for (int j = i + 1; j < 4; ++j) {
                    for (int k = 0; k < 4; ++k) {
                        for (int l = k + 1; l < 4; ++l) {
                            if (i != k && i != l && j != k && j != l) {
                                int u1 = oddNodes[i];
                                int v1 = oddNodes[j];
                                int u2 = oddNodes[k];
                                int v2 = oddNodes[l];
                                bool canConnectFirstPair = true;
                                bool canConnectSecondPair = true;
                                for (const auto& edge : edges) {
                                    if ((edge[0] == u1 && edge[1] == v1) || (edge[0] == v1 && edge[1] == u1)) {
                                        canConnectFirstPair = false;
                                    }
                                    if ((edge[0] == u2 && edge[1] == v2) || (edge[0] == v2 && edge[1] == u2)) {
                                        canConnectSecondPair = false;
                                    }
                                }
                                if (canConnectFirstPair && canConnectSecondPair) {
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
            return false;
        } else {
            return false;
        }   
    }
};
