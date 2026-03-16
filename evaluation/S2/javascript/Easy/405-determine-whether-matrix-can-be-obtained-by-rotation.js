// Source: https://leetcode.com/problems/determine-whether-matrix-can-be-obtained-by-rotation/   |   Difficulty: Easy
//
// Problem Description:
// Given two n x n binary matrices mat and target, return true if it is possible to make mat equal to target by rotating mat in 90-degree increments, or false otherwise.
//
// Example:
// Input: mat = [[0,1],[1,0]], target = [[1,0],[0,1]]
// Output: true
// Explanation: We can rotate mat 90 degrees clockwise to make mat equal target.
//
// Constraints:
// n == mat.length == target.length
// 	n == mat[i].length == target[i].length
// 	1 <= n <= 10
// 	mat[i][j] and target[i][j] are either 0 or 1.
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
 * @param {number[][]} mat
 * @param {number[][]} target
 * @return {boolean}
 */
var findRotation = function(mat, target) {
    const n = mat.length;
    
    // Function to rotate the matrix 90 degrees clockwise
    const rotate90 = (matrix) => {
        const rotated = Array(n).fill().map(() => Array(n).fill(0));
        for (let i = 0; i < n; i++) {
            for (let j = 0; j < n; j++) {
                rotated[j][n - 1 - i] = matrix[i][j];
            }
        }
        return rotated;
    };

    // Check if the matrix matches the target in any rotation
    let current = mat;
    for (let i = 0; i < 4; i++) {
        let isMatch = true;
        for (let j = 0; j < n; j++) {
            for (let k = 0; k < n; k++) {
                if (current[j][k] !== target[j][k]) {
                    isMatch = false;
                    break;
                }
            }
            if (!isMatch) break;
        }
        if (isMatch) return true;
        current = rotate90(current);
    }

    return false;
};
