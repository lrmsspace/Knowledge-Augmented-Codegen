// Source: https://leetcode.com/problems/sort-the-matrix-diagonally/   |   Difficulty: Medium
//
// Problem Description:
// A matrix diagonal is a diagonal line of cells starting from some cell in either the topmost row or leftmost column and going in the bottom-right direction until reaching the matrix's end. For example, the matrix diagonal starting from mat[2][0], where mat is a 6 x 3 matrix, includes cells mat[2][0], mat[3][1], and mat[4][2].
//
// Given an m x n matrix mat of integers, sort each matrix diagonal in ascending order and return the resulting matrix.
//
// Example:
// Input: mat = [[3,3,1,1],[2,2,1,2],[1,1,1,2]]
// Output: [[1,1,1,1],[1,2,2,2],[1,2,3,3]]
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= m, n <= 100
// 	1 <= mat[i][j] <= 100
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** diagonalSort(int** mat, int matSize, int* matColSize, int* returnSize, int** returnColumnSizes) {
    int m = matSize;
    int n = matColSize[0];
    int** res = (int**)malloc(sizeof(int*) * m);
    *returnColumnSizes = (int*)malloc(sizeof(int) * m);
    for (int i = 0; i < m; i++) {
        res[i] = (int*)malloc(sizeof(int) * n);
        (*returnColumnSizes)[i] = n;
        for (int j = 0; j < n; j++) {
            res[i][j] = mat[i][j];
        }
    }

    for (int col = 0; col < n; col++) {
        int count[101] = {0};
        int x = 0, y = col;
        while (x < m && y < n) {
            count[res[x][y]]++;
            x++;
            y++;
        }
        x = 0;
        y = col;
        for (int val = 1; val <= 100; val++) {
            while (count[val] > 0) {
                res[x][y] = val;
                x++;
                y++;
                count[val]--;
            }
        }
    }

    for (int row = 1; row < m; row++) {
        int count[101] = {0};
        int x = row, y = 0;
        while (x < m && y < n) {
            count[res[x][y]]++;
            x++;
            y++;
        }
        x = row;
        y = 0;
        for (int val = 1; val <= 100; val++) {
            while (count[val] > 0) {
                res[x][y] = val;
                x++;
                y++;
                count[val]--;
            }
        }
    }

    *returnSize = m;
    return res;     
}
