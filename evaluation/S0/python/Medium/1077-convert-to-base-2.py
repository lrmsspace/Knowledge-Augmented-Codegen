# Source: https://leetcode.com/problems/convert-to-base-2/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer n, return a binary string representing its representation in base -2.
#
# Note that the returned string should not have leading zeros unless the string is "0".
#
# Example:
# Input: n = 2
# Output: "110"
# Explantion: (-2)2 + (-2)1 = 2
#
# Constraints:
# 0 <= n <= 109
#

class Solution(object):
    def baseNeg2(self, n):
        """
        :type n: int
        :rtype: str
        """
        if n == 0:
            return "0"
        
        result = []
        while n != 0:
            n, remainder = divmod(n, -2)
            if remainder < 0:
                remainder += 2
                n += 1
            result.append(str(remainder))
        
        return ''.join(reversed(result))