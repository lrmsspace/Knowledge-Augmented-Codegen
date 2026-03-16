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

int orderOfLargestPlusSign(int n, int** mines, int minesSize, int* minesColSize) {
    int grid[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            grid[i][j] = 1;
        }
    }
    for (int i = 0; i < minesSize; i++) {
        grid[mines[i][0]][mines[i][1]] = 0;
    }

    int left[n][n], right[n][n], up[n][n], down[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {
                left[i][j] = (j == 0) ? 1 : left[i][j - 1] + 1;
                up[i][j] = (i == 0) ? 1 : up[i - 1][j] + 1;
            } else {
                left[i][j] = 0;
                up[i][j] = 0;
            }
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            if (grid[i][j] == 1) {
                right[i][j] = (j == n - 1) ? 1 : right[i][j + 1] + 1;
                down[i][j] = (i == n - 1) ? 1 : down[i + 1][j] + 1;
            } else {
                right[i][j] = 0;
                down[i][j] = 0;
            }
        }
    }

    int maxOrder = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int order = left[i][j];
            if (right[i][j] < order) order = right[i][j];
            if (up[i][j] < order) order = up[i][j];
            if (down[i][j] < order) order = down[i][j];
            if (order > maxOrder) {
                maxOrder = order;
            }
        }
    }
    return maxOrder; 
}
