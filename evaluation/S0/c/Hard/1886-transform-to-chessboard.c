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

int movesToChessboard(int** board, int boardSize, int* boardColSize) {
    int n = boardSize;
    int rowSum = 0, colSum = 0, rowSwap = 0, colSwap = 0;

    for (int i = 0; i < n; ++i) {
        rowSum += board[0][i];
        colSum += board[i][0];
        if (board[i][0] == i % 2) rowSwap++;
        if (board[0][i] == i % 2) colSwap++;
    }

    if (rowSum < n / 2 || rowSum > (n + 1) / 2) return -1;
    if (colSum < n / 2 || colSum > (n + 1) / 2) return -1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if ((board[0][0] ^ board[i][0] ^ board[0][j] ^ board[i][j]) != 0) {
                return -1;
            }
        }
    }

    if (n % 2) {
        if (colSwap % 2) colSwap = n - colSwap;
        if (rowSwap % 2) rowSwap = n - rowSwap;
    } else {
        colSwap = fmin(colSwap, n - colSwap);
        rowSwap = fmin(rowSwap, n - rowSwap);
    }

    return (colSwap + rowSwap) / 2;     
}
