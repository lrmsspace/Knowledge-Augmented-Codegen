// Source: https://leetcode.com/problems/minimum-steps-to-convert-string-with-operations/   |   Difficulty: Hard
//
// Problem Description:
// You are given two strings, word1 and word2, of equal length. You need to transform word1 into word2.
//
// For this, divide word1 into one or more contiguous substrings. For each substring substr you can perform the following operations:
//
//
//  
//  Replace: Replace the character at any one index of substr with another lowercase English letter.
//  
//  
//  Swap: Swap any two characters in substr.
//  
//  
//  Reverse Substring: Reverse substr.
//  
//
//
// Each of these counts as one operation and each character of each substring can be used in each type of operation at most once (i.e. no single index may be involved in more than one replace, one swap, or one reverse).
//
// Return the minimum number of operations required to transform word1 into word2.
//
// Example:
// Input: word1 = "abcdf", word2 = "dacbe"
//
// Output: 4
//
// Explanation:
//
// Divide word1 into "ab", "c", and "df". The operations are:
//
//
//  For the substring "ab",
//
//  
//   Perform operation of type 3 on "ab" -> "ba".
//   Perform operation of type 1 on "ba" -> "da".
//  
//  
//  For the substring "c" do no operations.
//  For the substring "df",
//  
//   Perform operation of type 1 on "df" -> "bf".
//   Perform operation of type 1 on "bf" -> "be".
//
// Constraints:
// 1 <= word1.length == word2.length <= 100
//  word1 and word2 consist only of lowercase English letters.
//

class Solution {
public:
    int minOperations(string word1, string word2) {
        int n = word1.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        int lcs = dp[n][n];
        return n - lcs;         
    }
};
