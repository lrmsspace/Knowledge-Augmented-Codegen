// Source: https://leetcode.com/problems/palindrome-partitioning-iii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s containing lowercase letters and an integer k. You need to :
//
//
// 	First, change some characters of s to other lowercase English letters.
// 	Then divide s into k non-empty disjoint substrings such that each substring is a palindrome.
//
//
// Return the minimal number of characters that you need to change to divide the string.
//
// Example:
// Input: s = "abc", k = 2
// Output: 1
// Explanation: You can split the string into "ab" and "c", and change 1 character in "ab" to make it palindrome.
//
// Constraints:
// 1 <= k <= s.length <= 100.
// 	s only contains lowercase English letters.
//

class Solution {
    public int palindromePartition(String s, int k) {
        int n = s.length();
        int[][] dp = new int[n][n];

        // Precompute the cost to convert each substring s[i..j] into a palindrome
        for (int length = 2; length <= n; length++) {
            for (int i = 0; i <= n - length; i++) {
                int j = i + length - 1;
                if (s.charAt(i) == s.charAt(j)) {
                    dp[i][j] = dp[i + 1][j - 1];
                } else {
                    dp[i][j] = dp[i + 1][j - 1] + 1;
                }
            }
        }

        // Initialize the DP array for minimum changes
        int[][] minChanges = new int[k + 1][n + 1];
        for (int i = 0; i <= k; i++) {
            for (int j = 0; j <= n; j++) {
                minChanges[i][j] = Integer.MAX_VALUE / 2; // Use a large number to avoid overflow
            }
        }
        minChanges[0][0] = 0;

        // Fill the DP table
        for (int parts = 1; parts <= k; parts++) {
            for (int end = parts; end <= n; end++) {
                for (int start = parts - 1; start < end; start++) {
                    minChanges[parts][end] = Math.min(minChanges[parts][end],
                            minChanges[parts - 1][start] + dp[start][end - 1]);
                }
            }
        }

        return minChanges[k][n];                    
    }
}
