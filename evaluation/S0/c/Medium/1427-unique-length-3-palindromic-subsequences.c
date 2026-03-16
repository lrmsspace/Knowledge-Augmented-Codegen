// Source: https://leetcode.com/problems/unique-length-3-palindromic-subsequences/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, return the number of unique palindromes of length three that are a subsequence of s.
//
// Note that even if there are multiple ways to obtain the same subsequence, it is still only counted once.
//
// A palindrome is a string that reads the same forwards and backwards.
//
// A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.
//
//
// 	For example, "ace" is a subsequence of "abcde".
//
// Example:
// Input: s = "aabca"
// Output: 3
// Explanation: The 3 palindromic subsequences of length 3 are:
// - "aba" (subsequence of "aabca")
// - "aaa" (subsequence of "aabca")
// - "aca" (subsequence of "aabca")
//
// Constraints:
// 3 <= s.length <= 105
// 	s consists of only lowercase English letters.
//

int countPalindromicSubsequence(char* s) {
    int first[26], last[26];
    for (int i = 0; i < 26; i++) {
        first[i] = -1;
        last[i] = -1;
    }

    for (int i = 0; s[i] != '\0'; i++) {
        int index = s[i] - 'a';
        if (first[index] == -1) {
            first[index] = i;
        }
        last[index] = i;
    }

    int result = 0;
    for (int i = 0; i < 26; i++) {
        if (first[i] != -1 && last[i] - first[i] > 1) {
            int seen[26] = {0};
            for (int j = first[i] + 1; j < last[i]; j++) {
                int index = s[j] - 'a';
                if (seen[index] == 0) {
                    seen[index] = 1;
                    result++;
                }
            }
        }
    }

    return result;      
}
