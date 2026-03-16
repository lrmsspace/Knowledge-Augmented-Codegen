# Source: https://leetcode.com/problems/find-number-of-coins-to-place-in-tree-nodes/   |   Difficulty: Hard
#
# Problem Description:
# You are given an undirected tree with n nodes labeled from 0 to n - 1, and rooted at node 0. You are given a 2D integer array edges of length n - 1, where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
#
# You are also given a 0-indexed integer array cost of length n, where cost[i] is the cost assigned to the ith node.
#
# You need to place some coins on every node of the tree. The number of coins to be placed at node i can be calculated as:
#
#
# 	If size of the subtree of node i is less than 3, place 1 coin.
# 	Otherwise, place an amount of coins equal to the maximum product of cost values assigned to 3 distinct nodes in the subtree of node i. If this product is negative, place 0 coins.
#
#
# Return an array coin of size n such that coin[i] is the number of coins placed at node i.
#
# Example:
# Input: edges = [[0,1],[0,2],[0,3],[0,4],[0,5]], cost = [1,2,3,4,5,6]
# Output: [120,1,1,1,1,1]
# Explanation: For node 0 place 6 * 5 * 4 = 120 coins. All other nodes are leaves with subtree of size 1, place 1 coin on each of them.
#
# Constraints:
# 2 <= n <= 2 * 104
# 	edges.length == n - 1
# 	edges[i].length == 2
# 	0 <= ai, bi < n
# 	cost.length == n
# 	1 <= |cost[i]| <= 104
# 	The input is generated such that edges represents a valid tree.
#

class Solution(object):
    def placedCoins(self, edges, cost):
        """
        :type edges: List[List[int]]
        :type cost: List[int]
        :rtype: List[int]
        """
        from collections import defaultdict
        import sys
        sys.setrecursionlimit(10**7)

        n = len(cost)
        tree = defaultdict(list)
        for u, v in edges:
            tree[u].append(v)
            tree[v].append(u)

        res = [0] * n

        def dfs(node, parent):
            subtree_nodes = [cost[node]]
            for neighbor in tree[node]:
                if neighbor != parent:
                    subtree_nodes.extend(dfs(neighbor, node))

            size = len(subtree_nodes)
            if size < 3:
                res[node] = 1
            else:
                subtree_nodes.sort(reverse=True)
                max_product = subtree_nodes[0] * subtree_nodes[1] * subtree_nodes[2]
                res[node] = max(0, max_product)

            return subtree_nodes

        dfs(0, -1)
        return res