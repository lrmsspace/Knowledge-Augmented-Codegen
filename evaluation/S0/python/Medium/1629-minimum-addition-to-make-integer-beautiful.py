# Source: https://leetcode.com/problems/minimum-addition-to-make-integer-beautiful/   |   Difficulty: Medium
#
# Problem Description:
# You are given two positive integers n and target.
#
# An integer is considered beautiful if the sum of its digits is less than or equal to target.
#
# Return the minimum non-negative integer x such that n + x is beautiful. The input will be generated such that it is always possible to make n beautiful.
#
# Example:
# Input: n = 16, target = 6
# Output: 4
# Explanation: Initially n is 16 and its digit sum is 1 + 6 = 7. After adding 4, n becomes 20 and digit sum becomes 2 + 0 = 2. It can be shown that we can not make n beautiful with adding non-negative integer less than 4.
#
# Constraints:
# 1 <= n <= 1012
# 	1 <= target <= 150
# 	The input will be generated such that it is always possible to make n beautiful.
#

class Solution(object):
    def makeIntegerBeautiful(self, n, target):
        """
        :type n: int
        :type target: int
        :rtype: int
        """
        def digit_sum(x):
            return sum(int(d) for d in str(x))
        
        if digit_sum(n) <= target:
            return 0
        
        addition = 0
        factor = 1
        
        while digit_sum(n) > target:
            digit = (n // factor) % 10
            increment = (10 - digit) % 10
            addition += increment * factor
            n += increment * factor
            factor *= 10
        
        return addition