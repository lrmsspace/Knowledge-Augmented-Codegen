// Source: https://leetcode.com/problems/maximum-non-negative-product-in-a-matrix/   |   Difficulty: Medium
//
// Problem Description:
// You are given a m x n matrix grid. Initially, you are located at the top-left corner (0, 0), and in each step, you can only move right or down in the matrix.
//
// Among all possible paths starting from the top-left corner (0, 0) and ending in the bottom-right corner (m - 1, n - 1), find the path with the maximum non-negative product. The product of a path is the product of all integers in the grid cells visited along the path.
//
// Return the maximum non-negative product modulo 109 + 7. If the maximum product is negative, return -1.
//
// Notice that the modulo is performed after getting the maximum product.
//
// Example:
// Input: grid = [[-1,-2,-3],[-2,-3,-3],[-3,-3,-2]]
// Output: -1
// Explanation: It is not possible to get non-negative product in the path from (0, 0) to (2, 2), so return -1.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 15
// 	-4 <= grid[i][j] <= 4
//

/**
 * @param {number[][]} grid
 * @return {number}
 */
var maxProductPath = function(grid) {
    const MOD = 1e9 + 7;
    const m = grid.length;
    const n = grid[0].length;
    const maxProduct = Array.from({ length: m }, () => Array(n).fill(0));
    const minProduct = Array.from({ length: m }, () => Array(n).fill(0));
    maxProduct[0][0] = grid[0][0];
    minProduct[0][0] = grid[0][0];
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            if (i === 0 && j === 0) continue;
            const val = grid[i][j];
            if (val >= 0) {         
                const maxFromTop = i > 0 ? maxProduct[i - 1][j] * val : -Infinity;
                const maxFromLeft = j > 0 ? maxProduct[i][j - 1] * val : -Infinity;
                maxProduct[i][j] = Math.max(maxFromTop, maxFromLeft);
                const minFromTop = i > 0 ? minProduct[i - 1][j] * val : Infinity;
                const minFromLeft = j > 0 ? minProduct[i][j - 1] * val : Infinity;
                minProduct[i][j] = Math.min(minFromTop, minFromLeft);
            } else {
                const maxFromTop = i > 0 ? minProduct[i - 1][j] * val : -Infinity;
                const maxFromLeft = j > 0 ? minProduct[i][j - 1] * val : -Infinity;
                maxProduct[i][j] = Math.max(maxFromTop, maxFromLeft);
                const minFromTop = i > 0 ? maxProduct[i - 1][j] * val : Infinity;
                const minFromLeft = j > 0 ? maxProduct[i][j - 1] * val : Infinity;
                minProduct[i][j] = Math.min(minFromTop, minFromLeft);
            }
        }
    }
    return maxProduct[m - 1][n - 1] < 0 ? -1 : maxProduct[m - 1][n - 1] % MOD;  
};
