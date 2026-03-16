// Source: https://leetcode.com/problems/minimum-absolute-difference-in-sliding-submatrix/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n integer matrix grid and an integer k.
//
// For every contiguous k x k submatrix of grid, compute the minimum absolute difference between any two distinct values within that submatrix.
//
// Return a 2D array ans of size (m - k + 1) x (n - k + 1), where ans[i][j] is the minimum absolute difference in the submatrix whose top-left corner is (i, j) in grid.
//
// Note: If all elements in the submatrix have the same value, the answer will be 0.
// A submatrix (x1, y1, x2, y2) is a matrix that is formed by choosing all cells matrix[x][y] where x1 <= x <= x2 and y1 <= y <= y2.
//
// Example:
// Input: grid = [[1,8],[3,-2]], k = 2
//
// Output: [[2]]
//
// Explanation:
//
//
// 	There is only one possible k x k submatrix: [[1, 8], [3, -2]].
// 	Distinct values in the submatrix are [1, 8, 3, -2].
// 	The minimum absolute difference in the submatrix is |1 - 3| = 2. Thus, the answer is [[2]].
//
// Constraints:
// 1 <= m == grid.length <= 30
// 	1 <= n == grid[i].length <= 30
// 	-105 <= grid[i][j] <= 105
// 	1 <= k <= min(m, n)
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** minAbsDiff(int** grid, int gridSize, int* gridColSize, int k, int* returnSize, int** returnColumnSizes) {
    int m = gridSize, n = gridColSize[0];
    int** ans = (int**)malloc((m - k + 1) * sizeof(int*));
    *returnColumnSizes = (int*)malloc((m - k + 1) * sizeof(int));
    *returnSize = m - k + 1;
    for (int i = 0; i < m - k + 1; i++) {
        ans[i] = (int*)malloc((n - k + 1) * sizeof(int));
        (*returnColumnSizes)[i] = n - k + 1;
        for (int j = 0; j < n - k + 1; j++) {
            int freq[200001] = {0};
            for (int x = i; x < i + k; x++) {
                for (int y = j; y < j + k; y++) {
                    freq[grid[x][y] + 100000]++;
                }
            }
            int prev = -1;
            int minDiff = 200001;
            for (int v = 0; v <= 200000; v++) {
                if (freq[v] > 0) {
                    if (prev != -1) {
                        minDiff = (minDiff < (v - prev)) ? minDiff : (v - prev);
                    }
                    prev = v;
                }
            }
            ans[i][j] = minDiff == 200001 ? 0 : minDiff;
        }
    }
    return ans;     
}
