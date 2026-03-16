# Source: https://leetcode.com/problems/delete-node-in-a-bst/   |   Difficulty: Medium
#
# Problem Description:
# Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node reference (possibly updated) of the BST.
#
# Basically, the deletion can be divided into two stages:
#
#
# 	Search for a node to remove.
# 	If the node is found, delete the node.
#
# Example:
# Input: root = [5,3,6,2,4,null,7], key = 3
# Output: [5,4,6,2,null,null,7]
# Explanation: Given key to delete is 3. So we find the node with value 3 and delete it.
# One valid answer is [5,4,6,2,null,null,7], shown in the above BST.
# Please notice that another valid answer is [5,2,6,null,4,null,7] and it's also accepted.
#
# Constraints:
# The number of nodes in the tree is in the range [0, 104].
# 	-105 <= Node.val <= 105
# 	Each node has a unique value.
# 	root is a valid binary search tree.
# 	-105 <= key <= 105
#
#
#  
# Follow up: Could you solve it with time complexity O(height of tree)?
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def deleteNode(self, root, key):
        """
        :type root: Optional[TreeNode]
        :type key: int
        :rtype: Optional[TreeNode]
        """
        if not root:
            return None
        
        if key < root.val:
            root.left = self.deleteNode(root.left, key)
        elif key > root.val:
            root.right = self.deleteNode(root.right, key)
        else:
            # Node with only one child or no child
            if not root.left:
                return root.right
            elif not root.right:
                return root.left
            
            # Node with two children: Get the inorder successor (smallest in the right subtree)
            temp = self.findMin(root.right)
            root.val = temp.val
            root.right = self.deleteNode(root.right, temp.val)
        
        return root