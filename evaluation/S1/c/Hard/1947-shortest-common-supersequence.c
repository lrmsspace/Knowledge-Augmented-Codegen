// Source: https://leetcode.com/problems/shortest-common-supersequence/   |   Difficulty: Hard
//
// Problem Description:
// Given two strings str1 and str2, return the shortest string that has both str1 and str2 as subsequences. If there are multiple valid strings, return any of them.
//
// A string s is a subsequence of string t if deleting some number of characters from t (possibly 0) results in the string s.
//
// Example:
// Input: str1 = "abac", str2 = "cab"
// Output: "cabac"
// Explanation: 
// str1 = "abac" is a subsequence of "cabac" because we can delete the first "c".
// str2 = "cab" is a subsequence of "cabac" because we can delete the last "ac".
// The answer provided is the shortest such string that satisfies these properties.
//
// Constraints:
// 1 <= str1.length, str2.length <= 1000
// 	str1 and str2 consist of lowercase English letters.
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

char* shortestCommonSupersequence(char* str1, char* str2) {
    int len1 = 0, len2 = 0;
    while (str1[len1]) len1++;
    while (str2[len2]) len2++;

    /* Compute LCS DP table */
    int dp[len1 + 1][len2 + 1];
    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }

    /* Reconstruct SCS from LCS DP table */
    int index = len1 + len2 - dp[len1][len2];
    char* scs = (char*)malloc((index + 1) * sizeof(char));
    scs[index] = '\0';

    int i = len1, j = len2;
    while (i > 0 && j > 0) {
        if (str1[i - 1] == str2[j - 1]) {
            scs[--index] = str1[i - 1];
            i--;
            j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            scs[--index] = str1[i - 1];
            i--;
        } else {
            scs[--index] = str2[j - 1];
            j--;
        }
    }

    while (i > 0) {
        scs[--index] = str1[i - 1];
        i--;
    }
    while (j > 0) {
        scs[--index] = str2[j - 1];
        j--;
    }

    return scs;     
}
