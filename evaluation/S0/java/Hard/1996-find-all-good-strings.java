// Source: https://leetcode.com/problems/find-all-good-strings/   |   Difficulty: Hard
//
// Problem Description:
// Given the strings s1 and s2 of size n and the string evil, return the number of good strings.
//
// A good string has size n, it is alphabetically greater than or equal to s1, it is alphabetically smaller than or equal to s2, and it does not contain the string evil as a substring. Since the answer can be a huge number, return this modulo 109 + 7.
//
// Example:
// Input: n = 2, s1 = "aa", s2 = "da", evil = "b"
// Output: 51 
// Explanation: There are 25 good strings starting with 'a': "aa","ac","ad",...,"az". Then there are 25 good strings starting with 'c': "ca","cc","cd",...,"cz" and finally there is one good string starting with 'd': "da".
//
// Constraints:
// s1.length == n
// 	s2.length == n
// 	s1 <= s2
// 	1 <= n <= 500
// 	1 <= evil.length <= 50
// 	All strings consist of lowercase English letters.
//

class Solution {
    public int findGoodStrings(int n, String s1, String s2, String evil) {
        int mod = 1_000_000_007;
        int m = evil.length();

        // KMP preprocessing
        int[] lps = new int[m];
        for (int i = 1, len = 0; i < m; ) {
            if (evil.charAt(i) == evil.charAt(len)) {
                lps[i++] = ++len;
            } else if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i++] = 0;
            }
        }

        // DP array
        Integer[][][] dp = new Integer[n + 1][m + 1][4];

        // DFS with memoization
        return dfs(0, 0, 0, n, s1, s2, evil, lps, dp, mod);
    }
}
