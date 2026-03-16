// Source: https://leetcode.com/problems/number-of-ways-to-reconstruct-a-tree/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array pairs, where pairs[i] = [xi, yi], and:
//
//
// 	There are no duplicates.
// 	xi < yi
//
//
// Let ways be the number of rooted trees that satisfy the following conditions:
//
//
// 	The tree consists of nodes whose values appeared in pairs.
// 	A pair [xi, yi] exists in pairs if and only if xi is an ancestor of yi or yi is an ancestor of xi.
// 	Note: the tree does not have to be a binary tree.
//
//
// Two ways are considered to be different if there is at least one node that has different parents in both ways.
//
// Return:
//
//
// 	0 if ways == 0
// 	1 if ways == 1
// 	2 if ways > 1
//
//
// A rooted tree is a tree that has a single root node, and all edges are oriented to be outgoing from the root.
//
// An ancestor of a node is any node on the path from the root to that node (excluding the node itself). The root has no ancestors.
//
// Example:
// Input: pairs = [[1,2],[2,3]]
// Output: 1
// Explanation: There is exactly one valid rooted tree, which is shown in the above figure.
//
// Constraints:
// 1 <= pairs.length <= 105
// 	1 <= xi < yi <= 500
// 	The elements in pairs are unique.
//
// Helpful references (internal KB):
// - Depth First Search (tree, graph, dfs)
//   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
//   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
//   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
//   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
// - Strong Orientation (graph, tree, dfs)
//   • When to use: Use this when you need to convert an undirected, bridgeless, and connected graph into a strongly connected directed graph, ensuring reachability between any two vertices.
//   • Idea: This algorithm transforms a bridgeless, connected undirected graph into a strongly connected directed graph by performing a Depth-First Search. It orients DFS tree edges away from the root and back edges towards ancestors, achieving strong connectivity in O(V+E) time.
//   • Invariants: All DFS tree edges discovered so far are oriented from parent to child.; All back edges discovered so far are oriented from child to ancestor.
//   • Tips: Verify the input graph is connected and bridgeless before applying the algorithm.; During DFS, mark visited vertices and track parent-child relationships to distinguish edge types.
//   • Pitfalls: Applying to a graph with bridges will result in a non-strongly connected graph.; Incorrectly identifying or orienting back edges can break the strong connectivity property.
// - Check whether a graph is bipartite (graph, queue, bfs)
//   • When to use: Use this when you need to determine if an undirected graph can be divided into two independent sets such that all edges connect vertices from different sets, or if it is two-colorable.
//   • Idea: This algorithm determines if an undirected graph is bipartite by attempting to 2-color it using BFS. It assigns alternating colors (or sets) to adjacent vertices, detecting non-bipartite conditions if an edge connects two vertices of the same color.
//   • Invariants: All visited vertices within the current BFS component are correctly 2-colored.; All edges processed so far connect vertices of different colors.
//   • Tips: Use two distinct colors (e.g., 0 and 1) to represent the two sets.; Iterate through all vertices and start a new BFS from any unvisited vertex to handle disconnected components.
//   • Pitfalls: Forgetting to handle disconnected graphs by ensuring all vertices are visited.; Incorrectly assigning colors, leading to false positives or negatives.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int checkWays(int** pairs, int pairsSize, int* pairsColSize) {
    int maxNode = 0;
    for (int i = 0; i < pairsSize; ++i) {
        if (pairs[i][0] > maxNode) maxNode = pairs[i][0];
        if (pairs[i][1] > maxNode) maxNode = pairs[i][1];
    }
    int n = maxNode + 1;

    int **adj = (int**)calloc(n, sizeof(int*));
    int *deg = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < pairsSize; ++i) {
        int u = pairs[i][0], v = pairs[i][1];
        deg[u]++;
        deg[v]++;
    }
    for (int i = 0; i < n; ++i) {
        if (deg[i] > 0) {
            adj[i] = (int*)malloc(deg[i] * sizeof(int));
            deg[i] = 0; // reset for reuse
        }
    }
    for (int i = 0; i < pairsSize; ++i) {
        int u = pairs[i][0], v = pairs[i][1];
        adj[u][deg[u]++] = v;
        adj[v][deg[v]++] = u;
    }

    int *parent = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; ++i) parent[i] = -1;

    int result = 1;
    for (int i = 1; i < n; ++i) {
        if (deg[i] == 0) continue; // not in graph

        int p = -1;
        for (int j = 0; j < deg[i]; ++j) {
            int neighbor = adj[i][j];
            if (parent[neighbor] != -1 || neighbor == 0) {
                if (p == -1 || deg[neighbor] < deg[p]) {
                    p = neighbor;
                }
            }
        }
        if (p == -1) {
            result = 0;
            break;
        }
        parent[i] = p;

        int expectedDeg = deg[p];
        if (expectedDeg == deg[i]) {
            result = 2;
        }
        for (int j = 0; j < deg[i]; ++j) {
            int neighbor = adj[i][j];
            if (neighbor == p) continue;
            int found = 0;
            for (int k = 0; k < deg[p]; ++k) {
                if (adj[p][k] == neighbor) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                result = 0;
                break;
            }
            if (!found) {
                break;
            }

        }
        if (result == 0) {
            break;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (adj[i]) free(adj[i]);
    }
    free(adj);
    free(deg);
    free(parent);
    return result;
}
