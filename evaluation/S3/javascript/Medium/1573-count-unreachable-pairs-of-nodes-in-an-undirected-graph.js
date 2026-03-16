// Source: https://leetcode.com/problems/count-unreachable-pairs-of-nodes-in-an-undirected-graph/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n. There is an undirected graph with n nodes, numbered from 0 to n - 1. You are given a 2D integer array edges where edges[i] = [ai, bi] denotes that there exists an undirected edge connecting nodes ai and bi.
//
// Return the number of pairs of different nodes that are unreachable from each other.
//
// Example:
// Input: n = 3, edges = [[0,1],[0,2],[1,2]]
// Output: 0
// Explanation: There are no pairs of nodes that are unreachable from each other. Therefore, we return 0.
//
// Constraints:
// 1 <= n <= 105
// 	0 <= edges.length <= 2 * 105
// 	edges[i].length == 2
// 	0 <= ai, bi < n
// 	ai != bi
// 	There are no repeated edges.
//
// Helpful references (internal KB):
// - Finding bridges in a graph in O(N+M) (graph, array, dfs)
//   • When to use: Use this algorithm when you need to identify edges whose removal would increase the number of connected components in an undirected graph. It's suitable for analyzing network robustness or critical connections.
//   • Idea: This algorithm uses Depth First Search (DFS) to find bridges in an undirected graph by tracking discovery times and the lowest reachable discovery time from a node or its descendants. It operates in linear time, O(N+M), where N is the number of vertices and M is the number of edges.
//   • Invariants: For any node `u` currently in the DFS stack, `tin[u]` is its unique discovery time.; For any node `u` and its child `v` in the DFS tree, `low[v]` represents the earliest discovery time reachable from `v`'s subtree (including `v`) using at most one back-edge.
//   • Tips: Initialize discovery times (tin) and lowest reachable times (low) arrays, along with a visited array.; Pass the parent vertex to the DFS function to avoid treating the parent edge as a back-edge.
//   • Pitfalls: Forgetting to pass the parent node or incorrectly handling the parent edge, leading to false bridge detections.; Failing to initialize `low` values correctly, especially for leaf nodes or isolated components.
// - Search for connected components in a graph (graph, dfs, bfs, enumeration)
//   • When to use: Use when you need to partition an undirected graph into maximal connected subgraphs where every node is reachable from every other node within its subgraph.
//   • Idea: This algorithm identifies all connected components in an undirected graph by iteratively performing graph traversals (DFS or BFS) from unvisited nodes. It has a time complexity of O(V + E) for adjacency list representation.
//   • Invariants: All nodes visited so far belong to an identified connected component.; Any node currently being visited is part of the current connected component being explored.
//   • Tips: Maintain a visited array or set to track processed nodes.; Iterate through all nodes, starting a new traversal if a node is unvisited.
//   • Pitfalls: Failing to iterate through all nodes to find all components in a disconnected graph.; Not correctly marking nodes as visited during traversal, leading to infinite loops or re-processing.
// - Finding articulation points in a graph in O(N+M) (graph, array, dfs)
//   • When to use: Use when identifying critical nodes whose removal would increase the number of connected components in an undirected graph. It's essential for analyzing network robustness and vulnerability.
//   • Idea: This algorithm finds all articulation points (cut vertices) in an undirected graph using a single Depth First Search traversal. It operates in linear time, O(N+M), where N is vertices and M is edges.
//   • Invariants: For any node `u`, `tin[u]` is its discovery time, and `low[u]` is initialized to `tin[u]`.; After visiting all children `v` of `u` (and their subtrees), `low[u]` will hold the minimum `tin` value reachable from `u` or its descendants via tree edges and at most one back-edge.
//   • Tips: Initialize `tin` (discovery time) and `low` (lowest reachable ancestor) arrays for all vertices.; The root of the DFS tree is an articulation point if it has more than one child in the DFS tree.
//   • Pitfalls: Forgetting to initialize `low[u]` with `tin[u]` before processing children.; Incorrectly applying the `tin[u] <= low[v]` condition to the root node of the DFS tree.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} n
 * @param {number[][]} edges
 * @return {number}
 */
var countPairs = function(n, edges) {
    const graph = new Array(n).fill(0).map(() => []);   
    for (const [a, b] of edges) {
        graph[a].push(b);
        graph[b].push(a);
    }
    const visited = new Array(n).fill(false);
    let count = 0;
    for (let i = 0; i < n; i++) {
        if (!visited[i]) {
            const componentSize = dfs(i, visited, graph);
            count += (n - componentSize) * componentSize;
        }
    }
    return count;
};

function dfs(node, visited, graph) {
    visited[node] = true;
    let size = 1;
    for (const neighbor of graph[node]) {
        if (!visited[neighbor]) {
            size += dfs(neighbor, visited, graph);
        }
    }
    return size;
}