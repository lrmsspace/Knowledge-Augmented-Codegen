// Source: https://leetcode.com/problems/number-of-enclaves/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n binary matrix grid, where 0 represents a sea cell and 1 represents a land cell.
//
// A move consists of walking from one land cell to another adjacent (4-directionally) land cell or walking off the boundary of the grid.
//
// Return the number of land cells in grid for which we cannot walk off the boundary of the grid in any number of moves.
//
// Example:
// Input: grid = [[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]
// Output: 3
// Explanation: There are three 1s that are enclosed by 0s, and one 1 that is not enclosed because its on the boundary.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 500
// 	grid[i][j] is either 0 or 1.
//

/**
 * @param {number[][]} grid
 * @return {number}
 */
var numEnclaves = function(grid) {
    const rows = grid.length;
    const cols = grid[0].length;
    const directions = [[1, 0], [-1, 0], [0, 1], [0, -1]];
        
    const dfs = (r, c) => {
        if (r < 0 || c < 0 || r >= rows || c >= cols || grid[r][c] === 0) {
            return;
            
        }   
        grid[r][c] = 0;
        for (const [dr, dc] of directions) {
            dfs(r + dr, c + dc);
        }
    };
    for (let r = 0; r < rows; r++) {
        for (let c = 0; c < cols; c++) {
            if (r === 0 || c === 0 || r === rows - 1 || c === cols - 1) {
                if (grid[r][c] === 1) {
                    dfs(r, c);
                }
            }
        }
    }
    let enclaveCount = 0;
    for (let r = 0; r < rows; r++) {
        for (let c = 0; c < cols; c++) {
            if (grid[r][c] === 1) {
                enclaveCount++;
            }
        }
    }
    return enclaveCount;
};
