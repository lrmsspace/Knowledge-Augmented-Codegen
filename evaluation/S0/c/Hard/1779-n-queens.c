// Source: https://leetcode.com/problems/n-queens/   |   Difficulty: Hard
//
// Problem Description:
// The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.
//
// Given an integer n, return all distinct solutions to the n-queens puzzle. You may return the answer in any order.
//
// Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space, respectively.
//
// Example:
// Input: n = 4
// Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
// Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above
//
// Constraints:
// 1 <= n <= 9
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** solveNQueens(int n, int* returnSize, int** returnColumnSizes) {
    if (!returnSize || !returnColumnSizes) return NULL;
    *returnSize = 0;
    *returnColumnSizes = NULL;
    if (n <= 0) return NULL;

    char ***results = NULL;
    int cap = 0;

    int *cols = (int*)calloc(n, sizeof(int));
    int *diag1 = (int*)calloc(2 * n - 1, sizeof(int));
    int *diag2 = (int*)calloc(2 * n - 1, sizeof(int));
    char **board = (char**)malloc(n * sizeof(char*));
    for (int i = 0; i < n; ++i) {
        board[i] = (char*)malloc((n + 1) * sizeof(char));
        for (int j = 0; j < n; ++j) {
            board[i][j] = '.';
        }
        board[i][n] = '\0';
    }

    void backtrack(int row) {
        if (row == n) {
            if (*returnSize >= cap) {
                int newCap = (cap == 0) ? 16 : cap * 2;
                char ***tmp = (char***)realloc(results, newCap * sizeof(char**));
                if (!tmp) return;
                results = tmp;
                int *tmpCols = (int*)realloc(*returnColumnSizes, newCap * sizeof(int));
                if (!tmpCols) return;
                *returnColumnSizes = tmpCols;
                cap = newCap;
            }
            char **solution = (char**)malloc(n * sizeof(char*));
            for (int i = 0; i < n; ++i) {
                solution[i] = (char*)malloc((n + 1) * sizeof(char));
                strcpy(solution[i], board[i]);
            }
            results[*returnSize] = solution;
            (*returnColumnSizes)[*returnSize] = n;
            (*returnSize)++;
            return;
        }

        for (int col = 0; col < n; ++col) {
            if (cols[col] || diag1[row + col] || diag2[row - col + n - 1]) {
                continue;
            }
            board[row][col] = 'Q';
            cols[col] = 1;
            diag1[row + col] = 1;
            diag2[row - col + n - 1] = 1;

            backtrack(row + 1);

            board[row][col] = '.';
            cols[col] = 0;
            diag1[row + col] = 0;
            diag2[row - col + n - 1] = 0;
        }
    }
    backtrack(0);
    for (int i = 0; i < n; ++i) {
        free(board[i]);
    }
    free(board);
    free(cols);
    free(diag1);
    free(diag2);
    return results;
}
