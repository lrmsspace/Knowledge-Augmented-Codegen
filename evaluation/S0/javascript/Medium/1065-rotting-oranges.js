// Source: https://leetcode.com/problems/rotting-oranges/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n grid where each cell can have one of three values:
//
//
// 	0 representing an empty cell,
// 	1 representing a fresh orange, or
// 	2 representing a rotten orange.
//
//
// Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.
//
// Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return -1.
//
// Example:
// Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
// Output: 4
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 10
// 	grid[i][j] is 0, 1, or 2.
//

/**
 * @param {number[][]} grid
 * @return {number}
 */
var orangesRotting = function(grid) {
    
    const rows = grid.length;
    const cols = grid[0].length;
    const queue = [];
    let freshOranges = 0;

    // Initialize the queue with all rotten oranges and count fresh oranges
    for (let r = 0; r < rows; r++) {
        for (let c = 0; c < cols; c++) {
            if (grid[r][c] === 2) {
                queue.push([r, c]);
            } else if (grid[r][c] === 1) {
                freshOranges++;
            }
        }
    }
    if (freshOranges === 0) return 0; // No fresh oranges to rot
    let minutes = 0;
    const directions = [[1, 0], [-1, 0], [0, 1], [0, -1]];

    while (queue.length > 0) {
        const size = queue.length;
        let rottedThisMinute = false;
        for (let i = 0; i < size; i++) {
            const [r, c] = queue.shift();
            for (const [dr, dc] of directions) {
                const newRow = r + dr;
                const newCol = c + dc;
                if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && grid[newRow][newCol] === 1) {
                    grid[newRow][newCol] = 2; // Rot the fresh orange
                    queue.push([newRow, newCol]);
                    freshOranges--;
                    rottedThisMinute = true;
                }
            }
        }
        if (rottedThisMinute) {
            minutes++;
        }
    }
    return freshOranges === 0 ? minutes : -1;   
                    
};
