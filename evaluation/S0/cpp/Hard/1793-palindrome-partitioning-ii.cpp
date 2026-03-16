// Source: https://leetcode.com/problems/palindrome-partitioning-ii/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s, partition s such that every substring of the partition is a palindrome.
//
// Return the minimum cuts needed for a palindrome partitioning of s.
//
// Example:
// Input: s = "aab"
// Output: 1
// Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.
//
// Constraints:
// 1 <= s.length <= 2000
// 	s consists of lowercase English letters only.
//

class Solution {
public:
    int minCut(string s) {
        int n = s.size();
        vector<vector<bool>> isPalindrome(n, vector<bool>(n, false));
        
        // Precompute palindrome substrings
        for (int length = 1; length <= n; length++) {
            for (int start = 0; start <= n - length; start++) {
                int end = start + length - 1;
                if (s[start] == s[end]) {
                    if (length <= 2) {
                        isPalindrome[start][end] = true;
                    } else {
                        isPalindrome[start][end] = isPalindrome[start + 1][end - 1];
                    }
                }
            }
        }
        
        // DP array to store minimum cuts
        vector<int> dp(n, INT_MAX);
        
        for (int i = 0; i < n; i++) {
            if (isPalindrome[0][i]) {
                dp[i] = 0;  // No cut needed if s[0..i] is a palindrome
            } else {
                for (int j = 0; j < i; j++) {
                    if (isPalindrome[j + 1][i]) {
                        dp[i] = min(dp[i], dp[j] + 1);
                    }
                }
            }
        }
        
        return dp[n - 1];           
    }
};
