// Source: https://leetcode.com/problems/increment-submatrices-by-one/   |   Difficulty: Medium
//
// Problem Description:
// You are given a positive integer n, indicating that we initially have an n x n 0-indexed integer matrix mat filled with zeroes.
//
// You are also given a 2D integer array query. For each query[i] = [row1i, col1i, row2i, col2i], you should do the following operation:
//
//
// 	Add 1 to every element in the submatrix with the top left corner (row1i, col1i) and the bottom right corner (row2i, col2i). That is, add 1 to mat[x][y] for all row1i <= x <= row2i and col1i <= y <= col2i.
//
//
// Return the matrix mat after performing every query.
//
// Example:
// Input: n = 3, queries = [[1,1,2,2],[0,0,1,1]]
// Output: [[1,1,0],[1,2,1],[0,1,1]]
// Explanation: The diagram above shows the initial matrix, the matrix after the first query, and the matrix after the second query.
// - In the first query, we add 1 to every element in the submatrix with the top left corner (1, 1) and bottom right corner (2, 2).
// - In the second query, we add 1 to every element in the submatrix with the top left corner (0, 0) and bottom right corner (1, 1).
//
// Constraints:
// 1 <= n <= 500
// 	1 <= queries.length <= 104
// 	0 <= row1i <= row2i < n
// 	0 <= col1i <= col2i < n
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** rangeAddQueries(int n, int** queries, int queriesSize, int* queriesColSize, int* returnSize, int** returnColumnSizes) {
    int** mat = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        mat[i] = (int*)calloc(n, sizeof(int));
    }

    for (int q = 0; q < queriesSize; q++) {
        int r1 = queries[q][0];
        int c1 = queries[q][1];
        int r2 = queries[q][2];
        int c2 = queries[q][3];

        mat[r1][c1] += 1;
        if (c2 + 1 < n) {
            mat[r1][c2 + 1] -= 1;
        }
        if (r2 + 1 < n) {
            mat[r2 + 1][c1] -= 1;
        }
        if (r2 + 1 < n && c2 + 1 < n) {
            mat[r2 + 1][c2 + 1] += 1;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 1; j < n; j++) {
            mat[i][j] += mat[i][j - 1];
        }
    }

    for (int j = 0; j < n; j++) {
        for (int i = 1; i < n; i++) {
            mat[i][j] += mat[i - 1][j];
        }
    }

    *returnSize = n;
    *returnColumnSizes = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        (*returnColumnSizes)[i] = n;
    }

    return mat;     
}
