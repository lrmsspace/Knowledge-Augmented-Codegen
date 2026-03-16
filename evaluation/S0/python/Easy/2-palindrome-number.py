# Source: https://leetcode.com/problems/palindrome-number/   |   Difficulty: Easy
#
# Problem Description:
# Given an integer x, return true if x is a palindrome, and false otherwise.
#
# Example:
# Input: x = 121
# Output: true
# Explanation: 121 reads as 121 from left to right and from right to left.
#
# Constraints:
# -231 <= x <= 231 - 1
#
#
#  
# Follow up: Could you solve it without converting the integer to a string?
#

class Solution(object):
    def isPalindrome(self, x):
        """
        :type x: int
        :rtype: bool
        """
        if x < 0:
            return False
        
        divisor = 1
        while x // divisor >= 10:
            divisor *= 10
        
        while x:
            leading = x // divisor
            trailing = x % 10
            
            if leading != trailing:
                return False
            
            x = (x % divisor) // 10
            divisor //= 100
        
        return True