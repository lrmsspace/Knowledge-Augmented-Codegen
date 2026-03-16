# Source: https://leetcode.com/problems/numbers-with-repeated-digits/   |   Difficulty: Hard
#
# Problem Description:
# Given an integer n, return the number of positive integers in the range [1, n] that have at least one repeated digit.
#
# Example:
# Input: n = 20
# Output: 1
# Explanation: The only positive number (<= 20) with at least 1 repeated digit is 11.
#
# Constraints:
# 1 <= n <= 109
#

class Solution(object):
    def numDupDigitsAtMostN(self, n):
        """
        :type n: int
        :rtype: int
        """
        digits = list(map(int, str(n + 1)))
        n = len(digits)

        # Count numbers with unique digits and length < n
        total = 0
        for i in range(1, n):
            total += 9 * self.permute(9, i - 1)

        # Count numbers with unique digits and length == n
        used = set()
        for i in range(n):
            for j in range(1 if i > 0 else 0, digits[i]):
                if j not in used:
                    total += self.permute(9 - i, n - i - 1)
            if digits[i] in used:
                break
            used.add(digits[i])

        return n - total - 1