# Source: https://leetcode.com/problems/count-the-digits-that-divide-a-number/   |   Difficulty: Easy
#
# Problem Description:
# Given an integer num, return the number of digits in num that divide num.
#
# An integer val divides nums if nums % val == 0.
#
# Example:
# Input: num = 7
# Output: 1
# Explanation: 7 divides itself, hence the answer is 1.
#
# Constraints:
# 1 <= num <= 109
# 	num does not contain 0 as one of its digits.
#

class Solution(object):
    def countDigits(self, num):
        """
        :type num: int
        :rtype: int
        """
        count = 0
        for digit in str(num):
            if num % int(digit) == 0:
                count += 1
        return count