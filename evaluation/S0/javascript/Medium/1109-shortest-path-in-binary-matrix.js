// Source: https://leetcode.com/problems/shortest-path-in-binary-matrix/   |   Difficulty: Medium
//
// Problem Description:
// Given an n x n binary matrix grid, return the length of the shortest clear path in the matrix. If there is no clear path, return -1.
//
// A clear path in a binary matrix is a path from the top-left cell (i.e., (0, 0)) to the bottom-right cell (i.e., (n - 1, n - 1)) such that:
//
//
// 	All the visited cells of the path are 0.
// 	All the adjacent cells of the path are 8-directionally connected (i.e., they are different and they share an edge or a corner).
//
//
// The length of a clear path is the number of visited cells of this path.
//
// Example:
// Input: grid = [[0,1],[1,0]]
// Output: 2
//
// Constraints:
// n == grid.length
// 	n == grid[i].length
// 	1 <= n <= 100
// 	grid[i][j] is 0 or 1
//

/**
 * @param {number[][]} grid
 * @return {number}
 */
var shortestPathBinaryMatrix = function(grid) {
    
    const n = grid.length;
    if (grid[0][0] === 1 || grid[n - 1][n - 1] === 1) return -1;
    const directions = [
        [0, 1], [1, 0], [1, 1], [-1, 0], [0, -1], [-1, -1], [1, -1], [-1, 1]
    ];
    const queue = [[0, 0, 1]]; // [row, col, pathLength]
    const visited = Array.from({ length: n }, () => Array(n).fill(false));
    visited[0][0] = true;

    while (queue.length > 0) {
        const [row, col, pathLength] = queue.shift();
        if (row === n - 1 && col === n - 1) {
            return pathLength;
        }   
        for (const [dr, dc] of directions) {
            const newRow = row + dr;
            const newCol = col + dc;
            if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < n &&       
                grid[newRow][newCol] === 0 && !visited[newRow][newCol]) {
                visited[newRow][newCol] = true;
                queue.push([newRow, newCol, pathLength + 1]);
            }
        }
    }
    return -1;    
};
