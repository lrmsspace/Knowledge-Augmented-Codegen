# Source: https://leetcode.com/problems/maximum-score-after-applying-operations-on-a-tree/   |   Difficulty: Medium
#
# Problem Description:
# There is an undirected tree with n nodes labeled from 0 to n - 1, and rooted at node 0. You are given a 2D integer array edges of length n - 1, where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
#
# You are also given a 0-indexed integer array values of length n, where values[i] is the value associated with the ith node.
#
# You start with a score of 0. In one operation, you can:
#
#
# 	Pick any node i.
# 	Add values[i] to your score.
# 	Set values[i] to 0.
#
#
# A tree is healthy if the sum of values on the path from the root to any leaf node is different than zero.
#
# Return the maximum score you can obtain after performing these operations on the tree any number of times so that it remains healthy.
#
# Example:
# Input: edges = [[0,1],[0,2],[0,3],[2,4],[4,5]], values = [5,2,5,2,1,1]
# Output: 11
# Explanation: We can choose nodes 1, 2, 3, 4, and 5. The value of the root is non-zero. Hence, the sum of values on the path from the root to any leaf is different than zero. Therefore, the tree is healthy and the score is values[1] + values[2] + values[3] + values[4] + values[5] = 11.
# It can be shown that 11 is the maximum score obtainable after any number of operations on the tree.
#
# Constraints:
# 2 <= n <= 2 * 104
# 	edges.length == n - 1
# 	edges[i].length == 2
# 	0 <= ai, bi < n
# 	values.length == n
# 	1 <= values[i] <= 109
# 	The input is generated such that edges represents a valid tree.
#

class Solution(object):
    def maximumScoreAfterOperations(self, edges, values):
        """
        :type edges: List[List[int]]
        :type values: List[int]
        :rtype: int
        """
        from collections import defaultdict
        
        n = len(values)
        tree = defaultdict(list)
        
        for u, v in edges:
            tree[u].append(v)
            tree[v].append(u)
        
        def dfs(node, parent):
            total = values[node]
            for neighbor in tree[node]:
                if neighbor != parent:
                    total += dfs(neighbor, node)
            return max(total, 0)
        
        return dfs(0, -1)