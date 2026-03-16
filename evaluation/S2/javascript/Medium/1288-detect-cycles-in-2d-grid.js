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
 * @param {character[][]} grid
 * @return {boolean}
 */
var containsCycle = function(grid) {
    const m = grid.length;
    const n = grid[0].length;
    const visited = Array.from({ length: m }, () => Array(n).fill(false));
    const directions = [[1, 0], [-1, 0], [0, 1], [0, -1]];
    
    const dfs = (x, y, fromX, fromY) => {
        visited[x][y] = true;
        for (const [dx, dy] of directions) {
            const nextX = x + dx;
            const nextY = y + dy;
            if (nextX < 0 || nextX >= m || nextY < 0 || nextY >= n || grid[nextX][nextY] !== grid[x][y]) {
                continue;
            }
            if ((nextX === fromX && nextY === fromY) || dfs(nextX, nextY, x, y)) {
                return true;
            }
        }
        return false;
    };
    
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            if (!visited[i][j] && dfs(i, j, -1, -1)) {
                return true;
            }
        }
    }
    
    return false;
};
