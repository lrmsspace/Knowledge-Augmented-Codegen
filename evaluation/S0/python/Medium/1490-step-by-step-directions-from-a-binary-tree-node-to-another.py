# Source: https://leetcode.com/problems/step-by-step-directions-from-a-binary-tree-node-to-another/   |   Difficulty: Medium
#
# Problem Description:
# You are given the root of a binary tree with n nodes. Each node is uniquely assigned a value from 1 to n. You are also given an integer startValue representing the value of the start node s, and a different integer destValue representing the value of the destination node t.
#
# Find the shortest path starting from node s and ending at node t. Generate step-by-step directions of such path as a string consisting of only the uppercase letters 'L', 'R', and 'U'. Each letter indicates a specific direction:
#
#
# 	'L' means to go from a node to its left child node.
# 	'R' means to go from a node to its right child node.
# 	'U' means to go from a node to its parent node.
#
#
# Return the step-by-step directions of the shortest path from node s to node t.
#
# Example:
# Input: root = [5,1,2,3,null,6,4], startValue = 3, destValue = 6
# Output: "UURL"
# Explanation: The shortest path is: 3 → 1 → 5 → 2 → 6.
#
# Constraints:
# The number of nodes in the tree is n.
# 	2 <= n <= 105
# 	1 <= Node.val <= n
# 	All the values in the tree are unique.
# 	1 <= startValue, destValue <= n
# 	startValue != destValue
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def getDirections(self, root, startValue, destValue):
        """
        :type root: Optional[TreeNode]
        :type startValue: int
        :type destValue: int
        :rtype: str
        """
        parent = {}
        def dfs(node):
            if not node:
                return
            if node.left:
                parent[node.left.val] = (node.val, 'L')
                dfs(node.left)
            if node.right:
                parent[node.right.val] = (node.val, 'R')
                dfs(node.right)
        dfs(root)

        path_to_root_start = []
        while startValue in parent:
            p, d = parent[startValue]
            path_to_root_start.append((p, d))
            startValue = p

        path_to_root_dest = []
        while destValue in parent:
            p, d = parent[destValue]
            path_to_root_dest.append((p, d))
            destValue = p

        i = len(path_to_root_start) - 1
        j = len(path_to_root_dest) - 1
        while i >= 0 and j >= 0 and path_to_root_start[i][0] == path_to_root_dest[j][0]:
            i -= 1
            j -= 1

        directions = []
        for k in range(i + 1):
            directions.append('U')
        for k in range(j, -1, -1):
            directions.append(path_to_root_dest[k][1])

        return ''.join(directions)