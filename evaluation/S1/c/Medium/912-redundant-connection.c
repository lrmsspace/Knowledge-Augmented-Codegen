// Source: https://leetcode.com/problems/redundant-connection/   |   Difficulty: Medium
//
// Problem Description:
// In this problem, a tree is an undirected graph that is connected and has no cycles.
//
// You are given a graph that started as a tree with n nodes labeled from 1 to n, with one additional edge added. The added edge has two different vertices chosen from 1 to n, and was not an edge that already existed. The graph is represented as an array edges of length n where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the graph.
//
// Return an edge that can be removed so that the resulting graph is a tree of n nodes. If there are multiple answers, return the answer that occurs last in the input.
//
// Example:
// Input: edges = [[1,2],[1,3],[2,3]]
// Output: [2,3]
//
// Constraints:
// n == edges.length
// 	3 <= n <= 1000
// 	edges[i].length == 2
// 	1 <= ai < bi <= edges.length
// 	ai != bi
// 	There are no repeated edges.
// 	The given graph is connected.
//
// Helpful references (internal KB):
// - Checking a graph for acyclicity and finding a cycle in O(M) (graph, array, dfs)
//   • When to use: Use when needing to determine if a graph contains any cycles or to identify one such cycle. It is applicable to both directed and undirected graphs.
//   • Idea: This algorithm uses Depth First Search to detect cycles in a graph by tracking visited states of nodes during traversal. It runs in O(V + E) time, where V is the number of vertices and E is the number of edges.
//   • Invariants: All nodes currently on the DFS recursion stack are marked as 'gray' (or equivalent).; All nodes fully explored and not part of the current path are marked as 'black' (or equivalent).
//   • Tips: For directed graphs, use a three-color scheme (white, gray, black) to distinguish states.; For undirected graphs, a simple visited array and checking against the immediate parent is sufficient.
//   • Pitfalls: Incorrectly handling the parent edge in undirected graphs can lead to false cycle detections.; Failing to distinguish between nodes currently in the recursion stack (gray) and fully processed nodes (black) in directed graphs.
// - Finding faces of a planar graph (graph, array, dfs, enumeration)
//   • When to use: Used to identify and enumerate all faces (regions) of a given planar graph, typically when its geometric embedding is known or can be derived.
//   • Idea: This algorithm finds all faces of a planar graph by traversing edges in a specific angular order around each vertex. It achieves a time complexity of O(N log N) due to sorting, or O(N) if edges are pre-sorted.
//   • Invariants: Every directed edge is part of exactly one face boundary traversal.; At any vertex u, the next edge (u, w) is chosen such that it is immediately counter-clockwise to the incoming edge (v, u) in u's adjacency list.
//   • Tips: Sort adjacent edges by polar angle for each vertex.; Mark directed edges as visited to ensure each face is found once.
//   • Pitfalls: Errors in polar angle sorting, especially for collinear edges.; Failing to correctly mark directed edges as visited, leading to infinite loops or duplicate faces.
// - Longest increasing subsequence (array, greedy, dp-1d)
//   • When to use: Use when finding the longest sequence of elements in a given array such that each element is greater than the preceding one, without changing their relative order. It's applicable for optimizing problems involving ordered subsets.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of an array where elements are in strictly increasing order. It can be solved in O(N log N) time using a greedy approach with binary search, or O(N^2) using dynamic programming.
//   • Invariants: The 'tails' array elements are always in strictly increasing order.; tails[i] stores the smallest possible ending element of an increasing subsequence of length i+1.
//   • Tips: Prefer the O(N log N) greedy approach with binary search for better performance.; The 'tails' array in the greedy approach stores the smallest tail of all increasing subsequences of a certain length.
//   • Pitfalls: Confusing LIS with Longest Common Subsequence (LCS) or contiguous subarrays.; Incorrectly handling duplicate elements when 'strictly increasing' is required.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findRedundantConnection(int** edges, int edgesSize, int* edgesColSize, int* returnSize) {
    int parent[edgesSize + 1];
    for (int i = 1; i <= edgesSize; i++) {
        parent[i] = i;
    }

    // Find function with path compression
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // Union function
    int unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY) {
            return 0; // Cycle detected
        }
        parent[rootY] = rootX;
        return 1; // Union successful
    }

    int* result = (int*)malloc(2 * sizeof(int));
    *returnSize = 2;

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        if (!unionSets(u, v)) {
            result[0] = u;
            result[1] = v;
        }
    }

    return result;      
}
