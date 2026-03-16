// Source: https://leetcode.com/problems/minimum-operations-to-write-the-letter-y-on-a-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed n x n grid where n is odd, and grid[r][c] is 0, 1, or 2.
//
// We say that a cell belongs to the Letter Y if it belongs to one of the following:
//
//
// 	The diagonal starting at the top-left cell and ending at the center cell of the grid.
// 	The diagonal starting at the top-right cell and ending at the center cell of the grid.
// 	The vertical line starting at the center cell and ending at the bottom border of the grid.
//
//
// The Letter Y is written on the grid if and only if:
//
//
// 	All values at cells belonging to the Y are equal.
// 	All values at cells not belonging to the Y are equal.
// 	The values at cells belonging to the Y are different from the values at cells not belonging to the Y.
//
//
// Return the minimum number of operations needed to write the letter Y on the grid given that in one operation you can change the value at any cell to 0, 1, or 2.
//
// Example:
// Input: grid = [[1,2,2],[1,1,0],[0,1,0]]
// Output: 3
// Explanation: We can write Y on the grid by applying the changes highlighted in blue in the image above. After the operations, all cells that belong to Y, denoted in bold, have the same value of 1 while those that do not belong to Y are equal to 0.
// It can be shown that 3 is the minimum number of operations needed to write Y on the grid.
//
// Constraints:
// 3 <= n <= 49 
// 	n == grid.length == grid[i].length
// 	0 <= grid[i][j] <= 2
// 	n is odd.
//
// Helpful references (internal KB):
// - N/A
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
var minimumOperationsToWriteY = function(grid) {
    const n = grid.length;
    const yCells = [];
    const nonYCells = [];
    
    // Identify Y cells
    const center = Math.floor(n / 2);
    for (let i = 0; i < center; i++) {
        yCells.push([i, i]);
        yCells.push([i, n - 1 - i]);
    }
    for (let i = center; i < n; i++) {
        yCells.push([i, center]);
    }
    
    // Identify non-Y cells
    for (let i = 0; i < n; i++) {
        for (let j = 0; j < n; j++) {
            if (!yCells.some(([yI, yJ]) => yI === i && yJ === j)) {
                nonYCells.push([i, j]);
            }
        }
    }

    let minOperations = Infinity;
    
    // Try all possible values for Y and non-Y cells
    for (let yValue = 0; yValue <= 2; yValue++) {
        for (let nonYValue = 0; nonYValue <= 2; nonYValue++) {
            if (yValue === nonYValue) continue;
            
            let operations = 0;
            
            // Count operations needed to set Y cells to yValue
            for (const [i, j] of yCells) {
                if (grid[i][j] !== yValue) operations++;
            }
            
            // Count operations needed to set non-Y cells to nonYValue
            for (const [i, j] of nonYCells) {
                if (grid[i][j] !== nonYValue) operations++;
            }
            
            minOperations = Math.min(minOperations, operations);
        }
    }
    
    return minOperations;
};
