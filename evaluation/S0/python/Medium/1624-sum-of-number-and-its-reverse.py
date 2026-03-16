# Source: https://leetcode.com/problems/sum-of-number-and-its-reverse/   |   Difficulty: Medium
#
# Problem Description:
# Given a non-negative integer num, return true if num can be expressed as the sum of any non-negative integer and its reverse, or false otherwise.
#
# Example:
# Input: num = 443
# Output: true
# Explanation: 172 + 271 = 443 so we return true.
#
# Constraints:
# 0 <= num <= 105
#

class Solution(object):
    def sumOfNumberAndReverse(self, num):
        """
        :type num: int
        :rtype: bool
        """
        for i in range(num + 1):
            rev_i = int(str(i)[::-1])
            if i + rev_i == num:
                return True
        return False