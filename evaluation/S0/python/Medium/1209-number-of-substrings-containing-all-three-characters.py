# Source: https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/   |   Difficulty: Medium
#
# Problem Description:
# Given a string s consisting only of characters a, b and c.
#
# Return the number of substrings containing at least one occurrence of all these characters a, b and c.
#
# Example:
# Input: s = "abcabc"
# Output: 10
# Explanation: The substrings containing at least one occurrence of the characters a, b and c are "abc", "abca", "abcab", "abcabc", "bca", "bcab", "bcabc", "cab", "cabc" and "abc" (again).
#
# Constraints:
# 3 <= s.length <= 5 x 10^4
# 	s only consists of a, b or c characters.
#

class Solution(object):
    def numberOfSubstrings(self, s):
        """
        :type s: str
        :rtype: int
        """
        count = {'a': 0, 'b': 0, 'c': 0}
        left = 0
        result = 0
        
        for right in range(len(s)):
            count[s[right]] += 1
            
            while all(count[char] > 0 for char in 'abc'):
                count[s[left]] -= 1
                left += 1
            
            result += left
        
        return result