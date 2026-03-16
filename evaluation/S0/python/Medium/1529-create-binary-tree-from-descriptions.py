# Source: https://leetcode.com/problems/create-binary-tree-from-descriptions/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 2D integer array descriptions where descriptions[i] = [parenti, childi, isLefti] indicates that parenti is the parent of childi in a binary tree of unique values. Furthermore,
#
#
# 	If isLefti == 1, then childi is the left child of parenti.
# 	If isLefti == 0, then childi is the right child of parenti.
#
#
# Construct the binary tree described by descriptions and return its root.
#
# The test cases will be generated such that the binary tree is valid.
#
# Example:
# Input: descriptions = [[20,15,1],[20,17,0],[50,20,1],[50,80,0],[80,19,1]]
# Output: [50,20,80,15,17,19]
# Explanation: The root node is the node with value 50 since it has no parent.
# The resulting binary tree is shown in the diagram.
#
# Constraints:
# 1 <= descriptions.length <= 104
# 	descriptions[i].length == 3
# 	1 <= parenti, childi <= 105
# 	0 <= isLefti <= 1
# 	The binary tree described by descriptions is valid.
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def createBinaryTree(self, descriptions):
        """
        :type descriptions: List[List[int]]
        :rtype: Optional[TreeNode]
        """
        parent_map = {}
        child_set = set()
        
        for parent, child, is_left in descriptions:
            if parent not in parent_map:
                parent_map[parent] = TreeNode(parent)
            if child not in parent_map:
                parent_map[child] = TreeNode(child)
            
            if is_left:
                parent_map[parent].left = parent_map[child]
            else:
                parent_map[parent].right = parent_map[child]
            
            child_set.add(child)
        
        # The root is the one that is never a child
        for parent in parent_map:
            if parent not in child_set:
                return parent_map[parent]
        
        return None