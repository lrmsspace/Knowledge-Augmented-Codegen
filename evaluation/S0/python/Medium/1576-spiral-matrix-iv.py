# Source: https://leetcode.com/problems/spiral-matrix-iv/   |   Difficulty: Medium
#
# Problem Description:
# You are given two integers m and n, which represent the dimensions of a matrix.
#
# You are also given the head of a linked list of integers.
#
# Generate an m x n matrix that contains the integers in the linked list presented in spiral order (clockwise), starting from the top-left of the matrix. If there are remaining empty spaces, fill them with -1.
#
# Return the generated matrix.
#
# Example:
# Input: m = 3, n = 5, head = [3,0,2,6,8,1,7,9,4,2,5,5,0]
# Output: [[3,0,2,6,8],[5,0,-1,-1,1],[5,2,4,9,7]]
# Explanation: The diagram above shows how the values are printed in the matrix.
# Note that the remaining spaces in the matrix are filled with -1.
#
# Constraints:
# 1 <= m, n <= 105
# 	1 <= m * n <= 105
# 	The number of nodes in the list is in the range [1, m * n].
# 	0 <= Node.val <= 1000
#

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution(object):
    def spiralMatrix(self, m, n, head):
        """
        :type m: int
        :type n: int
        :type head: Optional[ListNode]
        :rtype: List[List[int]]
        """
        matrix = [[-1 for _ in range(n)] for _ in range(m)]
        
        top, bottom, left, right = 0, m - 1, 0, n - 1
        current = head
        
        while top <= bottom and left <= right and current:
            for col in range(left, right + 1):
                if current:
                    matrix[top][col] = current.val
                    current = current.next
            top += 1
            
            for row in range(top, bottom + 1):
                if current:
                    matrix[row][right] = current.val
                    current = current.next
            right -= 1
            
            if top <= bottom:
                for col in range(right, left - 1, -1):
                    if current:
                        matrix[bottom][col] = current.val
                        current = current.next
                bottom -= 1
            
            if left <= right:
                for row in range(bottom, top - 1, -1):
                    if current:
                        matrix[row][left] = current.val
                        current = current.next
                left += 1
        
        return matrix