// Source: https://leetcode.com/problems/length-of-longest-v-shaped-diagonal-segment/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D integer matrix grid of size n x m, where each element is either 0, 1, or 2.
//
// A V-shaped diagonal segment is defined as:
//
//
// 	The segment starts with 1.
// 	The subsequent elements follow this infinite sequence: 2, 0, 2, 0, ....
// 	The segment:
// 	
// 		Starts along a diagonal direction (top-left to bottom-right, bottom-right to top-left, top-right to bottom-left, or bottom-left to top-right).
// 		Continues the sequence in the same diagonal direction.
// 		Makes at most one clockwise 90-degree turn to another diagonal direction while maintaining the sequence.
// 	
// 	
//
//
// Return the length of the longest V-shaped diagonal segment. If no valid segment exists, return 0.
//
// Example:
// Input: grid = [[2,2,1,2,2],[2,0,2,2,0],[2,0,1,1,0],[1,0,2,2,2],[2,0,0,2,2]]
//
// Output: 5
//
// Explanation:
//
//
//
// The longest V-shaped diagonal segment has a length of 5 and follows these coordinates: (0,2) → (1,3) → (2,4), takes a 90-degree clockwise turn at (2,4), and continues as (3,3) → (4,2).
//
// Constraints:
// n == grid.length
// 	m == grid[i].length
// 	1 <= n, m <= 500
// 	grid[i][j] is either 0, 1 or 2.
//

class Solution {
    public int lenOfVDiagonal(int[][] grid) {
        int n = grid.length, m = grid[0].length;
        int[][][] dp = new int[n][m][4];
        int res = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) {
                    dp[i][j][0] = 1;
                    dp[i][j][1] = 1;
                    res = Math.max(res, 1);
                } else if (grid[i][j] == 2 || grid[i][j] == 0) {
                    int val = grid[i][j] == 2 ? 2 : 0;

                    if (i > 0 && j > 0 && grid[i - 1][j - 1] == val) {
                        dp[i][j][0] = dp[i - 1][j - 1][0] + 1;
                        res = Math.max(res, dp[i][j][0]);
                    }

                    if (i > 0 && j < m - 1 && grid[i - 1][j + 1] == val) {
                        dp[i][j][1] = dp[i - 1][j + 1][1] + 1;
                        res = Math.max(res, dp[i][j][1]);
                    }

                    if (i > 0 && j > 0 && grid[i - 1][j - 1] == val) {
                        dp[i][j][2] = dp[i - 1][j - 1][2] + 1;
                    }
                    if (i < n - 1 && j < m - 1 && grid[i + 1][j + 1] == val) {
                        dp[i][j][2] = Math.max(dp[i][j][2], dp[i + 1][j + 1][0] + 1);
                    }
                    res = Math.max(res, dp[i][j][2]);

                    if (i > 0 && j < m - 1 && grid[i - 1][j + 1] == val) {
                        dp[i][j][3] = dp[i - 1][j + 1][3] + 1;
                    }
                    if (i < n - 1 && j > 0 && grid[i + 1][j - 1] == val) {
                        dp[i][j][3] = Math.max(dp[i][j][3], dp[i + 1][j - 1][1] + 1);
                    }
                    res = Math.max(res, dp[i][j][3]);
                }
            }
        }
        return res;          
    }
}
