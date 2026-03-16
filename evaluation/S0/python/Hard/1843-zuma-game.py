# Source: https://leetcode.com/problems/zuma-game/   |   Difficulty: Hard
#
# Problem Description:
# You are playing a variation of the game Zuma.
#
# In this variation of Zuma, there is a single row of colored balls on a board, where each ball can be colored red 'R', yellow 'Y', blue 'B', green 'G', or white 'W'. You also have several colored balls in your hand.
#
# Your goal is to clear all of the balls from the board. On each turn:
#
#
# 	Pick any ball from your hand and insert it in between two balls in the row or on either end of the row.
# 	If there is a group of three or more consecutive balls of the same color, remove the group of balls from the board.
# 	
# 		If this removal causes more groups of three or more of the same color to form, then continue removing each group until there are none left.
# 	
# 	
# 	If there are no more balls on the board, then you win the game.
# 	Repeat this process until you either win or do not have any more balls in your hand.
#
#
# Given a string board, representing the row of balls on the board, and a string hand, representing the balls in your hand, return the minimum number of balls you have to insert to clear all the balls from the board. If you cannot clear all the balls from the board using the balls in your hand, return -1.
#
# Example:
# Input: board = "WRRBBW", hand = "RB"
# Output: -1
# Explanation: It is impossible to clear all the balls. The best you can do is:
# - Insert 'R' so the board becomes WRRRBBW. WRRRBBW -> WBBW.
# - Insert 'B' so the board becomes WBBBW. WBBBW -> WW.
# There are still balls remaining on the board, and you are out of balls to insert.
#
# Constraints:
# 1 <= board.length <= 16
# 	1 <= hand.length <= 5
# 	board and hand consist of the characters 'R', 'Y', 'B', 'G', and 'W'.
# 	The initial row of balls on the board will not have any groups of three or more consecutive balls of the same color.
#

class Solution(object):
    def findMinStep(self, board, hand):
        """
        :type board: str
        :type hand: str
        :rtype: int
        """
        from collections import Counter

        def remove_consecutive(s):
            i = 0
            while i < len(s):
                j = i
                while j < len(s) and s[j] == s[i]:
                    j += 1
                if j - i >= 3:
                    return remove_consecutive(s[:i] + s[j:])
                else:
                    i = j
            return s

        def dfs(board, hand_count):
            board = remove_consecutive(board)
            if not board:
                return 0
            if all(count == 0 for count in hand_count.values()):
                return float('inf')

            min_steps = float('inf')
            for i in range(len(board) + 1):
                for color in hand_count:
                    if hand_count[color] > 0:
                        new_board = board[:i] + color + board[i:]
                        hand_count[color] -= 1
                        steps = dfs(new_board, hand_count)
                        if steps != float('inf'):
                            min_steps = min(min_steps, steps + 1)
                        hand_count[color] += 1
            return min_steps

        hand_count = Counter(hand)
        result = dfs(board, hand_count)
        return result if result != float('inf') else -1