// Source: https://leetcode.com/problems/maximize-palindrome-length-from-subsequences/   |   Difficulty: Hard
//
// Problem Description:
// You are given two strings, word1 and word2. You want to construct a string in the following manner:
//
//
// 	Choose some non-empty subsequence subsequence1 from word1.
// 	Choose some non-empty subsequence subsequence2 from word2.
// 	Concatenate the subsequences: subsequence1 + subsequence2, to make the string.
//
//
// Return the length of the longest palindrome that can be constructed in the described manner. If no palindromes can be constructed, return 0.
//
// A subsequence of a string s is a string that can be made by deleting some (possibly none) characters from s without changing the order of the remaining characters.
//
// A palindrome is a string that reads the same forward as well as backward.
//
// Example:
// Input: word1 = "cacb", word2 = "cbba"
// Output: 5
// Explanation: Choose "ab" from word1 and "cba" from word2 to make "abcba", which is a palindrome.
//
// Constraints:
// 1 <= word1.length, word2.length <= 1000
// 	word1 and word2 consist of lowercase English letters.
//

int longestPalindrome(char* word1, char* word2) {
    int len1 = strlen(word1);
    int len2 = strlen(word2);
    int dp[len1 + 1][len2 + 1];
    memset(dp, 0, sizeof(dp));
    int maxLen = 0;

    for (int i = 1; i <= len1; ++i) {
        for (int j = 1; j <= len2; ++j) {
            if (word1[i - 1] == word2[len2 - j]) {
                dp[i][j] = dp[i - 1][j - 1] + 2;
                if (dp[i][j] > maxLen) {
                    maxLen = dp[i][j];
                }
            } else {
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }

    return maxLen;      
}
