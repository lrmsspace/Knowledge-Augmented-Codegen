# Source: https://leetcode.com/problems/take-k-of-each-character-from-left-and-right/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string s consisting of the characters 'a', 'b', and 'c' and a non-negative integer k. Each minute, you may take either the leftmost character of s, or the rightmost character of s.
#
# Return the minimum number of minutes needed for you to take at least k of each character, or return -1 if it is not possible to take k of each character.
#
# Example:
# Input: s = "aabaaaacaabc", k = 2
# Output: 8
# Explanation: 
# Take three characters from the left of s. You now have two 'a' characters, and one 'b' character.
# Take five characters from the right of s. You now have four 'a' characters, two 'b' characters, and two 'c' characters.
# A total of 3 + 5 = 8 minutes is needed.
# It can be proven that 8 is the minimum number of minutes needed.
#
# Constraints:
# 1 <= s.length <= 105
# 	s consists of only the letters 'a', 'b', and 'c'.
# 	0 <= k <= s.length
#

class Solution(object):
    def takeCharacters(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: int
        """
        count = {'a': 0, 'b': 0, 'c': 0}
        for char in s:
            count[char] += 1

        if count['a'] < k or count['b'] < k or count['c'] < k:
            return -1

        n = len(s)
        left = 0
        max_len = 0
        current_count = {'a': 0, 'b': 0, 'c': 0}

        for right in range(n):
            current_count[s[right]] += 1

            while (current_count['a'] > count['a'] - k or
                   current_count['b'] > count['b'] - k or
                   current_count['c'] > count['c'] - k):
                current_count[s[left]] -= 1
                left += 1

            max_len = max(max_len, right - left + 1)

        return n - max_len