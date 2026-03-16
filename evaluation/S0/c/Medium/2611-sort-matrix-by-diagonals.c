// Source: https://leetcode.com/problems/sort-matrix-by-diagonals/   |   Difficulty: Medium
//
// Problem Description:
// You are given an n x n square matrix of integers grid. Return the matrix such that:
//
//
// 	The diagonals in the bottom-left triangle (including the middle diagonal) are sorted in non-increasing order.
// 	The diagonals in the top-right triangle are sorted in non-decreasing order.
//
// Example:
// Input: grid = [[1,7,3],[9,8,2],[4,5,6]]
//
// Output: [[8,2,3],[9,6,7],[4,5,1]]
//
// Explanation:
//
//
//
// The diagonals with a black arrow (bottom-left triangle) should be sorted in non-increasing order:
//
//
// 	[1, 8, 6] becomes [8, 6, 1].
// 	[9, 5] and [4] remain unchanged.
//
//
// The diagonals with a blue arrow (top-right triangle) should be sorted in non-decreasing order:
//
//
// 	[7, 2] becomes [2, 7].
// 	[3] remains unchanged.
//
// Constraints:
// grid.length == grid[i].length == n
// 	1 <= n <= 10
// 	-105 <= grid[i][j] <= 105
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** sortMatrix(int** grid, int gridSize, int* gridColSize, int* returnSize, int** returnColumnSizes) {
    int n = gridSize;
    int** result = (int**)malloc(n * sizeof(int*));
    *returnColumnSizes = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        result[i] = (int*)malloc(n * sizeof(int));
        (*returnColumnSizes)[i] = n;
        for (int j = 0; j < n; j++) {
            result[i][j] = grid[i][j];
        }
    }

    // Sort bottom-left diagonals (non-increasing order)
    for (int col = 0; col < n; col++) {
        int diagSize = n - col;
        int* diag = (int*)malloc(diagSize * sizeof(int));
        for (int k = 0; k < diagSize; k++) {
            diag[k] = result[k][col + k];
        }
        // Sort in non-increasing order
        for (int x = 0; x < diagSize - 1; x++) {
            for (int y = x + 1; y < diagSize; y++) {
                if (diag[x] < diag[y]) {
                    int temp = diag[x];
                    diag[x] = diag[y];
                    diag[y] = temp;
                }
            }
        }
        for (int k = 0; k < diagSize; k++) {
            result[k][col + k] = diag[k];
        }
        free(diag);
    }

    for (int row = 1; row < n; row++) {
        int diagSize = n - row;
        int* diag = (int*)malloc(diagSize * sizeof(int));
        for (int k = 0; k < diagSize; k++) {
            diag[k] = result[row + k][k];
        }
        // Sort in non-increasing order
        for (int x = 0; x < diagSize - 1; x++) {
            for (int y = x + 1; y < diagSize; y++) {
                if (diag[x] < diag[y]) {
                    int temp = diag[x];
                    diag[x] = diag[y];
                    diag[y] = temp;
                }
            }
        }
        for (int k = 0; k < diagSize; k++) {
            result[row + k][k] = diag[k];
        }
        free(diag);
    }
    // Sort top-right diagonals (non-decreasing order)
    for (int row = 0; row < n; row++) {
        int diagSize = row + 1;
        int* diag = (int*)malloc(diagSize * sizeof(int));
        for (int k = 0; k < diagSize; k++) {
            diag[k] = result[row - k][k];
        }
        // Sort in non-decreasing order
        for (int x = 0; x < diagSize - 1; x++) {
            for (int y = x + 1; y < diagSize; y++) {
                if (diag[x] > diag[y]) {
                    int temp = diag[x];
                    diag[x] = diag[y];
                    diag[y] = temp;
                }
            }
        }
        for (int k = 0; k < diagSize; k++) {
            result[row - k][k] = diag[k];
        }
        free(diag);
    }
    for (int col = 1; col < n; col++) {
        int diagSize = n - col;
        int* diag = (int*)malloc(diagSize * sizeof(int));
        for (int k = 0; k < diagSize; k++) {
            diag[k] = result[n - 1 - k][col + k];
        }
        // Sort in non-decreasing order
        for (int x = 0; x < diagSize - 1; x++) {
            for (int y = x + 1; y < diagSize; y++) {
                if (diag[x] > diag[y]) {
                    int temp = diag[x];
                    diag[x] = diag[y];
                    diag[y] = temp;
                }
            }
        }
        for (int k = 0; k < diagSize; k++) {
            result[n - 1 - k][col + k] = diag[k];
        }
        free(diag);
    }
    *returnSize = n;
    return result;
}
