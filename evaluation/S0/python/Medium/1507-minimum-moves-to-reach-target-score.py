# Source: https://leetcode.com/problems/minimum-moves-to-reach-target-score/   |   Difficulty: Medium
#
# Problem Description:
# You are playing a game with integers. You start with the integer 1 and you want to reach the integer target.
#
# In one move, you can either:
#
#
# 	Increment the current integer by one (i.e., x = x + 1).
# 	Double the current integer (i.e., x = 2 * x).
#
#
# You can use the increment operation any number of times, however, you can only use the double operation at most maxDoubles times.
#
# Given the two integers target and maxDoubles, return the minimum number of moves needed to reach target starting with 1.
#
# Example:
# Input: target = 5, maxDoubles = 0
# Output: 4
# Explanation: Keep incrementing by 1 until you reach target.
#
# Constraints:
# 1 <= target <= 109
# 	0 <= maxDoubles <= 100
#

class Solution(object):
    def minMoves(self, target, maxDoubles):
        """
        :type target: int
        :type maxDoubles: int
        :rtype: int
        """
        moves = 0
        while target > 1:
            if maxDoubles > 0 and target % 2 == 0:
                target //= 2
                maxDoubles -= 1
            else:
                target -= 1
            moves += 1
        return moves