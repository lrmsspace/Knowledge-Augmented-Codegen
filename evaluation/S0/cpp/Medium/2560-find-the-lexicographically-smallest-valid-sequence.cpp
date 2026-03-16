// Source: https://leetcode.com/problems/find-the-lexicographically-smallest-valid-sequence/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings word1 and word2.
//
// A string x is called almost equal to y if you can change at most one character in x to make it identical to y.
//
// A sequence of indices seq is called valid if:
//
//
// 	The indices are sorted in ascending order.
// 	Concatenating the characters at these indices in word1 in the same order results in a string that is almost equal to word2.
//
//
// Return an array of size word2.length representing the lexicographically smallest valid sequence of indices. If no such sequence of indices exists, return an empty array.
//
// Note that the answer must represent the lexicographically smallest array, not the corresponding string formed by those indices.
//
// Example:
// Input: word1 = "vbcca", word2 = "abc"
//
// Output: [0,1,2]
//
// Explanation:
//
// The lexicographically smallest valid sequence of indices is [0, 1, 2]:
//
//
// 	Change word1[0] to 'a'.
// 	word1[1] is already 'b'.
// 	word1[2] is already 'c'.
//
// Constraints:
// 1 <= word2.length < word1.length <= 3 * 105
// 	word1 and word2 consist only of lowercase English letters.
//

class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        vector<vector<int>> dp(n + 1, vector<int>(m + 1, INT_MAX));
        vector<vector<int>> choice(n + 1, vector<int>(m + 1, -1));

        dp[0][0] = 0;

        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= min(i, m); ++j) {
                // Skip word1[i-1]
                if (dp[i - 1][j] < dp[i][j]) {
                    dp[i][j] = dp[i - 1][j];
                    choice[i][j] = 0;
                }

                if (j > 0) {
                    // Match without change
                    if (word1[i - 1] == word2[j - 1] && dp[i - 1][j - 1] < dp[i][j]) {
                        dp[i][j] = dp[i - 1][j - 1];
                        choice[i][j] = 1;
                    }

                    // Match with change
                    if (dp[i - 1][j - 1] + 1 < dp[i][j]) {
                        dp[i][j] = dp[i - 1][j - 1] + 1;
                        choice[i][j] = 2;
                    }
                }
            }
        }

        if (dp[n][m] > 1) {
            return {};
        }

        vector<int> result;
        int i = n, j = m;
        while (i > 0 && j > 0) {
            if (choice[i][j] == 0) {
                --i;
            } else if (choice[i][j] == 1 || choice[i][j] == 2) {
                result.push_back(i - 1);
                --i;
                --j;
            }
        }

        reverse(result.begin(), result.end());
        return result;          
    }
};
