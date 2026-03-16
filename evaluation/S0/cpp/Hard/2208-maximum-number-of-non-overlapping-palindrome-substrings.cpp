// Source: https://leetcode.com/problems/maximum-number-of-non-overlapping-palindrome-substrings/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s and a positive integer k.
//
// Select a set of non-overlapping substrings from the string s that satisfy the following conditions:
//
//
// 	The length of each substring is at least k.
// 	Each substring is a palindrome.
//
//
// Return the maximum number of substrings in an optimal selection.
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: s = "abaccdbbd", k = 3
// Output: 2
// Explanation: We can select the substrings underlined in s = "abaccdbbd". Both "aba" and "dbbd" are palindromes and have a length of at least k = 3.
// It can be shown that we cannot find a selection with more than two valid substrings.
//
// Constraints:
// 1 <= k <= s.length <= 2000
// 	s consists of lowercase English letters.
//

class Solution {
public:
    int maxPalindromes(string s, int k) {
        int n = s.size();
        vector<bool> isPal(n, false);
        
        // Precompute palindromic substrings of length >= k
        for (int center = 0; center < n; center++) {
            // Odd length palindromes
            int left = center, right = center;
            while (left >= 0 && right < n && s[left] == s[right]) {
                if (right - left + 1 >= k) {
                    isPal[right] = true;
                }
                left--;
                right++;
            }
            
            // Even length palindromes
            left = center;
            right = center + 1;
            while (left >= 0 && right < n && s[left] == s[right]) {
                if (right - left + 1 >= k) {
                    isPal[right] = true;
                }
                left--;
                right++;
            }
        }
        
        // DP to find maximum number of non-overlapping palindromic substrings
        vector<int> dp(n + 1, 0);
        for (int i = 0; i < n; i++) {
            dp[i + 1] = dp[i];  // Not taking any palindrome ending at i
            if (isPal[i]) {
                dp[i + 1] = max(dp[i + 1], dp[i + 1 - k] + 1);
            }
        }
        
        return dp[n];           
    }
};
