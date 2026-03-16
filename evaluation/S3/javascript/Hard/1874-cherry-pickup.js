// Source: https://leetcode.com/problems/cherry-pickup/   |   Difficulty: Hard
//
// Problem Description:
// You are given an n x n grid representing a field of cherries, each cell is one of three possible integers.
//
//
// 	0 means the cell is empty, so you can pass through,
// 	1 means the cell contains a cherry that you can pick up and pass through, or
// 	-1 means the cell contains a thorn that blocks your way.
//
//
// Return the maximum number of cherries you can collect by following the rules below:
//
//
// 	Starting at the position (0, 0) and reaching (n - 1, n - 1) by moving right or down through valid path cells (cells with value 0 or 1).
// 	After reaching (n - 1, n - 1), returning to (0, 0) by moving left or up through valid path cells.
// 	When passing through a path cell containing a cherry, you pick it up, and the cell becomes an empty cell 0.
// 	If there is no valid path between (0, 0) and (n - 1, n - 1), then no cherries can be collected.
//
// Example:
// Input: grid = [[0,1,-1],[1,0,-1],[1,1,1]]
// Output: 5
// Explanation: The player started at (0, 0) and went down, down, right right to reach (2, 2).
// 4 cherries were picked up during this single trip, and the matrix becomes [[0,1,-1],[0,0,-1],[0,0,0]].
// Then, the player went left, up, up, left to return home, picking up one more cherry.
// The total number of cherries picked up is 5, and this is the maximum possible.
//
// Constraints:
// n == grid.length
// 	n == grid[i].length
// 	1 <= n <= 50
// 	grid[i][j] is -1, 0, or 1.
// 	grid[0][0] != -1
// 	grid[n - 1][n - 1] != -1
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
//   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
//   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
//   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
//   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
//   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - Placing Bishops on a Chessboard (array, matrix, dp-2d, recursion)
//   • When to use: Use this approach for counting arrangements of non-attacking pieces on a grid, particularly when piece movement is restricted to specific geometric lines like diagonals. It is effective when constraints allow for independent processing of subsets of the grid.
//   • Idea: This method employs 2D dynamic programming to count the number of ways to place bishops on a chessboard such that no two bishops attack each other. It leverages the property that bishops only attack along diagonals of the same color, processing diagonals iteratively to build up solutions in polynomial time.
//   • Invariants: All bishops placed on diagonals with index less than `i` do not attack each other.; The count `D[i][j]` correctly reflects all valid placements of `j` bishops on diagonals up to `i` of the same color.
//   • Tips: Exploit problem-specific constraints, such as bishop movement along diagonals, to simplify state definitions.; Decompose the problem by processing diagonals of the same color independently to avoid complex interactions.
//   • Pitfalls: Incorrectly handling diagonal numbering or miscalculating the number of squares in a diagonal.; Off-by-one errors when determining the number of available squares for placing a bishop on a diagonal.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} grid
 * @return {number}
 */
var cherryPickup = function(grid) {
    const n = grid.length;
    const dp = Array.from({ length: n }, () => Array(n).fill(-Infinity));
    dp[0][0] = grid[0][0];
        
    for (let k = 1; k < 2 * n - 1; k++) {
        const temp = Array.from({ length: n }, () => Array(n).fill(-Infinity));
        for (let i = Math.max(0, k - n + 1); i <= Math.min(n - 1, k); i++) {
            for (let j = Math.max(0, k - n + 1); j <= Math.min(n - 1, k); j++) {
                if (grid[i][k - i] === -1 || grid[j][k - j] === -1) continue;
                const cherries = grid[i][k - i] + (i !== j ? grid[j][k - j] : 0);
                temp[i][j] = Math.max(temp[i][j], dp[i][j] + cherries);
                if (i > 0) temp[i][j] = Math.max(temp[i][j], dp[i - 1][j] + cherries);
                if (j > 0) temp[i][j] = Math.max(temp[i][j], dp[i][j - 1] + cherries);
                if (i > 0 && j > 0) temp[i][j] = Math.max(temp[i][j], dp[i - 1][j - 1] + cherries);
            }
        }
        for (let i = 0; i < n; i++) {
            for (let j = 0; j < n; j++) {
                dp[i][j] = temp[i][j];
            }
        }
    }
    return Math.max(0, dp[n - 1][n - 1]);
    
};
