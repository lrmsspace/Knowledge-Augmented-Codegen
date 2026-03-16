# Source: https://leetcode.com/problems/tree-of-coprimes/   |   Difficulty: Hard
#
# Problem Description:
# There is a tree (i.e., a connected, undirected graph that has no cycles) consisting of n nodes numbered from 0 to n - 1 and exactly n - 1 edges. Each node has a value associated with it, and the root of the tree is node 0.
#
# To represent this tree, you are given an integer array nums and a 2D array edges. Each nums[i] represents the ith node's value, and each edges[j] = [uj, vj] represents an edge between nodes uj and vj in the tree.
#
# Two values x and y are coprime if gcd(x, y) == 1 where gcd(x, y) is the greatest common divisor of x and y.
#
# An ancestor of a node i is any other node on the shortest path from node i to the root. A node is not considered an ancestor of itself.
#
# Return an array ans of size n, where ans[i] is the closest ancestor to node i such that nums[i] and nums[ans[i]] are coprime, or -1 if there is no such ancestor.
#
# Example:
# Input: nums = [2,3,3,2], edges = [[0,1],[1,2],[1,3]]
# Output: [-1,0,0,1]
# Explanation: In the above figure, each node's value is in parentheses.
# - Node 0 has no coprime ancestors.
# - Node 1 has only one ancestor, node 0. Their values are coprime (gcd(2,3) == 1).
# - Node 2 has two ancestors, nodes 1 and 0. Node 1's value is not coprime (gcd(3,3) == 3), but node 0's
#   value is (gcd(2,3) == 1), so node 0 is the closest valid ancestor.
# - Node 3 has two ancestors, nodes 1 and 0. It is coprime with node 1 (gcd(3,2) == 1), so node 1 is its
#   closest valid ancestor.
#
# Constraints:
# nums.length == n
# 	1 <= nums[i] <= 50
# 	1 <= n <= 105
# 	edges.length == n - 1
# 	edges[j].length == 2
# 	0 <= uj, vj < n
# 	uj != vj
#

class Solution(object):
    def getCoprimes(self, nums, edges):
        """
        :type nums: List[int]
        :type edges: List[List[int]]
        :rtype: List[int]
        """
        from math import gcd
        from collections import defaultdict

        n = len(nums)
        tree = defaultdict(list)
        for u, v in edges:
            tree[u].append(v)
            tree[v].append(u)

        ans = [-1] * n
        stack = [(0, -1)]  # (node, parent)
        path = []  # (node, depth)
        value_map = defaultdict(list)  # value -> list of (node, depth)

        while stack:
            node, parent = stack.pop()
            num = nums[node]

            # Find the closest coprime ancestor
            max_depth = -1
            ancestor = -1
            for val in range(1, 51):
                if gcd(num, val) == 1 and value_map[val]:
                    anc_node, depth = value_map[val][-1]
                    if depth > max_depth:
                        max_depth = depth
                        ancestor = anc_node
            ans[node] = ancestor

            # Add current node to path and value_map
            path.append((node, len(path)))
            value_map[num].append((node, len(path) - 1))

            # Traverse children
            for neighbor in tree[node]:
                if neighbor != parent:
                    stack.append((neighbor, node))

            # Backtrack: remove current node from path and value_map
            path.pop()
            value_map[num].pop()

        return ans