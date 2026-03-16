// Source: https://leetcode.com/problems/transform-to-chessboard/   |   Difficulty: Hard
//
// Problem Description:
// You are given an n x n binary grid board. In each move, you can swap any two rows with each other, or any two columns with each other.
//
// Return the minimum number of moves to transform the board into a chessboard board. If the task is impossible, return -1.
//
// A chessboard board is a board where no 0's and no 1's are 4-directionally adjacent.
//
// Example:
// Input: board = [[0,1,1,0],[0,1,1,0],[1,0,0,1],[1,0,0,1]]
// Output: 2
// Explanation: One potential sequence of moves is shown.
// The first move swaps the first and second column.
// The second move swaps the second and third row.
//
// Constraints:
// n == board.length
//  n == board[i].length
//  2 <= n <= 30
//  board[i][j] is either 0 or 1.
//

class Solution {
    public int movesToChessboard(int[][] board) {
        int n = board.length;
        int rowMask = 0, colMask = 0;

        for (int i = 0; i < n; i++) {
            rowMask |= (board[0][i] << i);
            colMask |= (board[i][0] << i);
        }

        int reverseRowMask = ((1 << n) - 1) ^ rowMask;
        int reverseColMask = ((1 << n) - 1) ^ colMask;

        int rowCount = 0, colCount = 0;

        for (int i = 0; i < n; i++) {
            int currRowMask = 0, currColMask = 0;
            for (int j = 0; j < n; j++) {
                currRowMask |= (board[i][j] << j);
                currColMask |= (board[j][i] << j);
            }

            if (currRowMask != rowMask && currRowMask != reverseRowMask) {
                return -1;
            }
            if (currColMask != colMask && currColMask != reverseColMask) {
                return -1;
            }

            if (currRowMask == rowMask) {
                rowCount++;
            }
            if (currColMask == colMask) {
                colCount++;
            }
        }

        int rowMoves = getMoves(rowMask, rowCount, n);
        int colMoves = getMoves(colMask, colCount, n);

        return rowMoves == -1 || colMoves == -1 ? -1 : rowMoves + colMoves;         
    }
}
