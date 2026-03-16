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
// - Search for connected components in a graph (graph, dfs, bfs, enumeration)
//   • When to use: Use when you need to partition an undirected graph into maximal connected subgraphs where every node is reachable from every other node within its subgraph.
//   • Idea: This algorithm identifies all connected components in an undirected graph by iteratively performing graph traversals (DFS or BFS) from unvisited nodes. It has a time complexity of O(V + E) for adjacency list representation.
//   • Invariants: All nodes visited so far belong to an identified connected component.; Any node currently being visited is part of the current connected component being explored.
//   • Tips: Maintain a visited array or set to track processed nodes.; Iterate through all nodes, starting a new traversal if a node is unvisited.
//   • Pitfalls: Failing to iterate through all nodes to find all components in a disconnected graph.; Not correctly marking nodes as visited during traversal, leading to infinite loops or re-processing.
// - The Inclusion-Exclusion Principle (array, number, counting, sieve)
//   • When to use: Use when direct counting of elements satisfying specific conditions is difficult due to overlaps, and you need to find the count of elements satisfying at least one, exactly k, or none of several properties.
//   • Idea: The Inclusion-Exclusion Principle counts the size of a union of sets by alternately adding and subtracting the sizes of intersections of increasing numbers of sets. Its complexity is often exponential in the number of properties.
//   • Invariants: At the start of processing subsets of size k, the running total correctly accounts for all intersections of size less than k.; For every element x, its contribution to the total sum is 1 if it satisfies the target condition, and 0 otherwise.
//   • Tips: Clearly define the properties (P1, P2, ..., Pn) for which elements are counted.; Systematically calculate the sizes of all relevant intersections of properties.
//   • Pitfalls: Incorrectly defining the properties or the universe of elements being counted.; Errors in calculating the sizes of specific intersections of properties.
// - Directed Graphs (graph, matrix, dfs)
//   • When to use: Use when needing to determine reachability between all pairs of vertices in a directed graph, especially for small or dense graphs where O(V*(V+E)) time is acceptable.
//   • Idea: This approach determines all-pairs reachability in a directed graph by performing a Depth-First Search starting from each vertex. It has a time complexity of O(V*(V+E)) and a space complexity of O(V^2).
//   • Invariants: For any vertex u, after its dedicated DFS completes, TC[u][v] is true for all v reachable from u.; The transitive closure matrix TC accurately reflects all-pairs reachability in the original graph.
//   • Tips: Initialize a boolean matrix to store reachability results.; For each vertex, perform a full DFS to mark all nodes reachable from it.
//   • Pitfalls: High time complexity O(V*(V+E)) makes it unsuitable for large sparse graphs.; High space complexity O(V^2) can be prohibitive for graphs with many vertices.
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
    const graph = Array.from({ length: n }, () => []);
    const visited = new Array(n).fill(false);
    
    for (const [u, v] of edges) {
        graph[u].push(v);
        graph[v].push(u);
    }
    
    const bfs = (start) => {
        const queue = [start];
        visited[start] = true;
        let size = 0;
        
        while (queue.length > 0) {
            const node = queue.shift();
            size++;
            
            for (const neighbor of graph[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    queue.push(neighbor);
                }
            }
        }
        
        return size;
    };
    
    let unreachablePairs = 0;
    
    for (let i = 0; i < n; i++) {
        if (!visited[i]) {
            const componentSize = bfs(i);
            unreachablePairs += componentSize * (n - componentSize);
        }
    }
    
    return unreachablePairs / 2; // Each pair is counted twice
};
