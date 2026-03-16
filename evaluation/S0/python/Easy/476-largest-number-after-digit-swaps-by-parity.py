# Source: https://leetcode.com/problems/largest-number-after-digit-swaps-by-parity/   |   Difficulty: Easy
#
# Problem Description:
# You are given a positive integer num. You may swap any two digits of num that have the same parity (i.e. both odd digits or both even digits).
#
# Return the largest possible value of num after any number of swaps.
#
# Example:
# Input: num = 1234
# Output: 3412
# Explanation: Swap the digit 3 with the digit 1, this results in the number 3214.
# Swap the digit 2 with the digit 4, this results in the number 3412.
# Note that there may be other sequences of swaps but it can be shown that 3412 is the largest possible number.
# Also note that we may not swap the digit 4 with the digit 1 since they are of different parities.
#
# Constraints:
# 1 <= num <= 109
#

class Solution(object):
    def largestInteger(self, num):
        """
        :type num: int
        :rtype: int
        """
        num_str = str(num)
        even_digits = sorted([int(d) for d in num_str if int(d) % 2 == 0], reverse=True)
        odd_digits = sorted([int(d) for d in num_str if int(d) % 2 != 0], reverse=True)
        
        even_index, odd_index = 0, 0
        result = []
        
        for digit in num_str:
            if int(digit) % 2 == 0:
                result.append(str(even_digits[even_index]))
                even_index += 1
            else:
                result.append(str(odd_digits[odd_index]))
                odd_index += 1
        
        return int(''.join(result))