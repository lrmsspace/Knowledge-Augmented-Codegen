// Source: https://leetcode.com/problems/frog-position-after-t-seconds/   |   Difficulty: Hard
//
// Problem Description:
// Given an undirected tree consisting of n vertices numbered from 1 to n. A frog starts jumping from vertex 1. In one second, the frog jumps from its current vertex to another unvisited vertex if they are directly connected. The frog can not jump back to a visited vertex. In case the frog can jump to several vertices, it jumps randomly to one of them with the same probability. Otherwise, when the frog can not jump to any unvisited vertex, it jumps forever on the same vertex.
//
// The edges of the undirected tree are given in the array edges, where edges[i] = [ai, bi] means that exists an edge connecting the vertices ai and bi.
//
// Return the probability that after t seconds the frog is on the vertex target. Answers within 10-5 of the actual answer will be accepted.
//
// Example:
// Input: n = 7, edges = [[1,2],[1,3],[1,7],[2,4],[2,6],[3,5]], t = 2, target = 4
// Output: 0.16666666666666666 
// Explanation: The figure above shows the given graph. The frog starts at vertex 1, jumping with 1/3 probability to the vertex 2 after second 1 and then jumping with 1/2 probability to vertex 4 after second 2. Thus the probability for the frog is on the vertex 4 after 2 seconds is 1/3 * 1/2 = 1/6 = 0.16666666666666666.
//
// Constraints:
// 1 <= n <= 100
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	1 <= ai, bi <= n
// 	1 <= t <= 50
// 	1 <= target <= n
//
// Helpful references (internal KB):
// - Depth-first search (graph, array, dfs)
//   • When to use: Use when you need to explore as far as possible along each branch before backtracking, such as for finding paths, connected components, or cycles in a graph.
//   • Idea: DFS systematically explores a graph by going as deep as possible along each branch before backtracking. It runs in O(V + E) time and uses O(V) extra space.
//   • Invariants: All vertices reachable from the starting vertex through already explored paths are marked as visited.; When exploring a vertex 'u', all its unvisited neighbors 'v' are either currently being visited or will be visited recursively.
//   • Tips: Use a 'visited' array or set to prevent infinite loops in cyclic graphs.; Recursion stack can be managed explicitly with an iterative approach using a stack.
//   • Pitfalls: Stack overflow errors for deep graphs if implemented purely recursively.; Incorrectly handling visited states can lead to infinite loops or incorrect results.
// - Finding bridges in a graph in O(N+M) (graph, dfs)
//   • When to use: Use this algorithm to identify critical edges in an undirected graph whose removal would increase the number of connected components, effectively disconnecting parts of the graph.
//   • Idea: This algorithm finds all bridges in an undirected graph by performing a Depth First Search and tracking discovery times and lowest reachable ancestors. It operates with an optimal time complexity of O(N+M).
//   • Invariants: For any visited vertex u, disc[u] stores its discovery time in the DFS tree.; For any visited vertex u, low[u] stores the minimum discovery time reachable from u (including u) through u's subtree and at most one back-edge.
//   • Tips: Maintain discovery times (disc) and low-link values (low) for each vertex during DFS.; Initialize low[u] = disc[u] when first visiting vertex u.
//   • Pitfalls: Forgetting to mark visited nodes can lead to infinite loops or incorrect low-link values.; Incorrectly handling the parent edge during DFS, treating it as a back-edge.
// - Lowest Common Ancestor (tree, array, dfs)
//   • When to use: Use this algorithm to efficiently find the lowest common ancestor of two nodes in a tree. It is particularly effective for answering multiple LCA queries on a static tree after initial preprocessing.
//   • Idea: This algorithm preprocesses a tree using a DFS to build an Euler tour and record node depths. It transforms Lowest Common Ancestor (LCA) queries into Range Minimum Queries (RMQ) on the Euler tour, enabling O(1) query time after O(N log N) preprocessing.
//   • Invariants: During DFS, `euler` contains the sequence of visited nodes, and `height` stores each node's depth from the root.; The `first` array correctly maps each node to its initial index in the `euler` tour.
//   • Tips: Perform a single DFS to compute node depths and construct the Euler tour along with first occurrences.; Utilize a Sparse Table or Segment Tree for O(1) or O(log N) Range Minimum Query after preprocessing.
//   • Pitfalls: Incorrectly building the Euler tour, especially missing the 'return' visits to parent nodes.; Off-by-one errors when defining the range for the Range Minimum Query on the Euler tour.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

double frogPosition(int n, int** edges, int edgesSize, int* edgesColSize, int t, int target) {
    // Build adjacency list
    int adj[101][101] = {0};
    int deg[101] = {0};
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u][deg[u]++] = v;
        adj[v][deg[v]++] = u;
    }

    // DFS to find probability
    double result = 0.0;
    int visited[101] = {0};

    void dfs(int node, int time, double prob) {
        if (time > t) return;
        visited[node] = 1;

        if (node == target) {
            if (time == t || (time < t && deg[node] == (node == 1 ? 0 : 1))) {
                result += prob;
            }
            visited[node] = 0;
            return;
        }

        int unvisitedCount = 0;
        for (int i = 0; i < deg[node]; i++) {
            if (!visited[adj[node][i]]) {
                unvisitedCount++;
            }
        }

        if (unvisitedCount == 0) {
            dfs(node, time + 1, prob);
        } else {
            for (int i = 0; i < deg[node]; i++) {
                int nextNode = adj[node][i];
                if (!visited[nextNode]) {
                    dfs(nextNode, time + 1, prob / unvisitedCount);
                }
            }
        }

        visited[node] = 0;
    }

    dfs(1, 0, 1.0);
    return result;      
}
