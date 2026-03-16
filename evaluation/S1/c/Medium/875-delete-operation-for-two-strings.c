// Source: https://leetcode.com/problems/delete-operation-for-two-strings/   |   Difficulty: Medium
//
// Problem Description:
// Given two strings word1 and word2, return the minimum number of steps required to make word1 and word2 the same.
//
// In one step, you can delete exactly one character in either string.
//
// Example:
// Input: word1 = "sea", word2 = "eat"
// Output: 2
// Explanation: You need one step to make "sea" to "ea" and another step to make "eat" to "ea".
//
// Constraints:
// 1 <= word1.length, word2.length <= 500
// 	word1 and word2 consist of only lowercase English letters.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minDistance(char* word1, char* word2) {
    int len1 = 0, len2 = 0;
    while (word1[len1]) len1++;
    while (word2[len2]) len2++;

    int dp[len1 + 1][len2 + 1];

    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            if (i == 0) {
                dp[i][j] = j; // If word1 is empty, delete all characters from word2
            } else if (j == 0) {
                dp[i][j] = i; // If word2 is empty, delete all characters from word1
            } else if (word1[i - 1] == word2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1]; // Characters match, no deletion needed
            } else {
                dp[i][j] = 1 + (dp[i - 1][j] < dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1]);
                // Delete from either word1 or word2
            }
        }
    }

    return dp[len1][len2];      
}
