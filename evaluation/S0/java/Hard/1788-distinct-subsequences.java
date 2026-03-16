// Source: https://leetcode.com/problems/distinct-subsequences/   |   Difficulty: Hard
//
// Problem Description:
// Given two strings s and t, return the number of distinct subsequences of s which equals t.
//
// The test cases are generated so that the answer fits on a 32-bit signed integer.
//
// Example:
// Input: s = "rabbbit", t = "rabbit"
// Output: 3
// Explanation:
// As shown below, there are 3 ways you can generate "rabbit" from s.
// rabbbit
// rabbbit
// rabbbit
//
// Constraints:
// 1 <= s.length, t.length <= 1000
// 	s and t consist of English letters.
//

class Solution {
    public int numDistinct(String s, String t) {
        int m = s.length();
        int n = t.length();
        int[][] dp = new int[m + 1][n + 1];

        // An empty t can be formed by deleting all characters from s
        for (int i = 0; i <= m; i++) {
            dp[i][0] = 1;
        }

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s.charAt(i - 1) == t.charAt(j - 1)) {
                    dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }

        return dp[m][n];            
    }
}
