# Source: https://leetcode.com/problems/moving-stones-until-consecutive/   |   Difficulty: Medium
#
# Problem Description:
# There are three stones in different positions on the X-axis. You are given three integers a, b, and c, the positions of the stones.
#
# In one move, you pick up a stone at an endpoint (i.e., either the lowest or highest position stone), and move it to an unoccupied position between those endpoints. Formally, let's say the stones are currently at positions x, y, and z with x < y < z. You pick up the stone at either position x or position z, and move that stone to an integer position k, with x < k < z and k != y.
#
# The game ends when you cannot make any more moves (i.e., the stones are in three consecutive positions).
#
# Return an integer array answer of length 2 where:
#
#
# 	answer[0] is the minimum number of moves you can play, and
# 	answer[1] is the maximum number of moves you can play.
#
# Example:
# Input: a = 1, b = 2, c = 5
# Output: [1,2]
# Explanation: Move the stone from 5 to 3, or move the stone from 5 to 4 to 3.
#
# Constraints:
# 1 <= a, b, c <= 100
# 	a, b, and c have different values.
#

class Solution(object):
    def numMovesStones(self, a, b, c):
        """
        :type a: int
        :type b: int
        :type c: int
        :rtype: List[int]
        """
        x, y, z = sorted([a, b, c])
        max_moves = (z - y - 1) + (y - x - 1)
        if z - y == 1 and y - x == 1:
            min_moves = 0
        elif z - y <= 2 or y - x <= 2:
            min_moves = 1
        else:
            min_moves = 2
        return [min_moves, max_moves]