# Source: https://leetcode.com/problems/convert-integer-to-the-sum-of-two-no-zero-integers/   |   Difficulty: Easy
#
# Problem Description:
# No-Zero integer is a positive integer that does not contain any 0 in its decimal representation.
#
# Given an integer n, return a list of two integers [a, b] where:
#
#
# 	a and b are No-Zero integers.
# 	a + b = n
#
#
# The test cases are generated so that there is at least one valid solution. If there are many valid solutions, you can return any of them.
#
# Example:
# Input: n = 2
# Output: [1,1]
# Explanation: Let a = 1 and b = 1.
# Both a and b are no-zero integers, and a + b = 2 = n.
#
# Constraints:
# 2 <= n <= 104
#

class Solution(object):
    def getNoZeroIntegers(self, n):
        """
        :type n: int
        :rtype: List[int]
        """
        def has_zero(num):
            while num > 0:
                if num % 10 == 0:
                    return True
                num //= 10
            return False

        for a in range(1, n):
            b = n - a
            if not has_zero(a) and not has_zero(b):
                return [a, b]
        return []