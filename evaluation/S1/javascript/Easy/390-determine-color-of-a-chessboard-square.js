// Source: https://leetcode.com/problems/determine-color-of-a-chessboard-square/   |   Difficulty: Easy
//
// Problem Description:
// You are given coordinates, a string that represents the coordinates of a square of the chessboard. Below is a chessboard for your reference.
//
//
//
// Return true if the square is white, and false if the square is black.
//
// The coordinate will always represent a valid chessboard square. The coordinate will always have the letter first, and the number second.
//
// Example:
// Input: coordinates = "a1"
// Output: false
// Explanation: From the chessboard above, the square with coordinates "a1" is black, so return false.
//
// Constraints:
// coordinates.length == 2
// 	'a' <= coordinates[0] <= 'h'
// 	'1' <= coordinates[1] <= '8'
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
 * @param {string} coordinates
 * @return {boolean}
 */
var squareIsWhite = function(coordinates) {
    const file = coordinates.charCodeAt(0) - 'a'.charCodeAt(0) + 1;
    const rank = parseInt(coordinates[1]);
    return (file + rank) % 2 === 1; 
};
