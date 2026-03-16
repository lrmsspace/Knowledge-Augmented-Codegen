# Source: https://leetcode.com/problems/length-of-the-longest-valid-substring/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string word and an array of strings forbidden.
#
# A string is called valid if none of its substrings are present in forbidden.
#
# Return the length of the longest valid substring of the string word.
#
# A substring is a contiguous sequence of characters in a string, possibly empty.
#
# Example:
# Input: word = "cbaaaabc", forbidden = ["aaa","cb"]
# Output: 4
# Explanation: There are 11 valid substrings in word: "c", "b", "a", "ba", "aa", "bc", "baa", "aab", "ab", "abc" and "aabc". The length of the longest valid substring is 4. 
# It can be shown that all other substrings contain either "aaa" or "cb" as a substring.
#
# Constraints:
# 1 <= word.length <= 105
# 	word consists only of lowercase English letters.
# 	1 <= forbidden.length <= 105
# 	1 <= forbidden[i].length <= 10
# 	forbidden[i] consists only of lowercase English letters.
#

class Solution(object):
    def longestValidSubstring(self, word, forbidden):
        """
        :type word: str
        :type forbidden: List[str]
        :rtype: int
        """
        forbidden_set = set(forbidden)
        max_length = 0
        n = len(word)

        for i in range(n):
            for j in range(i + 1, n + 1):
                substring = word[i:j]
                if substring in forbidden_set:
                    break
                max_length = max(max_length, j - i)

        return max_length