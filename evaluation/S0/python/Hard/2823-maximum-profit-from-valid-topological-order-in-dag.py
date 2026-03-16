# Source: https://leetcode.com/problems/maximum-profit-from-valid-topological-order-in-dag/   |   Difficulty: Hard
#
# Problem Description:
# You are given a Directed Acyclic Graph (DAG) with n nodes labeled from 0 to n - 1, represented by a 2D array edges, where edges[i] = [ui, vi] indicates a directed edge from node ui to vi. Each node has an associated score given in an array score, where score[i] represents the score of node i.
#
# You must process the nodes in a valid topological order. Each node is assigned a 1-based position in the processing order.
#
# The profit is calculated by summing up the product of each node's score and its position in the ordering.
#
# Return the maximum possible profit achievable with an optimal topological order.
#
# A topological order of a DAG is a linear ordering of its nodes such that for every directed edge u → v, node u comes before v in the ordering.
#
# Example:
# Input: n = 2, edges = [[0,1]], score = [2,3]
#
# Output: 8
#
# Explanation:
#
#
#
# Node 1 depends on node 0, so a valid order is [0, 1].
#
#
# 	
# 		
# 			Node
# 			Processing Order
# 			Score
# 			Multiplier
# 			Profit Calculation
# 		
# 	
# 	
# 		
# 			0
# 			1st
# 			2
# 			1
# 			2 × 1 = 2
# 		
# 		
# 			1
# 			2nd
# 			3
# 			2
# 			3 × 2 = 6
# 		
# 	
#
#
# The maximum total profit achievable over all valid topological orders is 2 + 6 = 8.
#
# Constraints:
# 1 <= n == score.length <= 22
# 	1 <= score[i] <= 105
# 	0 <= edges.length <= n * (n - 1) / 2
# 	edges[i] == [ui, vi] denotes a directed edge from ui to vi.
# 	0 <= ui, vi < n
# 	ui != vi
# 	The input graph is guaranteed to be a DAG.
# 	There are no duplicate edges.
#

class Solution(object):
    def maxProfit(self, n, edges, score):
        """
        :type n: int
        :type edges: List[List[int]]
        :type score: List[int]
        :rtype: int
        """
        from collections import defaultdict

        graph = defaultdict(list)
        in_degree = [0] * n
        for u, v in edges:
            graph[u].append(v)
            in_degree[v] += 1

        dp = {}
        def dfs(mask, position):
            if mask == (1 << n) - 1:
                return 0
            if (mask, position) in dp:
                return dp[(mask, position)]

            max_profit = 0
            for node in range(n):
                if (mask & (1 << node)) == 0 and in_degree[node] == 0:
                    for neighbor in graph[node]:
                        in_degree[neighbor] -= 1
                    profit = score[node] * position + dfs(mask | (1 << node), position + 1)
                    max_profit = max(max_profit, profit)
                    for neighbor in graph[node]:
                        in_degree[neighbor] += 1

            dp[(mask, position)] = max_profit
            return max_profit

        return dfs(0, 1)