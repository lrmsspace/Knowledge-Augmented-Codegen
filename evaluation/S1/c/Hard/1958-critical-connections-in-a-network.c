// Source: https://leetcode.com/problems/critical-connections-in-a-network/   |   Difficulty: Hard
//
// Problem Description:
// There are n servers numbered from 0 to n - 1 connected by undirected server-to-server connections forming a network where connections[i] = [ai, bi] represents a connection between servers ai and bi. Any server can reach other servers directly or indirectly through the network.
//
// A critical connection is a connection that, if removed, will make some servers unable to reach some other server.
//
// Return all critical connections in the network in any order.
//
// Example:
// Input: n = 4, connections = [[0,1],[1,2],[2,0],[1,3]]
// Output: [[1,3]]
// Explanation: [[3,1]] is also accepted.
//
// Constraints:
// 2 <= n <= 105
// 	n - 1 <= connections.length <= 105
// 	0 <= ai, bi <= n - 1
// 	ai != bi
// 	There are no repeated connections.
//
// Helpful references (internal KB):
// - Finding bridges in a graph in O(N+M) (graph, dfs)
//   • When to use: Use this algorithm to identify critical edges in an undirected graph whose removal would increase the number of connected components, effectively disconnecting parts of the graph.
//   • Idea: This algorithm finds all bridges in an undirected graph by performing a Depth First Search and tracking discovery times and lowest reachable ancestors. It operates with an optimal time complexity of O(N+M).
//   • Invariants: For any visited vertex u, disc[u] stores its discovery time in the DFS tree.; For any visited vertex u, low[u] stores the minimum discovery time reachable from u (including u) through u's subtree and at most one back-edge.
//   • Tips: Maintain discovery times (disc) and low-link values (low) for each vertex during DFS.; Initialize low[u] = disc[u] when first visiting vertex u.
//   • Pitfalls: Forgetting to mark visited nodes can lead to infinite loops or incorrect low-link values.; Incorrectly handling the parent edge during DFS, treating it as a back-edge.
// - Strong Orientation (graph, dfs, biconnected-components)
//   • When to use: Use when you need to identify maximal subgraphs where removing any single vertex does not disconnect the subgraph. This is crucial for analyzing network robustness and fault tolerance.
//   • Idea: This algorithm decomposes a graph into maximal 2-vertex-connected subgraphs, meaning removing any single vertex does not disconnect them. It uses DFS to identify articulation points and bridges, achieving O(V+E) time complexity.
//   • Invariants: All edges on the DFS stack form part of a potential BCC.; A vertex's low-link value is the minimum discovery time reachable from it (including itself) through its DFS subtree and at most one back-edge.
//   • Tips: Maintain discovery times and low-link values for each vertex.; Use a stack to store edges or vertices of the current DFS path.
//   • Pitfalls: Incorrectly calculating low-link values, especially for back-edges.; Missing the root node articulation point condition (at least two children in DFS tree).
// - Search for connected components in a graph (stack, graph, dfs, recursion)
//   • When to use: Use when the goal is to identify distinct groups of interconnected nodes within a graph, or to find all nodes reachable from a specific starting point.
//   • Idea: Depth-First Search (DFS) explores a graph by traversing as far as possible along each branch before backtracking. It efficiently finds connected components by visiting all reachable nodes from an unvisited starting point, typically with O(V+E) time complexity.
//   • Invariants: All nodes in the current DFS path from the start node to the current node are on the recursion stack.; Any node marked as visited will not be re-processed by the current DFS call.
//   • Tips: Maintain a 'visited' status for each node to prevent cycles and redundant work.; Iterate through all nodes and start DFS if a node is unvisited to find all components.
//   • Pitfalls: Excessive recursion depth can lead to stack overflow errors for large graphs.; Forgetting to mark nodes as visited results in infinite loops in cyclic graphs.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** criticalConnections(int n, int** connections, int connectionsSize, int* connectionsColSize, int* returnSize, int** returnColumnSizes) {
    // Build adjacency list
    int** graph = (int**)malloc(n * sizeof(int*));
    int* graphColSize = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        graph[i] = (int*)malloc(n * sizeof(int)); // worst case
    }
    for (int i = 0; i < connectionsSize; i++) {
        int u = connections[i][0];
        int v = connections[i][1];
        graph[u][graphColSize[u]++] = v;
        graph[v][graphColSize[v]++] = u;
    }

    // Initialize arrays for DFS
    int* disc = (int*)calloc(n, sizeof(int));
    int* low = (int*)calloc(n, sizeof(int));
    int time = 1;

    // Result storage
    int** result = (int**)malloc(connectionsSize * sizeof(int*));
    *returnColumnSizes = (int*)malloc(connectionsSize * sizeof(int));
    int resCount = 0;

    // DFS function
    void dfs(int u, int parent) {
        disc[u] = low[u] = time++;
        for (int i = 0; i < graphColSize[u]; i++) {
            int v = graph[u][i];
            if (v == parent) continue; // skip the edge to parent
            if (disc[v] == 0) { // not visited
                dfs(v, u);
                low[u] = (low[u] < low[v]) ? low[u] : low[v];
                if (low[v] > disc[u]) {
                    result[resCount] = (int*)malloc(2 * sizeof(int));
                    result[resCount][0] = u;
                    result[resCount][1] = v;
                    (*returnColumnSizes)[resCount] = 2;
                    resCount++;
                }
            } else {
                low[u] = (low[u] < disc[v]) ? low[u] : disc[v];
            }
        }
    }

    // Run DFS from each unvisited node
    for (int i = 0; i < n; i++) {
        if (disc[i] == 0) {
            dfs(i, -1);
        }
    }

    // Free graph memory
    for (int i = 0; i < n; i++) {
        free(graph[i]);
    }
    free(graph);
    free(graphColSize);
    free(disc);
    free(low);

    *returnSize = resCount;
    return result;
}