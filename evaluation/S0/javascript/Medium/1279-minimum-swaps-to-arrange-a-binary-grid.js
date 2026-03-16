// Source: https://leetcode.com/problems/minimum-swaps-to-arrange-a-binary-grid/   |   Difficulty: Medium
//
// Problem Description:
// Given an n x n binary grid, in one step you can choose two adjacent rows of the grid and swap them.
//
// A grid is said to be valid if all the cells above the main diagonal are zeros.
//
// Return the minimum number of steps needed to make the grid valid, or -1 if the grid cannot be valid.
//
// The main diagonal of a grid is the diagonal that starts at cell (1, 1) and ends at cell (n, n).
//
// Example:
// Input: grid = [[0,0,1],[1,1,0],[1,0,0]]
// Output: 3
//
// Constraints:
// n == grid.length == grid[i].length
// 	1 <= n <= 200
// 	grid[i][j] is either 0 or 1
//

/**
 * @param {number[][]} grid
 * @return {number}
 */
var minSwaps = function(grid) {
    const n = grid.length;
    const trailingZeros = Array(n).fill(0); 
    for (let i = 0; i < n; i++) {
        let count = 0;
        for (let j = n - 1; j >= 0; j--) {
            if (grid[i][j] === 0) {
                count++;
            } else {
                break;
            }
        }
        trailingZeros[i] = count;
    }
    let swaps = 0;  
    for (let i = 0; i < n; i++) {
        const requiredZeros = n - 1 - i;
        let rowIndex = -1;  
        for (let j = i; j < n; j++) {
            if (trailingZeros[j] >= requiredZeros) {
                rowIndex = j;
                break;
            }
        }
        if (rowIndex === -1) {
            return -1; 
        }
        while (rowIndex > i) {
            [trailingZeros[rowIndex], trailingZeros[rowIndex - 1]] = [trailingZeros[rowIndex - 1], trailingZeros[rowIndex]];
            rowIndex--;
            swaps++;
        }
    }
    return swaps;   
};
