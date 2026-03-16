// Source: https://leetcode.com/problems/find-a-good-subset-of-the-matrix/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed m x n binary matrix grid.
//
// Let us call a non-empty subset of rows good if the sum of each column of the subset is at most half of the length of the subset.
//
// More formally, if the length of the chosen subset of rows is k, then the sum of each column should be at most floor(k / 2).
//
// Return an integer array that contains row indices of a good subset sorted in ascending order.
//
// If there are multiple good subsets, you can return any of them. If there are no good subsets, return an empty array.
//
// A subset of rows of the matrix grid is any matrix that can be obtained by deleting some (possibly none or all) rows from grid.
//
// Example:
// Input: grid = [[0,1,1,0],[0,0,0,1],[1,1,1,1]]
// Output: [0,1]
// Explanation: We can choose the 0th and 1st rows to create a good subset of rows.
// The length of the chosen subset is 2.
// - The sum of the 0th column is 0 + 0 = 0, which is at most half of the length of the subset.
// - The sum of the 1st column is 1 + 0 = 1, which is at most half of the length of the subset.
// - The sum of the 2nd column is 1 + 0 = 1, which is at most half of the length of the subset.
// - The sum of the 3rd column is 0 + 1 = 1, which is at most half of the length of the subset.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m <= 104
// 	1 <= n <= 5
// 	grid[i][j] is either 0 or 1.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* goodSubsetofBinaryMatrix(int** grid, int gridSize, int* gridColSize, int* returnSize){
    if (!returnSize || gridSize <= 0 || !gridColSize || *gridColSize <= 0)
        return NULL;

    int n = *gridColSize;
    int maxMask = 1 << n;
    int *rowForMask = (int*)calloc(maxMask, sizeof(int));
    if (!rowForMask) return NULL;

    for (int i = 0; i < gridSize; ++i) {
        int mask = 0;
        for (int j = 0; j < n; ++j) {
            if (grid[i][j]) {
                mask |= (1 << j);
            }
        }
        rowForMask[mask] = i + 1; /* store 1-based index */
    }

    /* check for single row with all zeros */
    if (rowForMask[0]) {
        int *result = (int*)malloc(sizeof(int));
        if (!result) {
            free(rowForMask);
            return NULL;
        }
        result[0] = rowForMask[0] - 1; /* convert to 0-based index */
        *returnSize = 1;
        free(rowForMask);
        return result;
    }

    /* check for pairs of rows that form a good subset */
    for (int m1 = 0; m1 < maxMask; ++m1) {
        if (!rowForMask[m1]) continue;
        for (int m2 = m1 + 1; m2 < maxMask; ++m2) {
            if (!rowForMask[m2]) continue;
            if ((m1 & m2) == 0) { /* valid pair */
                int *result = (int*)malloc(2 * sizeof(int));
                if (!result) {
                    free(rowForMask);
                    return NULL;
                }
                result[0] = rowForMask[m1] - 1; /* convert to 0-based index */
                result[1] = rowForMask[m2] - 1;
                *returnSize = 2;
                free(rowForMask);
                return result;
            }
        }
    }

    /* no good subset found */
    free(rowForMask);
    *returnSize = 0;
    return NULL;
}
