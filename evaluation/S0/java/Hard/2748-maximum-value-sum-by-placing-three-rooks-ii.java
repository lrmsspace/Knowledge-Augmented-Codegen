// Source: https://leetcode.com/problems/maximum-value-sum-by-placing-three-rooks-ii/   |   Difficulty: Hard
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
// 3 <= m == board.length <= 500
// 	3 <= n == board[i].length <= 500
// 	-109 <= board[i][j] <= 109
//

class Solution {
    public long maximumValueSum(int[][] board) {
        int m = board.length;
        int n = board[0].length;
        long maxSum = Long.MIN_VALUE;

        for (int col1 = 0; col1 < n; col1++) {
            for (int col2 = col1 + 1; col2 < n; col2++) {
                long[] rowValues = new long[m];
                for (int row = 0; row < m; row++) {
                    rowValues[row] = board[row][col1] + board[row][col2];
                }

                long maxRowValue = Long.MIN_VALUE;
                for (int row = 0; row < m; row++) {
                    maxRowValue = Math.max(maxRowValue, rowValues[row]);
                }

                for (int col3 = 0; col3 < n; col3++) {
                    if (col3 == col1 || col3 == col2) continue;

                    long currentMaxSum = Long.MIN_VALUE;
                    for (int row = 0; row < m; row++) {
                        currentMaxSum = Math.max(currentMaxSum, rowValues[row] + board[row][col3]);
                    }

                    maxSum = Math.max(maxSum, currentMaxSum);
                }
            }
        }

        return maxSum;          
    }
}
