# Source: https://leetcode.com/problems/all-elements-in-two-binary-search-trees/   |   Difficulty: Medium
#
# Problem Description:
# Given two binary search trees root1 and root2, return a list containing all the integers from both trees sorted in ascending order.
#
# Example:
# Input: root1 = [2,1,4], root2 = [1,0,3]
# Output: [0,1,1,2,3,4]
#
# Constraints:
# The number of nodes in each tree is in the range [0, 5000].
# 	-105 <= Node.val <= 105
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def getAllElements(self, root1, root2):
        """
        :type root1: Optional[TreeNode]
        :type root2: Optional[TreeNode]
        :rtype: List[int]
        """
        def inorder_traversal(root, elements):
            if root:
                inorder_traversal(root.left, elements)
                elements.append(root.val)
                inorder_traversal(root.right, elements)

        elements1 = []
        elements2 = []
        
        inorder_traversal(root1, elements1)
        inorder_traversal(root2, elements2)
        
        # Merge the two sorted lists
        merged_elements = []
        i, j = 0, 0
        
        while i < len(elements1) and j < len(elements2):
            if elements1[i] < elements2[j]:
                merged_elements.append(elements1[i])
                i += 1
            else:
                merged_elements.append(elements2[j])
                j += 1
        
        # Append remaining elements
        while i < len(elements1):
            merged_elements.append(elements1[i])
            i += 1
        
        while j < len(elements2):
            merged_elements.append(elements2[j])
            j += 1
        
        return merged_elements