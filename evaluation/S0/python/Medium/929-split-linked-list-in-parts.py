# Source: https://leetcode.com/problems/split-linked-list-in-parts/   |   Difficulty: Medium
#
# Problem Description:
# Given the head of a singly linked list and an integer k, split the linked list into k consecutive linked list parts.
#
# The length of each part should be as equal as possible: no two parts should have a size differing by more than one. This may lead to some parts being null.
#
# The parts should be in the order of occurrence in the input list, and parts occurring earlier should always have a size greater than or equal to parts occurring later.
#
# Return an array of the k parts.
#
# Example:
# Input: head = [1,2,3], k = 5
# Output: [[1],[2],[3],[],[]]
# Explanation:
# The first element output[0] has output[0].val = 1, output[0].next = null.
# The last element output[4] is null, but its string representation as a ListNode is [].
#
# Constraints:
# The number of nodes in the list is in the range [0, 1000].
# 	0 <= Node.val <= 1000
# 	1 <= k <= 50
#

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution(object):
    def splitListToParts(self, head, k):
        """
        :type head: Optional[ListNode]
        :type k: int
        :rtype: List[Optional[ListNode]]
        """
        # 计算链表长度
        length = 0
        current = head
        while current:
            length += 1
            current = current.next
        
        # 计算每部分的基本大小和额外节点数
        part_size = length // k
        extra_nodes = length % k
        
        parts = []
        current = head
        
        for i in range(k):
            part_head = current
            size = part_size + (1 if i < extra_nodes else 0)
            
            for j in range(size - 1):
                if current:
                    current = current.next
            
            if current:
                next_part_head = current.next
                current.next = None
                current = next_part_head
            
            parts.append(part_head)
        
        return parts