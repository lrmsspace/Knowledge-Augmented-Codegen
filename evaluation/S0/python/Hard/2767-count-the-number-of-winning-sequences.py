# Source: https://leetcode.com/problems/count-the-number-of-winning-sequences/   |   Difficulty: Hard
#
# Problem Description:
# Alice and Bob are playing a fantasy battle game consisting of n rounds where they summon one of three magical creatures each round: a Fire Dragon, a Water Serpent, or an Earth Golem. In each round, players simultaneously summon their creature and are awarded points as follows:
#
#
# 	If one player summons a Fire Dragon and the other summons an Earth Golem, the player who summoned the Fire Dragon is awarded a point.
# 	If one player summons a Water Serpent and the other summons a Fire Dragon, the player who summoned the Water Serpent is awarded a point.
# 	If one player summons an Earth Golem and the other summons a Water Serpent, the player who summoned the Earth Golem is awarded a point.
# 	If both players summon the same creature, no player is awarded a point.
#
#
# You are given a string s consisting of n characters 'F', 'W', and 'E', representing the sequence of creatures Alice will summon in each round:
#
#
# 	If s[i] == 'F', Alice summons a Fire Dragon.
# 	If s[i] == 'W', Alice summons a Water Serpent.
# 	If s[i] == 'E', Alice summons an Earth Golem.
#
#
# Bob’s sequence of moves is unknown, but it is guaranteed that Bob will never summon the same creature in two consecutive rounds. Bob beats Alice if the total number of points awarded to Bob after n rounds is strictly greater than the points awarded to Alice.
#
# Return the number of distinct sequences Bob can use to beat Alice.
#
# Since the answer may be very large, return it modulo 109 + 7.
#
# Example:
# Input: s = "FFF"
#
# Output: 3
#
# Explanation:
#
# Bob can beat Alice by making one of the following sequences of moves: "WFW", "FWF", or "WEW". Note that other winning sequences like "WWE" or "EWW" are invalid since Bob cannot make the same move twice in a row.
#
# Constraints:
# 1 <= s.length <= 1000
# 	s[i] is one of 'F', 'W', or 'E'.
#

class Solution(object):
    def countWinningSequences(self, s):
        """
        :type s: str
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(s)
        
        # dp[i][j][k]: number of ways up to round i, with j points for Bob, k points for Alice
        dp = [[[0] * (n + 1) for _ in range(n + 1)] for _ in range(n + 1)]
        dp[0][0][0] = 1
        
        for i in range(n):
            for j in range(n + 1):
                for k in range(n + 1):
                    if dp[i][j][k] == 0:
                        continue
                    
                    for bob_move in 'FWE':
                        if i > 0 and bob_move == s[i - 1]:
                            continue
                        
                        alice_move = s[i]
                        
                        if (bob_move == 'F' and alice_move == 'E') or \
                           (bob_move == 'W' and alice_move == 'F') or \
                           (bob_move == 'E' and alice_move == 'W'):
                            dp[i + 1][j + 1][k] = (dp[i + 1][j + 1][k] + dp[i][j][k]) % MOD
                        elif (alice_move == 'F' and bob_move == 'E') or \
                             (alice_move == 'W' and bob_move == 'F') or \
                             (alice_move == 'E' and bob_move == 'W'):
                            dp[i + 1][j][k + 1] = (dp[i + 1][j][k + 1] + dp[i][j][k]) % MOD
                        else:
                            dp[i + 1][j][k] = (dp[i + 1][j][k] + dp[i][j][k]) % MOD

        result = 0
        for j in range(n + 1):
            for k in range(j):
                result = (result + dp[n][j][k]) % MOD
        return result   