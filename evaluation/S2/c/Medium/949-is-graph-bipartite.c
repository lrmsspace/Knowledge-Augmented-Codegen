// Source: https://leetcode.com/problems/is-graph-bipartite/   |   Difficulty: Medium
//
// Problem Description:
// There is an undirected graph with n nodes, where each node is numbered between 0 and n - 1. You are given a 2D array graph, where graph[u] is an array of nodes that node u is adjacent to. More formally, for each v in graph[u], there is an undirected edge between node u and node v. The graph has the following properties:
//
//
// 	There are no self-edges (graph[u] does not contain u).
// 	There are no parallel edges (graph[u] does not contain duplicate values).
// 	If v is in graph[u], then u is in graph[v] (the graph is undirected).
// 	The graph may not be connected, meaning there may be two nodes u and v such that there is no path between them.
//
//
// A graph is bipartite if the nodes can be partitioned into two independent sets A and B such that every edge in the graph connects a node in set A and a node in set B.
//
// Return true if and only if it is bipartite.
//
// Example:
// Input: graph = [[1,2,3],[0,2],[0,1,3],[0,2]]
// Output: false
// Explanation: There is no way to partition the nodes into two independent sets such that every edge connects a node in one and a node in the other.
//
// Constraints:
// graph.length == n
// 	1 <= n <= 100
// 	0 <= graph[u].length < n
// 	0 <= graph[u][i] <= n - 1
// 	graph[u] does not contain u.
// 	All the values of graph[u] are unique.
// 	If graph[u] contains v, then graph[v] contains u.
//
// Helpful references (internal KB):
// - Check whether a graph is bipartite (graph, queue, bfs)
//   • When to use: Use this when you need to determine if an undirected graph can be divided into two independent sets such that all edges connect vertices from different sets, or if it is two-colorable.
//   • Idea: This algorithm determines if an undirected graph is bipartite by attempting to 2-color it using BFS. It assigns alternating colors (or sets) to adjacent vertices, detecting non-bipartite conditions if an edge connects two vertices of the same color.
//   • Invariants: All visited vertices within the current BFS component are correctly 2-colored.; All edges processed so far connect vertices of different colors.
//   • Tips: Use two distinct colors (e.g., 0 and 1) to represent the two sets.; Iterate through all vertices and start a new BFS from any unvisited vertex to handle disconnected components.
//   • Pitfalls: Forgetting to handle disconnected graphs by ensuring all vertices are visited.; Incorrectly assigning colors, leading to false positives or negatives.
// - 2-SAT (graph, scc)
//   • When to use: When a problem can be modeled as finding a satisfying assignment for a Boolean formula where each clause contains exactly two literals. It is used to determine if such an assignment exists and to construct one if it does.
//   • Idea: 2-SAT solves the Boolean satisfiability problem for formulas in conjunctive normal form where each clause has exactly two literals. It converts the formula into an implication graph and uses Strongly Connected Components (SCCs) to find a satisfying assignment or determine unsatisfiability in O(N+M) time.
//   • Invariants: Each clause (A OR B) is correctly represented by two implications: (NOT A => B) and (NOT B => A).; The implication graph correctly reflects all logical implications derived from the 2-CNF formula.
//   • Tips: Convert each clause (A OR B) into two implications: (NOT A => B) and (NOT B => A).; Represent each variable X and its negation NOT X as distinct nodes in the implication graph.
//   • Pitfalls: Incorrectly converting clauses to implications, missing one of the two directions.; Failing to handle the critical case where a variable and its negation are in the same SCC.
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

bool isBipartite(int** graph, int graphSize, int* graphColSize) {
    int color[graphSize];
    memset(color, -1, sizeof(color)); // Initialize all vertices as uncolored

    for (int i = 0; i < graphSize; i++) {
        if (color[i] == -1) { // If the vertex is uncolored
            color[i] = 0; // Start coloring with color 0
            int queue[graphSize]; // Queue for BFS
            int front = 0, rear = 0;
            queue[rear++] = i; // Enqueue the starting vertex

            while (front < rear) {
                int u = queue[front++]; // Dequeue a vertex

                for (int j = 0; j < graphColSize[u]; j++) {
                    int v = graph[u][j]; // Get adjacent vertex

                    if (color[v] == -1) { // If the adjacent vertex is uncolored
                        color[v] = 1 - color[u]; // Color with opposite color
                        queue[rear++] = v; // Enqueue the adjacent vertex
                    } else if (color[v] == color[u]) { // If the adjacent vertex has the same color
                        return false; // The graph is not bipartite
                    }
                }
            }
        }
    }

    return true; // The graph is bipartite      
}
