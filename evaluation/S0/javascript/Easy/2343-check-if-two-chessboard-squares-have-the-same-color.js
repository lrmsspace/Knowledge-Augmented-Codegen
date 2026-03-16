// Source: https://leetcode.com/problems/check-if-two-chessboard-squares-have-the-same-color/   |   Difficulty: Easy
//
// Problem Description:
// You are given two strings, coordinate1 and coordinate2, representing the coordinates of a square on an 8 x 8 chessboard.
//
// Below is the chessboard for reference.
//
//
//
// Return true if these two squares have the same color and false otherwise.
//
// The coordinate will always represent a valid chessboard square. The coordinate will always have the letter first (indicating its column), and the number second (indicating its row).
//
// Example:
// Input: coordinate1 = "a1", coordinate2 = "c3"
//
// Output: true
//
// Explanation:
//
// Both squares are black.
//
// Constraints:
// coordinate1.length == coordinate2.length == 2
// 	'a' <= coordinate1[0], coordinate2[0] <= 'h'
// 	'1' <= coordinate1[1], coordinate2[1] <= '8'
//

/**
 * @param {string} coordinate1
 * @param {string} coordinate2
 * @return {boolean}
 */
var checkTwoChessboards = function(coordinate1, coordinate2) {
    const col1 = coordinate1.charCodeAt(0) - 'a'.charCodeAt(0) + 1;
    const row1 = parseInt(coordinate1[1]);
    const col2 = coordinate2.charCodeAt(0) - 'a'.charCodeAt(0) + 1;
    const row2 = parseInt(coordinate2[1]);
    const color1 = (col1 + row1) % 2;
    const color2 = (col2 + row2) % 2;
    return color1 === color2;   
};
