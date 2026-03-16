// Source: https://leetcode.com/problems/number-of-closed-islands/   |   Difficulty: Medium
//
// Problem Description:
// Given a 2D grid consists of 0s (land) and 1s (water).  An island is a maximal 4-directionally connected group of 0s and a closed island is an island totally (all left, top, right, bottom) surrounded by 1s.
//
// Return the number of closed islands.
//
// Example:
// Input: grid = [[1,1,1,1,1,1,1,0],[1,0,0,0,0,1,1,0],[1,0,1,0,1,1,1,0],[1,0,0,0,0,1,0,1],[1,1,1,1,1,1,1,0]]
// Output: 2
// Explanation: 
// Islands in gray are closed because they are completely surrounded by water (group of 1s).
//
// Constraints:
// 1 <= grid.length, grid[0].length <= 100
// 	0 <= grid[i][j] <=1
//

/**
 * @param {number[][]} grid
 * @return {number}
 */
var closedIsland = function(grid) {
    const rows = grid.length;
    const cols = grid[0].length;
    let closedIslandsCount = 0;
        
    const dfs = (r, c) => {
        if (r < 0 || c < 0 || r >= rows || c >= cols) {
            return false;
        }
        if (grid[r][c] === 1) {
            return true;
        }
        grid[r][c] = 1; 
        const up = dfs(r - 1, c);
        const down = dfs(r + 1, c);
        const left = dfs(r, c - 1);
        const right = dfs(r, c + 1);
        return up && down && left && right;
    }
    for (let r = 0; r < rows; r++) {
        for (let c = 0; c < cols; c++) {
            if (grid[r][c] === 0) {
                if (dfs(r, c)) {
                    closedIslandsCount++;
                }
            }
        }
    }
    return closedIslandsCount;  
            
};
