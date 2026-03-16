# Source: https://leetcode.com/problems/maximize-grid-happiness/   |   Difficulty: Hard
#
# Problem Description:
# You are given four integers, m, n, introvertsCount, and extrovertsCount. You have an m x n grid, and there are two types of people: introverts and extroverts. There are introvertsCount introverts and extrovertsCount extroverts.
#
# You should decide how many people you want to live in the grid and assign each of them one grid cell. Note that you do not have to have all the people living in the grid.
#
# The happiness of each person is calculated as follows:
#
#
# 	Introverts start with 120 happiness and lose 30 happiness for each neighbor (introvert or extrovert).
# 	Extroverts start with 40 happiness and gain 20 happiness for each neighbor (introvert or extrovert).
#
#
# Neighbors live in the directly adjacent cells north, east, south, and west of a person's cell.
#
# The grid happiness is the sum of each person's happiness. Return the maximum possible grid happiness.
#
# Example:
# Input: m = 2, n = 3, introvertsCount = 1, extrovertsCount = 2
# Output: 240
# Explanation: Assume the grid is 1-indexed with coordinates (row, column).
# We can put the introvert in cell (1,1) and put the extroverts in cells (1,3) and (2,3).
# - Introvert at (1,1) happiness: 120 (starting happiness) - (0 * 30) (0 neighbors) = 120
# - Extrovert at (1,3) happiness: 40 (starting happiness) + (1 * 20) (1 neighbor) = 60
# - Extrovert at (2,3) happiness: 40 (starting happiness) + (1 * 20) (1 neighbor) = 60
# The grid happiness is 120 + 60 + 60 = 240.
# The above figure shows the grid in this example with each person's happiness. The introvert stays in the light green cell while the extroverts live on the light purple cells.
#
# Constraints:
# 1 <= m, n <= 5
# 	0 <= introvertsCount, extrovertsCount <= min(m * n, 6)
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
    def getMaxGridHappiness(self, m, n, introvertsCount, extrovertsCount):
        """
        :type m: int
        :type n: int
        :type introvertsCount: int
        :type extrovertsCount: int
        :rtype: int
        """
        from functools import lru_cache
        
        # Define the happiness values for introverts and extroverts
        INTROVERT_HAPPINESS = 120
        EXTROVERT_HAPPINESS = 40
        NEIGHBOR_EFFECT = 30
        
        # Total number of cells in the grid
        total_cells = m * n
        
        @lru_cache(maxsize=None)
        def dfs(pos, introverts_left, extroverts_left, grid_state):
            if pos == total_cells:
                return 0
            
            max_happiness = dfs(pos + 1, introverts_left, extroverts_left, grid_state)  # Skip this cell
            
            row, col = divmod(pos, n)
            neighbors = []
            if row > 0:  # Up
                neighbors.append(grid_state[pos - n])
            if col > 0:  # Left
                neighbors.append(grid_state[pos - 1])
            
            # Try placing an introvert
            if introverts_left > 0:
                happiness = INTROVERT_HAPPINESS
                for neighbor in neighbors:
                    if neighbor == 1:  # Neighbor is an introvert
                        happiness -= NEIGHBOR_EFFECT
                    elif neighbor == 2:  # Neighbor is an extrovert
                        happiness -= NEIGHBOR_EFFECT
                
                max_happiness = max(max_happiness, happiness + dfs(pos + 1, introverts_left - 1, extroverts_left, grid_state + (1,)))
            
            # Try placing an extrovert
            if extroverts_left > 0:
                happiness = EXTROVERT_HAPPINESS
                for neighbor in neighbors:
                    if neighbor == 1:  # Neighbor is an introvert
                        happiness += NEIGHBOR_EFFECT
                    elif neighbor == 2:  # Neighbor is an extrovert
                        happiness += NEIGHBOR_EFFECT
                
                max_happiness = max(max_happiness, happiness + dfs(pos + 1, introverts_left, extroverts_left - 1, grid_state + (2,)))
            
            return max_happiness
        
        return dfs(0, introvertsCount, extrovertsCount, ())