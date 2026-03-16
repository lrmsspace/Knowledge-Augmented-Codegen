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

int minDistance(char* word1, char* word2) {
    int len1 = strlen(word1);
    int len2 = strlen(word2);
    
    // Create a 2D array to store lengths of longest common subsequence
    int dp[len1 + 1][len2 + 1];
    
    // Initialize the dp array
    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            dp[i][j] = 0;
        }
    }
    
    // Fill the dp array
    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            if (word1[i - 1] == word2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }
    
    // The length of the longest common subsequence
    int lcs_length = dp[len1][len2];
    
    // Minimum deletions required
    return (len1 - lcs_length) + (len2 - lcs_length);       
}
