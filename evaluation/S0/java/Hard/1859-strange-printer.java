// Source: https://leetcode.com/problems/strange-printer/   |   Difficulty: Hard
//
// Problem Description:
// There is a strange printer with the following two special properties:
//
//
// 	The printer can only print a sequence of the same character each time.
// 	At each turn, the printer can print new characters starting from and ending at any place and will cover the original existing characters.
//
//
// Given a string s, return the minimum number of turns the printer needed to print it.
//
// Example:
// Input: s = "aaabbb"
// Output: 2
// Explanation: Print "aaa" first and then print "bbb".
//
// Constraints:
// 1 <= s.length <= 100
// 	s consists of lowercase English letters.
//

class Solution {
    public int strangePrinter(String s) {
        int n = s.length();
        int[][] dp = new int[n][n];

        for (int len = 1; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                dp[i][j] = len; // Maximum turns needed is len (printing one character at a time)

                for (int k = i; k < j; k++) {
                    int temp = dp[i][k] + dp[k + 1][j];
                    if (s.charAt(k) == s.charAt(j)) {
                        temp--; // Merge the last print if characters are the same
                    }
                    dp[i][j] = Math.min(dp[i][j], temp);
                }
            }
        }

        return dp[0][n - 1];            
    }
}
