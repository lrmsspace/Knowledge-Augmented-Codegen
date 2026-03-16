// Source: https://leetcode.com/problems/minimum-degree-of-a-connected-trio-in-a-graph/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected graph. You are given an integer n which is the number of nodes in the graph and an array edges, where each edges[i] = [ui, vi] indicates that there is an undirected edge between ui and vi.
//
// A connected trio is a set of three nodes where there is an edge between every pair of them.
//
// The degree of a connected trio is the number of edges where one endpoint is in the trio, and the other is not.
//
// Return the minimum degree of a connected trio in the graph, or -1 if the graph has no connected trios.
//
// Example:
// Input: n = 6, edges = [[1,2],[1,3],[3,2],[4,1],[5,2],[3,6]]
// Output: 3
// Explanation: There is exactly one trio, which is [1,2,3]. The edges that form its degree are bolded in the figure above.
//
// Constraints:
// 2 <= n <= 400
// 	edges[i].length == 2
// 	1 <= edges.length <= n * (n-1) / 2
// 	1 <= ui, vi <= n
// 	ui != vi
// 	There are no repeated edges.
//
// Helpful references (internal KB):
// - Finding Bridges Online (graph, tree, union-find, counting)
//   • When to use: Use when you need to dynamically track bridges and 2-edge-connected components in a graph as edges are added. It efficiently updates the graph structure and bridge count in an online fashion.
//   • Idea: This algorithm maintains 2-edge-connected components and bridges in a graph as edges are added, using a Union-Find structure to manage components and a forest to represent the relationships between them. It typically achieves near-amortized constant time per edge addition.
//   • Invariants: Each 2-edge-connected component is represented by a single root in the Union-Find structure.; The set of bridges forms a forest where each node is a 2-edge-connected component.
//   • Tips: Represent 2-edge-connected components using Union-Find for efficient merging.; Maintain a forest where nodes are 2-edge-connected components and edges are bridges.
//   • Pitfalls: Incorrectly identifying when an edge forms a cycle with existing bridges.; Failing to update the bridge count accurately when bridges are removed.
// - Finding the Eulerian path in O(M) (graph, eulerian-circuit, dfs)
//   • When to use: Use when you need to find a path or cycle that traverses every edge exactly once in a given graph. It's applicable when specific vertex degree conditions are met for path or cycle existence.
//   • Idea: This algorithm constructs an Eulerian path or cycle by first verifying vertex degree conditions and graph connectivity, then performing a recursive DFS-like traversal to build the path. It achieves a time complexity of O(M), where M is the number of edges.
//   • Invariants: Every edge in the constructed path has been traversed exactly once.; All edges incident to the current vertex have been explored or are part of the remaining graph.
//   • Tips: Verify graph connectivity, ignoring isolated vertices.; For an Eulerian path, ensure exactly two vertices have odd degrees.
//   • Pitfalls: Failing to check graph connectivity before starting.; Incorrectly counting odd degree vertices for path vs. cycle.
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
 * @return {number}
 */
var minTrioDegree = function(n, edges) {
    const graph = new Array(n + 1).fill(0).map(() => new Set());
    const degree = new Array(n + 1).fill(0);
    
    for (const [u, v] of edges) {
        graph[u].add(v);
        graph[v].add(u);
        degree[u]++;
        degree[v]++;
    }
    
    let minDegree = Infinity;
    
    for (let i = 1; i <= n; i++) {
        for (const j of graph[i]) {
            if (j > i) {
                for (const k of graph[j]) {
                    if (k > j && graph[i].has(k)) {
                        minDegree = Math.min(minDegree, degree[i] + degree[j] + degree[k] - 6);
                    }
                }
            }
        }
    }
    
    return minDegree === Infinity ? -1 : minDegree;
};
