// Source: https://leetcode.com/problems/fill-a-special-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given a non-negative integer n representing a 2n x 2n grid. You must fill the grid with integers from 0 to 22n - 1 to make it special. A grid is special if it satisfies all the following conditions:
//
//
// 	All numbers in the top-right quadrant are smaller than those in the bottom-right quadrant.
// 	All numbers in the bottom-right quadrant are smaller than those in the bottom-left quadrant.
// 	All numbers in the bottom-left quadrant are smaller than those in the top-left quadrant.
// 	Each of its quadrants is also a special grid.
//
//
// Return the special 2n x 2n grid.
//
// Note: Any 1x1 grid is special.
//
// Example:
// Input: n = 0
//
// Output: [[0]]
//
// Explanation:
//
// The only number that can be placed is 0, and there is only one possible position in the grid.
//
// Constraints:
// 0 <= n <= 10
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** specialGrid(int n, int* returnSize, int** returnColumnSizes) {
    int size = 1 << n;
    *returnSize = size;
    *returnColumnSizes = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        (*returnColumnSizes)[i] = size;
    }

    int** grid = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        grid[i] = (int*)malloc(size * sizeof(int));
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int num = 0;
            for (int k = 0; k < n; k++) {
                int bit_i = (i >> (n - k - 1)) & 1;
                int bit_j = (j >> (n - k - 1)) & 1;
                num |= (bit_i ^ bit_j) << (2 * (n - k - 1) + bit_j);
            }
            grid[i][j] = num;
        }
    }

    return grid;        
}
