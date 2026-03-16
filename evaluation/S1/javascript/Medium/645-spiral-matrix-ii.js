// Source: https://leetcode.com/problems/spiral-matrix-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given a positive integer n, generate an n x n matrix filled with elements from 1 to n2 in spiral order.
//
// Example:
// Input: n = 3
// Output: [[1,2,3],[8,9,4],[7,6,5]]
//
// Constraints:
// 1 <= n <= 20
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
 * @param {number} n
 * @return {number[][]}
 */
var generateMatrix = function(n) {
    const matrix = Array.from({ length: n }, () => Array(n).fill(0));

    let num = 1;
    let top = 0;
    let bottom = n - 1;
    let left = 0;
    let right = n - 1;

    while (num <= n * n) {
        for (let j = left; j <= right; j++) {
            matrix[top][j] = num++;
        }
        top++;

        for (let i = top; i <= bottom; i++) {
            matrix[i][right] = num++;
        }
        right--;

        for (let j = right; j >= left; j--) {
            matrix[bottom][j] = num++;
        }
        bottom--;

        for (let i = bottom; i >= top; i--) {
            matrix[i][left] = num++;
        }
        left++;
    }

    return matrix;
};
