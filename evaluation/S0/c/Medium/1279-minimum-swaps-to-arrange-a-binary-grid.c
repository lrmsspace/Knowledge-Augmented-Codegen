// Source: https://leetcode.com/problems/minimum-swaps-to-arrange-a-binary-grid/   |   Difficulty: Medium
//
// Problem Description:
// Given an n x n binary grid, in one step you can choose two adjacent rows of the grid and swap them.
//
// A grid is said to be valid if all the cells above the main diagonal are zeros.
//
// Return the minimum number of steps needed to make the grid valid, or -1 if the grid cannot be valid.
//
// The main diagonal of a grid is the diagonal that starts at cell (1, 1) and ends at cell (n, n).
//
// Example:
// Input: grid = [[0,0,1],[1,1,0],[1,0,0]]
// Output: 3
//
// Constraints:
// n == grid.length == grid[i].length
// 	1 <= n <= 200
// 	grid[i][j] is either 0 or 1
//

int minSwaps(int** grid, int gridSize, int* gridColSize) {
    int n = gridSize;
    int* trailingZeros = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = n - 1; j >= 0; j--) {
            if (grid[i][j] == 0) {
                count++;
            } else {
                break;
            }
        }
        trailingZeros[i] = count;
    }

    int swaps = 0;
    for (int i = 0; i < n; i++) {
        int requiredZeros = n - 1 - i;
        int rowIndex = -1;
        for (int j = i; j < n; j++) {
            if (trailingZeros[j] >= requiredZeros) {
                rowIndex = j;
                break;
            }
        }
        if (rowIndex == -1) {
            free(trailingZeros);
            return -1;
        }
        while (rowIndex > i) {
            int temp = trailingZeros[rowIndex];
            trailingZeros[rowIndex] = trailingZeros[rowIndex - 1];
            trailingZeros[rowIndex - 1] = temp;
            rowIndex--;
            swaps++;
        }
    }

    free(trailingZeros);
    return swaps;       
}
