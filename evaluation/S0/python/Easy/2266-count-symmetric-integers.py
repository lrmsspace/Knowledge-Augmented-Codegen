# Source: https://leetcode.com/problems/count-symmetric-integers/   |   Difficulty: Easy
#
# Problem Description:
# You are given two positive integers low and high.
#
# An integer x consisting of 2 * n digits is symmetric if the sum of the first n digits of x is equal to the sum of the last n digits of x. Numbers with an odd number of digits are never symmetric.
#
# Return the number of symmetric integers in the range [low, high].
#
# Example:
# Input: low = 1, high = 100
# Output: 9
# Explanation: There are 9 symmetric integers between 1 and 100: 11, 22, 33, 44, 55, 66, 77, 88, and 99.
#
# Constraints:
# 1 <= low <= high <= 104
#

class Solution(object):
    def countSymmetricIntegers(self, low, high):
        """
        :type low: int
        :type high: int
        :rtype: int
        """
        def is_symmetric(num):
            s = str(num)
            n = len(s)
            if n % 2 != 0:
                return False
            half = n // 2
            left_sum = sum(int(s[i]) for i in range(half))
            right_sum = sum(int(s[i]) for i in range(half, n))
            return left_sum == right_sum

        count = 0
        for num in range(low, high + 1):
            if is_symmetric(num):
                count += 1
        return count