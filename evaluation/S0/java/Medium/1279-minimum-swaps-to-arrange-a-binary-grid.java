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

class Solution {
    public int minSwaps(int[][] grid) {
        int n = grid.length;
        int[] trailingZeros = new int[n];

        // Count trailing zeros for each row
        for (int i = 0; i < n; i++) {
            int count = 0;
            for (int j = n - 1; j >= 0 && grid[i][j] == 0; j--) {
                count++;
            }
            trailingZeros[i] = count;
        }

        int swaps = 0;

        // For each row, ensure it has enough trailing zeros
        for (int i = 0; i < n; i++) {
            int requiredZeros = n - 1 - i;
            if (trailingZeros[i] >= requiredZeros) {
                continue; // This row is already valid
            }

            // Find a row below that has enough trailing zeros
            int j = i + 1;
            while (j < n && trailingZeros[j] < requiredZeros) {
                j++;
            }

            // If no such row exists, return -1
            if (j == n) {
                return -1;
            }

            // Swap rows to bring the found row up to the current position
            while (j > i) {
                int temp = trailingZeros[j];
                trailingZeros[j] = trailingZeros[j - 1];
                trailingZeros[j - 1] = temp;
                j--;
                swaps++;
            }
        }

        return swaps;           
    }
}
