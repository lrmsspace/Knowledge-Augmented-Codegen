# Source: https://leetcode.com/problems/find-players-with-zero-or-one-losses/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array matches where matches[i] = [winneri, loseri] indicates that the player winneri defeated player loseri in a match.
#
# Return a list answer of size 2 where:
#
#
# 	answer[0] is a list of all players that have not lost any matches.
# 	answer[1] is a list of all players that have lost exactly one match.
#
#
# The values in the two lists should be returned in increasing order.
#
# Note:
#
#
# 	You should only consider the players that have played at least one match.
# 	The testcases will be generated such that no two matches will have the same outcome.
#
# Example:
# Input: matches = [[1,3],[2,3],[3,6],[5,6],[5,7],[4,5],[4,8],[4,9],[10,4],[10,9]]
# Output: [[1,2,10],[4,5,7,8]]
# Explanation:
# Players 1, 2, and 10 have not lost any matches.
# Players 4, 5, 7, and 8 each have lost one match.
# Players 3, 6, and 9 each have lost two matches.
# Thus, answer[0] = [1,2,10] and answer[1] = [4,5,7,8].
#
# Constraints:
# 1 <= matches.length <= 105
# 	matches[i].length == 2
# 	1 <= winneri, loseri <= 105
# 	winneri != loseri
# 	All matches[i] are unique.
#

class Solution(object):
    def findWinners(self, matches):
        """
        :type matches: List[List[int]]
        :rtype: List[List[int]]
        """
        from collections import defaultdict

        loss_count = defaultdict(int)
        players = set()

        for winner, loser in matches:
            players.add(winner)
            players.add(loser)
            loss_count[loser] += 1

        no_loss = []
        one_loss = []

        for player in players:
            if loss_count[player] == 0:
                no_loss.append(player)
            elif loss_count[player] == 1:
                one_loss.append(player)

        return [sorted(no_loss), sorted(one_loss)]