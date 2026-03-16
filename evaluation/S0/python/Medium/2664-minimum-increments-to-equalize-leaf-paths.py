# Source: https://leetcode.com/problems/minimum-increments-to-equalize-leaf-paths/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer n and an undirected tree rooted at node 0 with n nodes numbered from 0 to n - 1. This is represented by a 2D array edges of length n - 1, where edges[i] = [ui, vi] indicates an edge from node ui to vi .
#
# Each node i has an associated cost given by cost[i], representing the cost to traverse that node.
#
# The score of a path is defined as the sum of the costs of all nodes along the path.
#
# Your goal is to make the scores of all root-to-leaf paths equal by increasing the cost of any number of nodes by any non-negative amount.
#
# Return the minimum number of nodes whose cost must be increased to make all root-to-leaf path scores equal.
#
# Example:
# Input: n = 3, edges = [[0,1],[0,2]], cost = [2,1,3]
#
# Output: 1
#
# Explanation:
#
#
#
# There are two root-to-leaf paths:
#
#
# 	Path 0 → 1 has a score of 2 + 1 = 3.
# 	Path 0 → 2 has a score of 2 + 3 = 5.
#
#
# To make all root-to-leaf path scores equal to 5, increase the cost of node 1 by 2.
# Only one node is increased, so the output is 1.
#
# Constraints:
# 2 <= n <= 105
# 	edges.length == n - 1
# 	edges[i] == [ui, vi]
# 	0 <= ui, vi < n
# 	cost.length == n
# 	1 <= cost[i] <= 109
# 	The input is generated such that edges represents a valid tree.
#

class Solution(object):
    def minIncrease(self, n, edges, cost):
        """
        :type n: int
        :type edges: List[List[int]]
        :type cost: List[int]
        :rtype: int
        """
        from collections import defaultdict
        
        tree = defaultdict(list)
        for u, v in edges:
            tree[u].append(v)
            tree[v].append(u)
        
        max_path_sum = 0
        increments = 0
        
        def dfs(node, parent):
            nonlocal max_path_sum, increments
            if len(tree[node]) == 1 and node != 0:  # Leaf node
                return cost[node]
            
            current_max = 0
            for neighbor in tree[node]:
                if neighbor != parent:
                    path_sum = dfs(neighbor, node)
                    current_max = max(current_max, path_sum)
            
            for neighbor in tree[node]:
                if neighbor != parent:
                    path_sum = dfs(neighbor, node)
                    increments += current_max - path_sum
            
            return current_max + cost[node]
        
        total_path_sum = dfs(0, -1)
        max_path_sum = total_path_sum
        
        return increments