// Source: https://leetcode.com/problems/longest-palindromic-subsequence-after-at-most-k-operations/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s and an integer k.
//
// In one operation, you can replace the character at any position with the next or previous letter in the alphabet (wrapping around so that 'a' is after 'z'). For example, replacing 'a' with the next letter results in 'b', and replacing 'a' with the previous letter results in 'z'. Similarly, replacing 'z' with the next letter results in 'a', and replacing 'z' with the previous letter results in 'y'.
//
// Return the length of the longest palindromic subsequence of s that can be obtained after performing at most k operations.
//
// Example:
// Input: s = "abced", k = 2
//
// Output: 3
//
// Explanation:
//
//
// 	Replace s[1] with the next letter, and s becomes "acced".
// 	Replace s[4] with the previous letter, and s becomes "accec".
//
//
// The subsequence "ccc" forms a palindrome of length 3, which is the maximum.
//
// Constraints:
// 1 <= s.length <= 200
// 	1 <= k <= 200
// 	s consists of only lowercase English letters.
//

class Solution {
    public int longestPalindromicSubsequence(String s, int k) {
        int n = s.length();
        int[][] dp = new int[n][n];

        for (int len = 1; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;

                if (i == j) {
                    dp[i][j] = 0;
                } else {
                    int cost = Math.abs(s.charAt(i) - s.charAt(j));
                    cost = Math.min(cost, 26 - cost);

                    if (len == 2) {
                        dp[i][j] = cost;
                    } else {
                        dp[i][j] = Math.min(dp[i + 1][j - 1] + cost, Math.min(dp[i + 1][j], dp[i][j - 1]));
                    }
                }
            }
        }

        for (int length = n; length >= 0; length--) {
            if (dp[0][n - 1] <= k) {
                return length;
            }
            // Reduce the length by removing two characters from either end
            dp[0][n - 1] -= 2;
        }

        return 0;           
    }
}
