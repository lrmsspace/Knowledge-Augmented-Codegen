// Source: https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/   |   Difficulty: Medium
//
// Problem Description:
// Given two strings s1 and s2, return the lowest ASCII sum of deleted characters to make two strings equal.
//
// Example:
// Input: s1 = "sea", s2 = "eat"
// Output: 231
// Explanation: Deleting "s" from "sea" adds the ASCII value of "s" (115) to the sum.
// Deleting "t" from "eat" adds 116 to the sum.
// At the end, both strings are equal, and 115 + 116 = 231 is the minimum sum possible to achieve this.
//
// Constraints:
// 1 <= s1.length, s2.length <= 1000
// 	s1 and s2 consist of lowercase English letters.
//

int minimumDeleteSum(char* s1, char* s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int dp[len1 + 1][len2 + 1];

    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            if (i == 0 && j == 0) {
                dp[i][j] = 0;
            } else if (i == 0) {
                dp[i][j] = dp[i][j - 1] + s2[j - 1];
            } else if (j == 0) {
                dp[i][j] = dp[i - 1][j] + s1[i - 1];
            } else if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = fmin(dp[i - 1][j] + s1[i - 1], dp[i][j - 1] + s2[j - 1]);
            }
        }
    }

    return dp[len1][len2];      
}
