# Source: https://leetcode.com/problems/smallest-k-length-subsequence-with-occurrences-of-a-letter/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string s, an integer k, a letter letter, and an integer repetition.
#
# Return the lexicographically smallest subsequence of s of length k that has the letter letter appear at least repetition times. The test cases are generated so that the letter appears in s at least repetition times.
#
# A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.
#
# A string a is lexicographically smaller than a string b if in the first position where a and b differ, string a has a letter that appears earlier in the alphabet than the corresponding letter in b.
#
# Example:
# Input: s = "leet", k = 3, letter = "e", repetition = 1
# Output: "eet"
# Explanation: There are four subsequences of length 3 that have the letter 'e' appear at least 1 time:
# - "lee" (from "leet")
# - "let" (from "leet")
# - "let" (from "leet")
# - "eet" (from "leet")
# The lexicographically smallest subsequence among them is "eet".
#
# Constraints:
# 1 <= repetition <= k <= s.length <= 5 * 104
# 	s consists of lowercase English letters.
# 	letter is a lowercase English letter, and appears in s at least repetition times.
#

class Solution(object):
    def smallestSubsequence(self, s, k, letter, repetition):
        """
        :type s: str
        :type k: int
        :type letter: str
        :type repetition: int
        :rtype: str
        """
        n = len(s)
        count_letter = s.count(letter)
        stack = []
        to_pick = k
        to_have = repetition

        for i, ch in enumerate(s):
            while stack and stack[-1] > ch and n - i > to_pick and (stack[-1] != letter or count_letter > to_have):
                popped = stack.pop()
                to_pick += 1
                if popped == letter:
                    to_have += 1

            if to_pick > 0:
                if ch == letter:
                    stack.append(ch)
                    to_pick -= 1
                    to_have -= 1
                else:
                    if to_pick > to_have:
                        stack.append(ch)
                        to_pick -= 1

            if ch == letter:
                count_letter -= 1

        return ''.join(stack)