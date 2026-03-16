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

/**
 * @param {string} s
 * @return {number}
 */
var minCut = function(s) {
    const n = s.length;
    const dp = new Array(n).fill(0);
    const isPalindrome = Array.from({ length: n }, () => new Array(n).fill(false));
        
    for (let i = 0; i < n; i++) {
        dp[i] = i; // Maximum cuts needed is i (cut before each character)
        for (let j = 0; j <= i; j++) {
            if (s[j] === s[i] && (i - j < 2 || isPalindrome[j + 1][i - 1])) {
                isPalindrome[j][i] = true;
                dp[i] = j === 0 ? 0 : Math.min(dp[i], dp[j - 1] + 1);
            }
        }
    }
    return dp[n - 1];
    
};
