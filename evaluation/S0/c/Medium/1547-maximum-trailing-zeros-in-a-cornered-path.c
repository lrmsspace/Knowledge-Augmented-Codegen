// Source: https://leetcode.com/problems/maximum-trailing-zeros-in-a-cornered-path/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array grid of size m x n, where each cell contains a positive integer.
//
// A cornered path is defined as a set of adjacent cells with at most one turn. More specifically, the path should exclusively move either horizontally or vertically up to the turn (if there is one), without returning to a previously visited cell. After the turn, the path will then move exclusively in the alternate direction: move vertically if it moved horizontally, and vice versa, also without returning to a previously visited cell.
//
// The product of a path is defined as the product of all the values in the path.
//
// Return the maximum number of trailing zeros in the product of a cornered path found in grid.
//
// Note:
//
//
// 	Horizontal movement means moving in either the left or right direction.
// 	Vertical movement means moving in either the up or down direction.
//
// Example:
// Input: grid = [[23,17,15,3,20],[8,1,20,27,11],[9,4,6,2,21],[40,9,1,10,6],[22,7,4,5,3]]
// Output: 3
// Explanation: The grid on the left shows a valid cornered path.
// It has a product of 15 * 20 * 6 * 1 * 10 = 18000 which has 3 trailing zeros.
// It can be shown that this is the maximum trailing zeros in the product of a cornered path.
//
// The grid in the middle is not a cornered path as it has more than one turn.
// The grid on the right is not a cornered path as it requires a return to a previously visited cell.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 105
// 	1 <= m * n <= 105
// 	1 <= grid[i][j] <= 1000
//

int maxTrailingZeros(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize, n = gridColSize[0];
    int left[m][n][2], right[m][n][2], up[m][n][2], down[m][n][2];
    memset(left, 0, sizeof(left));
    memset(right, 0, sizeof(right));
    memset(up, 0, sizeof(up));
    memset(down, 0, sizeof(down));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int val = grid[i][j];
            int cnt2 = 0, cnt5 = 0;
            while (val % 2 == 0) {
                cnt2++;
                val /= 2;
            }
            while (val % 5 == 0) {
                cnt5++;
                val /= 5;
            }
            if (j > 0) {
                left[i][j][0] = left[i][j - 1][0] + cnt2;
                left[i][j][1] = left[i][j - 1][1] + cnt5;
            } else {
                left[i][j][0] = cnt2;
                left[i][j][1] = cnt5;
            }
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = n - 1; j >= 0; j--) {
            int val = grid[i][j];
            int cnt2 = 0, cnt5 = 0;
            while (val % 2 == 0) {
                cnt2++;
                val /= 2;
            }
            while (val % 5 == 0) {
                cnt5++;
                val /= 5;
            }
            if (j < n - 1) {
                right[i][j][0] = right[i][j + 1][0] + cnt2;
                right[i][j][1] = right[i][j + 1][1] + cnt5;
            } else {
                right[i][j][0] = cnt2;
                right[i][j][1] = cnt5;
            }
        }
    }

    for (int j = 0; j < n; j++) {
        for (int i = 0; i < m; i++) {
            int val = grid[i][j];
            int cnt2 = 0, cnt5 = 0;
            while (val % 2 == 0) {
                cnt2++;
                val /= 2;
            }
            while (val % 5 == 0) {
                cnt5++;
                val /= 5;
            }
            if (i > 0) {
                up[i][j][0] = up[i - 1][j][0] + cnt2;
                up[i][j][1] = up[i - 1][j][1] + cnt5;
            } else {
                up[i][j][0] = cnt2;
                up[i][j][1] = cnt5;
            }
        }
    }
    for (int j = 0; j < n; j++) {
        for (int i = m - 1; i >= 0; i--) {
            int val = grid[i][j];
            int cnt2 = 0, cnt5 = 0;
            while (val % 2 == 0) {
                cnt2++;
                val /= 2;
            }
            while (val % 5 == 0) {
                cnt5++;
                val /= 5;
            }
            if (i < m - 1) {
                down[i][j][0] = down[i + 1][j][0] + cnt2;
                down[i][j][1] = down[i + 1][j][1] + cnt5;
            } else {
                down[i][j][0] = cnt2;
                down[i][j][1] = cnt5;
            }
        }
    }
    int maxZeros = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            // Up + Left
            int cnt2 = up[i][j][0] + left[i][j][0] - (grid[i][j] % 2 == 0 ? 1 : 0);
            int cnt5 = up[i][j][1] + left[i][j][1] - (grid[i][j] % 5 == 0 ? 1 : 0);
            if (cnt2 < cnt5) cnt2 = cnt5;
            if (cnt2 > maxZeros) maxZeros = cnt2;

            // Up + Right
            cnt2 = up[i][j][0] + right[i][j][0] - (grid[i][j] % 2 == 0 ? 1 : 0);
            cnt5 = up[i][j][1] + right[i][j][1] - (grid[i][j] % 5 == 0 ? 1 : 0);
            if (cnt2 < cnt5) cnt2 = cnt5;
            if (cnt2 > maxZeros) maxZeros = cnt2;

            // Down + Left
            cnt2 = down[i][j][0] + left[i][j][0] - (grid[i][j] % 2 == 0 ? 1 : 0);
            cnt5 = down[i][j][1] + left[i][j][1] - (grid[i][j] % 5 == 0 ? 1 : 0);
            if (cnt2 < cnt5) cnt2 = cnt5;
            if (cnt2 > maxZeros) maxZeros = cnt2;

            // Down + Right
            cnt2 = down[i][j][0] + right[i][j][0] - (grid[i][j] % 2 == 0 ? 1 : 0);
            cnt5 = down[i][j][1] + right[i][j][1] - (grid[i][j] % 5 == 0 ? 1 : 0);
            if (cnt2 < cnt5) cnt2 = cnt5;
            if (cnt2 > maxZeros) maxZeros = cnt2;
        }
    }   
    return maxZeros;
}
