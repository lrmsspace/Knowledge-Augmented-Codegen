// Source: https://leetcode.com/problems/minimum-number-of-flips-to-make-binary-grid-palindromic-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n binary matrix grid.
//
// A row or column is considered palindromic if its values read the same forward and backward.
//
// You can flip any number of cells in grid from 0 to 1, or from 1 to 0.
//
// Return the minimum number of cells that need to be flipped to make all rows and columns palindromic, and the total number of 1's in grid divisible by 4.
//
// Example:
// Input: grid = [[1,0,0],[0,1,0],[0,0,1]]
//
// Output: 3
//
// Explanation:
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m * n <= 2 * 105
// 	0 <= grid[i][j] <= 1
//

int minFlips(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize;
    int n = gridColSize[0];
    int totalFlips = 0;

    for (int i = 0; i <= (m - 1) / 2; i++) {
        for (int j = 0; j <= (n - 1) / 2; j++) {
            int onesCount = 0;
            int zerosCount = 0;

            // Collect the four symmetric positions
            int positions[4][2] = {
                {i, j},
                {m - 1 - i, j},
                {i, n - 1 - j},
                {m - 1 - i, n - 1 - j}
            };

            // Use a set to avoid counting duplicates in case of center rows/columns
            int uniquePositions[4][2];
            int uniqueCount = 0;
            for (int k = 0; k < 4; k++) {
                int x = positions[k][0];
                int y = positions[k][1];
                int isUnique = 1;
                for (int l = 0; l < uniqueCount; l++) {
                    if (uniquePositions[l][0] == x && uniquePositions[l][1] == y) {
                        isUnique = 0;
                        break;
                    }
                }
                if (isUnique) {
                    uniquePositions[uniqueCount][0] = x;
                    uniquePositions[uniqueCount][1] = y;
                    uniqueCount++;
                }
            }

            // Count ones and zeros in the unique positions
            for (int k = 0; k < uniqueCount; k++) {
                int x = uniquePositions[k][0];
                int y = uniquePositions[k][1];
                if (grid[x][y] == 1) {
                    onesCount++;
                } else {
                    zerosCount++;
                }
            }

            // Calculate minimum flips needed for this group
            totalFlips += (onesCount < zerosCount) ? onesCount : zerosCount;
        }
    }

    return totalFlips;      
}
