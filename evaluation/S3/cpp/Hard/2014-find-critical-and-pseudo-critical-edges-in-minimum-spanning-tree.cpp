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
// - Minimum spanning tree - Kruskal's algorithm (graph, array, mst-kruskal, union-find)
//   • When to use: Use when you need to find a minimum spanning tree in a graph, especially when the graph is sparse or when edge weights are the primary concern for selection.
//   • Idea: Kruskal's algorithm constructs a Minimum Spanning Tree by iteratively adding the lowest-weight edge that connects two previously disconnected components, avoiding cycles. It has a time complexity of O(E log E) or O(E log V) due to sorting edges and Union-Find operations.
//   • Invariants: The set of selected edges always forms a forest (no cycles).; Each component in the Union-Find structure represents a connected subtree of the potential MST.
//   • Tips: Always sort all edges by weight in non-decreasing order initially.; Use a Disjoint Set Union (Union-Find) data structure to efficiently track connected components and detect cycles.
//   • Pitfalls: Forgetting to sort edges or sorting them incorrectly (e.g., decreasing order for MST).; Not correctly implementing the Union-Find operations, leading to incorrect cycle detection or component merging.
// - Minimum Spanning Trees (graph, heap, mst-kruskal)
//   • When to use: Use Kruskal's algorithm to find a subset of edges that connects all vertices in an edge-weighted graph with the minimum possible total edge weight. It is suitable for sparse graphs or when edges are easily sorted.
//   • Idea: Kruskal's algorithm is a greedy algorithm that builds a Minimum Spanning Tree (MST) by iteratively adding the cheapest available edge that does not form a cycle. It typically runs in O(E log E) time, dominated by sorting edges or Union-Find operations.
//   • Invariants: The set of edges chosen so far forms a forest, where each tree is a component of the MST.; All edges considered so far that do not form a cycle are part of the current forest.
//   • Tips: Sort all edges by their weights in non-decreasing order before processing.; Utilize a Union-Find data structure to efficiently track connected components and detect cycles.
//   • Pitfalls: Incorrectly implementing Union-Find can lead to performance bottlenecks or incorrect cycle detection.; Failing to sort edges correctly will result in a non-minimal spanning tree.
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
         // Step 1: Kruskal's algorithm to find the weight of the MST
        int m = edges.size();
        vector<vector<int>> indexedEdges(m);
        for (int i = 0; i < m; ++i) {
            indexedEdges[i] = {edges[i][0], edges[i][1], edges[i][2], i}; // [u, v, weight, index]
        }
        sort(indexedEdges.begin(), indexedEdges.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[2] < b[2]; // Sort by weight
        });

        auto kruskal = [&](int skipEdge = -1, int forceEdge = -1) -> int {
            DisjointSetUnion dsu(n);
            int totalWeight = 0;

            if (forceEdge != -1) {
                dsu.unionBySize(indexedEdges[forceEdge][0], indexedEdges[forceEdge][1]);
                totalWeight += indexedEdges[forceEdge][2];
            }

            for (int i = 0; i < m; ++i) {
                if (i == skipEdge) continue;
                if (dsu.unionBySize(indexedEdges[i][0], indexedEdges[i][1])) {
                    totalWeight += indexedEdges[i][2];
                }
            }

            return dsu.count() == 1 ? totalWeight : INT_MAX; // Return INT_MAX if not all vertices are connected
        };

        int mstWeight = kruskal();

        vector<int> critical, pseudoCritical;
        for (int i = 0; i < m; ++i) {
            // Check if edge is critical
            if (kruskal(i) > mstWeight) {
                critical.push_back(indexedEdges[i][3]);
            } else if (kruskal(-1, i) == mstWeight) { // Check if edge is pseudo-critical
                pseudoCritical.push_back(indexedEdges[i][3]);
            }
        }

        return {critical, pseudoCritical};

    }
};
