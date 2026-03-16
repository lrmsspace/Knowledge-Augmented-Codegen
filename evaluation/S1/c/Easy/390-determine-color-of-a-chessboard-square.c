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
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool squareIsWhite(char* coordinates) {
    // Extract the column (letter) and row (number) from the coordinates
    char column = coordinates[0];
    char row = coordinates[1];

    // Determine the color based on the parity of the column and row
    // Columns 'a', 'c', 'e', 'g' are considered odd (1, 3, 5, 7)
    // Columns 'b', 'd', 'f', 'h' are considered even (2, 4, 6, 8)
    int isColumnOdd = (column - 'a' + 1) % 2; // 1 for odd columns, 0 for even columns
    int isRowOdd = (row - '1' + 1) % 2;       // 1 for odd rows, 0 for even rows

    // A square is white if both are odd or both are even
    return (isColumnOdd == isRowOdd);       
}
