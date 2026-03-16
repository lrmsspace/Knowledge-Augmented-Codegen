# Source: https://leetcode.com/problems/building-boxes/   |   Difficulty: Hard
#
# Problem Description:
# You have a cubic storeroom where the width, length, and height of the room are all equal to n units. You are asked to place n boxes in this room where each box is a cube of unit side length. There are however some rules to placing the boxes:
#
#
# 	You can place the boxes anywhere on the floor.
# 	If box x is placed on top of the box y, then each side of the four vertical sides of the box y must either be adjacent to another box or to a wall.
#
#
# Given an integer n, return the minimum possible number of boxes touching the floor.
#
# Example:
# Input: n = 3
# Output: 3
# Explanation: The figure above is for the placement of the three boxes.
# These boxes are placed in the corner of the room, where the corner is on the left side.
#
# Constraints:
# 1 <= n <= 109
#

class Solution(object):
    def minimumBoxes(self, n):
        """
        :type n: int
        :rtype: int
        """
        layer = 0
        total_boxes = 0
        
        # Find the maximum complete layers we can build with n boxes
        while total_boxes + (layer + 1) * (layer + 2) // 2 <= n:
            layer += 1
            total_boxes += layer * (layer + 1) // 2
        
        # Calculate remaining boxes after building complete layers
        remaining_boxes = n - total_boxes
        additional_boxes = 0
        current_row = 1
        
        # Place remaining boxes in the next layer
        while remaining_boxes > 0:
            boxes_in_current_row = min(remaining_boxes, current_row)
            additional_boxes += boxes_in_current_row
            remaining_boxes -= boxes_in_current_row
            current_row += 1
        
        return (layer * (layer + 1)) // 2 + additional_boxes