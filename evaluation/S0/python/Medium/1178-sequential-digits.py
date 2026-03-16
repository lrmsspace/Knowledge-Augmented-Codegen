# Source: https://leetcode.com/problems/sequential-digits/   |   Difficulty: Medium
#
# Problem Description:
# An integer has sequential digits if and only if each digit in the number is one more than the previous digit.
#
# Return a sorted list of all the integers in the range [low, high] inclusive that have sequential digits.
#
# Example:
# Input: low = 100, high = 300
# Output: [123,234]
#
# Constraints:
# 10 <= low <= high <= 10^9
#

class Solution(object):
    def sequentialDigits(self, low, high):
        """
        :type low: int
        :type high: int
        :rtype: List[int]
        """
        res = []
        digits = "123456789"
        n_low = len(str(low))
        n_high = len(str(high))
        
        for length in range(n_low, n_high + 1):
            for start in range(0, 10 - length):
                num = int(digits[start:start + length])
                if low <= num <= high:
                    res.append(num)
        
        return res