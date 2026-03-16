# Source: https://leetcode.com/problems/non-negative-integers-without-consecutive-ones/   |   Difficulty: Hard
#
# Problem Description:
# Given a positive integer n, return the number of the integers in the range [0, n] whose binary representations do not contain consecutive ones.
#
# Example:
# Input: n = 5
# Output: 5
# Explanation:
# Here are the non-negative integers <= 5 with their corresponding binary representations:
# 0 : 0
# 1 : 1
# 2 : 10
# 3 : 11
# 4 : 100
# 5 : 101
# Among them, only integer 3 disobeys the rule (two consecutive ones) and the other 5 satisfy the rule.
#
# Constraints:
# 1 <= n <= 109
#

class Solution(object):
    def findIntegers(self, n):
        """
        :type n: int
        :rtype: int
        """
        a, b = 1, 2
        prev_bit = 0
        result = 0
        for k in range(30, -1, -1):
            curr_bit = (n >> k) & 1
            if curr_bit == 1:
                result += b
                if prev_bit == 1:
                    result -= 1
                    break
            a, b = b, a + b
            prev_bit = curr_bit
        else:
            result += 1
        return result