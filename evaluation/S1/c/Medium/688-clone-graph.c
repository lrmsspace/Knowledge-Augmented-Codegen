// Source: https://leetcode.com/problems/clone-graph/   |   Difficulty: Medium
//
// Problem Description:
// Given a reference of a node in a connected undirected graph.
//
// Return a deep copy (clone) of the graph.
//
// Each node in the graph contains a value (int) and a list (List[Node]) of its neighbors.
//
//
// class Node {
//     public int val;
//     public List<Node> neighbors;
// }
//
//
//  
//
// Test case format:
//
// For simplicity, each node's value is the same as the node's index (1-indexed). For example, the first node with val == 1, the second node with val == 2, and so on. The graph is represented in the test case using an adjacency list.
//
// An adjacency list is a collection of unordered lists used to represent a finite graph. Each list describes the set of neighbors of a node in the graph.
//
// The given node will always be the first node with val = 1. You must return the copy of the given node as a reference to the cloned graph.
//
// Example:
// Input: adjList = [[2,4],[1,3],[2,4],[1,3]]
// Output: [[2,4],[1,3],[2,4],[1,3]]
// Explanation: There are 4 nodes in the graph.
// 1st node (val = 1)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
// 2nd node (val = 2)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).
// 3rd node (val = 3)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
// 4th node (val = 4)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).
//
// Constraints:
// The number of nodes in the graph is in the range [0, 100].
// 	1 <= Node.val <= 100
// 	Node.val is unique for each node.
// 	There are no repeated edges and no self-loops in the graph.
// 	The Graph is connected and all nodes can be visited starting from the given node.
//
// Helpful references (internal KB):
// - Search for connected components in a graph (graph, dfs, bfs, enumeration)
//   • When to use: Use when you need to partition an undirected graph into maximal connected subgraphs where every node is reachable from every other node within its subgraph.
//   • Idea: This algorithm identifies all connected components in an undirected graph by iteratively performing graph traversals (DFS or BFS) from unvisited nodes. It has a time complexity of O(V + E) for adjacency list representation.
//   • Invariants: All nodes visited so far belong to an identified connected component.; Any node currently being visited is part of the current connected component being explored.
//   • Tips: Maintain a visited array or set to track processed nodes.; Iterate through all nodes, starting a new traversal if a node is unvisited.
//   • Pitfalls: Failing to iterate through all nodes to find all components in a disconnected graph.; Not correctly marking nodes as visited during traversal, leading to infinite loops or re-processing.
// - Multi source BFS (queue, graph, multi-source-bfs, bfs)
//   • When to use: Use when you need to find the shortest distance from any of a given set of source nodes to all other reachable nodes in an unweighted graph or grid.
//   • Idea: Multi-source BFS explores a graph or grid by starting from multiple initial nodes simultaneously, finding the shortest path from any of these sources to all other reachable nodes. It operates in O(V + E) time for graphs or O(rows * cols) for grids.
//   • Invariants: All nodes currently in the queue are at the same shortest distance level from any source.; When a node `u` is dequeued, `dist[u]` represents the finalized shortest distance from any source to `u`.
//   • Tips: Initialize distances for all sources to 0 and add them to the queue.; Use a `visited` array or set to prevent redundant processing of nodes.
//   • Pitfalls: Forgetting to mark initial sources as visited before adding to the queue.; Incorrectly initializing distances for non-source nodes (should be infinity or a large value).
// - Finding bridges in a graph in O(N+M) (graph, dfs)
//   • When to use: Use this algorithm to identify critical edges in an undirected graph whose removal would increase the number of connected components, effectively disconnecting parts of the graph.
//   • Idea: This algorithm finds all bridges in an undirected graph by performing a Depth First Search and tracking discovery times and lowest reachable ancestors. It operates with an optimal time complexity of O(N+M).
//   • Invariants: For any visited vertex u, disc[u] stores its discovery time in the DFS tree.; For any visited vertex u, low[u] stores the minimum discovery time reachable from u (including u) through u's subtree and at most one back-edge.
//   • Tips: Maintain discovery times (disc) and low-link values (low) for each vertex during DFS.; Initialize low[u] = disc[u] when first visiting vertex u.
//   • Pitfalls: Forgetting to mark visited nodes can lead to infinite loops or incorrect low-link values.; Incorrectly handling the parent edge during DFS, treating it as a back-edge.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     int numNeighbors;
 *     struct Node** neighbors;
 * };
 */

struct Node *cloneGraph(struct Node *s) {
    if (!s) return NULL;

    // Create a mapping from original nodes to their clones
    struct Node* map[101] = { NULL };

    // BFS queue
    struct Node* queue[101];
    int front = 0, back = 0;

    // Clone the starting node and enqueue it
    struct Node* cloneStart = (struct Node*)malloc(sizeof(struct Node));
    cloneStart->val = s->val;
    cloneStart->numNeighbors = s->numNeighbors;
    cloneStart->neighbors = (struct Node**)malloc(sizeof(struct Node*) * s->numNeighbors);
    map[s->val] = cloneStart;
    queue[back++] = s;

    while (front < back) {
        struct Node* curr = queue[front++];
        struct Node* currClone = map[curr->val];

        for (int i = 0; i < curr->numNeighbors; i++) {
            struct Node* neighbor = curr->neighbors[i];
            if (!map[neighbor->val]) {
                // Clone the neighbor if it hasn't been cloned yet
                struct Node* neighborClone = (struct Node*)malloc(sizeof(struct Node));
                neighborClone->val = neighbor->val;
                neighborClone->numNeighbors = neighbor->numNeighbors;
                neighborClone->neighbors = (struct Node**)malloc(sizeof(struct Node*) * neighbor->numNeighbors);
                map[neighbor->val] = neighborClone;
                queue[back++] = neighbor;
            }
            // Link the cloned neighbor to the current cloned node
            currClone->neighbors[i] = map[neighbor->val];
        }
    }

    return cloneStart;  	
}
