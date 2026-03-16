// Source: https://leetcode.com/problems/find-the-width-of-columns-of-a-grid/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed m x n integer matrix grid. The width of a column is the maximum length of its integers.
//
//
// 	For example, if grid = [[-10], [3], [12]], the width of the only column is 3 since -10 is of length 3.
//
//
// Return an integer array ans of size n where ans[i] is the width of the ith column.
//
// The length of an integer x with len digits is equal to len if x is non-negative, and len + 1 otherwise.
//
// Example:
// Input: grid = [[1],[22],[333]]
// Output: [3]
// Explanation: In the 0th column, 333 is of length 3.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 100 
// 	-109 <= grid[r][c] <= 109
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findColumnWidth(int** grid, int gridSize, int* gridColSize, int* returnSize) {
    int* ans = (int*)malloc((*gridColSize) * sizeof(int));
    for (int c = 0; c < *gridColSize; c++) {
        int maxWidth = 0;
        for (int r = 0; r < gridSize; r++) {
            int num = grid[r][c];
            int width = (num < 0) ? 1 : 0; // Account for negative sign
            if (num == 0) {
                width = 1; // Zero has length 1
            } else {
                while (num != 0) {
                    width++;
                    num /= 10;
                }
            }
            if (width > maxWidth) {
                maxWidth = width;
            }
        }
        ans[c] = maxWidth;
    }
    *returnSize = *gridColSize;
    return ans;     
}
