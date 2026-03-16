// Source: https://leetcode.com/problems/longest-palindrome-after-substring-concatenation-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given two strings, s and t.
//
// You can create a new string by selecting a substring from s (possibly empty) and a substring from t (possibly empty), then concatenating them in order.
//
// Return the length of the longest palindrome that can be formed this way.
//
// Example:
// Input: s = "a", t = "a"
//
// Output: 2
//
// Explanation:
//
// Concatenating "a" from s and "a" from t results in "aa", which is a palindrome of length 2.
//
// Constraints:
// 1 <= s.length, t.length <= 1000
//  s and t consist of lowercase English letters.
//

class Solution {
    public int longestPalindrome(String s, String t) {
        int n = s.length();
        int m = t.length();
        int maxLen = 0;

        // Check all possible substrings of s
        for (int i = 0; i <= n; i++) {
            for (int j = i; j <= n; j++) {
                String subS = s.substring(i, j);
                String revSubS = new StringBuilder(subS).reverse().toString();

                // Check all possible substrings of t
                for (int p = 0; p <= m; p++) {
                    for (int q = p; q <= m; q++) {
                        String subT = t.substring(p, q);
                        String revSubT = new StringBuilder(subT).reverse().toString();

                        // Form the palindrome candidates
                        String candidate1 = subS + revSubT;
                        String candidate2 = subT + revSubS;

                        // Check if they are palindromes and update maxLen
                        if (isPalindrome(candidate1)) {
                            maxLen = Math.max(maxLen, candidate1.length());
                        }
                        if (isPalindrome(candidate2)) {
                            maxLen = Math.max(maxLen, candidate2.length());
                        }
                    }
                }
            }
        }

        return maxLen;          
    }
}
