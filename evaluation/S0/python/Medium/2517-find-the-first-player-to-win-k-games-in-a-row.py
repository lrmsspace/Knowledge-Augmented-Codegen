# Source: https://leetcode.com/problems/find-the-first-player-to-win-k-games-in-a-row/   |   Difficulty: Medium
#
# Problem Description:
# A competition consists of n players numbered from 0 to n - 1.
#
# You are given an integer array skills of size n and a positive integer k, where skills[i] is the skill level of player i. All integers in skills are unique.
#
# All players are standing in a queue in order from player 0 to player n - 1.
#
# The competition process is as follows:
#
#
# 	The first two players in the queue play a game, and the player with the higher skill level wins.
# 	After the game, the winner stays at the beginning of the queue, and the loser goes to the end of it.
#
#
# The winner of the competition is the first player who wins k games in a row.
#
# Return the initial index of the winning player.
#
# Example:
# Input: skills = [4,2,6,3,9], k = 2
#
# Output: 2
#
# Explanation:
#
# Initially, the queue of players is [0,1,2,3,4]. The following process happens:
#
#
# 	Players 0 and 1 play a game, since the skill of player 0 is higher than that of player 1, player 0 wins. The resulting queue is [0,2,3,4,1].
# 	Players 0 and 2 play a game, since the skill of player 2 is higher than that of player 0, player 2 wins. The resulting queue is [2,3,4,1,0].
# 	Players 2 and 3 play a game, since the skill of player 2 is higher than that of player 3, player 2 wins. The resulting queue is [2,4,1,0,3].
#
#
# Player 2 won k = 2 games in a row, so the winner is player 2.
#
# Constraints:
# n == skills.length
# 	2 <= n <= 105
# 	1 <= k <= 109
# 	1 <= skills[i] <= 106
# 	All integers in skills are unique.
#

class Solution(object):
    def findWinningPlayer(self, skills, k):
        """
        :type skills: List[int]
        :type k: int
        :rtype: int
        """
        from collections import deque

        n = len(skills)
        queue = deque(range(n))
        win_count = [0] * n

        while True:
            player1 = queue.popleft()
            player2 = queue.popleft()

            if skills[player1] > skills[player2]:
                winner, loser = player1, player2
            else:
                winner, loser = player2, player1

            win_count[winner] += 1
            queue.appendleft(winner)
            queue.append(loser)

            if win_count[winner] == k:
                return winner