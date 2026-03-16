// Source: https://leetcode.com/problems/longest-palindromic-substring/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, return the longest palindromic substring in s.
//
// Example:
// Input: s = "babad"
// Output: "bab"
// Explanation: "aba" is also a valid answer.
//
// Constraints:
// 1 <= s.length <= 1000
// 	s consist of only digits and English letters.
//

char* longestPalindrome(char* s) {
    int start = 0, end = 0;
    int len = strlen(s);

    for (int i = 0; i < len; i++) {
        int len1 = expandAroundCenter(s, i, i);     // Odd length palindromes
        int len2 = expandAroundCenter(s, i, i + 1); // Even length palindromes
        int maxLen = (len1 > len2) ? len1 : len2;

        if (maxLen > end - start) {
            start = i - (maxLen - 1) / 2;
            end = i + maxLen / 2;
        }
    }

    int palindromeLen = end - start + 1;
    char* result = (char*)malloc((palindromeLen + 1) * sizeof(char));
    strncpy(result, s + start, palindromeLen);
    result[palindromeLen] = '\0';

    return result;      
}
