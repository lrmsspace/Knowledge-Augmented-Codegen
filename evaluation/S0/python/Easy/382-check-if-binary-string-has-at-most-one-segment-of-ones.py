# Source: https://leetcode.com/problems/check-if-binary-string-has-at-most-one-segment-of-ones/   |   Difficulty: Easy
#
# Problem Description:
# Given a binary string s ​​​​​without leading zeros, return true​​​ if s contains at most one contiguous segment of ones. Otherwise, return false.
#
# Example:
# Input: s = "1001"
# Output: false
# Explanation: The ones do not form a contiguous segment.
#
# Constraints:
# 1 <= s.length <= 100
# 	s[i]​​​​ is either '0' or '1'.
# 	s[0] is '1'.
#

class Solution(object):
    def checkOnesSegment(self, s):
        """
        :type s: str
        :rtype: bool
        """
        return '01' not in s