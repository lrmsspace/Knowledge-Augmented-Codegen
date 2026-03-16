# Source: https://leetcode.com/problems/minimum-domino-rotations-for-equal-row/   |   Difficulty: Medium
#
# Problem Description:
# In a row of dominoes, tops[i] and bottoms[i] represent the top and bottom halves of the ith domino. (A domino is a tile with two numbers from 1 to 6 - one on each half of the tile.)
#
# We may rotate the ith domino, so that tops[i] and bottoms[i] swap values.
#
# Return the minimum number of rotations so that all the values in tops are the same, or all the values in bottoms are the same.
#
# If it cannot be done, return -1.
#
# Example:
# Input: tops = [2,1,2,4,2,2], bottoms = [5,2,6,2,3,2]
# Output: 2
# Explanation: 
# The first figure represents the dominoes as given by tops and bottoms: before we do any rotations.
# If we rotate the second and fourth dominoes, we can make every value in the top row equal to 2, as indicated by the second figure.
#
# Constraints:
# 2 <= tops.length <= 2 * 104
# 	bottoms.length == tops.length
# 	1 <= tops[i], bottoms[i] <= 6
#

class Solution(object):
    def minDominoRotations(self, tops, bottoms):
        """
        :type tops: List[int]
        :type bottoms: List[int]
        :rtype: int
        """
        def check(x):
            rotations_a = rotations_b = 0
            for i in range(len(tops)):
                if tops[i] != x and bottoms[i] != x:
                    return float('inf')
                elif tops[i] != x:
                    rotations_a += 1
                elif bottoms[i] != x:
                    rotations_b += 1
            return min(rotations_a, rotations_b)

        rotations = check(tops[0])
        if rotations != float('inf'):
            return rotations
        else:
            return check(bottoms[0]) if tops[0] != bottoms[0] else -1