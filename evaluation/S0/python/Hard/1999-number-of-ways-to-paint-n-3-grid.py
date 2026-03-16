# Source: https://leetcode.com/problems/number-of-ways-to-paint-n-3-grid/   |   Difficulty: Hard
#
# Problem Description:
# You have a grid of size n x 3 and you want to paint each cell of the grid with exactly one of the three colors: Red, Yellow, or Green while making sure that no two adjacent cells have the same color (i.e., no two cells that share vertical or horizontal sides have the same color).
#
# Given n the number of rows of the grid, return the number of ways you can paint this grid. As the answer may grow large, the answer must be computed modulo 109 + 7.
#
# Example:
# Input: n = 1
# Output: 12
# Explanation: There are 12 possible way to paint the grid as shown.
#
# Constraints:
# n == grid.length
# 	1 <= n <= 5000
#

class Solution(object):
    def numOfWays(self, n):
        """
        :type n: int
        :rtype: int
        """
        MOD = 10**9 + 7
        
        # a: patterns like ABA
        # b: patterns like ABC
        a, b = 6, 6
        
        for _ in range(2, n + 1):
            a, b = (3 * a + 2 * b) % MOD, (2 * a + 2 * b) % MOD
        
        return (a + b) % MOD