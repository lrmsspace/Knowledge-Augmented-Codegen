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
public:
    bool checkTwoChessboards(string coordinate1, string coordinate2) {
        auto color = [](const string& coordinate) {
            int col = coordinate[0] - 'a';
            int row = coordinate[1] - '1';
            return (col + row) % 2;
        };
        return color(coordinate1) == color(coordinate2);            
    }
};
