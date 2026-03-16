// Source: https://leetcode.com/problems/maximum-deletions-on-a-string/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s consisting of only lowercase English letters. In one operation, you can:
//
//
// 	Delete the entire string s, or
// 	Delete the first i letters of s if the first i letters of s are equal to the following i letters in s, for any i in the range 1 <= i <= s.length / 2.
//
//
// For example, if s = "ababc", then in one operation, you could delete the first two letters of s to get "abc", since the first two letters of s and the following two letters of s are both equal to "ab".
//
// Return the maximum number of operations needed to delete all of s.
//
// Example:
// Input: s = "abcabcdabc"
// Output: 2
// Explanation:
// - Delete the first 3 letters ("abc") since the next 3 letters are equal. Now, s = "abcdabc".
// - Delete all the letters.
// We used 2 operations so return 2. It can be proven that 2 is the maximum number of operations needed.
// Note that in the second operation we cannot delete "abc" again because the next occurrence of "abc" does not happen in the next 3 letters.
//
// Constraints:
// 1 <= s.length <= 4000
// 	s consists only of lowercase English letters.
//

class Solution {
public:
    int deleteString(string s) {
        int n = s.size();
        vector<int> dp(n + 1, 1);  // dp[i]: max operations to delete s[i..end]
        vector<vector<int>> lcp(n + 1, vector<int>(n + 1, 0));  // lcp[i][j]: longest common prefix of s[i..] and s[j..]

        // Compute longest common prefixes
        for (int i = n - 1; i >= 0; --i) {
            for (int j = n - 1; j > i; --j) {
                if (s[i] == s[j]) {
                    lcp[i][j] = lcp[i + 1][j + 1] + 1;
                }
            }
        }

        // Dynamic programming to find maximum deletions
        for (int i = n - 1; i >= 0; --i) {
            for (int length = 1; i + 2 * length <= n; ++length) {
                if (lcp[i][i + length] >= length) {
                    dp[i] = max(dp[i], 1 + dp[i + length]);
                }
            }
        }

        return dp[0];           
    }
};
