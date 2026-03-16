# Source: https://leetcode.com/problems/find-the-minimum-and-maximum-number-of-nodes-between-critical-points/   |   Difficulty: Medium
#
# Problem Description:
# A critical point in a linked list is defined as either a local maxima or a local minima.
#
# A node is a local maxima if the current node has a value strictly greater than the previous node and the next node.
#
# A node is a local minima if the current node has a value strictly smaller than the previous node and the next node.
#
# Note that a node can only be a local maxima/minima if there exists both a previous node and a next node.
#
# Given a linked list head, return an array of length 2 containing [minDistance, maxDistance] where minDistance is the minimum distance between any two distinct critical points and maxDistance is the maximum distance between any two distinct critical points. If there are fewer than two critical points, return [-1, -1].
#
# Example:
# Input: head = [3,1]
# Output: [-1,-1]
# Explanation: There are no critical points in [3,1].
#
# Constraints:
# The number of nodes in the list is in the range [2, 105].
# 	1 <= Node.val <= 105
#

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution(object):
    def nodesBetweenCriticalPoints(self, head):
        """
        :type head: Optional[ListNode]
        :rtype: List[int]
        """
        critical_points = []
        index = 1
        prev = head
        curr = head.next

        while curr and curr.next:
            if (curr.val > prev.val and curr.val > curr.next.val) or (curr.val < prev.val and curr.val < curr.next.val):
                critical_points.append(index)
            prev = curr
            curr = curr.next
            index += 1

        if len(critical_points) < 2:
            return [-1, -1]

        min_distance = float('inf')
        for i in range(1, len(critical_points)):
            min_distance = min(min_distance, critical_points[i] - critical_points[i - 1])

        max_distance = critical_points[-1] - critical_points[0]

        return [min_distance, max_distance]