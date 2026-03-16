// Source: https://leetcode.com/problems/check-if-there-is-a-valid-parentheses-string-path/   |   Difficulty: Hard
//
// Problem Description:
// A parentheses string is a non-empty string consisting only of '(' and ')'. It is valid if any of the following conditions is true:
//
//
// 	It is ().
// 	It can be written as AB (A concatenated with B), where A and B are valid parentheses strings.
// 	It can be written as (A), where A is a valid parentheses string.
//
//
// You are given an m x n matrix of parentheses grid. A valid parentheses string path in the grid is a path satisfying all of the following conditions:
//
//
// 	The path starts from the upper left cell (0, 0).
// 	The path ends at the bottom-right cell (m - 1, n - 1).
// 	The path only ever moves down or right.
// 	The resulting parentheses string formed by the path is valid.
//
//
// Return true if there exists a valid parentheses string path in the grid. Otherwise, return false.
//
// Example:
// Input: grid = [["(","(","("],[")","(",")"],["(","(",")"],["(","(",")"]]
// Output: true
// Explanation: The above diagram shows two possible paths that form valid parentheses strings.
// The first path shown results in the valid parentheses string "()(())".
// The second path shown results in the valid parentheses string "((()))".
// Note that there may be other valid parentheses string paths.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 100
// 	grid[i][j] is either '(' or ')'.
//

class Solution {
    public boolean hasValidPath(char[][] grid) {
        int m = grid.length, n = grid[0].length;
        if ((m + n) % 2 == 0 || grid[0][0] == ')' || grid[m - 1][n - 1] == '(') {
            return false;
        }

        boolean[][][] dp = new boolean[m][n][m + n];
        dp[0][0][grid[0][0] == '(' ? 1 : 0] = true;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k <= i + j; k++) {
                    if (grid[i][j] == '(') {
                        if (i > 0) {
                            dp[i][j][k] = dp[i][j][k] || dp[i - 1][j][k - 1];
                        }
                        if (j > 0) {
                            dp[i][j][k] = dp[i][j][k] || dp[i][j - 1][k - 1];
                        }
                    } else {
                        if (i > 0) {
                            dp[i][j][k] = dp[i][j][k] || dp[i - 1][j][k + 1];
                        }
                        if (j > 0) {
                            dp[i][j][k] = dp[i][j][k] || dp[i][j - 1][k + 1];
                        }
                    }
                }
            }
        }

        return dp[m - 1][n - 1][0];         
    }
}
