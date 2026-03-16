# Source: https://leetcode.com/problems/count-pairs-of-points-with-distance-k/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 2D integer array coordinates and an integer k, where coordinates[i] = [xi, yi] are the coordinates of the ith point in a 2D plane.
#
# We define the distance between two points (x1, y1) and (x2, y2) as (x1 XOR x2) + (y1 XOR y2) where XOR is the bitwise XOR operation.
#
# Return the number of pairs (i, j) such that i < j and the distance between points i and j is equal to k.
#
# Example:
# Input: coordinates = [[1,2],[4,2],[1,3],[5,2]], k = 5
# Output: 2
# Explanation: We can choose the following pairs:
# - (0,1): Because we have (1 XOR 4) + (2 XOR 2) = 5.
# - (2,3): Because we have (1 XOR 5) + (3 XOR 2) = 5.
#
# Constraints:
# 2 <= coordinates.length <= 50000
# 	0 <= xi, yi <= 106
# 	0 <= k <= 100
#

class Solution(object):
    def countPairs(self, coordinates, k):
        """
        :type coordinates: List[List[int]]
        :type k: int
        :rtype: int
        """
        from collections import defaultdict

        count = 0
        freq = defaultdict(int)

        for x, y in coordinates:
            for dx in range(0, k + 1):
                dy = k - dx
                x_target = x ^ dx
                y_target = y ^ dy
                count += freq[(x_target, y_target)]

            freq[(x, y)] += 1

        return count