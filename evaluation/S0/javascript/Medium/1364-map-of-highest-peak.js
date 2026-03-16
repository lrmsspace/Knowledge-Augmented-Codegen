// Source: https://leetcode.com/problems/map-of-highest-peak/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer matrix isWater of size m x n that represents a map of land and water cells.
//
//
// 	If isWater[i][j] == 0, cell (i, j) is a land cell.
// 	If isWater[i][j] == 1, cell (i, j) is a water cell.
//
//
// You must assign each cell a height in a way that follows these rules:
//
//
// 	The height of each cell must be non-negative.
// 	If the cell is a water cell, its height must be 0.
// 	Any two adjacent cells must have an absolute height difference of at most 1. A cell is adjacent to another cell if the former is directly north, east, south, or west of the latter (i.e., their sides are touching).
//
//
// Find an assignment of heights such that the maximum height in the matrix is maximized.
//
// Return an integer matrix height of size m x n where height[i][j] is cell (i, j)'s height. If there are multiple solutions, return any of them.
//
// Example:
// Input: isWater = [[0,1],[0,0]]
// Output: [[1,0],[2,1]]
// Explanation: The image shows the assigned heights of each cell.
// The blue cell is the water cell, and the green cells are the land cells.
//
// Constraints:
// m == isWater.length
// 	n == isWater[i].length
// 	1 <= m, n <= 1000
// 	isWater[i][j] is 0 or 1.
// 	There is at least one water cell.
//
//
//  
// Note: This question is the same as 542: https://leetcode.com/problems/01-matrix/
//

/**
 * @param {number[][]} isWater
 * @return {number[][]}
 */
var highestPeak = function(isWater) {
    const m = isWater.length;
    const n = isWater[0].length;
    const heights = Array.from({ length: m }, () => Array(n).fill(-1));
    const queue = [];
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            if (isWater[i][j] === 1) {
                heights[i][j] = 0;
                queue.push([i, j]);
            }
        }
    }
    const directions = [[0,1],[1,0],[0,-1],[-1,0]];
    while (queue.length) {
        const [x, y] = queue.shift();
        for (const [dx, dy] of directions) {
            const nx = x + dx;
            const ny = y + dy;
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && heights[nx][ny] === -1) {
                heights[nx][ny] = heights[x][y] + 1;
                queue.push([nx, ny]);
            }
        }
    }
    return heights;
};
