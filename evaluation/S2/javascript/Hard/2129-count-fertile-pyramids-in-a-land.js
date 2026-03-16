// Source: https://leetcode.com/problems/count-fertile-pyramids-in-a-land/   |   Difficulty: Hard
//
// Problem Description:
// A farmer has a rectangular grid of land with m rows and n columns that can be divided into unit cells. Each cell is either fertile (represented by a 1) or barren (represented by a 0). All cells outside the grid are considered barren.
//
// A pyramidal plot of land can be defined as a set of cells with the following criteria:
//
//
// 	The number of cells in the set has to be greater than 1 and all cells must be fertile.
// 	The apex of a pyramid is the topmost cell of the pyramid. The height of a pyramid is the number of rows it covers. Let (r, c) be the apex of the pyramid, and its height be h. Then, the plot comprises of cells (i, j) where r <= i <= r + h - 1 and c - (i - r) <= j <= c + (i - r).
//
//
// An inverse pyramidal plot of land can be defined as a set of cells with similar criteria:
//
//
// 	The number of cells in the set has to be greater than 1 and all cells must be fertile.
// 	The apex of an inverse pyramid is the bottommost cell of the inverse pyramid. The height of an inverse pyramid is the number of rows it covers. Let (r, c) be the apex of the pyramid, and its height be h. Then, the plot comprises of cells (i, j) where r - h + 1 <= i <= r and c - (r - i) <= j <= c + (r - i).
//
//
// Some examples of valid and invalid pyramidal (and inverse pyramidal) plots are shown below. Black cells indicate fertile cells.
//
// Given a 0-indexed m x n binary matrix grid representing the farmland, return the total number of pyramidal and inverse pyramidal plots that can be found in grid.
//
// Example:
// Input: grid = [[0,1,1,0],[1,1,1,1]]
// Output: 2
// Explanation: The 2 possible pyramidal plots are shown in blue and red respectively.
// There are no inverse pyramidal plots in this grid. 
// Hence total number of pyramidal and inverse pyramidal plots is 2 + 0 = 2.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 1000
// 	1 <= m * n <= 105
// 	grid[i][j] is either 0 or 1.
//
// Helpful references (internal KB):
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - 15 Puzzle Game: Existence Of The Solution (matrix, number, counting)
//   • When to use: Use this to quickly determine if a given 15-puzzle board configuration can be solved, avoiding exhaustive search. It's applicable when the goal is to check solvability rather than finding the solution path.
//   • Idea: This algorithm determines the solvability of a 15-puzzle configuration by analyzing the parity of inversions in the tile permutation and the blank tile's row. It involves counting inversions, which typically takes O(N^2) time for N tiles, or O(N log N) with a more advanced counting method.
//   • Invariants: The permutation used for inversion counting always excludes the blank tile.; Each pair of tiles (i, j) with i < j is considered exactly once for inversion counting.
//   • Tips: Remember to exclude the blank tile (0) when forming the permutation for inversion counting.; For a 4x4 grid, the blank tile's row (from bottom, 1-indexed) is crucial for the parity check.
//   • Pitfalls: Incorrectly including the blank tile (0) in the inversion count.; Miscalculating the blank tile's row index (e.g., 0-indexed from top vs. 1-indexed from bottom).
// - Binomial Coefficients (array, enumeration)
//   • When to use: When you need to calculate the number of ways to choose k items from n distinct items, often under modular constraints.
//   • Idea: Binomial coefficients represent the number of ways to choose k items from a set of n distinct items. They can be computed using Pascal's identity or factorials, with complexity varying based on the method and modulo requirements.
//   • Invariants: For Pascal's triangle, dp[i][j] stores C(i, j).; For factorial method, fact[i] stores i! % M.
//   • Tips: Use Pascal's triangle for small n and k values.; Precompute factorials and inverse factorials for larger n modulo a prime.
//   • Pitfalls: Overflow with large factorials if not using modular arithmetic.; Division by zero when computing inverse modulo if modulus is not prime.
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
var countPyramids = function(grid) {
    const m = grid.length, n = grid[0].length;
    const dpPyramid = Array.from({ length: m }, () => Array(n).fill(0));
    const dpInversePyramid = Array.from({ length: m }, () => Array(n).fill(0));
    let count = 0;
    
    // Count pyramids pointing upwards
    for (let i = m - 1; i >= 0; i--) {
        for (let j = 0; j < n; j++) {
            if (grid[i][j] === 1) {
                if (i === m - 1) {
                    dpPyramid[i][j] = 1;
                } else {
                    dpPyramid[i][j] = Math.min(dpPyramid[i + 1][j - 1], dpPyramid[i + 1][j], dpPyramid[i + 1][j + 1]) + 1;
                }
                count += dpPyramid[i][j];
            }
        }
    }
    
    // Count pyramids pointing downwards
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            if (grid[i][j] === 1) {
                if (i === 0) {
                    dpInversePyramid[i][j] = 1;
                } else {
                    dpInversePyramid[i][j] = Math.min(dpInversePyramid[i - 1][j - 1], dpInversePyramid[i - 1][j], dpInversePyramid[i - 1][j + 1]) + 1;
                }
                count += dpInversePyramid[i][j];
            }
        }
    }
    
    return count;
};
