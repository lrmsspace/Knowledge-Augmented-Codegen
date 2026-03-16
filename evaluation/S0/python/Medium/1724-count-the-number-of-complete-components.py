# Source: https://leetcode.com/problems/count-the-number-of-complete-components/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer n. There is an undirected graph with n vertices, numbered from 0 to n - 1. You are given a 2D integer array edges where edges[i] = [ai, bi] denotes that there exists an undirected edge connecting vertices ai and bi.
#
# Return the number of complete connected components of the graph.
#
# A connected component is a subgraph of a graph in which there exists a path between any two vertices, and no vertex of the subgraph shares an edge with a vertex outside of the subgraph.
#
# A connected component is said to be complete if there exists an edge between every pair of its vertices.
#
# Example:
# Input: n = 6, edges = [[0,1],[0,2],[1,2],[3,4]]
# Output: 3
# Explanation: From the picture above, one can see that all of the components of this graph are complete.
#
# Constraints:
# 1 <= n <= 50
# 	0 <= edges.length <= n * (n - 1) / 2
# 	edges[i].length == 2
# 	0 <= ai, bi <= n - 1
# 	ai != bi
# 	There are no repeated edges.
#

class Solution(object):
    def countCompleteComponents(self, n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: int
        """
        parent = [i for i in range(n)]
        size = [1] * n
        edge_count = [0] * n

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
                edge_count[rootX] += edge_count[rootY]
            edge_count[rootX] += 1

        for a, b in edges:
            union(a, b)

        complete_components = 0
        for i in range(n):
            if parent[i] == i:
                expected_edges = size[i] * (size[i] - 1) // 2
                if edge_count[i] == expected_edges:
                    complete_components += 1

        return complete_components