// Source: https://leetcode.com/problems/find-center-of-star-graph/   |   Difficulty: Easy
//
// Problem Description:
// There is an undirected star graph consisting of n nodes labeled from 1 to n. A star graph is a graph where there is one center node and exactly n - 1 edges that connect the center node with every other node.
//
// You are given a 2D integer array edges where each edges[i] = [ui, vi] indicates that there is an edge between the nodes ui and vi. Return the center of the given star graph.
//
// Example:
// Input: edges = [[1,2],[2,3],[4,2]]
// Output: 2
// Explanation: As shown in the figure above, node 2 is connected to every other node, so 2 is the center.
//
// Constraints:
// 3 <= n <= 105
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	1 <= ui, vi <= n
// 	ui != vi
// 	The given edges represent a valid star graph.
//
// Helpful references (internal KB):
// - Finding articulation points in a graph in O(N+M) (graph, array, dfs)
//   • When to use: Use when identifying critical nodes whose removal would increase the number of connected components in an undirected graph. It's essential for analyzing network robustness and vulnerability.
//   • Idea: This algorithm finds all articulation points (cut vertices) in an undirected graph using a single Depth First Search traversal. It operates in linear time, O(N+M), where N is vertices and M is edges.
//   • Invariants: For any node `u`, `tin[u]` is its discovery time, and `low[u]` is initialized to `tin[u]`.; After visiting all children `v` of `u` (and their subtrees), `low[u]` will hold the minimum `tin` value reachable from `u` or its descendants via tree edges and at most one back-edge.
//   • Tips: Initialize `tin` (discovery time) and `low` (lowest reachable ancestor) arrays for all vertices.; The root of the DFS tree is an articulation point if it has more than one child in the DFS tree.
//   • Pitfalls: Forgetting to initialize `low[u]` with `tin[u]` before processing children.; Incorrectly applying the `tin[u] <= low[v]` condition to the root node of the DFS tree.
// - Disjoint Set Union (ds, linked-list, union-find, dfs)
//   • When to use: Use when you need to maintain a collection of disjoint sets and perform union operations to merge sets or find the representative of an element's set efficiently. It's suitable for problems involving dynamic connectivity or grouping elements.
//   • Idea: Disjoint Set Union (DSU) is a data structure that stores a collection of disjoint sets and supports two primary operations: finding the representative of an element's set and merging two sets. It achieves nearly constant time complexity for these operations with path compression and union by rank/size optimizations.
//   • Invariants: Every element `i` belongs to exactly one set, represented by `find(i)`.; If `parent[i] == i`, then `i` is the representative (root) of its set.
//   • Tips: Implement path compression in `find` for optimal performance.; Use union by size or rank to maintain balanced trees.
//   • Pitfalls: Omitting path compression or union by rank/size can degrade performance to O(N).; Failing to correctly update auxiliary data stored at representatives during a union operation.
// - Kirchhoff's theorem. Finding the number of spanning trees (graph, matrix, counting)
//   • When to use: Used to determine the exact count of distinct spanning trees in a connected undirected graph, even when multiple edges are present. It is particularly useful for problems requiring precise enumeration of graph structures.
//   • Idea: This theorem calculates the number of spanning trees in a graph by finding the determinant of any cofactor of its Laplacian matrix. The typical complexity for an N-vertex graph is O(N^3) due to matrix determinant calculation.
//   • Invariants: The sum of degrees in the graph is always twice the number of edges.; The sum of any row or column in the Laplacian matrix is zero.
//   • Tips: Construct the Laplacian matrix (L = D - A) carefully, ensuring correct degrees and adjacency entries.; Account for multiple edges by summing their counts in the adjacency matrix and degree matrix.
//   • Pitfalls: Incorrectly calculating vertex degrees, especially with multiple edges or self-loops.; Using the determinant of the full Laplacian matrix, which is always zero.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int findCenter(int** edges, int edgesSize, int* edgesColSize) {
    // The center of a star graph will be the node that appears in every edge. Since there are n-1 edges, the center will be the node that appears in all of them.
    // We can simply check the first two edges to find the common node, which will be the center.

    int firstEdgeNode1 = edges[0][0];
    int firstEdgeNode2 = edges[0][1];
    
    // Check if the first node of the first edge is the center
    if (firstEdgeNode1 == edges[1][0] || firstEdgeNode1 == edges[1][1]) {
        return firstEdgeNode1;
    }
    
    // Otherwise, the second node of the first edge must be the center
    return firstEdgeNode2;      
}
