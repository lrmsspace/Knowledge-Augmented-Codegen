# Source: https://leetcode.com/problems/paint-house-iii/   |   Difficulty: Hard
#
# Problem Description:
# There is a row of m houses in a small city, each house must be painted with one of the n colors (labeled from 1 to n), some houses that have been painted last summer should not be painted again.
#
# A neighborhood is a maximal group of continuous houses that are painted with the same color.
#
#
# 	For example: houses = [1,2,2,3,3,2,1,1] contains 5 neighborhoods [{1}, {2,2}, {3,3}, {2}, {1,1}].
#
#
# Given an array houses, an m x n matrix cost and an integer target where:
#
#
# 	houses[i]: is the color of the house i, and 0 if the house is not painted yet.
# 	cost[i][j]: is the cost of paint the house i with the color j + 1.
#
#
# Return the minimum cost of painting all the remaining houses in such a way that there are exactly target neighborhoods. If it is not possible, return -1.
#
# Example:
# Input: houses = [0,0,0,0,0], cost = [[1,10],[10,1],[10,1],[1,10],[5,1]], m = 5, n = 2, target = 3
# Output: 9
# Explanation: Paint houses of this way [1,2,2,1,1]
# This array contains target = 3 neighborhoods, [{1}, {2,2}, {1,1}].
# Cost of paint all houses (1 + 1 + 1 + 1 + 5) = 9.
#
# Constraints:
# m == houses.length == cost.length
# 	n == cost[i].length
# 	1 <= m <= 100
# 	1 <= n <= 20
# 	1 <= target <= m
# 	0 <= houses[i] <= n
# 	1 <= cost[i][j] <= 104
#
# Helpful references (internal KB):
# - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
#   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
#   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
#   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
#   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
#   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
# - Knuth's Optimization (array, interval, dp-2d)
#   • When to use: When a range DP problem has a recurrence of the form dp(i, j) = min_k [dp(i, k) + dp(k+1, j) + C(i, j)] and the optimal splitting points satisfy opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
#   • Idea: Knuth's Optimization is a technique to speed up certain dynamic programming problems on ranges from O(N^3) to O(N^2) time complexity. It applies when the optimal splitting point for a subproblem exhibits a monotonic property across adjacent subproblems.
#   • Invariants: dp[i][j] stores the minimum cost for the interval [i, j].; opt[i][j] stores the optimal split point k for interval [i, j].
#   • Tips: Verify the quadrangle inequality for the cost function C(i, j).; Ensure the optimal split points exhibit monotonicity: opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
#   • Pitfalls: Applying the optimization without rigorously verifying the monotonicity condition.; Incorrectly calculating the cost function C(i, j) or its properties.
# - Finding a negative cycle in the graph (graph, matrix, floyd-warshall)
#   • When to use: Use when you need to find if a negative cycle exists in a graph, especially when dealing with all-pairs shortest paths or when edge weights can be negative. It is suitable for dense graphs.
#   • Idea: The Floyd-Warshall algorithm can detect negative cycles by checking if any vertex has a negative distance to itself after all iterations. It computes all-pairs shortest paths in O(V^3) time.
#   • Invariants: After k iterations, dist[i][j] stores the shortest path from i to j using only intermediate vertices from 0 to k-1.; For any i, dist[i][i] remains 0 unless a negative cycle involving i is found.
#   • Tips: Initialize distance matrix with edge weights or infinity for non-existent edges.; Set dist[i][i] to 0 for all i initially.
#   • Pitfalls: Incorrect initialization of the distance matrix, especially dist[i][i].; Forgetting to check the main diagonal for negative values after computation.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minCost(self, houses, cost, m, n, target):
        """
        :type houses: List[int]
        :type cost: List[List[int]]
        :type m: int
        :type n: int
        :type target: int
        :rtype: int
        """
        # Step 1: Initialize the DP table
        dp = [[[float('inf')] * (target + 1) for _ in range(n + 1)] for _ in range(m + 1)]
        
        # Step 2: Base cases for the first house
        for color in range(1, n + 1):
            if houses[0] == 0:
                dp[1][color][1] = cost[0][color - 1]
            elif houses[0] == color:
                dp[1][color][1] = 0
        
        # Step 3: Fill the DP table
        for i in range(2, m + 1):
            for color in range(1, n + 1):
                for t in range(1, target + 1):
                    if houses[i - 1] != 0 and houses[i - 1] != color:
                        continue
                    paint_cost = cost[i - 1][color - 1] if houses[i - 1] == 0 else 0
                    for prev_color in range(1, n + 1):
                        if prev_color == color:
                            dp[i][color][t] = min(dp[i][color][t], dp[i - 1][prev_color][t] + paint_cost)
                        else:
                            dp[i][color][t] = min(dp[i][color][t], dp[i - 1][prev_color][t - 1] + paint_cost)
        
        # Step 4: Find the minimum cost among all colors for target neighborhoods
        min_cost = min(dp[m][color][target] for color in range(1, n + 1))
        return min_cost if min_cost != float('inf') else -1