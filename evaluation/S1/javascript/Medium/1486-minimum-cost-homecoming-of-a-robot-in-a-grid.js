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
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Hungarian algorithm for solving the assignment problem (matrix, graph, array, greedy, bfs, enumeration)
//   • When to use: Use when finding a minimum cost perfect matching in a bipartite graph, typically represented as an N x N cost matrix, where each row must be assigned to exactly one column.
//   • Idea: The Hungarian algorithm finds a minimum weight perfect matching in a bipartite graph, solving the assignment problem for an N x N cost matrix. It iteratively finds augmenting paths in an equality graph and adjusts potentials, achieving O(N^3) time complexity.
//   • Invariants: For all i, j, u[i] + v[j] <= A[i][j] (potential condition).; The current matching is always valid (each row/column used at most once).
//   • Tips: Understand the concept of potentials and their role in maintaining the equality graph.; The algorithm can be adapted for maximum profit problems by negating costs.
//   • Pitfalls: Incorrectly updating potentials can lead to non-optimal solutions or infinite loops.; Handling non-square matrices requires careful padding with dummy values.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: Use when scheduling a set of jobs on a single machine to minimize the total weighted completion time, where each job has a processing time and a linear penalty coefficient.
//   • Idea: This algorithm finds an optimal schedule for jobs on a single machine with linear penalty functions by sorting jobs based on a specific ratio. It achieves an optimal solution in O(N log N) time complexity.
//   • Invariants: The partial schedule constructed so far is optimal for the jobs included.; For any two adjacent jobs 'j' and 'k' in the final schedule, if 'j' precedes 'k', then 'c_j/t_j >= c_k/t_k'.
//   • Tips: Derive the sorting criterion using an exchange argument for adjacent jobs.; The optimal order is determined by the ratio of cost coefficient to processing time.
//   • Pitfalls: Incorrectly applying the sorting criterion, especially the ratio order.; Overlooking edge cases like zero processing times or zero penalty coefficients.
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

    // Move vertically
    if (startRow < homeRow) {
        for (let r = startRow + 1; r <= homeRow; r++) {
            totalCost += rowCosts[r];
        }
    } else {
        for (let r = startRow - 1; r >= homeRow; r--) {
            totalCost += rowCosts[r];
        }
    }

    // Move horizontally
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
