# Source: https://leetcode.com/problems/numbers-at-most-n-given-digit-set/   |   Difficulty: Hard
#
# Problem Description:
# Given an array of digits which is sorted in non-decreasing order. You can write numbers using each digits[i] as many times as we want. For example, if digits = ['1','3','5'], we may write numbers such as '13', '551', and '1351315'.
#
# Return the number of positive integers that can be generated that are less than or equal to a given integer n.
#
# Example:
# Input: digits = ["1","3","5","7"], n = 100
# Output: 20
# Explanation: 
# The 20 numbers that can be written are:
# 1, 3, 5, 7, 11, 13, 15, 17, 31, 33, 35, 37, 51, 53, 55, 57, 71, 73, 75, 77.
#
# Constraints:
# 1 <= digits.length <= 9
# 	digits[i].length == 1
# 	digits[i] is a digit from '1' to '9'.
# 	All the values in digits are unique.
# 	digits is sorted in non-decreasing order.
# 	1 <= n <= 109
#

class Solution(object):
    def atMostNGivenDigitSet(self, digits, n):
        """
        :type digits: List[str]
        :type n: int
        :rtype: int
        """
        str_n = str(n)
        k = len(str_n)
        d = len(digits)
        
        # Count numbers with fewer digits than n
        total = 0
        for i in range(1, k):
            total += d ** i
        
        # Count numbers with the same number of digits as n
        for i in range(k):
            has_same_num = False
            for digit in digits:
                if digit < str_n[i]:
                    total += d ** (k - i - 1)
                elif digit == str_n[i]:
                    has_same_num = True
                    break
            if not has_same_num:
                return total
        
        return total + 1  # Include n itself if all digits matched