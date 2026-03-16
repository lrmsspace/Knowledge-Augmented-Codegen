// Source: https://leetcode.com/problems/01-matrix/   |   Difficulty: Medium
//
// Problem Description:
// Given an m x n binary matrix mat, return the distance of the nearest 0 for each cell.
//
// The distance between two cells sharing a common edge is 1.
//
// Example:
// Input: mat = [[0,0,0],[0,1,0],[0,0,0]]
// Output: [[0,0,0],[0,1,0],[0,0,0]]
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= m, n <= 104
// 	1 <= m * n <= 104
// 	mat[i][j] is either 0 or 1.
// 	There is at least one 0 in mat.
//
//
//  
// Note: This question is the same as 1765: https://leetcode.com/problems/map-of-highest-peak/
//

/**
 * @param {number[][]} mat
 * @return {number[][]}
 */
var updateMatrix = function(mat) {
    
    const rows = mat.length;
    const cols = mat[0].length;
    const dist = Array.from({ length: rows }, () => Array(cols).fill(Infinity));
    const directions = [[1, 0], [-1, 0], [0, 1], [0, -1]];
    const queue = [];
    for (let r = 0; r < rows; r++) {
        for (let c = 0; c < cols; c++) {
            if (mat[r][c] === 0) {
                dist[r][c] = 0;
                queue.push([r, c]);
            }
        }
    }
    while (queue.length) {
        const [r, c] = queue.shift();
        for (const [dr, dc] of directions) {
            const newRow = r + dr;
            const newCol = c + dc;
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols) {
                if (dist[newRow][newCol] > dist[r][c] + 1) {
                    dist[newRow][newCol] = dist[r][c] + 1;
                    queue.push([newRow, newCol]);
                }
            }
        }
    }
    return dist;
};
