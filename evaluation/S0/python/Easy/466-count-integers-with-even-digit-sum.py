# Source: https://leetcode.com/problems/count-integers-with-even-digit-sum/   |   Difficulty: Easy
#
# Problem Description:
# Given a positive integer num, return the number of positive integers less than or equal to num whose digit sums are even.
#
# The digit sum of a positive integer is the sum of all its digits.
#
# Example:
# Input: num = 4
# Output: 2
# Explanation:
# The only integers less than or equal to 4 whose digit sums are even are 2 and 4.
#
# Constraints:
# 1 <= num <= 1000
#

class Solution(object):
    def countEven(self, num):
        """
        :type num: int
        :rtype: int
        """
        count = 0
        for i in range(1, num + 1):
            if self.digit_sum(i) % 2 == 0:
                count += 1
        return count