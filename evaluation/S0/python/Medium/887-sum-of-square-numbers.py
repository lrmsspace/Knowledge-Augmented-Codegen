# Source: https://leetcode.com/problems/sum-of-square-numbers/   |   Difficulty: Medium
#
# Problem Description:
# Given a non-negative integer c, decide whether there're two integers a and b such that a2 + b2 = c.
#
# Example:
# Input: c = 5
# Output: true
# Explanation: 1 * 1 + 2 * 2 = 5
#
# Constraints:
# 0 <= c <= 231 - 1
#

class Solution(object):
    def judgeSquareSum(self, c):
        """
        :type c: int
        :rtype: bool
        """
        left = 0
        right = int(c**0.5)
        
        while left <= right:
            current_sum = left * left + right * right
            if current_sum == c:
                return True
            elif current_sum < c:
                left += 1
            else:
                right -= 1
        
        return False