# Source: https://leetcode.com/problems/existence-of-a-substring-in-a-string-and-its-reverse/   |   Difficulty: Easy
#
# Problem Description:
# Given a string s, find any substring of length 2 which is also present in the reverse of s.
#
# Return true if such a substring exists, and false otherwise.
#
# Example:
# Input: s = "leetcode"
#
# Output: true
#
# Explanation: Substring "ee" is of length 2 which is also present in reverse(s) == "edocteel".
#
# Constraints:
# 1 <= s.length <= 100
# 	s consists only of lowercase English letters.
#

class Solution(object):
    def isSubstringPresent(self, s):
        """
        :type s: str
        :rtype: bool
        """
        n = len(s)
        reversed_s = s[::-1]
        
        for i in range(n - 1):
            substring = s[i:i+2]
            if substring in reversed_s:
                return True
        
        return False