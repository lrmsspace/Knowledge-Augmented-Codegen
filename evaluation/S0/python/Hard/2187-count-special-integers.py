# Source: https://leetcode.com/problems/count-special-integers/   |   Difficulty: Hard
#
# Problem Description:
# We call a positive integer special if all of its digits are distinct.
#
# Given a positive integer n, return the number of special integers that belong to the interval [1, n].
#
# Example:
# Input: n = 20
# Output: 19
# Explanation: All the integers from 1 to 20, except 11, are special. Thus, there are 19 special integers.
#
# Constraints:
# 1 <= n <= 2 * 109
#

class Solution(object):
    def countSpecialNumbers(self, n):
        """
        :type n: int
        :rtype: int
        """
        str_n = str(n)
        n_digits = len(str_n)
        count = 0

        # Count special numbers with fewer digits than n
        for d in range(1, n_digits):
            count += 9 * self.permute(9, d - 1)

        # Count special numbers with the same number of digits as n
        used = set()
        for i in range(n_digits):
            digit = int(str_n[i])
            for d in range(0 if i > 0 else 1, digit):
                if d not in used:
                    count += self.permute(10 - (i + 1), n_digits - (i + 1))
            if digit in used:
                break
            used.add(digit)
        else:
            count += 1  # Include n itself if all digits are distinct

        return count