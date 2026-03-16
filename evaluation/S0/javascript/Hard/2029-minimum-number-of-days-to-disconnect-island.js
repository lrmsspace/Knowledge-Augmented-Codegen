// Source: https://leetcode.com/problems/minimum-number-of-days-to-disconnect-island/   |   Difficulty: Hard
//
// Problem Description:
// You are given an m x n binary grid grid where 1 represents land and 0 represents water. An island is a maximal 4-directionally (horizontal or vertical) connected group of 1's.
//
// The grid is said to be connected if we have exactly one island, otherwise is said disconnected.
//
// In one day, we are allowed to change any single land cell (1) into a water cell (0).
//
// Return the minimum number of days to disconnect the grid.
//
// Example:
// Input: grid = [[0,1,1,0],[0,1,1,0],[0,0,0,0]]
//
// Output: 2
// Explanation: We need at least 2 days to get a disconnected grid.
// Change land grid[1][1] and grid[0][2] to water and get 2 disconnected island.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 30
// 	grid[i][j] is either 0 or 1.
//

/**
 * @param {number[][]} grid
 * @return {number}
 */
var minDays = function(grid) {
    const m = grid.length;
    const n = grid[0].length;
    const directions = [[1, 0], [-1, 0], [0, 1], [0, -1]];
    
    const countIslands = () => {
        const visited = Array.from({ length: m }, () => new Array(n).fill(false));
        let islandCount = 0;
        for (let i = 0; i < m; i++) {
            for (let j = 0; j < n; j++) {
                if (grid[i][j] === 1 && !visited[i][j]) {
                    islandCount++;
                    const queue = [[i, j]];
                    visited[i][j] = true;
                    while (queue.length > 0) {
                        const [x, y] = queue.shift();
                        for (const [dx, dy] of directions) {
                            const newX = x + dx;
                            const newY = y + dy;
                            if (newX >= 0 && newX < m && newY >= 0 && newY < n && grid[newX][newY] === 1 && !visited[newX][newY]) {
                                visited[newX][newY] = true;
                                queue.push([newX, newY]);
                            }
                        }
                    }
                }
            }
        }        return islandCount;
    }

    if (countIslands() !== 1) {
        return 0;
    }
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            if (grid[i][j] === 1) {
                grid[i][j] = 0;
                if (countIslands() !== 1) {
                    return 1;
                }
                grid[i][j] = 1;
            }
        }
    }
    return 2;   
};
