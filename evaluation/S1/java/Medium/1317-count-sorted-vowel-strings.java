// Source: https://leetcode.com/problems/count-sorted-vowel-strings/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, return the number of strings of length n that consist only of vowels (a, e, i, o, u) and are lexicographically sorted.
//
// A string s is lexicographically sorted if for all valid i, s[i] is the same as or comes before s[i+1] in the alphabet.
//
// Example:
// Input: n = 1
// Output: 5
// Explanation: The 5 sorted strings that consist of vowels only are ["a","e","i","o","u"].
//
// Constraints:
// 1 <= n <= 50
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
    public int countVowelStrings(int n) {
        // Dynamic Programming approach
        // dp[i][j] represents the number of sorted strings of length i using the first j vowels
        int[][] dp = new int[n + 1][6];

        // Base case: There's one way to form a string of length 0 (the empty string)
        for (int j = 1; j <= 5; j++) {
            dp[0][j] = 1;
        }

        // Fill the DP table
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= 5; j++) {
                // The number of ways to form strings of length i using the first j vowels
                dp[i][j] = dp[i][j - 1] + dp[i - 1][j];
            }
        }

        return dp[n][5];            
    }
}
