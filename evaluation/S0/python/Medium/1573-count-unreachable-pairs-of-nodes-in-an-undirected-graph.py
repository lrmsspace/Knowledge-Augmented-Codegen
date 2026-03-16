# Source: https://leetcode.com/problems/count-unreachable-pairs-of-nodes-in-an-undirected-graph/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer n. There is an undirected graph with n nodes, numbered from 0 to n - 1. You are given a 2D integer array edges where edges[i] = [ai, bi] denotes that there exists an undirected edge connecting nodes ai and bi.
#
# Return the number of pairs of different nodes that are unreachable from each other.
#
# Example:
# Input: n = 3, edges = [[0,1],[0,2],[1,2]]
# Output: 0
# Explanation: There are no pairs of nodes that are unreachable from each other. Therefore, we return 0.
#
# Constraints:
# 1 <= n <= 105
# 	0 <= edges.length <= 2 * 105
# 	edges[i].length == 2
# 	0 <= ai, bi < n
# 	ai != bi
# 	There are no repeated edges.
#

class Solution(object):
    def countPairs(self, n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: int
        """
        parent = [i for i in range(n)]
        size = [1] * n

        def find(x):
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]

        def union(x, y):
            rootX = find(x)
            rootY = find(y)
            if rootX != rootY:
                if size[rootX] < size[rootY]:
                    rootX, rootY = rootY, rootX
                parent[rootY] = rootX
                size[rootX] += size[rootY]

        for a, b in edges:
            union(a, b)

        component_sizes = {}
        for i in range(n):
            root = find(i)
            if root not in component_sizes:
                component_sizes[root] = 0
            component_sizes[root] += 1

        total_pairs = n * (n - 1) // 2
        reachable_pairs = 0
        for comp_size in component_sizes.values():
            reachable_pairs += comp_size * (comp_size - 1) // 2

        return total_pairs - reachable_pairs