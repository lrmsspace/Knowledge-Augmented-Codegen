// Source: https://leetcode.com/problems/maximum-product-of-the-length-of-two-palindromic-subsequences/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, find two disjoint palindromic subsequences of s such that the product of their lengths is maximized. The two subsequences are disjoint if they do not both pick a character at the same index.
//
// Return the maximum possible product of the lengths of the two palindromic subsequences.
//
// A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters. A string is palindromic if it reads the same forward and backward.
//
// Example:
// Input: s = "leetcodecom"
// Output: 9
// Explanation: An optimal solution is to choose "ete" for the 1st subsequence and "cdc" for the 2nd subsequence.
// The product of their lengths is: 3 * 3 = 9.
//
// Constraints:
// 2 <= s.length <= 12
// 	s consists of lowercase English letters only.
//

class Solution {
    public int maxProduct(String s) {
        int n = s.length();
        int maxProduct = 0;

        // There are 2^n possible subsequences
        for (int mask1 = 1; mask1 < (1 << n); mask1++) {
            String subseq1 = buildSubsequence(s, mask1);
            if (isPalindrome(subseq1)) {
                for (int mask2 = 1; mask2 < (1 << n); mask2++) {
                    // Ensure the two subsequences are disjoint
                    if ((mask1 & mask2) == 0) {
                        String subseq2 = buildSubsequence(s, mask2);
                        if (isPalindrome(subseq2)) {
                            int product = subseq1.length() * subseq2.length();
                            maxProduct = Math.max(maxProduct, product);
                        }
                    }
                }
            }
        }

        return maxProduct;          
    }
}
