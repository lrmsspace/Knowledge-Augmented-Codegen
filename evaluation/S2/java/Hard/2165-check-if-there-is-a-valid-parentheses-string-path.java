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
    public boolean hasValidPath(char[][] grid) {
        int m = grid.length, n = grid[0].length;
        // dp[i][j] is the set of possible counts of '(' minus ')' at (i, j)
        Set<Integer>[][] dp = new HashSet[m][n];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                dp[i][j] = new HashSet<>();
                char c = grid[i][j];
                if (i == 0 && j == 0) {
                    dp[i][j].add(c == '(' ? 1 : -1);
                } else {
                    if (i > 0) {
                        for (int count : dp[i - 1][j]) {
                            int newCount = count + (c == '(' ? 1 : -1);
                            if (newCount >= 0) {
                                dp[i][j].add(newCount);
                            }
                        }
                    }
                    if (j > 0) {
                        for (int count : dp[i][j - 1]) {
                            int newCount = count + (c == '(' ? 1 : -1);
                            if (newCount >= 0) {
                                dp[i][j].add(newCount);
                            }
                        }
                    }
                }
            }
        }
        return dp[m - 1][n - 1].contains(0);            
    }
}
