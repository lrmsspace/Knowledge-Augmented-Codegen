# Source: https://leetcode.com/problems/maximum-product-of-the-length-of-two-palindromic-substrings/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed string s and are tasked with finding two non-intersecting palindromic substrings of odd length such that the product of their lengths is maximized.
#
# More formally, you want to choose four integers i, j, k, l such that 0 <= i <= j < k <= l < s.length and both the substrings s[i...j] and s[k...l] are palindromes and have odd lengths. s[i...j] denotes a substring from index i to index j inclusive.
#
# Return the maximum possible product of the lengths of the two non-intersecting palindromic substrings.
#
# A palindrome is a string that is the same forward and backward. A substring is a contiguous sequence of characters in a string.
#
# Example:
# Input: s = "ababbb"
# Output: 9
# Explanation: Substrings "aba" and "bbb" are palindromes with odd length. product = 3 * 3 = 9.
#
# Constraints:
# 2 <= s.length <= 105
# 	s consists of lowercase English letters.
#

class Solution(object):
    def maxProduct(self, s):
        """
        :type s: str
        :rtype: int
        """
        n = len(s)
        d1 = [0] * n  # d1[i] = radius of odd-length palindrome centered at i
        l, r = 0, -1
        for i in range(n):
            k = 1 if i > r else min(d1[l + r - i], r - i + 1)
            while 0 <= i - k and i + k < n and s[i - k] == s[i + k]:
                k += 1
            d1[i] = k
            k -= 1
            if i + k > r:
                l, r = i - k, i + k

        max_left = [0] * n
        max_right = [0] * n

        for i in range(n):
            length = 2 * d1[i] - 1
            start = i - (d1[i] - 1)
            end = i + (d1[i] - 1)

            max_left[end] = max(max_left[end], length)
            max_right[start] = max(max_right[start], length)

        for i in range(1, n):
            max_left[i] = max(max_left[i], max_left[i - 1])

        for i in range(n - 2, -1, -1):
            max_right[i] = max(max_right[i], max_right[i + 1])

        max_product = 0
        for i in range(n - 1):
            max_product = max(max_product, max_left[i] * max_right[i + 1])

        return max_product