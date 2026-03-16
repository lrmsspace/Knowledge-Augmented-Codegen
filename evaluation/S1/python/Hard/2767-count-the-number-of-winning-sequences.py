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
    def countWinningSequences(self, s):
        """
        :type s: str
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(s)
        
        # dp[i][j] will store the number of ways Bob can win from round i to n-1
        # j represents the last creature Bob summoned (0: F, 1: W, 2: E)
        dp = [[0] * 3 for _ in range(n + 1)]
        
        # Base case: at the end of the rounds, Bob has won if he has more points than Alice
        for j in range(3):
            dp[n][j] = 1
        
        for i in range(n - 1, -1, -1):
            for j in range(3):
                # Calculate points for this round
                alice_creature = s[i]
                bob_creature = j
                
                alice_points = 0
                bob_points = 0
                
                if alice_creature == 'F':
                    if bob_creature == 2:  # E
                        alice_points += 1
                    elif bob_creature == 1:  # W
                        bob_points += 1
                elif alice_creature == 'W':
                    if bob_creature == 0:  # F
                        alice_points += 1
                    elif bob_creature == 2:  # E
                        bob_points += 1
                elif alice_creature == 'E':
                    if bob_creature == 1:  # W
                        alice_points += 1
                    elif bob_creature == 0:  # F
                        bob_points += 1
                # Bob can choose any creature different from j in the next round
                for next_bob_creature in range(3):
                    if next_bob_creature != bob_creature:
                        if bob_points > alice_points:
                            dp[i][j] = (dp[i][j] + dp[i + 1][next_bob_creature]) % MOD
        return sum(dp[0][j] for j in range(3)) % MOD    