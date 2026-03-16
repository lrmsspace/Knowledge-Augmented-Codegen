// Source: https://leetcode.com/problems/count-pairs-of-nodes/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected graph defined by an integer n, the number of nodes, and a 2D integer array edges, the edges in the graph, where edges[i] = [ui, vi] indicates that there is an undirected edge between ui and vi. You are also given an integer array queries.
//
// Let incident(a, b) be defined as the number of edges that are connected to either node a or b.
//
// The answer to the jth query is the number of pairs of nodes (a, b) that satisfy both of the following conditions:
//
//
// 	a < b
// 	incident(a, b) > queries[j]
//
//
// Return an array answers such that answers.length == queries.length and answers[j] is the answer of the jth query.
//
// Note that there can be multiple edges between the same two nodes.
//
// Example:
// Input: n = 4, edges = [[1,2],[2,4],[1,3],[2,3],[2,1]], queries = [2,3]
// Output: [6,5]
// Explanation: The calculations for incident(a, b) are shown in the table above.
// The answers for each of the queries are as follows:
// - answers[0] = 6. All the pairs have an incident(a, b) value greater than 2.
// - answers[1] = 5. All the pairs except (3, 4) have an incident(a, b) value greater than 3.
//
// Constraints:
// 2 <= n <= 2 * 104
// 	1 <= edges.length <= 105
// 	1 <= ui, vi <= n
// 	ui != vi
// 	1 <= queries.length <= 20
// 	0 <= queries[j] < edges.length
//
// Helpful references (internal KB):
// - Counting labeled graphs (number, dp-2d, counting, recursion)
//   • When to use: When counting the total number of labeled graphs with a specific number of vertices and connected components. Useful for problems requiring enumeration of graph structures based on their connectivity properties.
//   • Idea: This technique uses dynamic programming to count labeled graphs with a given number of vertices and connected components by building up solutions from smaller subproblems. It leverages a recurrence relation that considers the component containing a specific vertex, leading to an O(N^2 * K) time complexity for N vertices and K components.
//   • Invariants: D[i][j] correctly stores the number of labeled graphs with i vertices and j components.; All C_s values for s < n are correctly precomputed before calculating D[n][k].
//   • Tips: Precompute binomial coefficients for efficiency.; Precompute the number of connected graphs (C_s) for all relevant s.
//   • Pitfalls: Incorrectly defining base cases for the dynamic programming table.; Off-by-one errors in binomial coefficient calculations or array indexing.
// - Strongly connected components and the condensation graph (graph, array, dfs, enumeration)
//   • When to use: Use this when systematically exploring all possible configurations, paths, or subsets within a graph or array. It's ideal for finding every solution or verifying properties across all potential states.
//   • Idea: Depth-First Search (DFS) is a graph traversal algorithm that explores as far as possible along each branch before backtracking. When combined with enumeration, it systematically generates all possible combinations or paths, typically with exponential time complexity O(V+E) for traversal or O(N!) / O(2^N) for enumeration.
//   • Invariants: The current path/subset being built is valid up to the current depth.; All previously explored branches from the current node have been fully processed.
//   • Tips: Define clear base cases for recursion termination.; Manage state changes carefully when entering and exiting recursive calls.
//   • Pitfalls: Infinite recursion due to missing or incorrect base cases.; Redundant computations if states are not properly managed or memoized.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
//   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
//   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
//   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
//   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
//   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
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
 * @param {number[]} queries
 * @return {number[]}
 */
var countPairs = function(n, edges, queries) {
    const degree = new Array(n + 1).fill(0);
    const edgeCount = new Map();
    for (const [u, v] of edges) {
        degree[u]++;
        degree[v]++;
        const key = u < v ? `${u},${v}` : `${v},${u}`;
        edgeCount.set(key, (edgeCount.get(key) || 0) + 1);
    }
    const result = [];
    for (const q of queries) {
        let count = 0;
        for (let a = 1; a <= n; a++) {
            for (let b = a + 1; b <= n; b++) {
                const key = `${a},${b}`;
                const incident = degree[a] + degree[b] - (edgeCount.get(key) || 0);
                if (incident > q) {
                    count++;
                }
            }
        }
        result.push(count);
    }
    return result;
    
};
