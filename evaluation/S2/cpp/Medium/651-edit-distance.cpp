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
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        for (int i = 0; i <= m; ++i) {
            dp[i][0] = i; // Deleting all characters from word1
        }
        for (int j = 0; j <= n; ++j) {
            dp[0][j] = j; // Inserting all characters from word2
        }

        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1]; // No operation needed
                } else {
                    dp[i][j] = min({dp[i - 1][j] + 1,    // Deletion
                                    dp[i][j - 1] + 1,    // Insertion
                                    dp[i - 1][j - 1] + 1}); // Replacement
                }
            }
        }

        return dp[m][n];            
    }
};
