# Source: https://leetcode.com/problems/minimum-operations-to-make-the-integer-zero/   |   Difficulty: Medium
#
# Problem Description:
# You are given two integers num1 and num2.
#
# In one operation, you can choose integer i in the range [0, 60] and subtract 2i + num2 from num1.
#
# Return the integer denoting the minimum number of operations needed to make num1 equal to 0.
#
# If it is impossible to make num1 equal to 0, return -1.
#
# Example:
# Input: num1 = 3, num2 = -2
# Output: 3
# Explanation: We can make 3 equal to 0 with the following operations:
# - We choose i = 2 and subtract 22 + (-2) from 3, 3 - (4 + (-2)) = 1.
# - We choose i = 2 and subtract 22 + (-2) from 1, 1 - (4 + (-2)) = -1.
# - We choose i = 0 and subtract 20 + (-2) from -1, (-1) - (1 + (-2)) = 0.
# It can be proven, that 3 is the minimum number of operations that we need to perform.
#
# Constraints:
# 1 <= num1 <= 109
#  -109 <= num2 <= 109
#

class Solution(object):
    def makeTheIntegerZero(self, num1, num2):
        """
        :type num1: int
        :type num2: int
        :rtype: int
        """
        operations = 0
        while num1 > 0:
            if num1 < operations:
                return -1
            num1 -= num2 + (1 << operations)
            operations += 1
        return operations if num1 == 0 else -1