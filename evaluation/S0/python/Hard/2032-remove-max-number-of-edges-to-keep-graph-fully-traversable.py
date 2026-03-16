# Source: https://leetcode.com/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/   |   Difficulty: Hard
#
# Problem Description:
# Alice and Bob have an undirected graph of n nodes and three types of edges:
#
#
# 	Type 1: Can be traversed by Alice only.
# 	Type 2: Can be traversed by Bob only.
# 	Type 3: Can be traversed by both Alice and Bob.
#
#
# Given an array edges where edges[i] = [typei, ui, vi] represents a bidirectional edge of type typei between nodes ui and vi, find the maximum number of edges you can remove so that after removing the edges, the graph can still be fully traversed by both Alice and Bob. The graph is fully traversed by Alice and Bob if starting from any node, they can reach all other nodes.
#
# Return the maximum number of edges you can remove, or return -1 if Alice and Bob cannot fully traverse the graph.
#
# Example:
# Input: n = 4, edges = [[3,1,2],[3,2,3],[1,1,3],[1,2,4],[1,1,2],[2,3,4]]
# Output: 2
# Explanation: If we remove the 2 edges [1,1,2] and [1,1,3]. The graph will still be fully traversable by Alice and Bob. Removing any additional edge will not make it so. So the maximum number of edges we can remove is 2.
#
# Constraints:
# 1 <= n <= 105
# 	1 <= edges.length <= min(105, 3 * n * (n - 1) / 2)
# 	edges[i].length == 3
# 	1 <= typei <= 3
# 	1 <= ui < vi <= n
# 	All tuples (typei, ui, vi) are distinct.
#

class Solution(object):
    def maxNumEdgesToRemove(self, n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: int
        """
        parentA = list(range(n))
        parentB = list(range(n))
        
        def find(parent, u):
            if parent[u] != u:
                parent[u] = find(parent, parent[u])
            return parent[u]
        
        def union(parent, u, v):
            pu, pv = find(parent, u), find(parent, v)
            if pu != pv:
                parent[pu] = pv
                return True
            return False
        
        edges.sort(key=lambda x: -x[0])
        
        used_edges = 0
        
        for t, u, v in edges:
            u -= 1
            v -= 1
            if t == 3:
                mergedA = union(parentA, u, v)
                mergedB = union(parentB, u, v)
                if mergedA or mergedB:
                    used_edges += 1
            elif t == 1:
                if union(parentA, u, v):
                    used_edges += 1
            else:  # t == 2
                if union(parentB, u, v):
                    used_edges += 1
        
        if len(set(find(parentA, i) for i in range(n))) > 1 or len(set(find(parentB, i) for i in range(n))) > 1:
            return -1
        return len(edges) - used_edges  