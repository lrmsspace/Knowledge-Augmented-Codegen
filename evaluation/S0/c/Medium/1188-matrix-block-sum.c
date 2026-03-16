// Source: https://leetcode.com/problems/matrix-block-sum/   |   Difficulty: Medium
//
// Problem Description:
// Given a m x n matrix mat and an integer k, return a matrix answer where each answer[i][j] is the sum of all elements mat[r][c] for:
//
//
// 	i - k <= r <= i + k,
// 	j - k <= c <= j + k, and
// 	(r, c) is a valid position in the matrix.
//
// Example:
// Input: mat = [[1,2,3],[4,5,6],[7,8,9]], k = 1
// Output: [[12,21,16],[27,45,33],[24,39,28]]
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= m, n, k <= 100
// 	1 <= mat[i][j] <= 100
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** matrixBlockSum(int** mat, int matSize, int* matColSize, int k, int* returnSize, int** returnColumnSizes) {
    int m = matSize;
    int n = matColSize[0];
    int** result = (int**)malloc(m * sizeof(int*));
    *returnColumnSizes = (int*)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        result[i] = (int*)malloc(n * sizeof(int));
        (*returnColumnSizes)[i] = n;
    }
    *returnSize = m;

    // Create prefix sum matrix
    int prefixSum[m + 1][n + 1];
    memset(prefixSum, 0, sizeof(prefixSum));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            prefixSum[i][j] = mat[i - 1][j - 1] + prefixSum[i - 1][j] + prefixSum[i][j - 1] - prefixSum[i - 1][j - 1];
        }
    }

    // Calculate block sums using prefix sums
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int r1 = fmax(0, i - k);
            int c1 = fmax(0, j - k);
            int r2 = fmin(m - 1, i + k);
            int c2 = fmin(n - 1, j + k);

            result[i][j] = prefixSum[r2 + 1][c2 + 1] - prefixSum[r1][c2 + 1] - prefixSum[r2 + 1][c1] + prefixSum[r1][c1];
        }
    }

    return result;      
}
