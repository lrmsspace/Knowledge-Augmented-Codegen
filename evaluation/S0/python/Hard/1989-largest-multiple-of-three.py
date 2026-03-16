# Source: https://leetcode.com/problems/largest-multiple-of-three/   |   Difficulty: Hard
#
# Problem Description:
# Given an array of digits digits, return the largest multiple of three that can be formed by concatenating some of the given digits in any order. If there is no answer return an empty string.
#
# Since the answer may not fit in an integer data type, return the answer as a string. Note that the returning answer must not contain unnecessary leading zeros.
#
# Example:
# Input: digits = [8,1,9]
# Output: "981"
#
# Constraints:
# 1 <= digits.length <= 104
# 	0 <= digits[i] <= 9
#

class Solution(object):
    def largestMultipleOfThree(self, digits):
        """
        :type digits: List[int]
        :rtype: str
        """
        count = [0] * 10
        total_sum = 0
        
        for digit in digits:
            count[digit] += 1
            total_sum += digit
        
        def remove_digits(mod, k):
            for i in range(mod, 10, 3):
                while count[i] > 0 and k > 0:
                    count[i] -= 1
                    k -= 1
            return k == 0
        
        remainder = total_sum % 3
        if remainder != 0:
            if not remove_digits(remainder, 1):
                if not remove_digits(3 - remainder, 2):
                    return ""
        
        result = []
        for i in range(9, -1, -1):
            result.append(str(i) * count[i])
        
        result_str = ''.join(result)
        if result_str and result_str[0] == '0':
            return '0'
        
        return result_str