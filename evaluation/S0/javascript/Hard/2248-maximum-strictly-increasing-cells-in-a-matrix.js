// Source: https://leetcode.com/problems/maximum-strictly-increasing-cells-in-a-matrix/   |   Difficulty: Hard
//
// Problem Description:
// Given a 1-indexed m x n integer matrix mat, you can select any cell in the matrix as your starting cell.
//
// From the starting cell, you can move to any other cell in the same row or column, but only if the value of the destination cell is strictly greater than the value of the current cell. You can repeat this process as many times as possible, moving from cell to cell until you can no longer make any moves.
//
// Your task is to find the maximum number of cells that you can visit in the matrix by starting from some cell.
//
// Return an integer denoting the maximum number of cells that can be visited.
//
// Example:
// Input: mat = [[3,1],[3,4]]
// Output: 2
// Explanation: The image shows how we can visit 2 cells starting from row 1, column 2. It can be shown that we cannot visit more than 2 cells no matter where we start from, so the answer is 2.
//
// Constraints:
// m == mat.length 
// 	n == mat[i].length 
// 	1 <= m, n <= 105
// 	1 <= m * n <= 105
// 	-105 <= mat[i][j] <= 105
//

/**
 * @param {number[][]} mat
 * @return {number}
 */
var maxIncreasingCells = function(mat) {
    const m = mat.length;
    const n = mat[0].length;
    const cells = [];
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            cells.push([mat[i][j], i, j]);
        }
    }
    cells.sort((a, b) => a[0] - b[0]);
    const rowMax = new Array(m).fill(0);
    const colMax = new Array(n).fill(0);
    let result = 1;
    for (const [value, row, col] of cells) {
        const maxLength = Math.max(rowMax[row], colMax[col]) + 1;
        rowMax[row] = Math.max(rowMax[row], maxLength);
        colMax[col] = Math.max(colMax[col], maxLength);
        result = Math.max(result, maxLength);
    }
    return result;  
};
