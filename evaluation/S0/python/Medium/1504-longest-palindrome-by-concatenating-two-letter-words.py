# Source: https://leetcode.com/problems/longest-palindrome-by-concatenating-two-letter-words/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array of strings words. Each element of words consists of two lowercase English letters.
#
# Create the longest possible palindrome by selecting some elements from words and concatenating them in any order. Each element can be selected at most once.
#
# Return the length of the longest palindrome that you can create. If it is impossible to create any palindrome, return 0.
#
# A palindrome is a string that reads the same forward and backward.
#
# Example:
# Input: words = ["lc","cl","gg"]
# Output: 6
# Explanation: One longest palindrome is "lc" + "gg" + "cl" = "lcggcl", of length 6.
# Note that "clgglc" is another longest palindrome that can be created.
#
# Constraints:
# 1 <= words.length <= 105
# 	words[i].length == 2
# 	words[i] consists of lowercase English letters.
#

class Solution(object):
    def longestPalindrome(self, words):
        """
        :type words: List[str]
        :rtype: int
        """
        count = {}
        for word in words:
            count[word] = count.get(word, 0) + 1

        length = 0
        has_odd_center = False

        for word, freq in count.items():
            rev_word = word[::-1]
            if word == rev_word:
                length += (freq // 2) * 4
                if freq % 2 == 1:
                    has_odd_center = True
            elif rev_word in count:
                paired_freq = min(freq, count[rev_word])
                length += paired_freq * 2
                count[rev_word] = 0  # Avoid double counting

        if has_odd_center:
            length += 2

        return length