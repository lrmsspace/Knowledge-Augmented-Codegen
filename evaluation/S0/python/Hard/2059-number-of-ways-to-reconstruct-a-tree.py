# Source: https://leetcode.com/problems/number-of-ways-to-reconstruct-a-tree/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array pairs, where pairs[i] = [xi, yi], and:
#
#
# 	There are no duplicates.
# 	xi < yi
#
#
# Let ways be the number of rooted trees that satisfy the following conditions:
#
#
# 	The tree consists of nodes whose values appeared in pairs.
# 	A pair [xi, yi] exists in pairs if and only if xi is an ancestor of yi or yi is an ancestor of xi.
# 	Note: the tree does not have to be a binary tree.
#
#
# Two ways are considered to be different if there is at least one node that has different parents in both ways.
#
# Return:
#
#
# 	0 if ways == 0
# 	1 if ways == 1
# 	2 if ways > 1
#
#
# A rooted tree is a tree that has a single root node, and all edges are oriented to be outgoing from the root.
#
# An ancestor of a node is any node on the path from the root to that node (excluding the node itself). The root has no ancestors.
#
# Example:
# Input: pairs = [[1,2],[2,3]]
# Output: 1
# Explanation: There is exactly one valid rooted tree, which is shown in the above figure.
#
# Constraints:
# 1 <= pairs.length <= 105
# 	1 <= xi < yi <= 500
# 	The elements in pairs are unique.
#

class Solution(object):
    def checkWays(self, pairs):
        """
        :type pairs: List[List[int]]
        :rtype: int
        """
        from collections import defaultdict
        
        graph = defaultdict(set)
        nodes = set()
        
        for u, v in pairs:
            graph[u].add(v)
            graph[v].add(u)
            nodes.add(u)
            nodes.add(v)
        
        res = 1
        for node in nodes:
            degree = len(graph[node])
            parent = -1
            parent_degree = float('inf')
            
            for neighbor in graph[node]:
                if len(graph[neighbor]) < parent_degree and len(graph[neighbor]) >= degree:
                    parent = neighbor
                    parent_degree = len(graph[neighbor])
            
            if parent == -1 and degree != len(nodes) - 1:
                return 0
            
            for neighbor in graph[node]:
                if neighbor != parent and neighbor not in graph[parent]:
                    return 0
            
            if parent != -1 and parent_degree == degree:
                res = 2
        
        return res