# Source: https://leetcode.com/problems/remove-k-digits/   |   Difficulty: Medium
#
# Problem Description:
# Given string num representing a non-negative integer num, and an integer k, return the smallest possible integer after removing k digits from num.
#
# Example:
# Input: num = "1432219", k = 3
# Output: "1219"
# Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
#
# Constraints:
# 1 <= k <= num.length <= 105
# 	num consists of only digits.
# 	num does not have any leading zeros except for the zero itself.
#

class Solution(object):
    def removeKdigits(self, num, k):
        """
        :type num: str
        :type k: int
        :rtype: str
        """
        stack = []
        
        for digit in num:
            while k > 0 and stack and stack[-1] > digit:
                stack.pop()
                k -= 1
            stack.append(digit)
        
        # If k is still greater than 0, remove from the end
        while k > 0:
            stack.pop()
            k -= 1
        
        # Build the final number and remove leading zeros
        result = ''.join(stack).lstrip('0')
        
        return result if result else '0'