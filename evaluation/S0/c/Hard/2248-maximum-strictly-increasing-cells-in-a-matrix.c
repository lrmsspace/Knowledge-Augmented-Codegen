// Source: https://leetcode.com/problems/maximum-strictly-increasing-cells-in-a-matrix/   |   Difficulty: Hard
//
// Problem Description:
// Given a 1-indexed m x n integer matrix mat, you can select any cell in the matrix as your starting cell.
//
// From the starting cell, you can move to any other cell in the same row or column, but only if the value of the destination cell is strictly greater than the value of the current cell. You can repeat this process as many times as possible, moving from cell to cell until you can no longer make any moves.
//
// Your task is to find the maximum number of cells that you can visit in the matrix by starting from some cell.
//
// Return an integer denoting the maximum number of cells that can be visited.
//
// Example:
// Input: mat = [[3,1],[3,4]]
// Output: 2
// Explanation: The image shows how we can visit 2 cells starting from row 1, column 2. It can be shown that we cannot visit more than 2 cells no matter where we start from, so the answer is 2.
//
// Constraints:
// m == mat.length 
// 	n == mat[i].length 
// 	1 <= m, n <= 105
// 	1 <= m * n <= 105
// 	-105 <= mat[i][j] <= 105
//

int maxIncreasingCells(int** mat, int matSize, int* matColSize) {
    int m = matSize, n = *matColSize;
    int size = m * n;
    int *dp = (int*)calloc(size, sizeof(int));
    if (!dp) return 0;

    typedef struct {
        int val;
        int row;
        int col;
    } Cell;

    Cell *cells = (Cell*)malloc(size * sizeof(Cell));
    if (!cells) { free(dp); return 0; }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cells[i * n + j].val = mat[i][j];
            cells[i * n + j].row = i;
            cells[i * n + j].col = j;
        }
    }

    qsort(cells, size, sizeof(Cell), cmpInt);

    int *maxRow = (int*)calloc(m, sizeof(int));
    int *maxCol = (int*)calloc(n, sizeof(int));
    if (!maxRow || !maxCol) {
        free(dp); free(cells); free(maxRow); free(maxCol);
        return 0;
    }

    int ans = 1;
    for (int i = 0; i < size;) {
        int j = i;
        while (j < size && cells[j].val == cells[i].val) ++j;

        for (int k = i; k < j; ++k) {
            int r = cells[k].row, c = cells[k].col;
            dp[r * n + c] = 1 + (maxRow[r] > maxCol[c] ? maxRow[r] : maxCol[c]);
            if (dp[r * n + c] > ans) ans = dp[r * n + c];
        }
        for (int k = i; k < j; ++k) {
            int r = cells[k].row, c = cells[k].col;
            if (dp[r * n + c] > maxRow[r]) maxRow[r] = dp[r * n + c];
            if (dp[r * n + c] > maxCol[c]) maxCol[c] = dp[r * n + c];
        }
        i = j;
    }

    free(dp);
    free(cells);
    free(maxRow);
    free(maxCol);
    return ans;
}
