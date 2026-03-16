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

int minMovesToCaptureTheQueen(int a, int b, int c, int d, int e, int f) {
    // Check if the rook can capture the queen in one move
    if (a == e || b == f) {
        // Check if the bishop is blocking the rook's path
        if (!((c == a && ((d > b && d < f) || (d < b && d > f))) ||
              (d == b && ((c > a && c < e) || (c < a && c > e))))) {
            return 1;
        }
    }

    // Check if the bishop can capture the queen in one move
    if (abs(c - e) == abs(d - f)) {
        // Check if the rook is blocking the bishop's path
        if (!((abs(c - a) == abs(d - b)) &&
              ((e > c && a > c && f > d && b > d) ||
               (e > c && a > c && f < d && b < d) ||
               (e < c && a < c && f > d && b > d) ||
               (e < c && a < c && f < d && b < d)))) {
            return 1;
        }
    }

    // If neither piece can capture the queen in one move, return 2
    return 2;       
}
