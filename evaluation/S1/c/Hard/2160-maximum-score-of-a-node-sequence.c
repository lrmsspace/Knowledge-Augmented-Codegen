// Source: https://leetcode.com/problems/maximum-score-of-a-node-sequence/   |   Difficulty: Hard
//
// Problem Description:
// There is an undirected graph with n nodes, numbered from 0 to n - 1.
//
// You are given a 0-indexed integer array scores of length n where scores[i] denotes the score of node i. You are also given a 2D integer array edges where edges[i] = [ai, bi] denotes that there exists an undirected edge connecting nodes ai and bi.
//
// A node sequence is valid if it meets the following conditions:
//
//
// 	There is an edge connecting every pair of adjacent nodes in the sequence.
// 	No node appears more than once in the sequence.
//
//
// The score of a node sequence is defined as the sum of the scores of the nodes in the sequence.
//
// Return the maximum score of a valid node sequence with a length of 4. If no such sequence exists, return -1.
//
// Example:
// Input: scores = [5,2,9,8,4], edges = [[0,1],[1,2],[2,3],[0,2],[1,3],[2,4]]
// Output: 24
// Explanation: The figure above shows the graph and the chosen node sequence [0,1,2,3].
// The score of the node sequence is 5 + 2 + 9 + 8 = 24.
// It can be shown that no other node sequence has a score of more than 24.
// Note that the sequences [3,1,2,0] and [1,0,2,3] are also valid and have a score of 24.
// The sequence [0,3,2,4] is not valid since no edge connects nodes 0 and 3.
//
// Constraints:
// n == scores.length
// 	4 <= n <= 5 * 104
// 	1 <= scores[i] <= 108
// 	0 <= edges.length <= 5 * 104
// 	edges[i].length == 2
// 	0 <= ai, bi <= n - 1
// 	ai != bi
// 	There are no duplicate edges.
//
// Helpful references (internal KB):
// - Minimum Spanning Trees (graph, greedy)
//   • When to use: When you need to find a subset of edges in a connected, edge-weighted graph that connects all vertices with the minimum possible total edge weight. Useful for network design problems where minimizing connection costs is crucial.
//   • Idea: A Minimum Spanning Tree (MST) algorithm finds a subset of edges in an edge-weighted graph that connects all vertices with the minimum possible total weight, forming a tree. This is typically solved using greedy approaches with a time complexity often involving sorting edges or using a priority queue.
//   • Invariants: The set of edges selected so far always forms a forest.; Each connected component formed by the chosen edges is a valid subtree of some Minimum Spanning Tree.
//   • Tips: Greedy approaches often work by iteratively adding the cheapest valid edge or expanding from a starting vertex.; The cut property and cycle property are fundamental for proving correctness of MST algorithms.
//   • Pitfalls: Assuming the graph is always connected; disconnected graphs require finding a minimum spanning forest.; Incorrectly applying the greedy choice without ensuring it maintains the MST property (e.g., creating a cycle).
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Games on arbitrary graphs (graph, array, dfs, game-theory)
//   • When to use: Use this algorithm to determine the outcome (win, lose, or draw) for every possible starting position in a two-player game played on a directed graph, assuming both players play optimally.
//   • Idea: This algorithm classifies each vertex in a directed graph as a winning, losing, or draw state for a two-player game. It iteratively applies rules based on neighbor states, optimized by a Depth-First Search on the reversed graph, achieving an O(M) time complexity.
//   • Invariants: A vertex `u` is a winning state if and only if it has at least one successor `v` that is a losing state.; A vertex `u` is a losing state if and only if all its successors `v` are winning states.
//   • Tips: Construct the reversed graph to efficiently propagate state classifications from successors to predecessors.; Initialize states for terminal vertices (those with no outgoing edges) as losing states.
//   • Pitfalls: Forgetting to account for draw states, which occur when neither winning nor losing conditions are met.; Incorrectly classifying terminal nodes; they are typically losing states in normal play games.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maximumScore(int* scores, int scoresSize, int** edges, int edgesSize, int* edgesColSize) {
    /* Build adjacency list with top 3 highest scores for each node */
    int** adj = (int**)malloc(scoresSize * sizeof(int*));
    int* adjSizes = (int*)calloc(scoresSize, sizeof(int));
    for (int i = 0; i < scoresSize; i++) {
        adj[i] = (int*)malloc(3 * sizeof(int));
        for (int j = 0; j < 3; j++) adj[i][j] = -1; // Initialize with -1
    }

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];

        // Update adjacency for u
        for (int j = 0; j < 3; j++) {
            if (adj[u][j] == -1 || scores[v] > scores[adj[u][j]]) {
                for (int k = 2; k > j; k--) adj[u][k] = adj[u][k - 1];
                adj[u][j] = v;
                break;
            }
        }

        // Update adjacency for v
        for (int j = 0; j < 3; j++) {
            if (adj[v][j] == -1 || scores[u] > scores[adj[v][j]]) {
                for (int k = 2; k > j; k--) adj[v][k] = adj[v][k - 1];
                adj[v][j] = u;
                break;
            }
        }
    }

    /* Calculate maximum score of valid node sequences of length 4 */
    int maxScore = -1;
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];

        for (int a = 0; a < 3; a++) {
            int nodeA = adj[u][a];
            if (nodeA == -1 || nodeA == v) continue;

            for (int b = 0; b < 3; b++) {
                int nodeB = adj[v][b];
                if (nodeB == -1 || nodeB == u || nodeB == nodeA) continue;

                int currentScore = scores[nodeA] + scores[u] + scores[v] + scores[nodeB];
                if (currentScore > maxScore) {
                    maxScore = currentScore;
                }
            }
        }
    }
    /* Free allocated memory */
    for (int i = 0; i < scoresSize; i++) {
        free(adj[i]);
    }
    free(adj);
    free(adjSizes);
    return maxScore;
}
