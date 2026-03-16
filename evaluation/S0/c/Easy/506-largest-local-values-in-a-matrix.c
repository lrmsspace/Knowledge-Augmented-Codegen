// Source: https://leetcode.com/problems/largest-local-values-in-a-matrix/   |   Difficulty: Easy
//
// Problem Description:
// You are given an n x n integer matrix grid.
//
// Generate an integer matrix maxLocal of size (n - 2) x (n - 2) such that:
//
//
// 	maxLocal[i][j] is equal to the largest value of the 3 x 3 matrix in grid centered around row i + 1 and column j + 1.
//
//
// In other words, we want to find the largest value in every contiguous 3 x 3 matrix in grid.
//
// Return the generated matrix.
//
// Example:
// Input: grid = [[9,9,8,1],[5,6,2,6],[8,2,6,4],[6,2,2,2]]
// Output: [[9,9],[8,6]]
// Explanation: The diagram above shows the original matrix and the generated matrix.
// Notice that each value in the generated matrix corresponds to the largest value of a contiguous 3 x 3 matrix in grid.
//
// Constraints:
// n == grid.length == grid[i].length
// 	3 <= n <= 100
// 	1 <= grid[i][j] <= 100
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** largestLocal(int** grid, int gridSize, int* gridColSize, int* returnSize, int** returnColumnSizes) {
    int n = gridSize;
    int newSize = n - 2;
    *returnSize = newSize;

    int** result = (int**)malloc(newSize * sizeof(int*));
    *returnColumnSizes = (int*)malloc(newSize * sizeof(int));
    for (int i = 0; i < newSize; i++) {
        result[i] = (int*)malloc(newSize * sizeof(int));
        (*returnColumnSizes)[i] = newSize;
    }

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            int maxVal = 0;
            for (int x = i; x < i + 3; x++) {
                for (int y = j; y < j + 3; y++) {
                    if (grid[x][y] > maxVal) {
                        maxVal = grid[x][y];
                    }
                }
            }
            result[i][j] = maxVal;
        }
    }

    return result;      
}
