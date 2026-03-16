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
    public int minCut(String s) {
        int n = s.length();
        boolean[][] isPalindrome = new boolean[n][n];
        int[] dp = new int[n];

        for (int end = 0; end < n; end++) {
            dp[end] = end; // Maximum cuts
            for (int start = 0; start <= end; start++) {
                if (s.charAt(start) == s.charAt(end) && (end - start <= 2 || isPalindrome[start + 1][end - 1])) {
                    isPalindrome[start][end] = true;
                    dp[end] = start == 0 ? 0 : Math.min(dp[end], dp[start - 1] + 1);
                }
            }
        }

        return dp[n - 1];           
    }
}
