# Source: https://leetcode.com/problems/check-if-the-number-is-fascinating/   |   Difficulty: Easy
#
# Problem Description:
# You are given an integer n that consists of exactly 3 digits.
#
# We call the number n fascinating if, after the following modification, the resulting number contains all the digits from 1 to 9 exactly once and does not contain any 0's:
#
#
# 	Concatenate n with the numbers 2 * n and 3 * n.
#
#
# Return true if n is fascinating, or false otherwise.
#
# Concatenating two numbers means joining them together. For example, the concatenation of 121 and 371 is 121371.
#
# Example:
# Input: n = 192
# Output: true
# Explanation: We concatenate the numbers n = 192 and 2 * n = 384 and 3 * n = 576. The resulting number is 192384576. This number contains all the digits from 1 to 9 exactly once.
#
# Constraints:
# 100 <= n <= 999
#

class Solution(object):
    def isFascinating(self, n):
        """
        :type n: int
        :rtype: bool
        """
        concat_str = str(n) + str(2 * n) + str(3 * n)
        digits_set = set(concat_str)
        
        return len(concat_str) == 9 and '0' not in digits_set and len(digits_set) == 9