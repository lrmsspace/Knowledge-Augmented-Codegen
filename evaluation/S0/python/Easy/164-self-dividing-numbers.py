# Source: https://leetcode.com/problems/self-dividing-numbers/   |   Difficulty: Easy
#
# Problem Description:
# A self-dividing number is a number that is divisible by every digit it contains.
#
#
# 	For example, 128 is a self-dividing number because 128 % 1 == 0, 128 % 2 == 0, and 128 % 8 == 0.
#
#
# A self-dividing number is not allowed to contain the digit zero.
#
# Given two integers left and right, return a list of all the self-dividing numbers in the range [left, right] (both inclusive).
#
# Example:
# Input: left = 1, right = 22
# Output: [1,2,3,4,5,6,7,8,9,11,12,15,22]
#
# Constraints:
# 1 <= left <= right <= 104
#

class Solution(object):
    def selfDividingNumbers(self, left, right):
        """
        :type left: int
        :type right: int
        :rtype: List[int]
        """
        result = []
        for num in range(left, right + 1):
            if self.is_self_dividing(num):
                result.append(num)
        return result