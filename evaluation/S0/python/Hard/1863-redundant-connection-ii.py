# Source: https://leetcode.com/problems/redundant-connection-ii/   |   Difficulty: Hard
#
# Problem Description:
# In this problem, a rooted tree is a directed graph such that, there is exactly one node (the root) for which all other nodes are descendants of this node, plus every node has exactly one parent, except for the root node which has no parents.
#
# The given input is a directed graph that started as a rooted tree with n nodes (with distinct values from 1 to n), with one additional directed edge added. The added edge has two different vertices chosen from 1 to n, and was not an edge that already existed.
#
# The resulting graph is given as a 2D-array of edges. Each element of edges is a pair [ui, vi] that represents a directed edge connecting nodes ui and vi, where ui is a parent of child vi.
#
# Return an edge that can be removed so that the resulting graph is a rooted tree of n nodes. If there are multiple answers, return the answer that occurs last in the given 2D-array.
#
# Example:
# Input: edges = [[1,2],[1,3],[2,3]]
# Output: [2,3]
#
# Constraints:
# n == edges.length
# 	3 <= n <= 1000
# 	edges[i].length == 2
# 	1 <= ui, vi <= n
# 	ui != vi
#

class Solution(object):
    def findRedundantDirectedConnection(self, edges):
        """
        :type edges: List[List[int]]
        :rtype: List[int]
        """
        parent = {}
        candA = None
        candB = None

        for u, v in edges:
            if v in parent:
                candA = [parent[v], v]
                candB = [u, v]
                break
            parent[v] = u

        def find(u):
            while u in parent:
                u = parent[u]
            return u

        for u, v in edges:
            if [u, v] == candB:
                continue
            pu = find(u)
            pv = find(v)
            if pu == pv:
                if candA:
                    return candA
                return [u, v]
            parent[v] = u

        return candB