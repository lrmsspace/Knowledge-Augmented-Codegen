# Source: https://leetcode.com/problems/add-edges-to-make-degrees-of-all-nodes-even/   |   Difficulty: Hard
#
# Problem Description:
# There is an undirected graph consisting of n nodes numbered from 1 to n. You are given the integer n and a 2D array edges where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi. The graph can be disconnected.
#
# You can add at most two additional edges (possibly none) to this graph so that there are no repeated edges and no self-loops.
#
# Return true if it is possible to make the degree of each node in the graph even, otherwise return false.
#
# The degree of a node is the number of edges connected to it.
#
# Example:
# Input: n = 5, edges = [[1,2],[2,3],[3,4],[4,2],[1,4],[2,5]]
# Output: true
# Explanation: The above diagram shows a valid way of adding an edge.
# Every node in the resulting graph is connected to an even number of edges.
#
# Constraints:
# 3 <= n <= 105
# 	2 <= edges.length <= 105
# 	edges[i].length == 2
# 	1 <= ai, bi <= n
# 	ai != bi
# 	There are no repeated edges.
#

class Solution(object):
    def isPossible(self, n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: bool
        """
        from collections import defaultdict
        graph = defaultdict(set)
        degree = [0] * (n + 1)

        for u, v in edges:
            graph[u].add(v)
            graph[v].add(u)
            degree[u] += 1
            degree[v] += 1

        odd_nodes = [i for i in range(1, n + 1) if degree[i] % 2 == 1]

        if len(odd_nodes) == 0:
            return True
        elif len(odd_nodes) == 2:
            u, v = odd_nodes
            if v not in graph[u]:
                return True
            for i in range(1, n + 1):
                if i != u and i != v and i not in graph[u] and i not in graph[v]:
                    return True
            return False
        elif len(odd_nodes) == 4:
            a, b, c, d = odd_nodes
            pairs = [(a, b), (c, d)], [(a, c), (b, d)], [(a, d), (b, c)]
            for pair1, pair2 in pairs:
                if pair1[1] not in graph[pair1[0]] and pair2[1] not in graph[pair2[0]]:
                    return True
            return False
        else:
            return False