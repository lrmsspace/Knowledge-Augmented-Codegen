# Source: https://leetcode.com/problems/remove-trailing-zeros-from-a-string/   |   Difficulty: Easy
#
# Problem Description:
# Given a positive integer num represented as a string, return the integer num without trailing zeros as a string.
#
# Example:
# Input: num = "51230100"
# Output: "512301"
# Explanation: Integer "51230100" has 2 trailing zeros, we remove them and return integer "512301".
#
# Constraints:
# 1 <= num.length <= 1000
# 	num consists of only digits.
# 	num doesn't have any leading zeros.
#

class Solution(object):
    def removeTrailingZeros(self, num):
        """
        :type num: str
        :rtype: str
        """
        return num.rstrip('0')