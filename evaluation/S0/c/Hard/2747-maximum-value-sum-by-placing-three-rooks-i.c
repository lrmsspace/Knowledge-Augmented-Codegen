// Source: https://leetcode.com/problems/maximum-value-sum-by-placing-three-rooks-i/   |   Difficulty: Hard
//
// Problem Description:
// You are given a m x n 2D array board representing a chessboard, where board[i][j] represents the value of the cell (i, j).
//
// Rooks in the same row or column attack each other. You need to place three rooks on the chessboard such that the rooks do not attack each other.
//
// Return the maximum sum of the cell values on which the rooks are placed.
//
// Example:
// Input: board = [[-3,1,1,1],[-3,1,-3,1],[-3,2,1,1]]
//
// Output: 4
//
// Explanation:
//
//
//
// We can place the rooks in the cells (0, 2), (1, 3), and (2, 1) for a sum of 1 + 1 + 2 = 4.
//
// Constraints:
// 3 <= m == board.length <= 100
// 	3 <= n == board[i].length <= 100
// 	-109 <= board[i][j] <= 109
//

long long maximumValueSum(int** board, int boardSize, int* boardColSize) {
    long long maxSum = -1000000000LL * 3;
    for (int r1 = 0; r1 < boardSize; ++r1) {
        for (int r2 = r1 + 1; r2 < boardSize; ++r2) {
            for (int r3 = r2 + 1; r3 < boardSize; ++r3) {
                /* select rows r1, r2, r3 */
                int n = boardColSize[0];
                int colVals[n];
                for (int c = 0; c < n; ++c) {
                    colVals[c] = board[r1][c] + board[r2][c] + board[r3][c];
                }
                /* find top 3 column sums */
                int top1 = -1000000000, top2 = -1000000000, top3 = -1000000000;
                for (int c = 0; c < n; ++c) {
                    int val = colVals[c];
                    if (val > top1) {
                        top3 = top2;
                        top2 = top1;
                        top1 = val;
                    } else if (val > top2) {
                        top3 = top2;
                        top2 = val;
                    } else if (val > top3) {
                        top3 = val;
                    }
                }
                long long sum = (long long)top1 + (long long)top2 + (long long)top3;
                if (sum > maxSum) {
                    maxSum = sum;
                }
            }
        }
    }
    return maxSum;      
}
