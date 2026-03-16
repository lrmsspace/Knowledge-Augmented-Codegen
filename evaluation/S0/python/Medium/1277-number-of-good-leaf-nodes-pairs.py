# Source: https://leetcode.com/problems/number-of-good-leaf-nodes-pairs/   |   Difficulty: Medium
#
# Problem Description:
# You are given the root of a binary tree and an integer distance. A pair of two different leaf nodes of a binary tree is said to be good if the length of the shortest path between them is less than or equal to distance.
#
# Return the number of good leaf node pairs in the tree.
#
# Example:
# Input: root = [1,2,3,null,4], distance = 3
# Output: 1
# Explanation: The leaf nodes of the tree are 3 and 4 and the length of the shortest path between them is 3. This is the only good pair.
#
# Constraints:
# The number of nodes in the tree is in the range [1, 210].
# 	1 <= Node.val <= 100
# 	1 <= distance <= 10
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def countPairs(self, root, distance):
        """
        :type root: Optional[TreeNode]
        :type distance: int
        :rtype: int
        """
        self.result = 0
        
        def dfs(node):
            if not node:
                return []
            if not node.left and not node.right:
                return [1]
            
            left_distances = dfs(node.left)
            right_distances = dfs(node.right)
            
            for ld in left_distances:
                for rd in right_distances:
                    if ld + rd <= distance:
                        self.result += 1
            
            current_distances = []
            for d in left_distances + right_distances:
                if d + 1 < distance:
                    current_distances.append(d + 1)
            
            return current_distances
        
        dfs(root)
        return self.result