# Source: https://leetcode.com/problems/minimum-string-length-after-removing-substrings/   |   Difficulty: Easy
#
# Problem Description:
# You are given a string s consisting only of uppercase English letters.
#
# You can apply some operations to this string where, in one operation, you can remove any occurrence of one of the substrings "AB" or "CD" from s.
#
# Return the minimum possible length of the resulting string that you can obtain.
#
# Note that the string concatenates after removing the substring and could produce new "AB" or "CD" substrings.
#
# Example:
# Input: s = "ABFCACDB"
# Output: 2
# Explanation: We can do the following operations:
# - Remove the substring "ABFCACDB", so s = "FCACDB".
# - Remove the substring "FCACDB", so s = "FCAB".
# - Remove the substring "FCAB", so s = "FC".
# So the resulting length of the string is 2.
# It can be shown that it is the minimum length that we can obtain.
#
# Constraints:
# 1 <= s.length <= 100
# 	s consists only of uppercase English letters.
#

class Solution(object):
    def minLength(self, s):
        """
        :type s: str
        :rtype: int
        """
        stack = []
        for char in s:
            if stack and ((stack[-1] == 'A' and char == 'B') or (stack[-1] == 'C' and char == 'D')):
                stack.pop()
            else:
                stack.append(char)
        return len(stack)