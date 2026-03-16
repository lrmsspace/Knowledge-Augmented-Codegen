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
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def winnerOfGame(self, colors):
        """
        :type colors: str
        :rtype: bool
        """
        a_moves = 0
        b_moves = 0
        count = 1
        
        for i in range(1, len(colors)):
            if colors[i] == colors[i - 1]:
                count += 1
            else:
                if colors[i - 1] == 'A' and count >= 3:
                    a_moves += count - 2
                elif colors[i - 1] == 'B' and count >= 3:
                    b_moves += count - 2
                count = 1
        
        if colors[-1] == 'A' and count >= 3:
            a_moves += count - 2
        elif colors[-1] == 'B' and count >= 3:
            b_moves += count - 2
        
        return a_moves > b_moves