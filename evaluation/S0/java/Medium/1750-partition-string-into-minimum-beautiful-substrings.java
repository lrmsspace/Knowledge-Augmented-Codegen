// Source: https://leetcode.com/problems/partition-string-into-minimum-beautiful-substrings/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary string s, partition the string into one or more substrings such that each substring is beautiful.
//
// A string is beautiful if:
//
//
// 	It doesn't contain leading zeros.
// 	It's the binary representation of a number that is a power of 5.
//
//
// Return the minimum number of substrings in such partition. If it is impossible to partition the string s into beautiful substrings, return -1.
//
// A substring is a contiguous sequence of characters in a string.
//
// Example:
// Input: s = "1011"
// Output: 2
// Explanation: We can paritition the given string into ["101", "1"].
// - The string "101" does not contain leading zeros and is the binary representation of integer 51 = 5.
// - The string "1" does not contain leading zeros and is the binary representation of integer 50 = 1.
// It can be shown that 2 is the minimum number of beautiful substrings that s can be partitioned into.
//
// Constraints:
// 1 <= s.length <= 15
// 	s[i] is either '0' or '1'.
//

class Solution {
    public int minimumBeautifulSubstrings(String s) {
        int n = s.length();
        int[] dp = new int[n + 1];
        final int INF = (int) 1e9;
        for (int i = 0; i <= n; i++) {
            dp[i] = INF;
        }
        dp[0] = 0;

        for (int i = 1; i <= n; i++) {
            for (int j = i - 1; j >= 0; j--) {
                String sub = s.substring(j, i);
                if (isPowerOfFive(sub)) {
                    dp[i] = Math.min(dp[i], dp[j] + 1);
                }
            }
        }

        return dp[n] == INF ? -1 : dp[n];           
    }
}
