# Source: https://leetcode.com/problems/longest-chunked-palindrome-decomposition/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string text. You should split it to k substrings (subtext1, subtext2, ..., subtextk) such that:
#
#
# 	subtexti is a non-empty string.
# 	The concatenation of all the substrings is equal to text (i.e., subtext1 + subtext2 + ... + subtextk == text).
# 	subtexti == subtextk - i + 1 for all valid values of i (i.e., 1 <= i <= k).
#
#
# Return the largest possible value of k.
#
# Example:
# Input: text = "ghiabcdefhelloadamhelloabcdefghi"
# Output: 7
# Explanation: We can split the string on "(ghi)(abcdef)(hello)(adam)(hello)(abcdef)(ghi)".
#
# Constraints:
# 1 <= text.length <= 1000
# 	text consists only of lowercase English characters.
#

class Solution(object):
    def longestDecomposition(self, text):
        """
        :type text: str
        :rtype: int
        """
        n = len(text)
        left, right = 0, n - 1
        count = 0
        prefix, suffix = "", ""

        while left <= right:
            prefix += text[left]
            suffix = text[right] + suffix

            if prefix == suffix:
                count += 2 if left != right else 1
                prefix, suffix = "", ""

            left += 1
            right -= 1

        return count