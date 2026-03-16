// Source: https://leetcode.com/problems/diagonal-traverse/   |   Difficulty: Medium
//
// Problem Description:
// Given an m x n matrix mat, return an array of all the elements of the array in a diagonal order.
//
// Example:
// Input: mat = [[1,2,3],[4,5,6],[7,8,9]]
// Output: [1,2,4,7,5,3,6,8,9]
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= m, n <= 104
// 	1 <= m * n <= 104
// 	-105 <= mat[i][j] <= 105
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findDiagonalOrder(int** mat, int matSize, int* matColSize, int* returnSize) {
    int m = matSize;
    int n = matColSize[0];
    int* result = (int*)malloc(sizeof(int) * m * n);
    int index = 0;

    for (int d = 0; d < m + n - 1; d++) {
        if (d % 2 == 0) {
            int r = (d < n) ? 0 : d - n + 1;
            int c = (d < n) ? d : n - 1;
            while (r < m && c >= 0) {
                result[index++] = mat[r][c];
                r++;
                c--;
            }
        } else {
            int r = (d < m) ? d : m - 1;
            int c = (d < m) ? 0 : d - m + 1;
            while (r >= 0 && c < n) {
                result[index++] = mat[r][c];
                r--;
                c++;
            }
        }
    }

    *returnSize = m * n;
    return result;      
}
