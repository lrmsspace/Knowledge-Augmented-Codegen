// Source: https://leetcode.com/problems/stamping-the-grid/   |   Difficulty: Hard
//
// Problem Description:
// You are given an m x n binary matrix grid where each cell is either 0 (empty) or 1 (occupied).
//
// You are then given stamps of size stampHeight x stampWidth. We want to fit the stamps such that they follow the given restrictions and requirements:
//
//
// 	Cover all the empty cells.
// 	Do not cover any of the occupied cells.
// 	We can put as many stamps as we want.
// 	Stamps can overlap with each other.
// 	Stamps are not allowed to be rotated.
// 	Stamps must stay completely inside the grid.
//
//
// Return true if it is possible to fit the stamps while following the given restrictions and requirements. Otherwise, return false.
//
// Example:
// Input: grid = [[1,0,0,0],[1,0,0,0],[1,0,0,0],[1,0,0,0],[1,0,0,0]], stampHeight = 4, stampWidth = 3
// Output: true
// Explanation: We have two overlapping stamps (labeled 1 and 2 in the image) that are able to cover all the empty cells.
//
// Constraints:
// m == grid.length
// 	n == grid[r].length
// 	1 <= m, n <= 105
// 	1 <= m * n <= 2 * 105
// 	grid[r][c] is either 0 or 1.
// 	1 <= stampHeight, stampWidth <= 105
//

bool possibleToStamp(int** grid, int gridSize, int* gridColSize, int stampHeight, int stampWidth) {
    int m = gridSize, n = gridColSize[0];
    int **h = (int**)malloc((m + 1) * sizeof(int*));
    for (int i = 0; i <= m; i++) {
        h[i] = (int*)calloc(n + 1, sizeof(int));
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            h[i][j] = h[i - 1][j] + h[i][j - 1] - h[i - 1][j - 1] + (grid[i - 1][j - 1] == 1 ? 1 : 0);
        }
    }
    int **canStamp = (int**)malloc((m + 1) * sizeof(int*));
    for (int i = 0; i <= m; i++) {
        canStamp[i] = (int*)calloc(n + 1, sizeof(int));
    }
    for (int i = stampHeight; i <= m; i++) {
        for (int j = stampWidth; j <= n; j++) {
            int total = h[i][j] - h[i - stampHeight][j] - h[i][j - stampWidth] + h[i - stampHeight][j - stampWidth];
            if (total == 0) {
                canStamp[i - stampHeight + 1][j - stampWidth + 1] = 1;
            }
        }
    }
    int **cover = (int**)malloc((m + 2) * sizeof(int*));
    for (int i = 0; i <= m + 1; i++) {
        cover[i] = (int*)calloc(n + 2, sizeof(int));
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            cover[i][j] = cover[i - 1][j] + cover[i][j - 1] - cover[i - 1][j - 1] + canStamp[i][j];
        }
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (grid[i - 1][j - 1] == 0) {
                int total = cover[fmin(i, m - stampHeight + 1)][fmin(j, n - stampWidth + 1)] - cover[fmax(0, i - stampHeight)][fmin(j, n - stampWidth + 1)] - cover[fmin(i, m - stampHeight + 1)][fmax(0, j - stampWidth)] + cover[fmax(0, i - stampHeight)][fmax(0, j - stampWidth)];
                if (total == 0) {
                    // Free allocated memory
                    for (int x = 0; x <= m; x++) {
                        free(h[x]);
                        free(canStamp[x]);
                    }
                    free(h);
                    free(canStamp);
                    for (int x = 0; x <= m + 1; x++) {
                        free(cover[x]);
                    }
                    free(cover);
                    return false;
                }
            }
        }
    }
    for (int i = 0; i <= m; i++) {
        free(h[i]);
        free(canStamp[i]);
    }
    free(h);
    free(canStamp);
    for (int i = 0; i <= m + 1; i++) {
        free(cover[i]);
    }
    free(cover);
    return true;
}
