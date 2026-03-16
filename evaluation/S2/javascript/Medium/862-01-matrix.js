// Source: https://leetcode.com/problems/01-matrix/   |   Difficulty: Medium
//
// Problem Description:
// Given an m x n binary matrix mat, return the distance of the nearest 0 for each cell.
//
// The distance between two cells sharing a common edge is 1.
//
// Example:
// Input: mat = [[0,0,0],[0,1,0],[0,0,0]]
// Output: [[0,0,0],[0,1,0],[0,0,0]]
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= m, n <= 104
// 	1 <= m * n <= 104
// 	mat[i][j] is either 0 or 1.
// 	There is at least one 0 in mat.
//
//
//  
// Note: This question is the same as 1765: https://leetcode.com/problems/map-of-highest-peak/
//
// Helpful references (internal KB):
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, matrix, matrix-exp, floyd-warshall)
//   • When to use: Use when finding the number or shortest length of paths between all pairs of vertices that consist of exactly a given number of edges. It's suitable for problems requiring path properties over a fixed number of steps.
//   • Idea: This technique extends matrix multiplication to find path properties (count or shortest length) of a fixed number of edges in a graph. It leverages binary exponentiation on an adjacency matrix with a modified 'min-plus' or 'sum-product' operation, achieving O(N^3 log K) complexity.
//   • Invariants: After k matrix multiplications, L_k[i][j] stores the shortest path length (or count) from i to j using exactly k edges.; The original adjacency matrix G remains unchanged throughout the exponentiation process.
//   • Tips: For shortest paths, initialize non-existent edges with infinity in the adjacency matrix.; For counting paths, initialize non-existent edges with zero in the adjacency matrix.
//   • Pitfalls: Incorrectly handling the identity matrix for base cases, especially for k=0 paths.; Off-by-one errors when defining the base matrix or the number of matrix multiplications.
// - Multi source BFS (queue, graph, multi-source-bfs, bfs)
//   • When to use: Use when you need to find the shortest distance from any of a given set of source nodes to all other reachable nodes in an unweighted graph or grid.
//   • Idea: Multi-source BFS explores a graph or grid by starting from multiple initial nodes simultaneously, finding the shortest path from any of these sources to all other reachable nodes. It operates in O(V + E) time for graphs or O(rows * cols) for grids.
//   • Invariants: All nodes currently in the queue are at the same shortest distance level from any source.; When a node `u` is dequeued, `dist[u]` represents the finalized shortest distance from any source to `u`.
//   • Tips: Initialize distances for all sources to 0 and add them to the queue.; Use a `visited` array or set to prevent redundant processing of nodes.
//   • Pitfalls: Forgetting to mark initial sources as visited before adding to the queue.; Incorrectly initializing distances for non-source nodes (should be infinity or a large value).
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} mat
 * @return {number[][]}
 */
var updateMatrix = function(mat) {
    const m = mat.length, n = mat[0].length;
    const dist = Array.from({ length: m }, () => Array(n).fill(Infinity));
    const queue = [];
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            if (mat[i][j] === 0) {
                dist[i][j] = 0;
                queue.push([i, j]);
            }
        }
    }
    const directions = [[-1, 0], [1, 0], [0, -1], [0, 1]];
    while (queue.length > 0) {
        const [i, j] = queue.shift();
        for (const [di, dj] of directions) {
            const ni = i + di;
            const nj = j + dj;
            if (ni >= 0 && ni < m && nj >= 0 && nj < n && dist[ni][nj] > dist[i][j] + 1) {
                dist[ni][nj] = dist[i][j] + 1;
                queue.push([ni, nj]);
            }
        }
    }
    return dist;
};
