# Source: https://leetcode.com/problems/merge-k-sorted-lists/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
#
# Merge all the linked-lists into one sorted linked-list and return it.
#
# Example:
# Input: lists = [[1,4,5],[1,3,4],[2,6]]
# Output: [1,1,2,3,4,4,5,6]
# Explanation: The linked-lists are:
# [
#   1->4->5,
#   1->3->4,
#   2->6
# ]
# merging them into one sorted linked list:
# 1->1->2->3->4->4->5->6
#
# Constraints:
# k == lists.length
# 	0 <= k <= 104
# 	0 <= lists[i].length <= 500
# 	-104 <= lists[i][j] <= 104
# 	lists[i] is sorted in ascending order.
# 	The sum of lists[i].length will not exceed 104.
#

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution(object):
    def mergeKLists(self, lists):
        """
        :type lists: List[Optional[ListNode]]
        :rtype: Optional[ListNode]
        """
        import heapq

        min_heap = []
        
        # Initialize the heap with the head of each list
        for l in lists:
            if l:
                heapq.heappush(min_heap, (l.val, l))
        
        dummy = ListNode(0)
        current = dummy
        
        while min_heap:
            val, node = heapq.heappop(min_heap)
            current.next = ListNode(val)
            current = current.next
            
            if node.next:
                heapq.heappush(min_heap, (node.next.val, node.next))
        
        return dummy.next