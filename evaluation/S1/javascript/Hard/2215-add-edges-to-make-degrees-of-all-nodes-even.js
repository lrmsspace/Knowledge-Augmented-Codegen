// Source: https://leetcode.com/problems/add-edges-to-make-degrees-of-all-nodes-even/   |   Difficulty: Hard
//
// Problem Description:
// There is an undirected graph consisting of n nodes numbered from 1 to n. You are given the integer n and a 2D array edges where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi. The graph can be disconnected.
//
// You can add at most two additional edges (possibly none) to this graph so that there are no repeated edges and no self-loops.
//
// Return true if it is possible to make the degree of each node in the graph even, otherwise return false.
//
// The degree of a node is the number of edges connected to it.
//
// Example:
// Input: n = 5, edges = [[1,2],[2,3],[3,4],[4,2],[1,4],[2,5]]
// Output: true
// Explanation: The above diagram shows a valid way of adding an edge.
// Every node in the resulting graph is connected to an even number of edges.
//
// Constraints:
// 3 <= n <= 105
// 	2 <= edges.length <= 105
// 	edges[i].length == 2
// 	1 <= ai, bi <= n
// 	ai != bi
// 	There are no repeated edges.
//
// Helpful references (internal KB):
// - Finding faces of a planar graph (graph, array, dfs, enumeration)
//   • When to use: Used to identify and enumerate all faces (regions) of a given planar graph, typically when its geometric embedding is known or can be derived.
//   • Idea: This algorithm finds all faces of a planar graph by traversing edges in a specific angular order around each vertex. It achieves a time complexity of O(N log N) due to sorting, or O(N) if edges are pre-sorted.
//   • Invariants: Every directed edge is part of exactly one face boundary traversal.; At any vertex u, the next edge (u, w) is chosen such that it is immediately counter-clockwise to the incoming edge (v, u) in u's adjacency list.
//   • Tips: Sort adjacent edges by polar angle for each vertex.; Mark directed edges as visited to ensure each face is found once.
//   • Pitfalls: Errors in polar angle sorting, especially for collinear edges.; Failing to correctly mark directed edges as visited, leading to infinite loops or duplicate faces.
// - Undirected Graphs (graph, matrix, simulation)
//   • When to use: Use when modeling symmetric relationships between entities, analyzing graph properties like connectivity or degrees, or simulating processes on a network where connections are bidirectional.
//   • Idea: An undirected graph consists of a set of vertices and a set of edges, where each edge connects two vertices symmetrically. Basic operations often have a time complexity of O(V+E) or O(V^2) depending on representation.
//   • Invariants: For every edge (u, v) in the graph, the edge (v, u) also exists.; The sum of degrees of all vertices equals twice the number of edges.
//   • Tips: Choose adjacency list for sparse graphs, adjacency matrix for dense graphs.; Degrees of vertices are easily calculated from adjacency representations.
//   • Pitfalls: Forgetting to add both (u,v) and (v,u) when using an adjacency matrix or list.; Not handling disconnected components during full graph traversals.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, matrix, matrix-exp, counting)
//   • When to use: Use when needing to count the number of paths of a specific length between all pairs of vertices in a graph, or to find reachability in a fixed number of steps.
//   • Idea: This algorithm leverages matrix exponentiation to find the number of paths of a fixed length `k` between all pairs of vertices in a graph. Each matrix multiplication step extends path lengths by one, resulting in an O(N^3 log K) time complexity for an N-vertex graph.
//   • Invariants: After `m` matrix multiplications, `C_m[i][j]` stores the number of paths of length `m` from `i` to `j`.; The initial adjacency matrix `G` remains constant throughout the exponentiation process.
//   • Tips: Represent the graph as an adjacency matrix where `G[i][j]` is the number of direct edges.; Matrix multiplication `C_k * G` yields `C_{k+1}` for path counts.
//   • Pitfalls: Standard matrix multiplication is O(N^3), leading to O(N^3 log K) overall time complexity.; Memory usage is O(N^2) for storing matrices, which can be prohibitive for very large graphs.
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
 * @return {boolean}
 */
var isPossible = function(n, edges) {
    const degree = new Array(n).fill(0);
    for (const [a, b] of edges) {
        degree[a - 1]++;
        degree[b - 1]++;
    }

    const oddDegreeNodes = [];
    for (let i = 0; i < n; i++) {
        if (degree[i] % 2 !== 0) {
            oddDegreeNodes.push(i);
        }
    }
    const oddCount = oddDegreeNodes.length;

    if (oddCount === 0) {
        return true; // All nodes already have even degree
    } else if (oddCount === 2) {
        // Check if we can connect the two odd degree nodes directly or through an intermediate node
        const [u, v] = oddDegreeNodes;
        const edgeSet = new Set(edges.map(([a, b]) => `${Math.min(a, b)}-${Math.max(a, b)}`));
        if (!edgeSet.has(`${Math.min(u + 1, v + 1)}-${Math.max(u + 1, v + 1)}`)) {
            return true; // Connect u and v directly
        }
        for (let i = 0; i < n; i++) {
            if (i !== u && i !== v) {
                if (!edgeSet.has(`${Math.min(u + 1, i + 1)}-${Math.max(u + 1, i + 1)}`) &&
                    !edgeSet.has(`${Math.min(v + 1, i + 1)}-${Math.max(v + 1, i + 1)}`)) {
                    return true; // Connect u and v through an intermediate node i
                }
            }
        }
        return false; // No valid connection found
    }
    else if (oddCount === 4) {
        // Check if we can pair the four odd degree nodes into two pairs that can be connected
        const edgeSet = new Set(edges.map(([a, b]) => `${Math.min(a, b)}-${Math.max(a, b)}`));
        for (let i = 0; i < 4; i++) {
            for (let j = i + 1; j < 4; j++) {
                const u1 = oddDegreeNodes[i];
                const v1 = oddDegreeNodes[j];
                if (!edgeSet.has(`${Math.min(u1 + 1, v1 + 1)}-${Math.max(u1 + 1, v1 + 1)}`)) {
                    const remainingNodes = oddDegreeNodes.filter((_, idx) => idx !== i && idx !== j);
                    const u2 = remainingNodes[0];
                    const v2 = remainingNodes[1];
                    if (!edgeSet.has(`${Math.min(u2 + 1, v2 + 1)}-${Math.max(u2 + 1, v2 + 1)}`)) {
                        return true; // Connect u1 with v1 and u2 with v2
                    }
                }
            }
        }
        return false; // No valid pairing found
    }
    return false; // More than 4 odd degree nodes cannot be fixed with at most 2 edges

};
