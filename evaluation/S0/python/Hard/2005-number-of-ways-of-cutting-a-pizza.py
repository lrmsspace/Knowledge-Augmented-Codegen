# Source: https://leetcode.com/problems/number-of-ways-of-cutting-a-pizza/   |   Difficulty: Hard
#
# Problem Description:
# Given a rectangular pizza represented as a rows x cols matrix containing the following characters: 'A' (an apple) and '.' (empty cell) and given the integer k. You have to cut the pizza into k pieces using k-1 cuts. 
#
# For each cut you choose the direction: vertical or horizontal, then you choose a cut position at the cell boundary and cut the pizza into two pieces. If you cut the pizza vertically, give the left part of the pizza to a person. If you cut the pizza horizontally, give the upper part of the pizza to a person. Give the last piece of pizza to the last person.
#
# Return the number of ways of cutting the pizza such that each piece contains at least one apple. Since the answer can be a huge number, return this modulo 10^9 + 7.
#
# Example:
# Input: pizza = ["A..","AAA","..."], k = 3
# Output: 3 
# Explanation: The figure above shows the three ways to cut the pizza. Note that pieces must contain at least one apple.
#
# Constraints:
# 1 <= rows, cols <= 50
# 	rows == pizza.length
# 	cols == pizza[i].length
# 	1 <= k <= 10
# 	pizza consists of characters 'A' and '.' only.
#

class Solution(object):
    def ways(self, pizza, k):
        """
        :type pizza: List[str]
        :type k: int
        :rtype: int
        """
        MOD = 10**9 + 7
        rows, cols = len(pizza), len(pizza[0])
        
        # Precompute the number of apples in the submatrix from (r, c) to bottom-right
        apples = [[0] * (cols + 1) for _ in range(rows + 1)]
        for r in range(rows - 1, -1, -1):
            for c in range(cols - 1, -1, -1):
                apples[r][c] = apples[r + 1][c] + apples[r][c + 1] - apples[r + 1][c + 1] + (1 if pizza[r][c] == 'A' else 0)
        
        # DP array: dp[cuts][r][c] = number of ways to cut pizza starting from (r, c) with 'cuts' cuts left
        dp = [[[0] * cols for _ in range(rows)] for _ in range(k)]
        
        # Base case: when there's only one piece left, check if it has at least one apple
        for r in range(rows):
            for c in range(cols):
                dp[0][r][c] = 1 if apples[r][c] > 0 else 0
        
        # Fill the DP table
        for cuts in range(1, k):
            for r in range(rows):
                for c in range(cols):
                    # Horizontal cuts
                    for nr in range(r + 1, rows):
                        if apples[r][c] - apples[nr][c] > 0:  # Upper piece has at least one apple
                            dp[cuts][r][c] = (dp[cuts][r][c] + dp[cuts - 1][nr][c]) % MOD
                    # Vertical cuts
                    for nc in range(c + 1, cols):
                        if apples[r][c] - apples[r][nc] > 0:  # Left piece has at least one apple
                            dp[cuts][r][c] = (dp[cuts][r][c] + dp[cuts - 1][r][nc]) % MOD
        
        return dp[k - 1][0][0]