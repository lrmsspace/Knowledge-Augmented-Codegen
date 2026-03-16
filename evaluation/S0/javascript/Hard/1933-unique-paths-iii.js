// Source: https://leetcode.com/problems/unique-paths-iii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an m x n integer array grid where grid[i][j] could be:
//
//
// 	1 representing the starting square. There is exactly one starting square.
// 	2 representing the ending square. There is exactly one ending square.
// 	0 representing empty squares we can walk over.
// 	-1 representing obstacles that we cannot walk over.
//
//
// Return the number of 4-directional walks from the starting square to the ending square, that walk over every non-obstacle square exactly once.
//
// Example:
// Input: grid = [[1,0,0,0],[0,0,0,0],[0,0,2,-1]]
// Output: 2
// Explanation: We have the following two paths: 
// 1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2)
// 2. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2)
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 20
// 	1 <= m * n <= 20
// 	-1 <= grid[i][j] <= 2
// 	There is exactly one starting cell and one ending cell.
//

/**
 * @param {number[][]} grid
 * @return {number}
 */
var uniquePathsIII = function(grid) {
    const m = grid.length;
    const n = grid[0].length;
    let emptyCount = 0;
    let startX, startY;
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            if (grid[i][j] === 0) {
                emptyCount++;
            } else if (grid[i][j] === 1) {
                startX = i;
                startY = j;
            }
        }
    }
    const directions = [[0, 1], [1, 0], [0, -1], [-1, 0]];
    const dfs = (x, y, count) => {
        if (grid[x][y] === 2) {
            return count === emptyCount + 1 ? 1 : 0;
        }
        let paths = 0;
        const temp = grid[x][y];
        grid[x][y] = -1;
        for (const [dx, dy] of directions) {
            const newX = x + dx;
            const newY = y + dy;
            if (newX >= 0 && newX < m && newY >= 0 && newY < n && grid[newX][newY] !== -1) {
                paths += dfs(newX, newY, count + 1);
            }
        }
        grid[x][y] = temp;
        return paths;
    }
    return dfs(startX, startY, 0);  
};