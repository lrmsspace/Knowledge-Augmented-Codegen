# Source: https://leetcode.com/problems/count-square-sum-triples/   |   Difficulty: Easy
#
# Problem Description:
# A square triple (a,b,c) is a triple where a, b, and c are integers and a2 + b2 = c2.
#
# Given an integer n, return the number of square triples such that 1 <= a, b, c <= n.
#
# Example:
# Input: n = 5
# Output: 2
# Explanation: The square triples are (3,4,5) and (4,3,5).
#
# Constraints:
# 1 <= n <= 250
#

class Solution(object):
    def countTriples(self, n):
        """
        :type n: int
        :rtype: int
        """
        count = 0
        for a in range(1, n + 1):
            for b in range(1, n + 1):
                c_squared = a * a + b * b
                c = int(c_squared ** 0.5)
                if c * c == c_squared and c <= n:
                    count += 1
        return count