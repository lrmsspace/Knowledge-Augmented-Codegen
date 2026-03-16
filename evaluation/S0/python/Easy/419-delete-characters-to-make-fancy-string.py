# Source: https://leetcode.com/problems/delete-characters-to-make-fancy-string/   |   Difficulty: Easy
#
# Problem Description:
# A fancy string is a string where no three consecutive characters are equal.
#
# Given a string s, delete the minimum possible number of characters from s to make it fancy.
#
# Return the final string after the deletion. It can be shown that the answer will always be unique.
#
# Example:
# Input: s = "leeetcode"
# Output: "leetcode"
# Explanation:
# Remove an 'e' from the first group of 'e's to create "leetcode".
# No three consecutive characters are equal, so return "leetcode".
#
# Constraints:
# 1 <= s.length <= 105
# 	s consists only of lowercase English letters.
#

class Solution(object):
    def makeFancyString(self, s):
        """
        :type s: str
        :rtype: str
        """
        result = []
        count = 0
        
        for char in s:
            if len(result) >= 2 and result[-1] == char and result[-2] == char:
                continue
            result.append(char)
        
        return ''.join(result)