// Source: https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/   |   Difficulty: Hard
//
// Problem Description:
// Given a weighted undirected connected graph with n vertices numbered from 0 to n - 1, and an array edges where edges[i] = [ai, bi, weighti] represents a bidirectional and weighted edge between nodes ai and bi. A minimum spanning tree (MST) is a subset of the graph's edges that connects all vertices without cycles and with the minimum possible total edge weight.
//
// Find all the critical and pseudo-critical edges in the given graph's minimum spanning tree (MST). An MST edge whose deletion from the graph would cause the MST weight to increase is called a critical edge. On the other hand, a pseudo-critical edge is that which can appear in some MSTs but not all.
//
// Note that you can return the indices of the edges in any order.
//
// Example:
// Input: n = 5, edges = [[0,1,1],[1,2,1],[2,3,2],[0,3,2],[0,4,3],[3,4,3],[1,4,6]]
// Output: [[0,1],[2,3,4,5]]
// Explanation: The figure above describes the graph.
// The following figure shows all the possible MSTs:
//
// Notice that the two edges 0 and 1 appear in all MSTs, therefore they are critical edges, so we return them in the first list of the output.
// The edges 2, 3, 4, and 5 are only part of some MSTs, therefore they are considered pseudo-critical edges. We add them to the second list of the output.
//
// Constraints:
// 2 <= n <= 100
// 	1 <= edges.length <= min(200, n * (n - 1) / 2)
// 	edges[i].length == 3
// 	0 <= ai < bi < n
// 	1 <= weighti <= 1000
// 	All pairs (ai, bi) are distinct.
//
// Helpful references (internal KB):
// - Minimum spanning tree - Kruskal with Disjoint Set Union (graph, ds, mst-kruskal, union-find)
//   • When to use: Use when you need to find a minimum spanning tree in a graph, especially when the graph is sparse or the number of edges is not excessively large compared to vertices.
//   • Idea: Sorts all graph edges by weight and iteratively adds the cheapest edge that connects two previously disconnected components using a Disjoint Set Union (DSU) data structure. This process builds an MST with O(M log M) or O(M log N) time complexity.
//   • Invariants: After processing k edges, the chosen edges form a forest where each tree is a component of the MST.; Any edge not yet processed has a weight greater than or equal to all processed edges.
//   • Tips: Sort edges by weight in non-decreasing order.; Initialize DSU such that each vertex is in its own set.
//   • Pitfalls: Forgetting to sort edges, leading to an incorrect MST.; Inefficient DSU implementation without path compression or union by rank/size.
// - Finding bridges in a graph in O(N+M) (graph, dfs)
//   • When to use: Use this algorithm to identify critical edges in an undirected graph whose removal would increase the number of connected components, effectively disconnecting parts of the graph.
//   • Idea: This algorithm finds all bridges in an undirected graph by performing a Depth First Search and tracking discovery times and lowest reachable ancestors. It operates with an optimal time complexity of O(N+M).
//   • Invariants: For any visited vertex u, disc[u] stores its discovery time in the DFS tree.; For any visited vertex u, low[u] stores the minimum discovery time reachable from u (including u) through u's subtree and at most one back-edge.
//   • Tips: Maintain discovery times (disc) and low-link values (low) for each vertex during DFS.; Initialize low[u] = disc[u] when first visiting vertex u.
//   • Pitfalls: Forgetting to mark visited nodes can lead to infinite loops or incorrect low-link values.; Incorrectly handling the parent edge during DFS, treating it as a back-edge.
// - Second Best Minimum Spanning Tree (graph, array, mst-kruskal, enumeration)
//   • When to use: Use when you need to find a spanning tree with the second smallest total edge weight, often for redundancy or alternative network path planning. It's applicable in scenarios requiring fault tolerance beyond a single optimal solution.
//   • Idea: This algorithm finds a spanning tree with the second minimum total edge weight in a connected, undirected graph. It involves finding the primary MST, then modifying it by replacing one MST edge with a non-MST edge.
//   • Invariants: The primary MST is always a valid spanning tree with minimum total weight.; Adding any non-MST edge (u,v) to the MST creates exactly one cycle.
//   • Tips: First, compute the primary Minimum Spanning Tree (MST) using an algorithm like Kruskal's or Prim's.; For each edge not in the MST, adding it to the MST creates a unique cycle. Find the maximum weight edge on this cycle.
//   • Pitfalls: Naively recomputing an entire MST for each removed edge is inefficient (O(V * E log E)).; Incorrectly identifying the maximum weight edge on the cycle formed by adding a non-MST edge.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        // Augment edges with their original indices
        int m = edges.size();
        vector<vector<int>> indexedEdges(m);
        for (int i = 0; i < m; ++i) {
            indexedEdges[i] = {edges[i][0], edges[i][1], edges[i][2], i};
        }
        
        // Sort edges by weight
        sort(indexedEdges.begin(), indexedEdges.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[2] < b[2];
        });
        
        // Function to find MST weight with optional edge inclusion/exclusion
        auto findMSTWeight = [&](int n, const vector<vector<int>>& edges, int excludeEdge = -1, int includeEdge = -1) {
            DisjointSetUnion dsu(n);
            int totalWeight = 0;
            
            // Include the specified edge first if any
            if (includeEdge != -1) {
                dsu.unionSets(edges[includeEdge][0], edges[includeEdge][1]);
                totalWeight += edges[includeEdge][2];
            }
            
            for (int i = 0; i < edges.size(); ++i) {
                if (i == excludeEdge) continue;
                if (dsu.unionSets(edges[i][0], edges[i][1])) {
                    totalWeight += edges[i][2];
                }
            }
            
            // Check if all vertices are connected
            for (int i = 0; i < n; ++i) {
                if (dsu.findSet(i) != dsu.findSet(0)) {
                    return INT_MAX; // Not all vertices are connected
                }
            }
            return totalWeight;
        };
        
        int originalMSTWeight = findMSTWeight(n, indexedEdges);
        vector<int> criticalEdges, pseudoCriticalEdges;
        
        for (int i = 0; i < m; ++i) {
            // Check if edge is critical
            if (findMSTWeight(n, indexedEdges, i) > originalMSTWeight) {
                criticalEdges.push_back(indexedEdges[i][3]);
            } 
            // Check if edge is pseudo-critical
            else if (findMSTWeight(n, indexedEdges, -1, i) == originalMSTWeight) {
                pseudoCriticalEdges.push_back(indexedEdges[i][3]);
            }
            
        }
        
        return {criticalEdges, pseudoCriticalEdges};
    }
};
