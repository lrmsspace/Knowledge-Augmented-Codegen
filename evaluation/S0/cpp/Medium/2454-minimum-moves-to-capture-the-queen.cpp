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

class Solution {
public:
    int minMovesToCaptureTheQueen(int a, int b, int c, int d, int e, int f) {
        // Check if rook can capture the queen in one move
        if (a == e || b == f) {
            // Check if bishop is blocking the rook
            if (!((c == a && ((b < d && d < f) || (f < d && d < b))) ||
                  (d == b && ((a < c && c < e) || (e < c && c < a))))) {
                return 1;
            }
        }

        // Check if bishop can capture the queen in one move
        if (abs(c - e) == abs(d - f)) {
            // Check if rook is blocking the bishop
            if (!((abs(a - c) == abs(b - d)) &&
                  ((a < c && c < e && b < d && d < f) ||
                   (e < c && c < a && f < d && d < b) ||
                   (a < c && c < e && f < d && d < b) ||
                   (e < c && c < a && b < d && d < f)))) {
                return 1;
            }
        }

        // Check if rook can reach a position to capture the queen in two moves
        if (a != e && b != f) {
            return 2;
        }

        // Check if bishop can reach a position to capture the queen in two moves
        if ((abs(c + d - e - f) % 2) == 0) {
            return 2;
        }

        return 3;           
    }
};
