// Source: https://leetcode.com/problems/available-captures-for-rook/   |   Difficulty: Easy
//
// Problem Description:
// You are given an 8 x 8 matrix representing a chessboard. There is exactly one white rook represented by 'R', some number of white bishops 'B', and some number of black pawns 'p'. Empty squares are represented by '.'.
//
// A rook can move any number of squares horizontally or vertically (up, down, left, right) until it reaches another piece or the edge of the board. A rook is attacking a pawn if it can move to the pawn's square in one move.
//
// Note: A rook cannot move through other pieces, such as bishops or pawns. This means a rook cannot attack a pawn if there is another piece blocking the path.
//
// Return the number of pawns the white rook is attacking.
//
// Example:
// Input: board = [[".",".",".",".",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".","R",".",".",".","p"],[".",".",".",".",".",".",".","."],[".",".",".",".",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".",".",".",".",".","."],[".",".",".",".",".",".",".","."]]
//
// Output: 3
//
// Explanation:
//
// In this example, the rook is attacking all the pawns.
//
// Constraints:
// board.length == 8
// 	board[i].length == 8
// 	board[i][j] is either 'R', '.', 'B', or 'p'
// 	There is exactly one cell with board[i][j] == 'R'
//

class Solution {
public:
    int numRookCaptures(vector<vector<char>>& board) {
        int rookX = -1, rookY = -1;
        // Locate the rook's position
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (board[i][j] == 'R') {
                    rookX = i;
                    rookY = j;
                    break;
                }
            }
            if (rookX != -1) break;
        }

        int captures = 0;
        // Directions: up, down, left, right
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        for (auto& dir : directions) {
            int x = rookX + dir.first;
            int y = rookY + dir.second;

            while (x >= 0 && x < 8 && y >= 0 && y < 8) {
                if (board[x][y] == 'B') {
                    // Bishop blocks the path
                    break;
                } else if (board[x][y] == 'p') {
                    // Pawn can be captured
                    captures++;
                    break;
                }
                x += dir.first;
                y += dir.second;
            }
        }

        return captures;            
    }
};
