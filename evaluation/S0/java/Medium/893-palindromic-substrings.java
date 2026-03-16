// Source: https://leetcode.com/problems/palindromic-substrings/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, return the number of palindromic substrings in it.
//
// A string is a palindrome when it reads the same backward as forward.
//
// A substring is a contiguous sequence of characters within the string.
//
// Example:
// Input: s = "abc"
// Output: 3
// Explanation: Three palindromic strings: "a", "b", "c".
//
// Constraints:
// 1 <= s.length <= 1000
// 	s consists of lowercase English letters.
//

class Solution {
    public int countSubstrings(String s) {
        int n = s.length();
        boolean[][] dp = new boolean[n][n];
        int count = 0;

        for (int length = 1; length <= n; length++) {
            for (int i = 0; i <= n - length; i++) {
                int j = i + length - 1;

                if (s.charAt(i) == s.charAt(j)) {
                    if (length <= 2) {
                        dp[i][j] = true;
                    } else {
                        dp[i][j] = dp[i + 1][j - 1];
                    }
                }

                if (dp[i][j]) {
                    count++;
                }
            }
        }

        return count;           
    }
}
