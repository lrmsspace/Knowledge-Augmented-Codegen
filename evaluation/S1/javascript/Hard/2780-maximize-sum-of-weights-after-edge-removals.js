// Source: https://leetcode.com/problems/maximize-sum-of-weights-after-edge-removals/   |   Difficulty: Hard
//
// Problem Description:
// There exists an undirected tree with n nodes numbered 0 to n - 1. You are given a 2D integer array edges of length n - 1, where edges[i] = [ui, vi, wi] indicates that there is an edge between nodes ui and vi with weight wi in the tree.
//
// Your task is to remove zero or more edges such that:
//
//
// 	Each node has an edge with at most k other nodes, where k is given.
// 	The sum of the weights of the remaining edges is maximized.
//
//
// Return the maximum possible sum of weights for the remaining edges after making the necessary removals.
//
// Example:
// Input: edges = [[0,1,4],[0,2,2],[2,3,12],[2,4,6]], k = 2
//
// Output: 22
//
// Explanation:
//
//
//
//
// 	Node 2 has edges with 3 other nodes. We remove the edge [0, 2, 2], ensuring that no node has edges with more than k = 2 nodes.
// 	The sum of weights is 22, and we can't achieve a greater sum. Thus, the answer is 22.
//
// Constraints:
// 2 <= n <= 105
// 	1 <= k <= n - 1
// 	edges.length == n - 1
// 	edges[i].length == 3
// 	0 <= edges[i][0] <= n - 1
// 	0 <= edges[i][1] <= n - 1
// 	1 <= edges[i][2] <= 106
// 	The input is generated such that edges form a valid tree.
//
// Helpful references (internal KB):
// - Minimum Spanning Trees (graph, greedy)
//   • When to use: When you need to find a subset of edges in a connected, edge-weighted graph that connects all vertices with the minimum possible total edge weight. Useful for network design problems where minimizing connection costs is crucial.
//   • Idea: A Minimum Spanning Tree (MST) algorithm finds a subset of edges in an edge-weighted graph that connects all vertices with the minimum possible total weight, forming a tree. This is typically solved using greedy approaches with a time complexity often involving sorting edges or using a priority queue.
//   • Invariants: The set of edges selected so far always forms a forest.; Each connected component formed by the chosen edges is a valid subtree of some Minimum Spanning Tree.
//   • Tips: Greedy approaches often work by iteratively adding the cheapest valid edge or expanding from a starting vertex.; The cut property and cycle property are fundamental for proving correctness of MST algorithms.
//   • Pitfalls: Assuming the graph is always connected; disconnected graphs require finding a minimum spanning forest.; Incorrectly applying the greedy choice without ensuring it maintains the MST property (e.g., creating a cycle).
// - Depth First Search (tree, graph, dfs)
//   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
//   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
//   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
//   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
// - Finding faces of a planar graph (graph, array, dfs, enumeration)
//   • When to use: Used to identify and enumerate all faces (regions) of a given planar graph, typically when its geometric embedding is known or can be derived.
//   • Idea: This algorithm finds all faces of a planar graph by traversing edges in a specific angular order around each vertex. It achieves a time complexity of O(N log N) due to sorting, or O(N) if edges are pre-sorted.
//   • Invariants: Every directed edge is part of exactly one face boundary traversal.; At any vertex u, the next edge (u, w) is chosen such that it is immediately counter-clockwise to the incoming edge (v, u) in u's adjacency list.
//   • Tips: Sort adjacent edges by polar angle for each vertex.; Mark directed edges as visited to ensure each face is found once.
//   • Pitfalls: Errors in polar angle sorting, especially for collinear edges.; Failing to correctly mark directed edges as visited, leading to infinite loops or duplicate faces.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} edges
 * @param {number} k
 * @return {number}
 */
var maximizeSumOfWeights = function(edges, k) {
    const n = edges.length + 1; // Since it's a tree with n-1 edges
    const graph = Array.from({ length: n }, () => []);
    
    // Build the adjacency list for the tree
    for (const [u, v, w] of edges) {
        graph[u].push({ node: v, weight: w });
        graph[v].push({ node: u, weight: w });
    }
    
    let maxSum = 0;

    function dfs(node, parent) {
        let weights = [];
        
        for (const { node: neighbor, weight } of graph[node]) {
            if (neighbor === parent) continue; // Skip the edge back to the parent
            
            const childWeight = dfs(neighbor, node);
            weights.push(childWeight + weight);
        }
        
        // Sort weights in descending order and keep only the top k
        weights.sort((a, b) => b - a);
        
        // Add the top k weights to the result
        for (let i = 0; i < Math.min(k, weights.length); i++) {
            maxSum += weights[i];
        }
        
        // Return the maximum weight that can be passed up to the parent
        return weights.length > 0 ? weights[0] : 0;
    }
    
    dfs(0, -1); // Start DFS from node 0 with no parent
    return maxSum;
};
