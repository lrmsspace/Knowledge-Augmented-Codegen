# Source: https://leetcode.com/problems/count-the-number-of-good-nodes/   |   Difficulty: Medium
#
# Problem Description:
# There is an undirected tree with n nodes labeled from 0 to n - 1, and rooted at node 0. You are given a 2D integer array edges of length n - 1, where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
#
# A node is good if all the subtrees rooted at its children have the same size.
#
# Return the number of good nodes in the given tree.
#
# A subtree of treeName is a tree consisting of a node in treeName and all of its descendants.
#
# Example:
# Input: edges = [[0,1],[0,2],[1,3],[1,4],[2,5],[2,6]]
#
# Output: 7
#
# Explanation:
#
# All of the nodes of the given tree are good.
#
# Constraints:
# 2 <= n <= 105
# 	edges.length == n - 1
# 	edges[i].length == 2
# 	0 <= ai, bi < n
# 	The input is generated such that edges represents a valid tree.
#

class Solution(object):
    def countGoodNodes(self, edges):
        """
        :type edges: List[List[int]]
        :rtype: int
        """
        from collections import defaultdict
        
        tree = defaultdict(list)
        for a, b in edges:
            tree[a].append(b)
            tree[b].append(a)
        
        self.good_nodes_count = 0
        
        def dfs(node, parent):
            sizes = []
            for child in tree[node]:
                if child != parent:
                    sizes.append(dfs(child, node))
            
            if len(sizes) == 0 or all(size == sizes[0] for size in sizes):
                self.good_nodes_count += 1
            
            return 1 + sum(sizes)
        
        dfs(0, -1)
        return self.good_nodes_count