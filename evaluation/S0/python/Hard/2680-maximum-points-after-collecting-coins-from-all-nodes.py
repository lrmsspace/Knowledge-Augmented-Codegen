# Source: https://leetcode.com/problems/maximum-points-after-collecting-coins-from-all-nodes/   |   Difficulty: Hard
#
# Problem Description:
# There exists an undirected tree rooted at node 0 with n nodes labeled from 0 to n - 1. You are given a 2D integer array edges of length n - 1, where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree. You are also given a 0-indexed array coins of size n where coins[i] indicates the number of coins in the vertex i, and an integer k.
#
# Starting from the root, you have to collect all the coins such that the coins at a node can only be collected if the coins of its ancestors have been already collected.
#
# Coins at nodei can be collected in one of the following ways:
#
#
# 	Collect all the coins, but you will get coins[i] - k points. If coins[i] - k is negative then you will lose abs(coins[i] - k) points.
# 	Collect all the coins, but you will get floor(coins[i] / 2) points. If this way is used, then for all the nodej present in the subtree of nodei, coins[j] will get reduced to floor(coins[j] / 2).
#
#
# Return the maximum points you can get after collecting the coins from all the tree nodes.
#
# Example:
# Input: edges = [[0,1],[1,2],[2,3]], coins = [10,10,3,3], k = 5
# Output: 11                        
# Explanation: 
# Collect all the coins from node 0 using the first way. Total points = 10 - 5 = 5.
# Collect all the coins from node 1 using the first way. Total points = 5 + (10 - 5) = 10.
# Collect all the coins from node 2 using the second way so coins left at node 3 will be floor(3 / 2) = 1. Total points = 10 + floor(3 / 2) = 11.
# Collect all the coins from node 3 using the second way. Total points = 11 + floor(1 / 2) = 11.
# It can be shown that the maximum points we can get after collecting coins from all the nodes is 11.
#
# Constraints:
# n == coins.length
# 	2 <= n <= 105
# 	0 <= coins[i] <= 104
# 	edges.length == n - 1
# 	0 <= edges[i][0], edges[i][1] < n
# 	0 <= k <= 104
#

class Solution(object):
    def maximumPoints(self, edges, coins, k):
        """
        :type edges: List[List[int]]
        :type coins: List[int]
        :type k: int
        :rtype: int
        """
        from collections import defaultdict, deque
        n = len(coins)
        tree = defaultdict(list)
        for u, v in edges:
            tree[u].append(v)
            tree[v].append(u)

        parent = [-1] * n
        depth = [0] * n
        q = deque([0])
        order = []
        while q:
            node = q.popleft()
            order.append(node)
            for nei in tree[node]:
                if nei != parent[node]:
                    parent[nei] = node
                    depth[nei] = depth[node] + 1
                    q.append(nei)

        dp = [[0, 0] for _ in range(n)]
        for node in reversed(order):
            dp[node][0] += max(coins[node] - k, 0)
            dp[node][1] += coins[node] // 2
            for nei in tree[node]:
                if nei != parent[node]:
                    dp[node][0] += max(dp[nei][0], dp[nei][1])
                    dp[node][1] += dp[nei][1]

        return max(dp[0][0], dp[0][1])