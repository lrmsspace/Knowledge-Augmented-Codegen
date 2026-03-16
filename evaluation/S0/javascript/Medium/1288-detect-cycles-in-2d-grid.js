// Source: https://leetcode.com/problems/detect-cycles-in-2d-grid/   |   Difficulty: Medium
//
// Problem Description:
// Given a 2D array of characters grid of size m x n, you need to find if there exists any cycle consisting of the same value in grid.
//
// A cycle is a path of length 4 or more in the grid that starts and ends at the same cell. From a given cell, you can move to one of the cells adjacent to it - in one of the four directions (up, down, left, or right), if it has the same value of the current cell.
//
// Also, you cannot move to the cell that you visited in your last move. For example, the cycle (1, 1) -> (1, 2) -> (1, 1) is invalid because from (1, 2) we visited (1, 1) which was the last visited cell.
//
// Return true if any cycle of the same value exists in grid, otherwise, return false.
//
// Example:
// Input: grid = [["a","a","a","a"],["a","b","b","a"],["a","b","b","a"],["a","a","a","a"]]
// Output: true
// Explanation: There are two valid cycles shown in different colors in the image below:
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 500
// 	grid consists only of lowercase English letters.
//

/**
 * @param {character[][]} grid
 * @return {boolean}
 */
var containsCycle = function(grid) {
    const m = grid.length;
    const n = grid[0].length;
    const visited = Array.from({ length: m }, () => Array(n).fill(false));
    const directions = [[0, 1], [1, 0], [0, -1], [-1, 0]];

    const dfs = (x, y, fromX, fromY, char) => {
        if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] !== char) {
            return false;
        }
        if (visited[x][y]) {
            return true;
        }
        visited[x][y] = true;
        for (const [dx, dy] of directions) {
            const newX = x + dx;
            const newY = y + dy;
            if (newX === fromX && newY === fromY) {
                continue;
            }
            if (dfs(newX, newY, x, y, char)) {
                return true;
            }
        }
        return false;
    };

    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            if (!visited[i][j] && dfs(i, j, -1, -1, grid[i][j])) {
                return true;
            }
        }
    }
    return false;
};