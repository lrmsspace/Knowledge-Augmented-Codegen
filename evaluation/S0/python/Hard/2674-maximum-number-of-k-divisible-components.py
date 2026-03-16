# Source: https://leetcode.com/problems/maximum-number-of-k-divisible-components/   |   Difficulty: Hard
#
# Problem Description:
# There is an undirected tree with n nodes labeled from 0 to n - 1. You are given the integer n and a 2D integer array edges of length n - 1, where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
#
# You are also given a 0-indexed integer array values of length n, where values[i] is the value associated with the ith node, and an integer k.
#
# A valid split of the tree is obtained by removing any set of edges, possibly empty, from the tree such that the resulting components all have values that are divisible by k, where the value of a connected component is the sum of the values of its nodes.
#
# Return the maximum number of components in any valid split.
#
# Example:
# Input: n = 5, edges = [[0,2],[1,2],[1,3],[2,4]], values = [1,8,1,4,4], k = 6
# Output: 2
# Explanation: We remove the edge connecting node 1 with 2. The resulting split is valid because:
# - The value of the component containing nodes 1 and 3 is values[1] + values[3] = 12.
# - The value of the component containing nodes 0, 2, and 4 is values[0] + values[2] + values[4] = 6.
# It can be shown that no other valid split has more than 2 connected components.
#
# Constraints:
# 1 <= n <= 3 * 104
# 	edges.length == n - 1
# 	edges[i].length == 2
# 	0 <= ai, bi < n
# 	values.length == n
# 	0 <= values[i] <= 109
# 	1 <= k <= 109
# 	Sum of values is divisible by k.
# 	The input is generated such that edges represents a valid tree.
#

class Solution(object):
    def maxKDivisibleComponents(self, n, edges, values, k):
        """
        :type n: int
        :type edges: List[List[int]]
        :type values: List[int]
        :type k: int
        :rtype: int
        """
        from collections import defaultdict

        tree = defaultdict(list)
        for u, v in edges:
            tree[u].append(v)
            tree[v].append(u)

        result = 0

        def dfs(node, parent):
            nonlocal result
            subtotal = values[node]
            for child in tree[node]:
                if child != parent:
                    subtotal += dfs(child, node)
            if subtotal % k == 0 and node != 0:
                result += 1
                return 0
            return subtotal

        dfs(0, -1)
        return result   