# Source: https://leetcode.com/problems/smallest-value-after-replacing-with-sum-of-prime-factors/   |   Difficulty: Medium
#
# Problem Description:
# You are given a positive integer n.
#
# Continuously replace n with the sum of its prime factors.
#
#
# 	Note that if a prime factor divides n multiple times, it should be included in the sum as many times as it divides n.
#
#
# Return the smallest value n will take on.
#
# Example:
# Input: n = 15
# Output: 5
# Explanation: Initially, n = 15.
# 15 = 3 * 5, so replace n with 3 + 5 = 8.
# 8 = 2 * 2 * 2, so replace n with 2 + 2 + 2 = 6.
# 6 = 2 * 3, so replace n with 2 + 3 = 5.
# 5 is the smallest value n will take on.
#
# Constraints:
# 2 <= n <= 105
#

class Solution(object):
    def smallestValue(self, n):
        """
        :type n: int
        :rtype: int
        """
        def prime_factors_sum(x):
            total = 0
            factor = 2
            while factor * factor <= x:
                while x % factor == 0:
                    total += factor
                    x //= factor
                factor += 1
            if x > 1:
                total += x
            return total

        seen = set()
        while n not in seen:
            seen.add(n)
            new_n = prime_factors_sum(n)
            if new_n == n:
                break
            n = new_n

        return n