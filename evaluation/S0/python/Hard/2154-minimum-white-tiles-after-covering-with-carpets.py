# Source: https://leetcode.com/problems/minimum-white-tiles-after-covering-with-carpets/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed binary string floor, which represents the colors of tiles on a floor:
#
#
# 	floor[i] = '0' denotes that the ith tile of the floor is colored black.
# 	On the other hand, floor[i] = '1' denotes that the ith tile of the floor is colored white.
#
#
# You are also given numCarpets and carpetLen. You have numCarpets black carpets, each of length carpetLen tiles. Cover the tiles with the given carpets such that the number of white tiles still visible is minimum. Carpets may overlap one another.
#
# Return the minimum number of white tiles still visible.
#
# Example:
# Input: floor = "10110101", numCarpets = 2, carpetLen = 2
# Output: 2
# Explanation: 
# The figure above shows one way of covering the tiles with the carpets such that only 2 white tiles are visible.
# No other way of covering the tiles with the carpets can leave less than 2 white tiles visible.
#
# Constraints:
# 1 <= carpetLen <= floor.length <= 1000
# 	floor[i] is either '0' or '1'.
# 	1 <= numCarpets <= 1000
#

class Solution(object):
    def minimumWhiteTiles(self, floor, numCarpets, carpetLen):
        """
        :type floor: str
        :type numCarpets: int
        :type carpetLen: int
        :rtype: int
        """
        n = len(floor)
        dp = [[0] * (numCarpets + 1) for _ in range(n + 1)]

        for i in range(1, n + 1):
            is_white = 1 if floor[i - 1] == '1' else 0
            for j in range(numCarpets + 1):
                dp[i][j] = dp[i - 1][j] + is_white
                if j > 0:
                    dp[i][j] = min(dp[i][j], dp[max(0, i - carpetLen)][j - 1])

        return dp[n][numCarpets]