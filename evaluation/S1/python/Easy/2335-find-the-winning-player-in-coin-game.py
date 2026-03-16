# Source: https://leetcode.com/problems/find-the-winning-player-in-coin-game/   |   Difficulty: Easy
#
# Problem Description:
# You are given two positive integers x and y, denoting the number of coins with values 75 and 10 respectively.
#
# Alice and Bob are playing a game. Each turn, starting with Alice, the player must pick up coins with a total value 115. If the player is unable to do so, they lose the game.
#
# Return the name of the player who wins the game if both players play optimally.
#
# Example:
# Input: x = 2, y = 7
#
# Output: "Alice"
#
# Explanation:
#
# The game ends in a single turn:
#
#
# 	Alice picks 1 coin with a value of 75 and 4 coins with a value of 10.
#
# Constraints:
# 1 <= x, y <= 100
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
    def winningPlayer(self, x, y):
        """
        :type x: int
        :type y: int
        :rtype: str
        """
        # 每轮需要 115 的硬币组合
        # 优先使用 75 的硬币，因为它们价值更高
        while True:
            # Alice's turn
            if x > 0 and y >= 4:
                x -= 1
                y -= 4
            elif y >= 11:
                y -= 11
            else:
                return "Bob"

            # Bob's turn
            if x > 0 and y >= 4:
                x -= 1
                y -= 4
            elif y >= 11:
                y -= 11
            else:
                return "Alice"