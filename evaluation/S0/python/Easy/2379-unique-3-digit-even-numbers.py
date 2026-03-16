# Source: https://leetcode.com/problems/unique-3-digit-even-numbers/   |   Difficulty: Easy
#
# Problem Description:
# You are given an array of digits called digits. Your task is to determine the number of distinct three-digit even numbers that can be formed using these digits.
#
# Note: Each copy of a digit can only be used once per number, and there may not be leading zeros.
#
# Example:
# Input: digits = [1,2,3,4]
#
# Output: 12
#
# Explanation: The 12 distinct 3-digit even numbers that can be formed are 124, 132, 134, 142, 214, 234, 312, 314, 324, 342, 412, and 432. Note that 222 cannot be formed because there is only 1 copy of the digit 2.
#
# Constraints:
# 3 <= digits.length <= 10
# 	0 <= digits[i] <= 9
#

class Solution(object):
    def totalNumbers(self, digits):
        """
        :type digits: List[int]
        :rtype: int
        """
        unique_numbers = set()
        
        n = len(digits)
        
        for i in range(n):
            for j in range(n):
                for k in range(n):
                    if i != j and j != k and i != k:
                        hundreds = digits[i]
                        tens = digits[j]
                        units = digits[k]
                        
                        if hundreds != 0 and units % 2 == 0:
                            number = hundreds * 100 + tens * 10 + units
                            unique_numbers.add(number)
        
        return len(unique_numbers)