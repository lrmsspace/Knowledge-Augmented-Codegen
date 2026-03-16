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

class Solution {
    public boolean checkTwoChessboards(String coordinate1, String coordinate2) {
        int col1 = coordinate1.charAt(0) - 'a' + 1;
        int row1 = coordinate1.charAt(1) - '0';
        int col2 = coordinate2.charAt(0) - 'a' + 1;
        int row2 = coordinate2.charAt(1) - '0';

        return (col1 + row1) % 2 == (col2 + row2) % 2;          
    }
}
