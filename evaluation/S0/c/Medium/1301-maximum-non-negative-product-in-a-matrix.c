// Source: https://leetcode.com/problems/maximum-non-negative-product-in-a-matrix/   |   Difficulty: Medium
//
// Problem Description:
// You are given a m x n matrix grid. Initially, you are located at the top-left corner (0, 0), and in each step, you can only move right or down in the matrix.
//
// Among all possible paths starting from the top-left corner (0, 0) and ending in the bottom-right corner (m - 1, n - 1), find the path with the maximum non-negative product. The product of a path is the product of all integers in the grid cells visited along the path.
//
// Return the maximum non-negative product modulo 109 + 7. If the maximum product is negative, return -1.
//
// Notice that the modulo is performed after getting the maximum product.
//
// Example:
// Input: grid = [[-1,-2,-3],[-2,-3,-3],[-3,-3,-2]]
// Output: -1
// Explanation: It is not possible to get non-negative product in the path from (0, 0) to (2, 2), so return -1.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 15
// 	-4 <= grid[i][j] <= 4
//

int maxProductPath(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize, n = gridColSize[0];
    long long mod = 1e9 + 7;
    long long maxProd[m][n], minProd[m][n];

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0) {
                maxProd[i][j] = minProd[i][j] = grid[i][j];
            } else {
                long long candidatesMax[2] = {LLONG_MIN, LLONG_MIN};
                long long candidatesMin[2] = {LLONG_MAX, LLONG_MAX};

                if (i > 0) {
                    candidatesMax[0] = maxProd[i - 1][j] * grid[i][j];
                    candidatesMin[0] = minProd[i - 1][j] * grid[i][j];
                }
                if (j > 0) {
                    candidatesMax[1] = maxProd[i][j - 1] * grid[i][j];
                    candidatesMin[1] = minProd[i][j - 1] * grid[i][j];
                }

                maxProd[i][j] = fmax(fmax(candidatesMax[0], candidatesMax[1]),
                                     fmax(candidatesMin[0], candidatesMin[1]));
                minProd[i][j] = fmin(fmin(candidatesMax[0], candidatesMax[1]),
                                     fmin(candidatesMin[0], candidatesMin[1]));
            }
        }
    }

    return maxProd[m - 1][n - 1] < 0 ? -1 : (int)(maxProd[m - 1][n - 1] % mod);     
}
