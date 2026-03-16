// Source: https://leetcode.com/problems/maximum-score-after-applying-operations-on-a-tree/   |   Difficulty: Medium
//
// Problem Description:
// There is an undirected tree with n nodes labeled from 0 to n - 1, and rooted at node 0. You are given a 2D integer array edges of length n - 1, where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
//
// You are also given a 0-indexed integer array values of length n, where values[i] is the value associated with the ith node.
//
// You start with a score of 0. In one operation, you can:
//
//
// 	Pick any node i.
// 	Add values[i] to your score.
// 	Set values[i] to 0.
//
//
// A tree is healthy if the sum of values on the path from the root to any leaf node is different than zero.
//
// Return the maximum score you can obtain after performing these operations on the tree any number of times so that it remains healthy.
//
// Example:
// Input: edges = [[0,1],[0,2],[0,3],[2,4],[4,5]], values = [5,2,5,2,1,1]
// Output: 11
// Explanation: We can choose nodes 1, 2, 3, 4, and 5. The value of the root is non-zero. Hence, the sum of values on the path from the root to any leaf is different than zero. Therefore, the tree is healthy and the score is values[1] + values[2] + values[3] + values[4] + values[5] = 11.
// It can be shown that 11 is the maximum score obtainable after any number of operations on the tree.
//
// Constraints:
// 2 <= n <= 2 * 104
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	0 <= ai, bi < n
// 	values.length == n
// 	1 <= values[i] <= 109
// 	The input is generated such that edges represents a valid tree.
//
// Helpful references (internal KB):
// - Depth First Search (tree, graph, dfs)
//   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
//   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
//   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
//   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
// - Heavy-light decomposition (tree, segment-tree, lca, dfs)
//   • When to use: When you need to perform path queries or updates on a tree efficiently, often involving operations like sum, min, max, or XOR on edges/nodes along a path. It transforms tree paths into linear segments for data structure application.
//   • Idea: Heavy-light decomposition partitions a tree into disjoint heavy paths and light edges, allowing tree path operations to be performed efficiently using data structures like segment trees. It typically achieves O(log^2 N) or O(log N) complexity per query/update after O(N log N) or O(N) preprocessing.
//   • Invariants: Each node belongs to exactly one heavy path.; Moving from a node to its parent via a light edge reduces the subtree size by at least half.
//   • Tips: Perform two DFS traversals: one for subtree sizes and parent pointers, another for heavy/light edges and path IDs.; Map tree nodes to a 1D array for segment tree operations based on their position in heavy paths.
//   • Pitfalls: Incorrectly identifying heavy edges (largest subtree size) during the first DFS.; Off-by-one errors when mapping nodes to segment tree indices or handling path boundaries.
// - Longest increasing subsequence (array, dp-1d, segment-tree, coordinate-compress)
//   • When to use: Use when you need to find the longest possible subsequence of a given sequence such that elements in the subsequence are in strictly increasing order, preserving their original relative order.
//   • Idea: This algorithm finds the longest subsequence where elements are in strictly increasing order. It can be solved with dynamic programming in O(N^2) time or optimized to O(N log N) using binary search or a segment tree.
//   • Invariants: The 'tails' array (or DP array) is always sorted in increasing order.; For any index 'i', 'tails[i]' stores the smallest possible ending element of an increasing subsequence of length 'i+1'.
//   • Tips: The O(N log N) approach maintains an array where dp[i] stores the smallest ending element of an increasing subsequence of length i+1.; Binary search is used to find the correct position for the current element in the dp array.
//   • Pitfalls: Confusing subsequence with subarray, which requires contiguous elements.; Incorrectly handling duplicates for strictly increasing versus non-decreasing requirements.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long maximumScoreAfterOperations(int** edges, int edgesSize, int* edgesColSize, int* values, int valuesSize) {
    int n = valuesSize;
    /* Build adjacency list */
    int *adjSizes = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < edgesSize; ++i) {
        adjSizes[edges[i][0]]++;
        adjSizes[edges[i][1]]++;
    }
    int *adjCaps = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        adjCaps[i] = adjSizes[i];
    }
    int **adj = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        adj[i] = (int*)malloc(adjCaps[i] * sizeof(int));
        adjSizes[i] = 0;
    }
    for (int i = 0; i < edgesSize; ++i) {
        int u = edges[i][0], v = edges[i][1];
        adj[u][adjSizes[u]++] = v;
        adj[v][adjSizes[v]++] = u;
    }

    /* DFS to calculate maximum score */
    long long result = 0;

    long long dfs(int node, int parent) {
        long long totalChildScore = 0;
        long long maxChildScore = 0;
        for (int i = 0; i < adjSizes[node]; ++i) {
            int neighbor = adj[node][i];
            if (neighbor == parent) continue;
            long long childScore = dfs(neighbor, node);
            if (childScore > 0) {
                totalChildScore += childScore;
                if (childScore > maxChildScore) {
                    maxChildScore = childScore;
                }
            }
        }
        long long nodeScore = values[node] + totalChildScore;
        if (node != 0) { // Not root
            result += nodeScore - maxChildScore;
            return nodeScore;
        } else { // Root
            result += nodeScore;
            return 0; // Root's return value is not used
        }
    }

    dfs(0, -1);

    /* Free memory */
    for (int i = 0; i < n; ++i) {
        free(adj[i]);
    }
    free(adj);
    free(adjSizes);
    free(adjCaps);

    return result;
}
