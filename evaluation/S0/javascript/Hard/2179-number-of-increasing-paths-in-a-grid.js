// Source: https://leetcode.com/problems/number-of-increasing-paths-in-a-grid/   |   Difficulty: Hard
//
// Problem Description:
// You are given an m x n integer matrix grid, where you can move from a cell to any adjacent cell in all 4 directions.
//
// Return the number of strictly increasing paths in the grid such that you can start from any cell and end at any cell. Since the answer may be very large, return it modulo 109 + 7.
//
// Two paths are considered different if they do not have exactly the same sequence of visited cells.
//
// Example:
// Input: grid = [[1,1],[3,4]]
// Output: 8
// Explanation: The strictly increasing paths are:
// - Paths with length 1: [1], [1], [3], [4].
// - Paths with length 2: [1 -> 3], [1 -> 4], [3 -> 4].
// - Paths with length 3: [1 -> 3 -> 4].
// The total number of paths is 4 + 3 + 1 = 8.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 1000
// 	1 <= m * n <= 105
// 	1 <= grid[i][j] <= 105
//

/**
 * @param {number[][]} grid
 * @return {number}
 */
var countPaths = function(grid) {
    const mod = 1e9 + 7;
    const m = grid.length;
    const n = grid[0].length;
    const dp = Array.from({ length: m }, () => new Array(n).fill(0));
    const directions = [[1, 0], [-1, 0], [0, 1], [0, -1]];
    const dfs = (x, y) => {
        if (dp[x][y] > 0) {
            return dp[x][y];
        }
        let count = 1;
        for (const [dx, dy] of directions) {
            const newX = x + dx;
            const newY = y + dy;
            if (newX >= 0 && newX < m && newY >= 0 && newY < n && grid[newX][newY] > grid[x][y]) {
                count = (count + dfs(newX, newY)) % mod;
            }
        }
        dp[x][y] = count;
        return count;
    }
    let result = 0;
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            result = (result + dfs(i, j)) % mod;
        }
    }
    return result;  
};
