# Source: https://leetcode.com/problems/remove-colored-pieces-if-both-neighbors-are-the-same-color/   |   Difficulty: Medium
#
# Problem Description:
# There are n pieces arranged in a line, and each piece is colored either by 'A' or by 'B'. You are given a string colors of length n where colors[i] is the color of the ith piece.
#
# Alice and Bob are playing a game where they take alternating turns removing pieces from the line. In this game, Alice moves first.
#
#
# 	Alice is only allowed to remove a piece colored 'A' if both its neighbors are also colored 'A'. She is not allowed to remove pieces that are colored 'B'.
# 	Bob is only allowed to remove a piece colored 'B' if both its neighbors are also colored 'B'. He is not allowed to remove pieces that are colored 'A'.
# 	Alice and Bob cannot remove pieces from the edge of the line.
# 	If a player cannot make a move on their turn, that player loses and the other player wins.
#
#
# Assuming Alice and Bob play optimally, return true if Alice wins, or return false if Bob wins.
#
# Example:
# Input: colors = "AAABABB"
# Output: true
# Explanation:
# AAABABB -> AABABB
# Alice moves first.
# She removes the second 'A' from the left since that is the only 'A' whose neighbors are both 'A'.
#
# Now it's Bob's turn.
# Bob cannot make a move on his turn since there are no 'B's whose neighbors are both 'B'.
# Thus, Alice wins, so return true.
#
# Constraints:
# 1 <= colors.length <= 105
# 	colors consists of only the letters 'A' and 'B'
#

class Solution(object):
    def winnerOfGame(self, colors):
        """
        :type colors: str
        :rtype: bool
        """
        a_moves = 0
        b_moves = 0
        n = len(colors)
        
        for i in range(1, n - 1):
            if colors[i] == 'A' and colors[i - 1] == 'A' and colors[i + 1] == 'A':
                a_moves += 1
            elif colors[i] == 'B' and colors[i - 1] == 'B' and colors[i + 1] == 'B':
                b_moves += 1
        
        return a_moves > b_moves