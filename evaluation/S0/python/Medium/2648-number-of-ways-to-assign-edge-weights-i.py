# Source: https://leetcode.com/problems/number-of-ways-to-assign-edge-weights-i/   |   Difficulty: Medium
#
# Problem Description:
# There is an undirected tree with n nodes labeled from 1 to n, rooted at node 1. The tree is represented by a 2D integer array edges of length n - 1, where edges[i] = [ui, vi] indicates that there is an edge between nodes ui and vi.
#
# Initially, all edges have a weight of 0. You must assign each edge a weight of either 1 or 2.
#
# The cost of a path between any two nodes u and v is the total weight of all edges in the path connecting them.
#
# Select any one node x at the maximum depth. Return the number of ways to assign edge weights in the path from node 1 to x such that its total cost is odd.
#
# Since the answer may be large, return it modulo 109 + 7.
#
# Note: Ignore all edges not in the path from node 1 to x.
#
# Example:
# Input: edges = [[1,2]]
#
# Output: 1
#
# Explanation:
#
#
# 	The path from Node 1 to Node 2 consists of one edge (1 → 2).
# 	Assigning weight 1 makes the cost odd, while 2 makes it even. Thus, the number of valid assignments is 1.
#
# Constraints:
# 2 <= n <= 105
# 	edges.length == n - 1
# 	edges[i] == [ui, vi]
# 	1 <= ui, vi <= n
# 	edges represents a valid tree.
#

class Solution(object):
    def assignEdgeWeights(self, edges):
        """
        :type edges: List[List[int]]
        :rtype: int
        """
        MOD = 10**9 + 7
        
        from collections import defaultdict, deque
        
        n = len(edges) + 1
        tree = defaultdict(list)
        
        for u, v in edges:
            tree[u].append(v)
            tree[v].append(u)
        
        # BFS to find the maximum depth
        max_depth = 0
        queue = deque([(1, 0)])  # (node, depth)
        visited = set([1])
        
        while queue:
            node, depth = queue.popleft()
            max_depth = max(max_depth, depth)
            
            for neighbor in tree[node]:
                if neighbor not in visited:
                    visited.add(neighbor)
                    queue.append((neighbor, depth + 1))
        
        # The number of ways to assign weights such that the total cost is odd
        # is equal to the number of edges in the path from root to the deepest node.
        # Each edge can be assigned weight 1 or 2, and we need an odd sum.
        # This can be achieved by having an odd number of edges with weight 1.
        
        # If max_depth is even, we can have (max_depth // 2) edges with weight 1
        # and (max_depth // 2) edges with weight 2. The number of ways is C(max_depth, max_depth // 2).
        # If max_depth is odd, we can have (max_depth // 2 + 1) edges with weight 1
        # and (max_depth // 2) edges with weight 2. The number of ways is C(max_depth, max_depth // 2 + 1).
        
        from math import comb
        
        if max_depth % 2 == 0:
            ways = comb(max_depth, max_depth // 2) % MOD
        else:
            ways = comb(max_depth, max_depth // 2 + 1) % MOD
        
        return ways