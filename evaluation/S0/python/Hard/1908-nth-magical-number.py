# Source: https://leetcode.com/problems/nth-magical-number/   |   Difficulty: Hard
#
# Problem Description:
# A positive integer is magical if it is divisible by either a or b.
#
# Given the three integers n, a, and b, return the nth magical number. Since the answer may be very large, return it modulo 109 + 7.
#
# Example:
# Input: n = 1, a = 2, b = 3
# Output: 2
#
# Constraints:
# 1 <= n <= 109
# 	2 <= a, b <= 4 * 104
#

class Solution(object):
    def nthMagicalNumber(self, n, a, b):
        """
        :type n: int
        :type a: int
        :type b: int
        :rtype: int
        """
        MOD = 10**9 + 7
        
        def gcd(x, y):
            while y:
                x, y = y, x % y
            return x
        
        lcm = a * b // gcd(a, b)
        
        def magical_count(x):
            return x // a + x // b - x // lcm
        
        left, right = 1, n * min(a, b)
        while left < right:
            mid = (left + right) // 2
            if magical_count(mid) < n:
                left = mid + 1
            else:
                right = mid
        
        return left % MOD