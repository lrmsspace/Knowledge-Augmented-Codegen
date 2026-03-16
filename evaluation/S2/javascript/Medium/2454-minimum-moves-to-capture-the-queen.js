// Source: https://leetcode.com/problems/minimum-moves-to-capture-the-queen/   |   Difficulty: Medium
//
// Problem Description:
// There is a 1-indexed 8 x 8 chessboard containing 3 pieces.
//
// You are given 6 integers a, b, c, d, e, and f where:
//
//
// 	(a, b) denotes the position of the white rook.
// 	(c, d) denotes the position of the white bishop.
// 	(e, f) denotes the position of the black queen.
//
//
// Given that you can only move the white pieces, return the minimum number of moves required to capture the black queen.
//
// Note that:
//
//
// 	Rooks can move any number of squares either vertically or horizontally, but cannot jump over other pieces.
// 	Bishops can move any number of squares diagonally, but cannot jump over other pieces.
// 	A rook or a bishop can capture the queen if it is located in a square that they can move to.
// 	The queen does not move.
//
// Example:
// Input: a = 1, b = 1, c = 8, d = 8, e = 2, f = 3
// Output: 2
// Explanation: We can capture the black queen in two moves by moving the white rook to (1, 3) then to (2, 3).
// It is impossible to capture the black queen in less than two moves since it is not being attacked by any of the pieces at the beginning.
//
// Constraints:
// 1 <= a, b, c, d, e, f <= 8
// 	No two pieces are on the same square.
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
 * @param {number} a
 * @param {number} b
 * @param {number} c
 * @param {number} d
 * @param {number} e
 * @param {number} f
 * @return {number}
 */
var minMovesToCaptureTheQueen = function(a, b, c, d, e, f) {
    const rookAttacks = (a === e || b === f) && !(c === a && (d < b && d > f || d > b && d < f));
    const bishopAttacks = Math.abs(c - e) === Math.abs(d - f) && !(a === c && (b < d && b > f || b > d && b < f));
    if (rookAttacks || bishopAttacks) return 1;
    return 2;
};
