# Source: https://leetcode.com/problems/painting-a-grid-with-three-different-colors/   |   Difficulty: Hard
#
# Problem Description:
# You are given two integers m and n. Consider an m x n grid where each cell is initially white. You can paint each cell red, green, or blue. All cells must be painted.
#
# Return the number of ways to color the grid with no two adjacent cells having the same color. Since the answer can be very large, return it modulo 109 + 7.
#
# Example:
# Input: m = 1, n = 1
# Output: 3
# Explanation: The three possible colorings are shown in the image above.
#
# Constraints:
# 1 <= m <= 5
# 	1 <= n <= 1000
#

class Solution(object):
    def colorTheGrid(self, m, n):
        """
        :type m: int
        :type n: int
        :rtype: int
        """
        MOD = 10**9 + 7
        
        def generate_states(m):
            states = []
            def backtrack(state):
                if len(state) == m:
                    states.append(tuple(state))
                    return
                for color in range(3):
                    if not state or state[-1] != color:
                        state.append(color)
                        backtrack(state)
                        state.pop()
            backtrack([])
            return states
        
        def valid_transition(s1, s2):
            for c1, c2 in zip(s1, s2):
                if c1 == c2:
                    return False
            return True
        
        states = generate_states(m)
        state_count = len(states)
        
        dp = [[0] * state_count for _ in range(n)]
        
        for j in range(state_count):
            dp[0][j] = 1
        
        for i in range(1, n):
            for j in range(state_count):
                for k in range(state_count):
                    if valid_transition(states[j], states[k]):
                        dp[i][j] = (dp[i][j] + dp[i-1][k]) % MOD
        
        return sum(dp[n-1]) % MOD