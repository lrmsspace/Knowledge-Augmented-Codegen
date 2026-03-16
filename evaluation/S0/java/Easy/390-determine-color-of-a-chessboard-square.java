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

class Solution {
    public boolean squareIsWhite(String coordinates) {
        char file = coordinates.charAt(0); // 'a' to 'h'
        char rank = coordinates.charAt(1); // '1' to '8'

        // Calculate the sum of the file and rank indices
        int fileIndex = file - 'a' + 1; // Convert 'a'-'h' to 1-8
        int rankIndex = rank - '1' + 1; // Convert '1'-'8' to 1-8

        // A square is white if the sum of its file and rank indices is odd
        return (fileIndex + rankIndex) % 2 == 1;            
    }
}
