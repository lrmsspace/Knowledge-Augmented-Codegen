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

long long maximumValueSum(int** board, int boardSize, int* boardColSize) {
    int m = boardSize;
    int n = boardColSize[0];
    long long maxSum = -3000000000LL * 3;

    for (int c1 = 0; c1 < n; ++c1) {
        for (int c2 = c1 + 1; c2 < n; ++c2) {
            /* Prepare row sums for columns c1 and c2 */
            long long *rowSums = (long long*)malloc(m * sizeof(long long));
            if (!rowSums) return 0; /* allocation failure */
            for (int r = 0; r < m; ++r) {
                rowSums[r] = (long long)board[r][c1] + (long long)board[r][c2];
            }

            /* Find top 3 row sums */
            long long top1 = -3000000000LL, top2 = -3000000000LL, top3 = -3000000000LL;
            for (int r = 0; r < m; ++r) {
                if (rowSums[r] > top1) {
                    top3 = top2;
                    top2 = top1;
                    top1 = rowSums[r];
                } else if (rowSums[r] > top2) {
                    top3 = top2;
                    top2 = rowSums[r];
                } else if (rowSums[r] > top3) {
                    top3 = rowSums[r];
                }
            }

            /* Update maxSum with the best third column */
            for (int c3 = 0; c3 < n; ++c3) {
                if (c3 == c1 || c3 == c2) continue;
                long long currentSum = top1 + (long long)board[0][c3]; /* Start with top1 */
                for (int r = 0; r < m; ++r) {
                    if (rowSums[r] == top1) {
                        currentSum = top2 + (long long)board[r][c3];
                    } else if (rowSums[r] == top2) {
                        currentSum = top1 + (long long)board[r][c3];
                    } else {
                        currentSum = top1 + (long long)board[r][c3];
                    }       
                    if (currentSum > maxSum) {
                        maxSum = currentSum;
                    }
                }
                free(rowSums);
            }
        }
    }
    return maxSum;
}
