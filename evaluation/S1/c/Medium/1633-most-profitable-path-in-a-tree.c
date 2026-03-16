// Source: https://leetcode.com/problems/most-profitable-path-in-a-tree/   |   Difficulty: Medium
//
// Problem Description:
// There is an undirected tree with n nodes labeled from 0 to n - 1, rooted at node 0. You are given a 2D integer array edges of length n - 1 where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
//
// At every node i, there is a gate. You are also given an array of even integers amount, where amount[i] represents:
//
//
// 	the price needed to open the gate at node i, if amount[i] is negative, or,
// 	the cash reward obtained on opening the gate at node i, otherwise.
//
//
// The game goes on as follows:
//
//
// 	Initially, Alice is at node 0 and Bob is at node bob.
// 	At every second, Alice and Bob each move to an adjacent node. Alice moves towards some leaf node, while Bob moves towards node 0.
// 	For every node along their path, Alice and Bob either spend money to open the gate at that node, or accept the reward. Note that:
// 	
// 		If the gate is already open, no price will be required, nor will there be any cash reward.
// 		If Alice and Bob reach the node simultaneously, they share the price/reward for opening the gate there. In other words, if the price to open the gate is c, then both Alice and Bob pay c / 2 each. Similarly, if the reward at the gate is c, both of them receive c / 2 each.
// 	
// 	
// 	If Alice reaches a leaf node, she stops moving. Similarly, if Bob reaches node 0, he stops moving. Note that these events are independent of each other.
//
//
// Return the maximum net income Alice can have if she travels towards the optimal leaf node.
//
// Example:
// Input: edges = [[0,1],[1,2],[1,3],[3,4]], bob = 3, amount = [-2,4,2,-4,6]
// Output: 6
// Explanation: 
// The above diagram represents the given tree. The game goes as follows:
// - Alice is initially on node 0, Bob on node 3. They open the gates of their respective nodes.
//   Alice's net income is now -2.
// - Both Alice and Bob move to node 1. 
//   Since they reach here simultaneously, they open the gate together and share the reward.
//   Alice's net income becomes -2 + (4 / 2) = 0.
// - Alice moves on to node 3. Since Bob already opened its gate, Alice's income remains unchanged.
//   Bob moves on to node 0, and stops moving.
// - Alice moves on to node 4 and opens the gate there. Her net income becomes 0 + 6 = 6.
// Now, neither Alice nor Bob can make any further moves, and the game ends.
// It is not possible for Alice to get a higher net income.
//
// Constraints:
// 2 <= n <= 105
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	0 <= ai, bi < n
// 	ai != bi
// 	edges represents a valid tree.
// 	1 <= bob < n
// 	amount.length == n
// 	amount[i] is an even integer in the range [-104, 104].
//
// Helpful references (internal KB):
// - 0-1 BFS (graph, deque, 01-bfs, bfs)
//   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently computes single-source shortest paths, outperforming Dijkstra's for this specific weight constraint.
//   • Idea: 0-1 BFS is a graph traversal algorithm that finds the single-source shortest paths in a graph where all edge weights are restricted to 0 or 1. It uses a deque to process nodes, achieving an optimal time complexity of O(V + E).
//   • Invariants: When a node 'u' is extracted from the front of the deque, 'dist[u]' is its shortest path from the source.; The deque always contains nodes whose distances are either 'D' or 'D+1', where 'D' is the distance of the last node extracted.
//   • Tips: Always push 0-weight edges to the front of the deque.; Push 1-weight edges to the back of the deque.
//   • Pitfalls: Pushing 0-weight edges to the back or 1-weight edges to the front of the deque.; Not correctly initializing distances or the source node.
// - Depth First Search (tree, graph, dfs)
//   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
//   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
//   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
//   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
// - Finding the Eulerian path in O(M) (graph, enumeration, bfs)
//   • When to use: Use when the problem requires visiting every edge in a graph exactly once, either starting and ending at the same vertex (cycle) or at two different vertices (path).
//   • Idea: An Eulerian path is a trail in a graph which visits every edge exactly once. An Eulerian cycle is an Eulerian path that starts and ends on the same vertex.
//   • Invariants: Every edge in the graph is considered exactly once for inclusion in the path.; The current path segment always forms a valid trail in the graph.
//   • Tips: Check vertex degrees to determine path/cycle existence before attempting to find it.; For an Eulerian path, start traversal from one of the two odd-degree vertices.
//   • Pitfalls: Incorrectly handling multi-edges or self-loops can lead to errors in degree calculation or traversal.; Failing to check graph connectivity can result in incomplete paths or infinite loops.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int mostProfitablePath(int** edges, int edgesSize, int* edgesColSize, int bob, int* amount, int amountSize) {
    /* Build adjacency list */
    int n = amountSize;
    int *adjSizes = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < edgesSize; ++i) {
        adjSizes[edges[i][0]]++;
        adjSizes[edges[i][1]]++;
    }
    int **adj = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        adj[i] = (int*)malloc(adjSizes[i] * sizeof(int));
        adjSizes[i] = 0;
    }
    for (int i = 0; i < edgesSize; ++i) {
        int u = edges[i][0], v = edges[i][1];
        adj[u][adjSizes[u]++] = v;
        adj[v][adjSizes[v]++] = u;
    }

    /* Find Bob's path to root using DFS */
    int *bobPath = (int*)malloc(n * sizeof(int));
    int bobPathLen = 0;
    bool *visited = (bool*)calloc(n, sizeof(bool));
    void dfsBob(int node, int target) {
        if (node == target) {
            bobPath[bobPathLen++] = node;
            return;
        }
        visited[node] = true;
        for (int i = 0; i < adjSizes[node]; ++i) {
            int neighbor = adj[node][i];
            if (!visited[neighbor]) {
                dfsBob(neighbor, target);
                if (bobPathLen > 0) {
                    bobPath[bobPathLen++] = node;
                    return;
                }
            }
        }
    }
    dfsBob(bob, 0);

    /* Mark Bob's arrival times */
    int *bobArrival = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) bobArrival[i] = -1;
    for (int t = 0; t < bobPathLen; ++t) {
        bobArrival[bobPath[t]] = t;
    }

    /* DFS for Alice's optimal path */
    int maxProfit = -1000000000;
    void dfsAlice(int node, int time, int currentProfit) {
        visited[node] = true;

        /* Calculate profit at this node */
        if (bobArrival[node] == -1 || time < bobArrival[node]) {
            currentProfit += amount[node];
        } else if (time == bobArrival[node]) {
            currentProfit += amount[node] / 2;
        }
        bool isLeaf = true;
        for (int i = 0; i < adjSizes[node]; ++i) {
            int neighbor = adj[node][i];
            if (!visited[neighbor]) {
                isLeaf = false;
                dfsAlice(neighbor, time + 1, currentProfit);
            }
        }
        if (isLeaf) {
            if (currentProfit > maxProfit) {
                maxProfit = currentProfit;
            }
        }
        visited[node] = false;
    }
    visited = (bool*)calloc(n, sizeof(bool));
    dfsAlice(0, 0, 0);
    /* Free allocated memory */
    for (int i = 0; i < n; ++i) {
        free(adj[i]);
    }
    free(adj);
    free(adjSizes);
    free(bobPath);
    free(bobArrival);
    free(visited);
    return maxProfit;
}
