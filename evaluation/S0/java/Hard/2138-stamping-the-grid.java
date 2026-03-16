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

class Solution {
    public boolean possibleToStamp(int[][] grid, int stampHeight, int stampWidth) {
        int m = grid.length, n = grid[0].length;

        int[][] preSum = new int[m + 1][n + 1];
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                preSum[i][j] = grid[i - 1][j - 1] + preSum[i - 1][j] + preSum[i][j - 1] - preSum[i - 1][j - 1];
            }
        }

        int[][] stampable = new int[m + 1][n + 1];
        for (int i = stampHeight; i <= m; i++) {
            for (int j = stampWidth; j <= n; j++) {
                int total = preSum[i][j] - preSum[i - stampHeight][j] - preSum[i][j - stampWidth] + preSum[i - stampHeight][j - stampWidth];
                if (total == 0) {
                    stampable[i - stampHeight + 1][j - stampWidth + 1]++;
                    stampable[i - stampHeight + 1][j + 1]--;
                    stampable[i + 1][j - stampWidth + 1]--;
                    stampable[i + 1][j + 1]++;
                }
            }
        }

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                stampable[i][j] += stampable[i - 1][j] + stampable[i][j - 1] - stampable[i - 1][j - 1];
            }
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0 && stampable[i + 1][j + 1] <= 0) {
                    return false;
                }
            }
        }

        return true;            
    }
}
