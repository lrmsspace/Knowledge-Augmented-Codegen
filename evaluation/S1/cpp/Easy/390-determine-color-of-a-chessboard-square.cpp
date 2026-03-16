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
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    bool squareIsWhite(string coordinates) {
        char file = coordinates[0]; // 'a' to 'h'
        char rank = coordinates[1]; // '1' to '8'
        
        // Calculate the color based on file and rank
        // Files 'a', 'c', 'e', 'g' are odd (1, 3, 5, 7)
        // Files 'b', 'd', 'f', 'h' are even (2, 4, 6, 8)
        int fileNum = file - 'a' + 1; // Convert file to number 1-8
        int rankNum = rank - '1' + 1; // Convert rank to number 1-8
        
        // A square is white if the sum of fileNum and rankNum is odd
        return (fileNum + rankNum) % 2 == 1;            
    }
};
