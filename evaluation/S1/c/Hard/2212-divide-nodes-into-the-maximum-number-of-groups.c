// Source: https://leetcode.com/problems/divide-nodes-into-the-maximum-number-of-groups/   |   Difficulty: Hard
//
// Problem Description:
// You are given a positive integer n representing the number of nodes in an undirected graph. The nodes are labeled from 1 to n.
//
// You are also given a 2D integer array edges, where edges[i] = [ai, bi] indicates that there is a bidirectional edge between nodes ai and bi. Notice that the given graph may be disconnected.
//
// Divide the nodes of the graph into m groups (1-indexed) such that:
//
//
// 	Each node in the graph belongs to exactly one group.
// 	For every pair of nodes in the graph that are connected by an edge [ai, bi], if ai belongs to the group with index x, and bi belongs to the group with index y, then |y - x| = 1.
//
//
// Return the maximum number of groups (i.e., maximum m) into which you can divide the nodes. Return -1 if it is impossible to group the nodes with the given conditions.
//
// Example:
// Input: n = 6, edges = [[1,2],[1,4],[1,5],[2,6],[2,3],[4,6]]
// Output: 4
// Explanation: As shown in the image we:
// - Add node 5 to the first group.
// - Add node 1 to the second group.
// - Add nodes 2 and 4 to the third group.
// - Add nodes 3 and 6 to the fourth group.
// We can see that every edge is satisfied.
// It can be shown that that if we create a fifth group and move any node from the third or fourth group to it, at least on of the edges will not be satisfied.
//
// Constraints:
// 1 <= n <= 500
// 	1 <= edges.length <= 104
// 	edges[i].length == 2
// 	1 <= ai, bi <= n
// 	ai != bi
// 	There is at most one edge between any pair of vertices.
//
// Helpful references (internal KB):
// - Check whether a graph is bipartite (graph, queue, bfs)
//   • When to use: Use this when you need to determine if an undirected graph can be divided into two independent sets such that all edges connect vertices from different sets, or if it is two-colorable.
//   • Idea: This algorithm determines if an undirected graph is bipartite by attempting to 2-color it using BFS. It assigns alternating colors (or sets) to adjacent vertices, detecting non-bipartite conditions if an edge connects two vertices of the same color.
//   • Invariants: All visited vertices within the current BFS component are correctly 2-colored.; All edges processed so far connect vertices of different colors.
//   • Tips: Use two distinct colors (e.g., 0 and 1) to represent the two sets.; Iterate through all vertices and start a new BFS from any unvisited vertex to handle disconnected components.
//   • Pitfalls: Forgetting to handle disconnected graphs by ensuring all vertices are visited.; Incorrectly assigning colors, leading to false positives or negatives.
// - Search for connected components in a graph (graph, dfs, bfs, enumeration)
//   • When to use: Use when you need to partition an undirected graph into maximal connected subgraphs where every node is reachable from every other node within its subgraph.
//   • Idea: This algorithm identifies all connected components in an undirected graph by iteratively performing graph traversals (DFS or BFS) from unvisited nodes. It has a time complexity of O(V + E) for adjacency list representation.
//   • Invariants: All nodes visited so far belong to an identified connected component.; Any node currently being visited is part of the current connected component being explored.
//   • Tips: Maintain a visited array or set to track processed nodes.; Iterate through all nodes, starting a new traversal if a node is unvisited.
//   • Pitfalls: Failing to iterate through all nodes to find all components in a disconnected graph.; Not correctly marking nodes as visited during traversal, leading to infinite loops or re-processing.
// - Counting labeled graphs (number, recursion, counting, dp-1d)
//   • When to use: When the problem requires enumerating distinct labeled graphs with specific properties, such as connectivity, on a given number of vertices. It is suitable for combinatorial counting problems involving graph structures.
//   • Idea: This technique determines the number of connected labeled graphs by subtracting the count of disconnected graphs from the total. It typically employs a recursive or dynamic programming approach, often involving combinatorial terms like binomial coefficients, with a polynomial time complexity.
//   • Invariants: The total number of labeled graphs $G_n$ for $n$ vertices is always $2^{n(n-1)/2}$.; For any $n$, the sum of connected and disconnected labeled graphs equals the total number of labeled graphs.
//   • Tips: Start with the total number of labeled graphs $G_n = 2^{n(n-1)/2}$.; Use complementary counting: total graphs minus disconnected graphs.
//   • Pitfalls: Forgetting to divide by $n$ when converting from rooted to unrooted disconnected graphs.; Incorrectly handling base cases for recursive definitions or DP states.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int magnificentSets(int n, int** edges, int edgesSize, int* edgesColSize) {
    /* Build adjacency list */
    int **adj = (int**)malloc((n + 1) * sizeof(int*));
    int *adjSizes = (int*)calloc(n + 1, sizeof(int));
    for (int i = 0; i <= n; ++i) {
        adj[i] = (int*)malloc(n * sizeof(int)); /* max n-1 neighbors */
    }
    for (int i = 0; i < edgesSize; ++i) {
        int u = edges[i][0], v = edges[i][1];
        adj[u][adjSizes[u]++] = v;
        adj[v][adjSizes[v]++] = u;
    }

    int *visited = (int*)calloc(n + 1, sizeof(int));
    int result = 0;

    /* BFS function to check bipartiteness and find max depth */
    int bfs(int start) {
        int queue[n + 1];
        int front = 0, back = 0;
        queue[back++] = start;
        visited[start] = 1; /* level 1 */
        int maxLevel = 1;

        while (front < back) {
            int node = queue[front++];
            int currLevel = visited[node];

            for (int i = 0; i < adjSizes[node]; ++i) {
                int neighbor = adj[node][i];
                if (!visited[neighbor]) {
                    visited[neighbor] = currLevel + 1;
                    if (visited[neighbor] > maxLevel) maxLevel = visited[neighbor];
                    queue[back++] = neighbor;
                } else if ((visited[neighbor] % 2) == (currLevel % 2)) {
                    return -1; /* not bipartite */
                }
            }
        }
        return maxLevel;
    }

    /* Process each component */
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            int depth = bfs(i);
            if (depth == -1) {
                result = -1;
                break;
            }
            result += depth;
        }
    }

    /* Free memory */
    for (int i = 0; i <= n; ++i) {
        free(adj[i]);
    }
    free(adj);
    free(adjSizes);
    free(visited);

    return result;      
}
