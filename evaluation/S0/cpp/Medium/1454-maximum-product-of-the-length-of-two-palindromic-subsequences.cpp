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
public:
    int maxProduct(string s) {
        int n = s.size();
        vector<int> palinMasks;

        // Generate all palindromic subsequences using bitmasking
        for (int mask = 1; mask < (1 << n); ++mask) {
            string subseq;
            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) {
                    subseq.push_back(s[i]);
                }
            }
            if (isPalindrome(subseq)) {
                palinMasks.push_back(mask);
            }
        }

        int maxProduct = 0;
        // Check all pairs of palindromic subsequences
        for (int i = 0; i < palinMasks.size(); ++i) {
            for (int j = i + 1; j < palinMasks.size(); ++j) {
                if ((palinMasks[i] & palinMasks[j]) == 0) { // Disjoint check
                    int len1 = __builtin_popcount(palinMasks[i]);
                    int len2 = __builtin_popcount(palinMasks[j]);
                    maxProduct = max(maxProduct, len1 * len2);
                }
            }
        }

        return maxProduct;          
    }
};
