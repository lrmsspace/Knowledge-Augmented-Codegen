// Source: https://leetcode.com/problems/largest-plus-sign/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n. You have an n x n binary grid grid with all values initially 1's except for some indices given in the array mines. The ith element of the array mines is defined as mines[i] = [xi, yi] where grid[xi][yi] == 0.
//
// Return the order of the largest axis-aligned plus sign of 1's contained in grid. If there is none, return 0.
//
// An axis-aligned plus sign of 1's of order k has some center grid[r][c] == 1 along with four arms of length k - 1 going up, down, left, and right, and made of 1's. Note that there could be 0's or 1's beyond the arms of the plus sign, only the relevant area of the plus sign is checked for 1's.
//
// Example:
// Input: n = 5, mines = [[4,2]]
// Output: 2
// Explanation: In the above grid, the largest plus sign can only be of order 2. One of them is shown.
//
// Constraints:
// 1 <= n <= 500
// 	1 <= mines.length <= 5000
// 	0 <= xi, yi < n
// 	All the pairs (xi, yi) are unique.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int orderOfLargestPlusSign(int n, int[][] mines) {
        int[][] grid = new int[n][n];
        for (int i = 0; i < n; i++) {
            Arrays.fill(grid[i], 1);
        }
        for (int[] mine : mines) {
            grid[mine[0]][mine[1]] = 0;
        }

        int[][] left = new int[n][n];
        int[][] right = new int[n][n];
        int[][] up = new int[n][n];
        int[][] down = new int[n][n];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    left[i][j] = (j > 0 ? left[i][j - 1] : 0) + 1;
                    up[i][j] = (i > 0 ? up[i - 1][j] : 0) + 1;
                }
            }
        }

        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (grid[i][j] == 1) {
                    right[i][j] = (j < n - 1 ? right[i][j + 1] : 0) + 1;
                    down[i][j] = (i < n - 1 ? down[i + 1][j] : 0) + 1;
                }
            }
        }

        int maxOrder = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    int order = Math.min(Math.min(left[i][j], right[i][j]), Math.min(up[i][j], down[i][j]));
                    maxOrder = Math.max(maxOrder, order);
                }
            }
        }

        return maxOrder;            
    }
}
