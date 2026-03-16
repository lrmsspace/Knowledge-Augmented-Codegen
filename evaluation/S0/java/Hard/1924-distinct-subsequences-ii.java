// Source: https://leetcode.com/problems/distinct-subsequences-ii/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s, return the number of distinct non-empty subsequences of s. Since the answer may be very large, return it modulo 109 + 7.
// A subsequence of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not.
//
// Example:
// Input: s = "abc"
// Output: 7
// Explanation: The 7 distinct subsequences are "a", "b", "c", "ab", "ac", "bc", and "abc".
//
// Constraints:
// 1 <= s.length <= 2000
// 	s consists of lowercase English letters.
//

class Solution {
    public int distinctSubseqII(String s) {
        int MOD = 1_000_000_007;
        int n = s.length();
        int[] dp = new int[n + 1];
        dp[0] = 1; // empty subsequence

        int[] lastOccurrence = new int[26];
        for (int i = 0; i < 26; i++) {
            lastOccurrence[i] = -1;
        }

        for (int i = 1; i <= n; i++) {
            char currentChar = s.charAt(i - 1);
            dp[i] = (2 * dp[i - 1]) % MOD;

            int lastIndex = lastOccurrence[currentChar - 'a'];
            if (lastIndex != -1) {
                dp[i] = (dp[i] - dp[lastIndex] + MOD) % MOD;
            }

            lastOccurrence[currentChar - 'a'] = i - 1;
        }

        return (dp[n] - 1 + MOD) % MOD; // subtracting the empty subsequence            
    }
}
