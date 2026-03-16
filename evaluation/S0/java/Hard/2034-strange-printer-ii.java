// Source: https://leetcode.com/problems/strange-printer-ii/   |   Difficulty: Hard
//
// Problem Description:
// There is a strange printer with the following two special requirements:
//
//
// 	On each turn, the printer will print a solid rectangular pattern of a single color on the grid. This will cover up the existing colors in the rectangle.
// 	Once the printer has used a color for the above operation, the same color cannot be used again.
//
//
// You are given a m x n matrix targetGrid, where targetGrid[row][col] is the color in the position (row, col) of the grid.
//
// Return true if it is possible to print the matrix targetGrid, otherwise, return false.
//
// Example:
// Input: targetGrid = [[1,1,1,1],[1,2,2,1],[1,2,2,1],[1,1,1,1]]
// Output: true
//
// Constraints:
// m == targetGrid.length
// 	n == targetGrid[i].length
// 	1 <= m, n <= 60
// 	1 <= targetGrid[row][col] <= 60
//

class Solution {
    public boolean isPrintable(int[][] targetGrid) {
        int m = targetGrid.length, n = targetGrid[0].length;
        int[][] bounds = new int[61][4];
        for (int[] b : bounds) {
            Arrays.fill(b, -1);
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int color = targetGrid[i][j];
                if (bounds[color][0] == -1) {
                    bounds[color][0] = i;
                    bounds[color][1] = j;
                    bounds[color][2] = i;
                    bounds[color][3] = j;
                } else {
                    bounds[color][0] = Math.min(bounds[color][0], i);
                    bounds[color][1] = Math.min(bounds[color][1], j);
                    bounds[color][2] = Math.max(bounds[color][2], i);
                    bounds[color][3] = Math.max(bounds[color][3], j);
                }
            }
        }

        boolean[] printed = new boolean[61];
        int totalColors = 0;
        for (int color = 1; color <= 60; color++) {
            if (bounds[color][0] != -1) {
                totalColors++;
            }
        }

        while (totalColors > 0) {
            boolean printedThisRound = false;
            for (int color = 1; color <= 60; color++) {
                if (printed[color] || bounds[color][0] == -1) {
                    continue;
                }
                boolean canPrint = true;
                for (int i = bounds[color][0]; i <= bounds[color][2]; i++) {
                    for (int j = bounds[color][1]; j <= bounds[color][3]; j++) {
                        if (targetGrid[i][j] != color && !printed[targetGrid[i][j]]) {
                            canPrint = false;
                            break;
                        }
                    }
                    if (!canPrint) {
                        break;
                    }
                }
                if (canPrint) {
                    printed[color] = true;
                    printedThisRound = true;
                    totalColors--;
                }
            }
            if (!printedThisRound) {
                return false;
            }
        }
        return true;                    
    }
}
