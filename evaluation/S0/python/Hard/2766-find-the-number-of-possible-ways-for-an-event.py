# Source: https://leetcode.com/problems/find-the-number-of-possible-ways-for-an-event/   |   Difficulty: Hard
#
# Problem Description:
# You are given three integers n, x, and y.
#
# An event is being held for n performers. When a performer arrives, they are assigned to one of the x stages. All performers assigned to the same stage will perform together as a band, though some stages might remain empty.
#
# After all performances are completed, the jury will award each band a score in the range [1, y].
#
# Return the total number of possible ways the event can take place.
#
# Since the answer may be very large, return it modulo 109 + 7.
#
# Note that two events are considered to have been held differently if either of the following conditions is satisfied:
#
#
# 	Any performer is assigned a different stage.
# 	Any band is awarded a different score.
#
# Example:
# Input: n = 1, x = 2, y = 3
#
# Output: 6
#
# Explanation:
#
#
# 	There are 2 ways to assign a stage to the performer.
# 	The jury can award a score of either 1, 2, or 3 to the only band.
#
# Constraints:
# 1 <= n, x, y <= 1000
#

class Solution(object):
    def numberOfWays(self, n, x, y):
        """
        :type n: int
        :type x: int
        :type y: int
        :rtype: int
        """
        MOD = 10**9 + 7

        # Precompute Stirling numbers of the second kind
        stirling = [[0] * (n + 1) for _ in range(n + 1)]
        stirling[0][0] = 1

        for i in range(1, n + 1):
            for j in range(1, i + 1):
                stirling[i][j] = (stirling[i - 1][j - 1] + j * stirling[i - 1][j]) % MOD

        # Precompute powers of y
        pow_y = [1] * (n + 1)
        for i in range(1, n + 1):
            pow_y[i] = (pow_y[i - 1] * y) % MOD

        result = 0
        for k in range(1, min(n, x) + 1):
            result = (result + stirling[n][k] * pow_y[k]) % MOD

        return result