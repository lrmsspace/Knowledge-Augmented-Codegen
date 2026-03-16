// Source: https://leetcode.com/problems/largest-local-values-in-a-matrix/   |   Difficulty: Easy
//
// Problem Description:
// You are given an n x n integer matrix grid.
//
// Generate an integer matrix maxLocal of size (n - 2) x (n - 2) such that:
//
//
// 	maxLocal[i][j] is equal to the largest value of the 3 x 3 matrix in grid centered around row i + 1 and column j + 1.
//
//
// In other words, we want to find the largest value in every contiguous 3 x 3 matrix in grid.
//
// Return the generated matrix.
//
// Example:
// Input: grid = [[9,9,8,1],[5,6,2,6],[8,2,6,4],[6,2,2,2]]
// Output: [[9,9],[8,6]]
// Explanation: The diagram above shows the original matrix and the generated matrix.
// Notice that each value in the generated matrix corresponds to the largest value of a contiguous 3 x 3 matrix in grid.
//
// Constraints:
// n == grid.length == grid[i].length
// 	3 <= n <= 100
// 	1 <= grid[i][j] <= 100
//

/**
 * @param {number[][]} grid
 * @return {number[][]}
 */
var largestLocal = function(grid) {
    const n = grid.length;
    const maxLocal = Array.from({ length: n - 2 }, () => new Array(n - 2).fill(0));
    for (let i = 0; i < n - 2; i++) {
        for (let j = 0; j < n - 2; j++) {
            let maxVal = 0;
            for (let x = i; x < i + 3; x++) {
                for (let y = j; y < j + 3; y++) {
                    if (grid[x][y] > maxVal) {
                        maxVal = grid[x][y];
                    }
                }
            }
            maxLocal[i][j] = maxVal;
        }
    }
    return maxLocal;
};