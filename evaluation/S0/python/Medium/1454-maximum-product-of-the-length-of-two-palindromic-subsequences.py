# Source: https://leetcode.com/problems/maximum-product-of-the-length-of-two-palindromic-subsequences/   |   Difficulty: Medium
#
# Problem Description:
# Given a string s, find two disjoint palindromic subsequences of s such that the product of their lengths is maximized. The two subsequences are disjoint if they do not both pick a character at the same index.
#
# Return the maximum possible product of the lengths of the two palindromic subsequences.
#
# A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters. A string is palindromic if it reads the same forward and backward.
#
# Example:
# Input: s = "leetcodecom"
# Output: 9
# Explanation: An optimal solution is to choose "ete" for the 1st subsequence and "cdc" for the 2nd subsequence.
# The product of their lengths is: 3 * 3 = 9.
#
# Constraints:
# 2 <= s.length <= 12
# 	s consists of lowercase English letters only.
#

class Solution(object):
    def maxProduct(self, s):
        """
        :type s: str
        :rtype: int
        """
        n = len(s)
        palindromes = {}

        # Generate all subsequences and check for palindromes
        for mask in range(1, 1 << n):
            subseq = []
            for i in range(n):
                if mask & (1 << i):
                    subseq.append(s[i])
            subseq_str = ''.join(subseq)
            if subseq_str == subseq_str[::-1]:  # Check if palindrome
                palindromes[mask] = len(subseq_str)

        max_product = 0
        masks = list(palindromes.keys())
        for i in range(len(masks)):
            for j in range(i + 1, len(masks)):
                if masks[i] & masks[j] == 0:  # Disjoint subsequences
                    product = palindromes[masks[i]] * palindromes[masks[j]]
                    max_product = max(max_product, product)

        return max_product