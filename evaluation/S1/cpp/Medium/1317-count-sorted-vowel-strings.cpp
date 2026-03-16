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
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int countVowelStrings(int n) {
        // dp[i][j]: number of strings of length i ending with j-th vowel
        vector<vector<int>> dp(n + 1, vector<int>(5, 0));

        // Base case: for length 1, there's one string for each vowel
        for (int j = 0; j < 5; ++j) {
            dp[1][j] = 1;
        }

        // Fill the DP table
        for (int i = 2; i <= n; ++i) {
            for (int j = 0; j < 5; ++j) {
                dp[i][j] = 0;
                for (int k = j; k < 5; ++k) {
                    dp[i][j] += dp[i - 1][k];
                }
            }
        }

        // Sum up all strings of length n
        int result = 0;
        for (int j = 0; j < 5; ++j) {
            result += dp[n][j];
        }

        return result;
    }
};
