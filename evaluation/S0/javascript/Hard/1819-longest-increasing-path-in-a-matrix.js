// Source: https://leetcode.com/problems/longest-increasing-path-in-a-matrix/   |   Difficulty: Hard
//
// Problem Description:
// Given an m x n integers matrix, return the length of the longest increasing path in matrix.
//
// From each cell, you can either move in four directions: left, right, up, or down. You may not move diagonally or move outside the boundary (i.e., wrap-around is not allowed).
//
// Example:
// Input: matrix = [[9,9,4],[6,6,8],[2,1,1]]
// Output: 4
// Explanation: The longest increasing path is [1, 2, 6, 9].
//
// Constraints:
// m == matrix.length
// 	n == matrix[i].length
// 	1 <= m, n <= 200
// 	0 <= matrix[i][j] <= 231 - 1
//

/**
 * @param {number[][]} matrix
 * @return {number}
 */
var longestIncreasingPath = function(matrix) {
    const m = matrix.length;
    const n = matrix[0].length;
    const cache = Array.from({ length: m }, () => new Array(n).fill(0));
    let maxLength = 0;
    const directions = [[0, 1], [1, 0], [0, -1], [-1, 0]];
    
    const dfs = (x, y) => { 
        if (cache[x][y] !== 0) {
            return cache[x][y];
        }
        let maxPath = 1;
        for (let [dx, dy] of directions) {
            const newX = x + dx;
            const newY = y + dy;
            if (newX >= 0 && newX < m && newY >= 0 && newY < n && matrix[newX][newY] > matrix[x][y]) {
                maxPath = Math.max(maxPath, 1 + dfs(newX, newY));
            }
        }
        cache[x][y] = maxPath;
        return maxPath;
    }

    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            maxLength = Math.max(maxLength, dfs(i, j));
        }
    }
    return maxLength;   
};
