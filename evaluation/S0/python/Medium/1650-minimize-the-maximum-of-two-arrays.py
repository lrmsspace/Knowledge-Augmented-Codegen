# Source: https://leetcode.com/problems/minimize-the-maximum-of-two-arrays/   |   Difficulty: Medium
#
# Problem Description:
# We have two arrays arr1 and arr2 which are initially empty. You need to add positive integers to them such that they satisfy all the following conditions:
#
#
# 	arr1 contains uniqueCnt1 distinct positive integers, each of which is not divisible by divisor1.
# 	arr2 contains uniqueCnt2 distinct positive integers, each of which is not divisible by divisor2.
# 	No integer is present in both arr1 and arr2.
#
#
# Given divisor1, divisor2, uniqueCnt1, and uniqueCnt2, return the minimum possible maximum integer that can be present in either array.
#
# Example:
# Input: divisor1 = 2, divisor2 = 7, uniqueCnt1 = 1, uniqueCnt2 = 3
# Output: 4
# Explanation: 
# We can distribute the first 4 natural numbers into arr1 and arr2.
# arr1 = [1] and arr2 = [2,3,4].
# We can see that both arrays satisfy all the conditions.
# Since the maximum value is 4, we return it.
#
# Constraints:
# 2 <= divisor1, divisor2 <= 105
# 	1 <= uniqueCnt1, uniqueCnt2 < 109
# 	2 <= uniqueCnt1 + uniqueCnt2 <= 109
#

class Solution(object):
    def minimizeSet(self, divisor1, divisor2, uniqueCnt1, uniqueCnt2):
        """
        :type divisor1: int
        :type divisor2: int
        :type uniqueCnt1: int
        :type uniqueCnt2: int
        :rtype: int
        """
        import math

        lcm = divisor1 * divisor2 // math.gcd(divisor1, divisor2)

        def can(x):
            count1 = x - x // divisor1 - (x // lcm)
            count2 = x - x // divisor2 - (x // lcm)
            return count1 >= uniqueCnt1 and count2 >= uniqueCnt2

        left, right = 1, 10**18
        while left < right:
            mid = (left + right) // 2
            if can(mid):
                right = mid
            else:
                left = mid + 1

        return left