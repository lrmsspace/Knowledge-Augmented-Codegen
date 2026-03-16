// Source: https://leetcode.com/problems/lucky-numbers-in-a-matrix/   |   Difficulty: Easy
//
// Problem Description:
// Given an m x n matrix of distinct numbers, return all lucky numbers in the matrix in any order.
//
// A lucky number is an element of the matrix such that it is the minimum element in its row and maximum in its column.
//
// Example:
// Input: matrix = [[3,7,8],[9,11,13],[15,16,17]]
// Output: [15]
// Explanation: 15 is the only lucky number since it is the minimum in its row and the maximum in its column.
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= n, m <= 50
// 	1 <= matrix[i][j] <= 105.
// 	All elements in the matrix are distinct.
//
// Helpful references (internal KB):
// - Hungarian algorithm for solving the assignment problem (matrix, graph, array, greedy, bfs, enumeration)
//   • When to use: Use when finding a minimum cost perfect matching in a bipartite graph, typically represented as an N x N cost matrix, where each row must be assigned to exactly one column.
//   • Idea: The Hungarian algorithm finds a minimum weight perfect matching in a bipartite graph, solving the assignment problem for an N x N cost matrix. It iteratively finds augmenting paths in an equality graph and adjusts potentials, achieving O(N^3) time complexity.
//   • Invariants: For all i, j, u[i] + v[j] <= A[i][j] (potential condition).; The current matching is always valid (each row/column used at most once).
//   • Tips: Understand the concept of potentials and their role in maintaining the equality graph.; The algorithm can be adapted for maximum profit problems by negating costs.
//   • Pitfalls: Incorrectly updating potentials can lead to non-optimal solutions or infinite loops.; Handling non-square matrices requires careful padding with dummy values.
// - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
//   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
//   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
//   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
//   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
//   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
// - Minimum spanning tree - Prim's algorithm (graph, matrix, array, mst-prim, greedy)
//   • When to use: When you need to find a minimum spanning tree in a connected, weighted graph, especially efficient for dense graphs or when starting from an arbitrary vertex.
//   • Idea: Prim's algorithm is a greedy algorithm that constructs a Minimum Spanning Tree (MST) by iteratively adding the cheapest edge connecting a vertex in the growing tree to a vertex outside it. It typically runs in O(E log V) with a priority queue or O(V^2) with an adjacency matrix.
//   • Invariants: The set of edges chosen so far forms a tree (no cycles) and connects a subset of vertices.; At each step, the chosen edge is the minimum weight edge connecting a vertex in the current MST to a vertex outside it.
//   • Tips: Initialize distances (or minimum edge weights) for all vertices not in the MST to infinity.; Use a priority queue to efficiently retrieve the minimum weight edge connecting to the current MST.
//   • Pitfalls: Failing to correctly update edge weights to neighbors when a new vertex is added to the MST.; Not handling disconnected graphs, which will result in only an MST for the starting component.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} matrix
 * @return {number[]}
 */
var luckyNumbers = function(matrix) {
    const luckyNums = [];
    const rows = matrix.length;
    const cols = matrix[0].length;
    
    // Find the minimum value in each row
    const rowMins = [];
    for (let i = 0; i < rows; i++) {
        let min = matrix[i][0];
        for (let j = 1; j < cols; j++) {
            if (matrix[i][j] < min) {
                min = matrix[i][j];
            }
        }
        rowMins.push(min);
    }
    
    // Find the maximum value in each column
    const colMaxs = [];
    for (let j = 0; j < cols; j++) {
        let max = matrix[0][j];
        for (let i = 1; i < rows; i++) {
            if (matrix[i][j] > max) {
                max = matrix[i][j];
            }
        }
        colMaxs.push(max);
    }
    
    // Check each element to see if it is a lucky number
    for (let i = 0; i < rows; i++) {
        for (let j = 0; j < cols; j++) {
            const val = matrix[i][j];
            if (val === rowMins[i] && val === colMaxs[j]) {
                luckyNums.push(val);
            }
        }
    }
    
    return luckyNums;
};
