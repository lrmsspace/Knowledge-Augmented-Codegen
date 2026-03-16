# Source: https://leetcode.com/problems/check-balanced-string/   |   Difficulty: Easy
#
# Problem Description:
# You are given a string num consisting of only digits. A string of digits is called balanced if the sum of the digits at even indices is equal to the sum of digits at odd indices.
#
# Return true if num is balanced, otherwise return false.
#
# Example:
# Input: num = "1234"
#
# Output: false
#
# Explanation:
#
#
# 	The sum of digits at even indices is 1 + 3 == 4, and the sum of digits at odd indices is 2 + 4 == 6.
# 	Since 4 is not equal to 6, num is not balanced.
#
# Constraints:
# 2 <= num.length <= 100
# 	num consists of digits only
#

class Solution(object):
    def isBalanced(self, num):
        """
        :type num: str
        :rtype: bool
        """
        even_sum = 0
        odd_sum = 0
        
        for i in range(len(num)):
            digit = int(num[i])
            if i % 2 == 0:
                even_sum += digit
            else:
                odd_sum += digit
        
        return even_sum == odd_sum