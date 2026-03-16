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

class Solution {
    public long maximumValueSum(int[][] board) {
        int m = board.length;
        int n = board[0].length;
        long maxSum = Long.MIN_VALUE;

        for (int r1 = 0; r1 < m; r1++) {
            for (int r2 = r1 + 1; r2 < m; r2++) {
                for (int r3 = r2 + 1; r3 < m; r3++) {
                    long currentMax = Long.MIN_VALUE;

                    for (int c1 = 0; c1 < n; c1++) {
                        for (int c2 = 0; c2 < n; c2++) {
                            if (c2 == c1) continue;
                            for (int c3 = 0; c3 < n; c3++) {
                                if (c3 == c1 || c3 == c2) continue;

                                long currentSum = (long) board[r1][c1] + board[r2][c2] + board[r3][c3];
                                currentMax = Math.max(currentMax, currentSum);
                            }
                        }
                    }

                    maxSum = Math.max(maxSum, currentMax);
                }
            }
        }

        return maxSum;          
    }
}
