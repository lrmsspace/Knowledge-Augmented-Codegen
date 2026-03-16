// Source: https://leetcode.com/problems/grid-teleportation-traversal/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D character grid matrix of size m x n, represented as an array of strings, where matrix[i][j] represents the cell at the intersection of the ith row and jth column. Each cell is one of the following:
//
//
// 	'.' representing an empty cell.
// 	'#' representing an obstacle.
// 	An uppercase letter ('A'-'Z') representing a teleportation portal.
//
//
// You start at the top-left cell (0, 0), and your goal is to reach the bottom-right cell (m - 1, n - 1). You can move from the current cell to any adjacent cell (up, down, left, right) as long as the destination cell is within the grid bounds and is not an obstacle.
//
// If you step on a cell containing a portal letter and you haven't used that portal letter before, you may instantly teleport to any other cell in the grid with the same letter. This teleportation does not count as a move, but each portal letter can be used at most once during your journey.
//
// Return the minimum number of moves required to reach the bottom-right cell. If it is not possible to reach the destination, return -1.
//
// Example:
// Input: matrix = ["A..",".A.","..."]
//
// Output: 2
//
// Explanation:
//
//
//
//
// 	Before the first move, teleport from (0, 0) to (1, 1).
// 	In the first move, move from (1, 1) to (1, 2).
// 	In the second move, move from (1, 2) to (2, 2).
//
// Constraints:
// 1 <= m == matrix.length <= 103
// 	1 <= n == matrix[i].length <= 103
// 	matrix[i][j] is either '#', '.', or an uppercase English letter.
// 	matrix[0][0] is not an obstacle.
//

/**
 * @param {string[]} matrix
 * @return {number}
 */
var minMoves = function(matrix) {


    const m = matrix.length;
    const n = matrix[0].length;
    const portals = {};
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            const cell = matrix[i][j];
            if (cell >= 'A' && cell <= 'Z') {
                if (!portals[cell]) {
                    portals[cell] = [];
                }
                portals[cell].push([i, j]);
            }
        }
    }

    const visited = Array.from({ length: m }, () => Array(n).fill(false));
    const usedPortals = new Set();
    const queue = [[0, 0, 0]];
    visited[0][0] = true;
    while (queue.length > 0) {
        const [x, y, moves] = queue.shift();
        if (x === m - 1 && y === n - 1) {
            return moves;
        }
        const directions = [[1, 0], [-1, 0], [0, 1], [0, -1]];
        for (const [dx, dy] of directions) {    
            const newX = x + dx;
            const newY = y + dy;
            if (newX >= 0 && newX < m && newY >= 0 && newY < n && matrix[newX][newY] !== '#' && !visited[newX][newY]) {
                visited[newX][newY] = true;
                queue.push([newX, newY, moves + 1]);
            }   
        }
        const cell = matrix[x][y];
        if (cell >= 'A' && cell <= 'Z' && !usedPortals.has(cell)) {
            usedPortals.add(cell);
            for (const [portalX, portalY] of portals[cell]) {
                if (!visited[portalX][portalY]) {
                    visited[portalX][portalY] = true;
                    queue.push([portalX, portalY, moves]);
                }
            }
        }
    }
    return -1;
};
