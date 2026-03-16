# Source: https://leetcode.com/problems/three-divisors/   |   Difficulty: Easy
#
# Problem Description:
# Given an integer n, return true if n has exactly three positive divisors. Otherwise, return false.
#
# An integer m is a divisor of n if there exists an integer k such that n = k * m.
#
# Example:
# Input: n = 2
# Output: false
# Explantion: 2 has only two divisors: 1 and 2.
#
# Constraints:
# 1 <= n <= 104
#

class Solution(object):
    def isThree(self, n):
        """
        :type n: int
        :rtype: bool
        """
        if n < 4:
            return False
        
        count = 0
        for i in range(1, int(n**0.5) + 1):
            if n % i == 0:
                count += 1
                if i != n // i:
                    count += 1
            if count > 3:
                return False
        
        return count == 3