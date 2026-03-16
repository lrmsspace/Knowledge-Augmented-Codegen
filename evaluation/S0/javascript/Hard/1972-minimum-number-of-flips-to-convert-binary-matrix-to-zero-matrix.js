// Source: https://leetcode.com/problems/minimum-number-of-flips-to-convert-binary-matrix-to-zero-matrix/   |   Difficulty: Hard
//
// Problem Description:
// Given a m x n binary matrix mat. In one step, you can choose one cell and flip it and all the four neighbors of it if they exist (Flip is changing 1 to 0 and 0 to 1). A pair of cells are called neighbors if they share one edge.
//
// Return the minimum number of steps required to convert mat to a zero matrix or -1 if you cannot.
//
// A binary matrix is a matrix with all cells equal to 0 or 1 only.
//
// A zero matrix is a matrix with all cells equal to 0.
//
// Example:
// Input: mat = [[0,0],[0,1]]
// Output: 3
// Explanation: One possible solution is to flip (1, 0) then (0, 1) and finally (1, 1) as shown.
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= m, n <= 3
// 	mat[i][j] is either 0 or 1.
//

/**
 * @param {number[][]} mat
 * @return {number}
 */
var minFlips = function(mat) {
    const m = mat.length;
    const n = mat[0].length;
    const target = 0;
    let start = 0;  
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            if (mat[i][j] === 1) {
                start |= (1 << (i * n + j));
            }
        }
    }
    const queue = [start];
    const visited = new Set([start]);
    let steps = 0;
    const directions = [[0, 0], [1, 0], [-1, 0], [0, 1], [0, -1]];

    while (queue.length > 0) {
        const size = queue.length;
        for (let i = 0; i < size; i++) {
            const state = queue.shift();
            if (state === target) {
                return steps;
            }
            for (let j = 0; j < m * n; j++) {
                let nextState = state;
                for (const [dx, dy] of directions) {
                    const x = Math.floor(j / n) + dx;
                    const y = (j % n) + dy;
                    if (x >= 0 && x < m && y >= 0 && y < n) {
                        nextState ^= (1 << (x * n + y));
                    }
                }
                if (!visited.has(nextState)) {
                    visited.add(nextState);
                    queue.push(nextState);
                }
            }
        }
        steps++;
    }
    return -1;  
};
