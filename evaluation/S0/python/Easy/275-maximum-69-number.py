# Source: https://leetcode.com/problems/maximum-69-number/   |   Difficulty: Easy
#
# Problem Description:
# You are given a positive integer num consisting only of digits 6 and 9.
#
# Return the maximum number you can get by changing at most one digit (6 becomes 9, and 9 becomes 6).
#
# Example:
# Input: num = 9669
# Output: 9969
# Explanation: 
# Changing the first digit results in 6669.
# Changing the second digit results in 9969.
# Changing the third digit results in 9699.
# Changing the fourth digit results in 9666.
# The maximum number is 9969.
#
# Constraints:
# 1 <= num <= 104
# 	num consists of only 6 and 9 digits.
#

class Solution(object):
    def maximum69Number (self, num):
        """
        :type num: int
        :rtype: int
        """
        num_str = str(num)
        num_list = list(num_str)
        
        for i in range(len(num_list)):
            if num_list[i] == '6':
                num_list[i] = '9'
                break
        
        return int(''.join(num_list))