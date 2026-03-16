# Source: https://leetcode.com/problems/furthest-point-from-origin/   |   Difficulty: Easy
#
# Problem Description:
# You are given a string moves of length n consisting only of characters 'L', 'R', and '_'. The string represents your movement on a number line starting from the origin 0.
#
# In the ith move, you can choose one of the following directions:
#
#
# 	move to the left if moves[i] = 'L' or moves[i] = '_'
# 	move to the right if moves[i] = 'R' or moves[i] = '_'
#
#
# Return the distance from the origin of the furthest point you can get to after n moves.
#
# Example:
# Input: moves = "L_RL__R"
# Output: 3
# Explanation: The furthest point we can reach from the origin 0 is point -3 through the following sequence of moves "LLRLLLR".
#
# Constraints:
# 1 <= moves.length == n <= 50
# 	moves consists only of characters 'L', 'R' and '_'.
#

class Solution(object):
    def furthestDistanceFromOrigin(self, moves):
        """
        :type moves: str
        :rtype: int
        """
        left_moves = moves.count('L')
        right_moves = moves.count('R')
        flexible_moves = moves.count('_')
        
        # The furthest distance is achieved by using all flexible moves in the direction of the side with more fixed moves
        if left_moves > right_moves:
            return left_moves + flexible_moves - right_moves
        else:
            return right_moves + flexible_moves - left_moves