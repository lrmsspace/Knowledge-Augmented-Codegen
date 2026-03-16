// Source: https://leetcode.com/problems/minimum-cost-homecoming-of-a-robot-in-a-grid/   |   Difficulty: Medium
//
// Problem Description:
// There is an m x n grid, where (0, 0) is the top-left cell and (m - 1, n - 1) is the bottom-right cell. You are given an integer array startPos where startPos = [startrow, startcol] indicates that initially, a robot is at the cell (startrow, startcol). You are also given an integer array homePos where homePos = [homerow, homecol] indicates that its home is at the cell (homerow, homecol).
//
// The robot needs to go to its home. It can move one cell in four directions: left, right, up, or down, and it can not move outside the boundary. Every move incurs some cost. You are further given two 0-indexed integer arrays: rowCosts of length m and colCosts of length n.
//
//
// 	If the robot moves up or down into a cell whose row is r, then this move costs rowCosts[r].
// 	If the robot moves left or right into a cell whose column is c, then this move costs colCosts[c].
//
//
// Return the minimum total cost for this robot to return home.
//
// Example:
// Input: startPos = [1, 0], homePos = [2, 3], rowCosts = [5, 4, 3], colCosts = [8, 2, 6, 7]
// Output: 18
// Explanation: One optimal path is that:
// Starting from (1, 0)
// -> It goes down to (2, 0). This move costs rowCosts[2] = 3.
// -> It goes right to (2, 1). This move costs colCosts[1] = 2.
// -> It goes right to (2, 2). This move costs colCosts[2] = 6.
// -> It goes right to (2, 3). This move costs colCosts[3] = 7.
// The total cost is 3 + 2 + 6 + 7 = 18
//
// Constraints:
// m == rowCosts.length
// 	n == colCosts.length
// 	1 <= m, n <= 105
// 	0 <= rowCosts[r], colCosts[c] <= 104
// 	startPos.length == 2
// 	homePos.length == 2
// 	0 <= startrow, homerow < m
// 	0 <= startcol, homecol < n
//
// Helpful references (internal KB):
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
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
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} startPos
 * @param {number[]} homePos
 * @param {number[]} rowCosts
 * @param {number[]} colCosts
 * @return {number}
 */
var minCost = function(startPos, homePos, rowCosts, colCosts) {
    let totalCost = 0;
    const [startRow, startCol] = startPos;
    const [homeRow, homeCol] = homePos;

    // Move vertically towards the home row
    if (startRow < homeRow) {
        for (let r = startRow + 1; r <= homeRow; r++) {
            totalCost += rowCosts[r];
        }
    } else {
        for (let r = startRow - 1; r >= homeRow; r--) {
            totalCost += rowCosts[r];
        }
    }

    // Move horizontally towards the home column
    if (startCol < homeCol) {
        for (let c = startCol + 1; c <= homeCol; c++) {
            totalCost += colCosts[c];
        }
    } else {
        for (let c = startCol - 1; c >= homeCol; c--) {
            totalCost += colCosts[c];
        }
    }

    return totalCost;
};
