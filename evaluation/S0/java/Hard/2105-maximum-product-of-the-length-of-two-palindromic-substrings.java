// Source: https://leetcode.com/problems/maximum-product-of-the-length-of-two-palindromic-substrings/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed string s and are tasked with finding two non-intersecting palindromic substrings of odd length such that the product of their lengths is maximized.
//
// More formally, you want to choose four integers i, j, k, l such that 0 <= i <= j < k <= l < s.length and both the substrings s[i...j] and s[k...l] are palindromes and have odd lengths. s[i...j] denotes a substring from index i to index j inclusive.
//
// Return the maximum possible product of the lengths of the two non-intersecting palindromic substrings.
//
// A palindrome is a string that is the same forward and backward. A substring is a contiguous sequence of characters in a string.
//
// Example:
// Input: s = "ababbb"
// Output: 9
// Explanation: Substrings "aba" and "bbb" are palindromes with odd length. product = 3 * 3 = 9.
//
// Constraints:
// 2 <= s.length <= 105
// 	s consists of lowercase English letters.
//

class Solution {
    public long maxProduct(String s) {
        int n = s.length();
        int[] dp1 = new int[n];
        int[] dp2 = new int[n];

        // Manacher's Algorithm to find all odd-length palindromes
        int center = 0, right = 0;
        for (int i = 0; i < n; i++) {
            int mirror = 2 * center - i;
            if (i < right) {
                dp1[i] = Math.min(right - i, dp1[mirror]);
            }
            int a = i + (1 + dp1[i]);
            int b = i - (1 + dp1[i]);
            while (a < n && b >= 0 && s.charAt(a) == s.charAt(b)) {
                dp1[i]++;
                a++;
                b--;
            }
            if (i + dp1[i] > right) {
                center = i;
                right = i + dp1[i];
            }
        }

        // Calculate maximum palindrome lengths from the left
        int maxLen = 0;
        for (int i = 0; i < n; i++) {
            maxLen = Math.max(maxLen, 2 * dp1[i] + 1);
            dp2[i] = maxLen;
        }

        // Calculate maximum palindrome lengths from the right and find max product
        long result = 0;
        maxLen = 0;
        for (int i = n - 1; i >= 0; i--) {
            maxLen = Math.max(maxLen, 2 * dp1[i] + 1);
            if (i > 0) {
                result = Math.max(result, (long) dp2[i - 1] * maxLen);
            }
        }

        return result;          
    }
}
