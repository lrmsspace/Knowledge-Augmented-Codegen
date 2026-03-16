// Source: https://leetcode.com/problems/reaching-points/   |   Difficulty: Hard
//
// Problem Description:
// Given four integers sx, sy, tx, and ty, return true if it is possible to convert the point (sx, sy) to the point (tx, ty) through some operations, or false otherwise.
//
// The allowed operation on some point (x, y) is to convert it to either (x, x + y) or (x + y, y).
//
// Example:
// Input: sx = 1, sy = 1, tx = 3, ty = 5
// Output: true
// Explanation:
// One series of moves that transforms the starting point to the target is:
// (1, 1) -> (1, 2)
// (1, 2) -> (3, 2)
// (3, 2) -> (3, 5)
//
// Constraints:
// 1 <= sx, sy, tx, ty <= 109
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
 * @param {number} tx
 * @param {number} ty
 * @return {boolean}
 */
var reachingPoints = function(sx, sy, tx, ty) {
    while (tx >= sx && ty >= sy) {
        if (tx === ty) break;
        if (tx > ty) {
            tx -= ty;
        } else {
            ty -= tx;
        }
    }
    
    return tx === sx && ty === sy;
};
