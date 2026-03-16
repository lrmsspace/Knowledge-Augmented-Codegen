# Source: https://leetcode.com/problems/number-of-good-paths/   |   Difficulty: Hard
#
# Problem Description:
# There is a tree (i.e. a connected, undirected graph with no cycles) consisting of n nodes numbered from 0 to n - 1 and exactly n - 1 edges.
#
# You are given a 0-indexed integer array vals of length n where vals[i] denotes the value of the ith node. You are also given a 2D integer array edges where edges[i] = [ai, bi] denotes that there exists an undirected edge connecting nodes ai and bi.
#
# A good path is a simple path that satisfies the following conditions:
#
#
# 	The starting node and the ending node have the same value.
# 	All nodes between the starting node and the ending node have values less than or equal to the starting node (i.e. the starting node's value should be the maximum value along the path).
#
#
# Return the number of distinct good paths.
#
# Note that a path and its reverse are counted as the same path. For example, 0 -> 1 is considered to be the same as 1 -> 0. A single node is also considered as a valid path.
#
# Example:
# Input: vals = [1,3,2,1,3], edges = [[0,1],[0,2],[2,3],[2,4]]
# Output: 6
# Explanation: There are 5 good paths consisting of a single node.
# There is 1 additional good path: 1 -> 0 -> 2 -> 4.
# (The reverse path 4 -> 2 -> 0 -> 1 is treated as the same as 1 -> 0 -> 2 -> 4.)
# Note that 0 -> 2 -> 3 is not a good path because vals[2] > vals[0].
#
# Constraints:
# n == vals.length
# 	1 <= n <= 3 * 104
# 	0 <= vals[i] <= 105
# 	edges.length == n - 1
# 	edges[i].length == 2
# 	0 <= ai, bi < n
# 	ai != bi
# 	edges represents a valid tree.
#

class Solution(object):
    def numberOfGoodPaths(self, vals, edges):
        """
        :type vals: List[int]
        :type edges: List[List[int]]
        :rtype: int
        """
        from collections import defaultdict

        n = len(vals)
        adj = [[] for _ in range(n)]
        for u, v in edges:
            adj[u].append(v)
            adj[v].append(u)

        parent = list(range(n)))
        size = [1] * n

        def find(x):
            while parent[x] != x:
                parent[x] = parent[parent[x]]
                x = parent[x]
            return x

        def union(x, y):
            rootX = find(x)
            rootY = find(y)
            if rootX != rootY:
                if size[rootX] < size[rootY]:
                    rootX, rootY = rootY, rootX
                parent[rootY] = rootX
                size[rootX] += size[rootY]

        value_to_nodes = defaultdict(list)
        for i, val in enumerate(vals):
            value_to_nodes[val].append(i)

        result = 0
        for val in sorted(value_to_nodes.keys()):
            nodes = value_to_nodes[val]
            for node in nodes:
                for neighbor in adj[node]:
                    if vals[neighbor] <= val:
                        union(node, neighbor)

            group_count = defaultdict(int)
            for node in nodes:
                root = find(node)
                group_count[root] += 1

            for count in group_count.values():
                result += count * (count + 1) // 2

        return result