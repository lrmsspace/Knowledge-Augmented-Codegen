// Source: https://leetcode.com/problems/disconnect-path-in-a-binary-matrix-by-at-most-one-flip/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed m x n binary matrix grid. You can move from a cell (row, col) to any of the cells (row + 1, col) or (row, col + 1) that has the value 1. The matrix is disconnected if there is no path from (0, 0) to (m - 1, n - 1).
//
// You can flip the value of at most one (possibly none) cell. You cannot flip the cells (0, 0) and (m - 1, n - 1).
//
// Return true if it is possible to make the matrix disconnect or false otherwise.
//
// Note that flipping a cell changes its value from 0 to 1 or from 1 to 0.
//
// Example:
// Input: grid = [[1,1,1],[1,0,0],[1,1,1]]
// Output: true
// Explanation: We can change the cell shown in the diagram above. There is no path from (0, 0) to (2, 2) in the resulting grid.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 1000
// 	1 <= m * n <= 105
// 	grid[i][j] is either 0 or 1.
// 	grid[0][0] == grid[m - 1][n - 1] == 1
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
 * @param {number[][]} grid
 * @return {boolean}
 */
var isPossibleToCutPath = function(grid) {
    const m = grid.length;
    const n = grid[0].length;

    const canReachEnd = (startRow, startCol, endRow, endCol) => {
        const visited = Array.from({ length: m }, () => Array(n).fill(false));
        const queue = [[startRow, startCol]];
        visited[startRow][startCol] = true;

        while (queue.length > 0) {
            const [row, col] = queue.shift();
            if (row === endRow && col === endCol) {
                return true;
            }
            for (const [dr, dc] of [[1, 0], [0, 1]]) {
                const newRow = row + dr;
                const newCol = col + dc;
                if (
                    newRow >= 0 && newRow < m &&
                    newCol >= 0 && newCol < n &&
                    grid[newRow][newCol] === 1 &&
                    !visited[newRow][newCol]
                ) {
                    visited[newRow][newCol] = true;
                    queue.push([newRow, newCol]);
                }
            }
        }
        return false;
    };

    // Check if there is already a path from (0, 0) to (m - 1, n - 1)
    if (!canReachEnd(0, 0, m - 1, n - 1)) {
        return true; // Already disconnected
    }

    // Try flipping each cell that is not on the path and check if it disconnects the path
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            if ((i === 0 && j === 0) || (i === m - 1 && j === n - 1)) {
                continue; // Skip the start and end cells
            }
            if (grid[i][j] === 1) {
                grid[i][j] = 0; // Flip to disconnect
                if (!canReachEnd(0, 0, m - 1, n - 1)) {
                    return true; // Successfully disconnected
                }
                grid[i][j] = 1; // Flip back
            }
        }
    }

    return false; // Unable to disconnect with one flip
};
