# Source: https://leetcode.com/problems/substring-with-largest-variance/   |   Difficulty: Hard
#
# Problem Description:
# The variance of a string is defined as the largest difference between the number of occurrences of any 2 characters present in the string. Note the two characters may or may not be the same.
#
# Given a string s consisting of lowercase English letters only, return the largest variance possible among all substrings of s.
#
# A substring is a contiguous sequence of characters within a string.
#
# Example:
# Input: s = "aababbb"
# Output: 3
# Explanation:
# All possible variances along with their respective substrings are listed below:
# - Variance 0 for substrings "a", "aa", "ab", "abab", "aababb", "ba", "b", "bb", and "bbb".
# - Variance 1 for substrings "aab", "aba", "abb", "aabab", "ababb", "aababbb", and "bab".
# - Variance 2 for substrings "aaba", "ababbb", "abbb", and "babb".
# - Variance 3 for substring "babbb".
# Since the largest possible variance is 3, we return it.
#
# Constraints:
# 1 <= s.length <= 104
#  s consists of lowercase English letters.
#

class Solution(object):
    def largestVariance(self, s):
        """
        :type s: str
        :rtype: int
        """
        unique_chars = set(s)
        max_variance = 0

        for a in unique_chars:
            for b in unique_chars:
                if a == b:
                    continue

                count_a = 0
                count_b = 0
                has_b = False
                local_max = float('-inf')

                for char in s:
                    if char == a:
                        count_a += 1
                    elif char == b:
                        count_b += 1
                        has_b = True

                    if has_b:
                        local_max = max(local_max, count_a - count_b)

                    if count_b > count_a:
                        count_a = 0
                        count_b = 0
                        has_b = False

                max_variance = max(max_variance, local_max)

        return max_variance