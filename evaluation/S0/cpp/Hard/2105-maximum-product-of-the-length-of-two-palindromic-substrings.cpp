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
public:
    long long maxProduct(string s) {
        int n = s.size();
        vector<int> dp1(n, 0), dp2(n, 0);
        
        // Manacher's Algorithm to find longest odd-length palindromic substring centered at each index
        for (int center = 0, right = -1; center < n; center++) {
            int radius = (center < right) ? min(dp1[right - center], right - center) : 0;
            while (center - radius - 1 >= 0 && center + radius + 1 < n && s[center - radius - 1] == s[center + radius + 1]) {
                radius++;
            }
            dp1[center] = radius;
            if (center + radius > right) {
                right = center + radius;
            }
        }
        
        // Calculate maximum palindrome lengths from the left
        vector<int> maxLeft(n, 0);
        for (int i = 0; i < n; i++) {
            int len = dp1[i] * 2 + 1;
            int start = i - dp1[i];
            maxLeft[i] = len;
            if (i > 0) {
                maxLeft[i] = max(maxLeft[i], maxLeft[i - 1]);
            }
        }
        
        // Calculate maximum palindrome lengths from the right
        vector<int> maxRight(n, 0);
        for (int i = n - 1; i >= 0; i--) {
            int len = dp1[i] * 2 + 1;
            int end = i + dp1[i];
            maxRight[i] = len;
            if (i < n - 1) {
                maxRight[i] = max(maxRight[i], maxRight[i + 1]);
            }
        }
        
        // Calculate maximum product
        long long maxProduct = 0;
        for (int i = 0; i < n - 1; i++) {
            maxProduct = max(maxProduct, (long long)maxLeft[i] * maxRight[i + 1]);
        }
        
        return maxProduct;          
    }
};
