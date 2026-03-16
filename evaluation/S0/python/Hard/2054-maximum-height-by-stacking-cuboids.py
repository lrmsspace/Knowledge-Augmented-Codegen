# Source: https://leetcode.com/problems/maximum-height-by-stacking-cuboids/   |   Difficulty: Hard
#
# Problem Description:
# Given n cuboids where the dimensions of the ith cuboid is cuboids[i] = [widthi, lengthi, heighti] (0-indexed). Choose a subset of cuboids and place them on each other.
#
# You can place cuboid i on cuboid j if widthi <= widthj and lengthi <= lengthj and heighti <= heightj. You can rearrange any cuboid's dimensions by rotating it to put it on another cuboid.
#
# Return the maximum height of the stacked cuboids.
#
# Example:
# Input: cuboids = [[50,45,20],[95,37,53],[45,23,12]]
# Output: 190
# Explanation:
# Cuboid 1 is placed on the bottom with the 53x37 side facing down with height 95.
# Cuboid 0 is placed next with the 45x20 side facing down with height 50.
# Cuboid 2 is placed next with the 23x12 side facing down with height 45.
# The total height is 95 + 50 + 45 = 190.
#
# Constraints:
# n == cuboids.length
# 	1 <= n <= 100
# 	1 <= widthi, lengthi, heighti <= 100
#

class Solution(object):
    def maxHeight(self, cuboids):
        """
        :type cuboids: List[List[int]]
        :rtype: int
        """
        for c in cuboids:
            c.sort()
        cuboids.sort()
        
        n = len(cuboids)
        dp = [0] * n
        
        for i in range(n):
            dp[i] = cuboids[i][2]
            for j in range(i):
                if (cuboids[j][0] <= cuboids[i][0] and
                    cuboids[j][1] <= cuboids[i][1] and
                    cuboids[j][2] <= cuboids[i][2]):
                    dp[i] = max(dp[i], dp[j] + cuboids[i][2])
        
        return max(dp)