# Source: https://leetcode.com/problems/minimum-score-after-removals-on-a-tree/   |   Difficulty: Hard
#
# Problem Description:
# There is an undirected connected tree with n nodes labeled from 0 to n - 1 and n - 1 edges.
#
# You are given a 0-indexed integer array nums of length n where nums[i] represents the value of the ith node. You are also given a 2D integer array edges of length n - 1 where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
#
# Remove two distinct edges of the tree to form three connected components. For a pair of removed edges, the following steps are defined:
#
#
# 	Get the XOR of all the values of the nodes for each of the three components respectively.
# 	The difference between the largest XOR value and the smallest XOR value is the score of the pair.
#
#
#
# 	For example, say the three components have the node values: [4,5,7], [1,9], and [3,3,3]. The three XOR values are 4 ^ 5 ^ 7 = 6, 1 ^ 9 = 8, and 3 ^ 3 ^ 3 = 3. The largest XOR value is 8 and the smallest XOR value is 3. The score is then 8 - 3 = 5.
#
#
# Return the minimum score of any possible pair of edge removals on the given tree.
#
# Example:
# Input: nums = [1,5,5,4,11], edges = [[0,1],[1,2],[1,3],[3,4]]
# Output: 9
# Explanation: The diagram above shows a way to make a pair of removals.
# - The 1st component has nodes [1,3,4] with values [5,4,11]. Its XOR value is 5 ^ 4 ^ 11 = 10.
# - The 2nd component has node [0] with value [1]. Its XOR value is 1 = 1.
# - The 3rd component has node [2] with value [5]. Its XOR value is 5 = 5.
# The score is the difference between the largest and smallest XOR value which is 10 - 1 = 9.
# It can be shown that no other pair of removals will obtain a smaller score than 9.
#
# Constraints:
# n == nums.length
# 	3 <= n <= 1000
# 	1 <= nums[i] <= 108
# 	edges.length == n - 1
# 	edges[i].length == 2
# 	0 <= ai, bi < n
# 	ai != bi
# 	edges represents a valid tree.
#

class Solution(object):
    def minimumScore(self, nums, edges):
        """
        :type nums: List[int]
        :type edges: List[List[int]]
        :rtype: int
        """
        from collections import defaultdict

        n = len(nums)
        tree = defaultdict(list)
        for u, v in edges:
            tree[u].append(v)
            tree[v].append(u)

        total_xor = 0
        for num in nums:
            total_xor ^= num

        parent = [-1] * n
        subtree_xor = [0] * n

        def dfs(node, par):
            subtree_xor[node] = nums[node]
            parent[node] = par
            for child in tree[node]:
                if child != par:
                    dfs(child, node)
                    subtree_xor[node] ^= subtree_xor[child]

        dfs(0, -1)

        min_score = float('inf')

        for i in range(1, n):
            for j in range(i + 1, n):
                xor1 = subtree_xor[i]
                xor2 = subtree_xor[j]

                if parent[j] == i:
                    xor2 = total_xor ^ subtree_xor[i]
                elif parent[i] == j:
                    xor1 = total_xor ^ subtree_xor[j]

                xor3 = total_xor ^ xor1 ^ xor2
                current_score = max(xor1, xor2, xor3) - min(xor1, xor2, xor3)
                min_score = min(min_score, current_score)

        return min_score    