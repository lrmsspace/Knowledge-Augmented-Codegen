# Source: https://leetcode.com/problems/path-in-zigzag-labelled-binary-tree/   |   Difficulty: Medium
#
# Problem Description:
# In an infinite binary tree where every node has two children, the nodes are labelled in row order.
#
# In the odd numbered rows (ie., the first, third, fifth,...), the labelling is left to right, while in the even numbered rows (second, fourth, sixth,...), the labelling is right to left.
#
#
#
# Given the label of a node in this tree, return the labels in the path from the root of the tree to the node with that label.
#
# Example:
# Input: label = 14
# Output: [1,3,4,14]
#
# Constraints:
# 1 <= label <= 10^6
#

class Solution(object):
    def pathInZigZagTree(self, label):
        """
        :type label: int
        :rtype: List[int]
        """
        path = []
        level = 0
        node = label
        
        # Determine the level of the node
        while (1 << level) <= node:
            level += 1
        
        while level > 0:
            path.append(node)
            level -= 1
            
            # Calculate the total number of nodes at the current level
            total_nodes_at_level = 1 << level
            
            # Calculate the parent node in a normal binary tree
            parent = node // 2
            
            # If the current level is even, we need to adjust for zigzag labeling
            if level % 2 == 0:
                node = (total_nodes_at_level * 2 - 1) - parent
            else:
                node = parent
        
        return path[::-1]