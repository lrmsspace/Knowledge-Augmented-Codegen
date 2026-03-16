// Source: https://leetcode.com/problems/distinct-subsequences-ii/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s, return the number of distinct non-empty subsequences of s. Since the answer may be very large, return it modulo 109 + 7.
// A subsequence of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not.
//
// Example:
// Input: s = "abc"
// Output: 7
// Explanation: The 7 distinct subsequences are "a", "b", "c", "ab", "ac", "bc", and "abc".
//
// Constraints:
// 1 <= s.length <= 2000
// 	s consists of lowercase English letters.
//

class Solution {
public:
    int distinctSubseqII(string s) {
        const int MOD = 1e9 + 7;
        int n = s.size();
        vector<long long> dp(n + 1, 0);
        dp[0] = 1;  // empty subsequence
        
        vector<int> last(26, -1);  // last occurrence of each character
        
        for (int i = 1; i <= n; i++) {
            char c = s[i - 1];
            dp[i] = (dp[i - 1] * 2) % MOD;
            
            if (last[c - 'a'] != -1) {
                int j = last[c - 'a'];
                dp[i] = (dp[i] - dp[j - 1] + MOD) % MOD;
            }
            
            last[c - 'a'] = i;
        }
        
        return (dp[n] - 1 + MOD) % MOD;  // exclude empty subsequence           
    }
};
