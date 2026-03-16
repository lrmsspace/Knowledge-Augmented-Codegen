# Source: https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/   |   Difficulty: Hard
#
# Problem Description:
# Given a weighted undirected connected graph with n vertices numbered from 0 to n - 1, and an array edges where edges[i] = [ai, bi, weighti] represents a bidirectional and weighted edge between nodes ai and bi. A minimum spanning tree (MST) is a subset of the graph's edges that connects all vertices without cycles and with the minimum possible total edge weight.
#
# Find all the critical and pseudo-critical edges in the given graph's minimum spanning tree (MST). An MST edge whose deletion from the graph would cause the MST weight to increase is called a critical edge. On the other hand, a pseudo-critical edge is that which can appear in some MSTs but not all.
#
# Note that you can return the indices of the edges in any order.
#
# Example:
# Input: n = 5, edges = [[0,1,1],[1,2,1],[2,3,2],[0,3,2],[0,4,3],[3,4,3],[1,4,6]]
# Output: [[0,1],[2,3,4,5]]
# Explanation: The figure above describes the graph.
# The following figure shows all the possible MSTs:
#
# Notice that the two edges 0 and 1 appear in all MSTs, therefore they are critical edges, so we return them in the first list of the output.
# The edges 2, 3, 4, and 5 are only part of some MSTs, therefore they are considered pseudo-critical edges. We add them to the second list of the output.
#
# Constraints:
# 2 <= n <= 100
# 	1 <= edges.length <= min(200, n * (n - 1) / 2)
# 	edges[i].length == 3
# 	0 <= ai < bi < n
# 	1 <= weighti <= 1000
# 	All pairs (ai, bi) are distinct.
#

class Solution(object):
    def findCriticalAndPseudoCriticalEdges(self, n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: List[List[int]]
        """
        def find(parent, x):
            if parent[x] != x:
                parent[x] = find(parent, parent[x])
            return parent[x]

        def union(parent, rank, x, y):
            rootX = find(parent, x)
            rootY = find(parent, y)
            if rootX != rootY:
                if rank[rootX] > rank[rootY]:
                    parent[rootY] = rootX
                elif rank[rootX] < rank[rootY]:
                    parent[rootX] = rootY
                else:
                    parent[rootY] = rootX
                    rank[rootX] += 1
                return True
            return False

        # Step 1: Sort edges by weight
        indexed_edges = [(weight, u, v, i) for i, (u, v, weight) in enumerate(edges)]
        indexed_edges.sort()

        # Function to calculate MST weight with optional inclusion/exclusion of an edge
        def kruskal(exclude_edge_index=None, include_edge=None):
            parent = list(range(n))
            rank = [0] * n
            total_weight = 0
            edges_used = 0

            # If there's an edge to include, add it first
            if include_edge is not None:
                weight, u, v, _ = include_edge
                if union(parent, rank, u, v):
                    total_weight += weight
                    edges_used += 1

            for weight, u, v, i in indexed_edges:
                if i == exclude_edge_index:
                    continue
                if union(parent, rank, u, v):
                    total_weight += weight
                    edges_used += 1
                    if edges_used == n - 1:
                        break

            if edges_used == n - 1:
                return total_weight
            else:
                return float('inf')

        # Step 2: Find the weight of the original MST
        original_mst_weight = kruskal()

        critical_edges = []
        pseudo_critical_edges = []

        # Step 3: Check each edge for critical and pseudo-critical status
        for weight, u, v, i in indexed_edges:
            # Check if edge is critical
            if kruskal(exclude_edge_index=i) > original_mst_weight:
                critical_edges.append(i)
            else:
                # Check if edge is pseudo-critical
                if kruskal(include_edge=(weight, u, v, i)) == original_mst_weight:
                    pseudo_critical_edges.append(i) 
        return [critical_edges, pseudo_critical_edges]  