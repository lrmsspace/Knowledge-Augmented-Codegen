# Source: https://leetcode.com/problems/manhattan-distances-of-all-arrangements-of-pieces/   |   Difficulty: Hard
#
# Problem Description:
# You are given three integers m, n, and k.
#
# There is a rectangular grid of size m × n containing k identical pieces. Return the sum of Manhattan distances between every pair of pieces over all valid arrangements of pieces.
#
# A valid arrangement is a placement of all k pieces on the grid with at most one piece per cell.
#
# Since the answer may be very large, return it modulo 109 + 7.
#
# The Manhattan Distance between two cells (xi, yi) and (xj, yj) is |xi - xj| + |yi - yj|.
#
# Example:
# Input: m = 2, n = 2, k = 2
#
# Output: 8
#
# Explanation:
#
# The valid arrangements of pieces on the board are:
#
#
#
#
# 	In the first 4 arrangements, the Manhattan distance between the two pieces is 1.
# 	In the last 2 arrangements, the Manhattan distance between the two pieces is 2.
#
#
# Thus, the total Manhattan distance across all valid arrangements is 1 + 1 + 1 + 1 + 2 + 2 = 8.
#
# Constraints:
# 1 <= m, n <= 105
# 	2 <= m * n <= 105
# 	2 <= k <= m * n
#

class Solution(object):
    def distanceSum(self, m, n, k):
        """
        :type m: int
        :type n: int
        :type k: int
        :rtype: int
        """
        MOD = 10**9 + 7

        def modinv(a, p):
            return pow(a, p - 2, p)

        total_cells = m * n

        def comb(a, b):
            if b > a or b < 0:
                return 0
            numerator = 1
            for i in range(b):
                numerator = (numerator * (a - i)) % MOD
            denominator = 1
            for i in range(1, b + 1):
                denominator = (denominator * i) % MOD
            return (numerator * modinv(denominator, MOD)) % MOD

        arrangements = comb(total_cells, k)
        if arrangements == 0:
            return 0

        row_contrib = (m * (m - 1) // 2) * n * n % MOD
        col_contrib = (n * (n - 1) // 2) * m * m % MOD
        total_contrib = (row_contrib + col_contrib) % MOD

        ways_to_choose_2 = comb(total_cells - 2, k - 2)
        result = (total_contrib * ways_to_choose_2) % MOD
        result = (result * modinv(arrangements, MOD)) % MOD

        return result   