// Source: https://leetcode.com/problems/determine-if-a-cell-is-reachable-at-a-given-time/   |   Difficulty: Medium
//
// Problem Description:
// You are given four integers sx, sy, fx, fy, and a non-negative integer t.
//
// In an infinite 2D grid, you start at the cell (sx, sy). Each second, you must move to any of its adjacent cells.
//
// Return true if you can reach cell (fx, fy) after exactly t seconds, or false otherwise.
//
// A cell's adjacent cells are the 8 cells around it that share at least one corner with it. You can visit the same cell several times.
//
// Example:
// Input: sx = 2, sy = 4, fx = 7, fy = 7, t = 6
// Output: true
// Explanation: Starting at cell (2, 4), we can reach cell (7, 7) in exactly 6 seconds by going through the cells depicted in the picture above.
//
// Constraints:
// 1 <= sx, sy, fx, fy <= 109
// 	0 <= t <= 109
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
 * @param {number} sx
 * @param {number} sy
 * @param {number} fx
 * @param {number} fy
 * @param {number} t
 * @return {boolean}
 */
var isReachableAtTime = function(sx, sy, fx, fy, t) {
    const distance = Math.max(Math.abs(fx - sx), Math.abs(fy - sy));
    return distance <= t && (t - distance) % 2 === 0;
};
