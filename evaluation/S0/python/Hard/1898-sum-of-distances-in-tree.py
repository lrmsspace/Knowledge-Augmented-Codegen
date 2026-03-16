# Source: https://leetcode.com/problems/sum-of-distances-in-tree/   |   Difficulty: Hard
#
# Problem Description:
# There is an undirected connected tree with n nodes labeled from 0 to n - 1 and n - 1 edges.
#
# You are given the integer n and the array edges where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
#
# Return an array answer of length n where answer[i] is the sum of the distances between the ith node in the tree and all other nodes.
#
# Example:
# Input: n = 6, edges = [[0,1],[0,2],[2,3],[2,4],[2,5]]
# Output: [8,12,6,10,10,10]
# Explanation: The tree is shown above.
# We can see that dist(0,1) + dist(0,2) + dist(0,3) + dist(0,4) + dist(0,5)
# equals 1 + 1 + 2 + 2 + 2 = 8.
# Hence, answer[0] = 8, and so on.
#
# Constraints:
# 1 <= n <= 3 * 104
# 	edges.length == n - 1
# 	edges[i].length == 2
# 	0 <= ai, bi < n
# 	ai != bi
# 	The given input represents a valid tree.
#

class Solution(object):
    def sumOfDistancesInTree(self, n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: List[int]
        """
        from collections import defaultdict

        tree = defaultdict(list)
        for u, v in edges:
            tree[u].append(v)
            tree[v].append(u)

        count = [1] * n
        res = [0] * n

        def post_order(node, parent):
            for child in tree[node]:
                if child != parent:
                    post_order(child, node)
                    count[node] += count[child]
                    res[node] += res[child] + count[child]

        def pre_order(node, parent):
            for child in tree[node]:
                if child != parent:
                    res[child] = res[node] - count[child] + (n - count[child])
                    pre_order(child, node)

        post_order(0, -1)
        pre_order(0, -1)
        return res