// Source: https://leetcode.com/problems/largest-magic-square/   |   Difficulty: Medium
//
// Problem Description:
// A k x k magic square is a k x k grid filled with integers such that every row sum, every column sum, and both diagonal sums are all equal. The integers in the magic square do not have to be distinct. Every 1 x 1 grid is trivially a magic square.
//
// Given an m x n integer grid, return the size (i.e., the side length k) of the largest magic square that can be found within this grid.
//
// Example:
// Input: grid = [[7,1,4,5,6],[2,5,1,6,4],[1,5,4,3,2],[1,2,7,3,4]]
// Output: 3
// Explanation: The largest magic square has a size of 3.
// Every row sum, column sum, and diagonal sum of this magic square is equal to 12.
// - Row sums: 5+1+6 = 5+4+3 = 2+7+3 = 12
// - Column sums: 5+5+2 = 1+4+7 = 6+3+3 = 12
// - Diagonal sums: 5+4+3 = 6+4+2 = 12
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 50
// 	1 <= grid[i][j] <= 106
//

int largestMagicSquare(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize, n = gridColSize[0];
    int maxSize = 1;

    // Precompute prefix sums for rows and columns
    int rowPrefixSum[m][n + 1];
    int colPrefixSum[m + 1][n];
    memset(rowPrefixSum, 0, sizeof(rowPrefixSum));
    memset(colPrefixSum, 0, sizeof(colPrefixSum));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            rowPrefixSum[i][j + 1] = rowPrefixSum[i][j] + grid[i][j];
            colPrefixSum[i + 1][j] = colPrefixSum[i][j] + grid[i][j];
        }
    }

    // Check for magic squares of size k
    for (int k = 2; k <= (m < n ? m : n); k++) {
        for (int i = 0; i <= m - k; i++) {
            for (int j = 0; j <= n - k; j++) {
                int targetSum = rowPrefixSum[i][j + k] - rowPrefixSum[i][j];
                int isMagic = 1;

                // Check rows
                for (int r = i; r < i + k; r++) {
                    if (rowPrefixSum[r][j + k] - rowPrefixSum[r][j] != targetSum) {
                        isMagic = 0;
                        break;
                    }
                }
                if (!isMagic) continue;

                // Check columns
                for (int c = j; c < j + k; c++) {
                    if (colPrefixSum[i + k][c] - colPrefixSum[i][c] != targetSum) {
                        isMagic = 0;
                        break;
                    }
                }
                if (!isMagic) continue;

                // Check diagonals
                int diag1Sum = 0, diag2Sum = 0;
                for (int d = 0; d < k; d++) {
                    diag1Sum += grid[i + d][j + d];
                    diag2Sum += grid[i + d][j + k - 1 - d];
                }
                if (diag1Sum != targetSum || diag2Sum != targetSum) {
                    isMagic = 0;
                }
                if (isMagic) {
                    if (k > maxSize) {
                        maxSize = k;
                    }
                }
                
            }
        }
    }
    return maxSize;
}
