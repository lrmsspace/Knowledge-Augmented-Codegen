# Source: https://leetcode.com/problems/count-beautiful-numbers/   |   Difficulty: Hard
#
# Problem Description:
# You are given two positive integers, l and r. A positive integer is called beautiful if the product of its digits is divisible by the sum of its digits.
#
# Return the count of beautiful numbers between l and r, inclusive.
#
# Example:
# Input: l = 10, r = 20
#
# Output: 2
#
# Explanation:
#
# The beautiful numbers in the range are 10 and 20.
#
# Constraints:
# 1 <= l <= r < 109
#

class Solution(object):
    def beautifulNumbers(self, l, r):
        """
        :type l: int
        :type r: int
        :rtype: int
        """
        def is_beautiful(num):
            digit_sum = 0
            digit_product = 1
            while num > 0:
                digit = num % 10
                digit_sum += digit
                digit_product *= digit
                num //= 10
            return digit_sum != 0 and digit_product % digit_sum == 0

        count = 0
        for num in range(l, r + 1):
            if is_beautiful(num):
                count += 1
        return count