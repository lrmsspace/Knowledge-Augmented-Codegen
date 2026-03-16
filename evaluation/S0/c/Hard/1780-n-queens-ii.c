// Source: https://leetcode.com/problems/n-queens-ii/   |   Difficulty: Hard
//
// Problem Description:
// The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.
//
// Given an integer n, return the number of distinct solutions to the n-queens puzzle.
//
// Example:
// Input: n = 4
// Output: 2
// Explanation: There are two distinct solutions to the 4-queens puzzle as shown.
//
// Constraints:
// 1 <= n <= 9
//

int totalNQueens(int n) {
    int count = 0;
    int *cols = (int*)calloc(n, sizeof(int));
    int *diag1 = (int*)calloc(2 * n - 1, sizeof(int));
    int *diag2 = (int*)calloc(2 * n - 1, sizeof(int));

    void backtrack(int row) {
        if (row == n) {
            count++;
            return;
        }
        for (int col = 0; col < n; col++) {
            if (cols[col] || diag1[row + col] || diag2[row - col + n - 1]) continue;
            cols[col] = diag1[row + col] = diag2[row - col + n - 1] = 1;
            backtrack(row + 1);
            cols[col] = diag1[row + col] = diag2[row - col + n - 1] = 0;
        }
    }

    backtrack(0);
    free(cols);
    free(diag1);
    free(diag2);
    return count;       
}
