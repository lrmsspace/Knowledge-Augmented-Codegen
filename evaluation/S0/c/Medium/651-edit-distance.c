// Source: https://leetcode.com/problems/edit-distance/   |   Difficulty: Medium
//
// Problem Description:
// Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.
//
// You have the following three operations permitted on a word:
//
//
// 	Insert a character
// 	Delete a character
// 	Replace a character
//
// Example:
// Input: word1 = "horse", word2 = "ros"
// Output: 3
// Explanation: 
// horse -> rorse (replace 'h' with 'r')
// rorse -> rose (remove 'r')
// rose -> ros (remove 'e')
//
// Constraints:
// 0 <= word1.length, word2.length <= 500
// 	word1 and word2 consist of lowercase English letters.
//

int minDistance(char* word1, char* word2) {
    int len1 = strlen(word1);
    int len2 = strlen(word2);
    
    int dp[len1 + 1][len2 + 1];
    
    for (int i = 0; i <= len1; i++) {
        dp[i][0] = i;
    }
    
    for (int j = 0; j <= len2; j++) {
        dp[0][j] = j;
    }
    
    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            if (word1[i - 1] == word2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                int insertOp = dp[i][j - 1] + 1;
                int deleteOp = dp[i - 1][j] + 1;
                int replaceOp = dp[i - 1][j - 1] + 1;
                
                dp[i][j] = insertOp < deleteOp ? (insertOp < replaceOp ? insertOp : replaceOp) : (deleteOp < replaceOp ? deleteOp : replaceOp);
            }
        }
    }
    
    return dp[len1][len2];      
}
