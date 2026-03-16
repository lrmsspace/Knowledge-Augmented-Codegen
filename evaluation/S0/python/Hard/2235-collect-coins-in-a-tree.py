# Source: https://leetcode.com/problems/collect-coins-in-a-tree/   |   Difficulty: Hard
#
# Problem Description:
# There exists an undirected and unrooted tree with n nodes indexed from 0 to n - 1. You are given an integer n and a 2D integer array edges of length n - 1, where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree. You are also given an array coins of size n where coins[i] can be either 0 or 1, where 1 indicates the presence of a coin in the vertex i.
#
# Initially, you choose to start at any vertex in the tree. Then, you can perform the following operations any number of times: 
#
#
#  Collect all the coins that are at a distance of at most 2 from the current vertex, or
#  Move to any adjacent vertex in the tree.
#
#
# Find the minimum number of edges you need to go through to collect all the coins and go back to the initial vertex.
#
# Note that if you pass an edge several times, you need to count it into the answer several times.
#
# Example:
# Input: coins = [1,0,0,0,0,1], edges = [[0,1],[1,2],[2,3],[3,4],[4,5]]
# Output: 2
# Explanation: Start at vertex 2, collect the coin at vertex 0, move to vertex 3, collect the coin at vertex 5 then move back to vertex 2.
#
# Constraints:
# n == coins.length
#  1 <= n <= 3 * 104
#  0 <= coins[i] <= 1
#  edges.length == n - 1
#  edges[i].length == 2
#  0 <= ai, bi < n
#  ai != bi
#  edges represents a valid tree.
#

class Solution(object):
    def collectTheCoins(self, coins, edges):
        """
        :type coins: List[int]
        :type edges: List[List[int]]
        :rtype: int
        """
        from collections import defaultdict, deque

        n = len(coins)
        graph = defaultdict(list)
        degree = [0] * n

        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)
            degree[u] += 1
            degree[v] += 1

        # Step 1: Remove leaves without coins
        queue = deque()
        for i in range(n):
            if degree[i] == 1 and coins[i] == 0:
                queue.append(i)

        while queue:
            node = queue.popleft()
            degree[node] -= 1
            for neighbor in graph[node]:
                degree[neighbor] -= 1
                if degree[neighbor] == 1 and coins[neighbor] == 0:
                    queue.append(neighbor)

        # Step 2: Remove two layers of leaves
        for _ in range(2):
            queue = deque()
            for i in range(n):
                if degree[i] == 1:
                    queue.append(i)

            while queue:
                node = queue.popleft()
                degree[node] -= 1
                for neighbor in graph[node]:
                    degree[neighbor] -= 1

        # Count remaining edges
        remaining_edges = sum(degree) // 2
        return remaining_edges * 2