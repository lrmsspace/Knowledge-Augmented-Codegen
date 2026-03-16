# Source: https://leetcode.com/problems/difference-between-maximum-and-minimum-price-sum/   |   Difficulty: Hard
#
# Problem Description:
# There exists an undirected and initially unrooted tree with n nodes indexed from 0 to n - 1. You are given the integer n and a 2D integer array edges of length n - 1, where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
#
# Each node has an associated price. You are given an integer array price, where price[i] is the price of the ith node.
#
# The price sum of a given path is the sum of the prices of all nodes lying on that path.
#
# The tree can be rooted at any node root of your choice. The incurred cost after choosing root is the difference between the maximum and minimum price sum amongst all paths starting at root.
#
# Return the maximum possible cost amongst all possible root choices.
#
# Example:
# Input: n = 6, edges = [[0,1],[1,2],[1,3],[3,4],[3,5]], price = [9,8,7,6,10,5]
# Output: 24
# Explanation: The diagram above denotes the tree after rooting it at node 2. The first part (colored in red) shows the path with the maximum price sum. The second part (colored in blue) shows the path with the minimum price sum.
# - The first path contains nodes [2,1,3,4]: the prices are [7,8,6,10], and the sum of the prices is 31.
# - The second path contains the node [2] with the price [7].
# The difference between the maximum and minimum price sum is 24. It can be proved that 24 is the maximum cost.
#
# Constraints:
# 1 <= n <= 105
# 	edges.length == n - 1
# 	0 <= ai, bi <= n - 1
# 	edges represents a valid tree.
# 	price.length == n
# 	1 <= price[i] <= 105
#

class Solution(object):
    def maxOutput(self, n, edges, price):
        """
        :type n: int
        :type edges: List[List[int]]
        :type price: List[int]
        :rtype: int
        """
        from collections import defaultdict

        tree = defaultdict(list)
        for u, v in edges:
            tree[u].append(v)
            tree[v].append(u)

        max_cost = 0

        def dfs(node, parent):
            nonlocal max_cost
            max1, max2 = 0, 0

            for child in tree[node]:
                if child != parent:
                    child_max = dfs(child, node)
                    if child_max > max1:
                        max2 = max1
                        max1 = child_max
                    elif child_max > max2:
                        max2 = child_max

            max_cost = max(max_cost, max1 + max2 + price[node])
            return max1 + price[node]

        dfs(0, -1)
        return max_cost 