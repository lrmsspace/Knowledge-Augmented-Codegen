# Source: https://leetcode.com/problems/smallest-value-of-the-rearranged-number/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer num. Rearrange the digits of num such that its value is minimized and it does not contain any leading zeros.
#
# Return the rearranged number with minimal value.
#
# Note that the sign of the number does not change after rearranging the digits.
#
# Example:
# Input: num = 310
# Output: 103
# Explanation: The possible arrangements for the digits of 310 are 013, 031, 103, 130, 301, 310. 
# The arrangement with the smallest value that does not contain any leading zeros is 103.
#
# Constraints:
# -1015 <= num <= 1015
#

class Solution(object):
    def smallestNumber(self, num):
        """
        :type num: int
        :rtype: int
        """
        if num == 0:
            return 0
        
        negative = num < 0
        digits = list(str(abs(num)))
        
        if negative:
            digits.sort(reverse=True)
            return -int(''.join(digits))
        else:
            digits.sort()
            if digits[0] == '0':
                for i in range(1, len(digits)):
                    if digits[i] != '0':
                        digits[0], digits[i] = digits[i], digits[0]
                        break
            return int(''.join(digits))