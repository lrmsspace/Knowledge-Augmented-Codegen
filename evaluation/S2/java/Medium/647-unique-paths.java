// Source: https://leetcode.com/problems/unique-paths/   |   Difficulty: Medium
//
// Problem Description:
// There is a robot on an m x n grid. The robot is initially located at the top-left corner (i.e., grid[0][0]). The robot tries to move to the bottom-right corner (i.e., grid[m - 1][n - 1]). The robot can only move either down or right at any point in time.
//
// Given the two integers m and n, return the number of possible unique paths that the robot can take to reach the bottom-right corner.
//
// The test cases are generated so that the answer will be less than or equal to 2 * 109.
//
// Example:
// Input: m = 3, n = 7
// Output: 28
//
// Constraints:
// 1 <= m, n <= 100
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
    public int uniquePaths(int m, int n) {
        int[][] dp = new int[m][n];

        // Base cases: There is only one way to reach any cell in the first row or first column
        for (int i = 0; i < m; i++) {
            dp[i][0] = 1;
        }
        for (int j = 0; j < n; j++) {
            dp[0][j] = 1;
        }

        // Fill the dp table using the relation: dp[i][j] = dp[i-1][j] + dp[i][j-1]
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }

        return dp[m - 1][n - 1];            
    }
}
