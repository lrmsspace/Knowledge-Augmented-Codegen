# Source: https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/   |   Difficulty: Medium
#
# Problem Description:
# Given an n x n matrix where each of the rows and columns is sorted in ascending order, return the kth smallest element in the matrix.
#
# Note that it is the kth smallest element in the sorted order, not the kth distinct element.
#
# You must find a solution with a memory complexity better than O(n2).
#
# Example:
# Input: matrix = [[1,5,9],[10,11,13],[12,13,15]], k = 8
# Output: 13
# Explanation: The elements in the matrix are [1,5,9,10,11,12,13,13,15], and the 8th smallest number is 13
#
# Constraints:
# n == matrix.length == matrix[i].length
# 	1 <= n <= 300
# 	-109 <= matrix[i][j] <= 109
# 	All the rows and columns of matrix are guaranteed to be sorted in non-decreasing order.
# 	1 <= k <= n2
#
#
#  
# Follow up:
#
#
# 	Could you solve the problem with a constant memory (i.e., O(1) memory complexity)?
# 	Could you solve the problem in O(n) time complexity? The solution may be too advanced for an interview but you may find reading this paper fun.
#

class Solution(object):
    def kthSmallest(self, matrix, k):
        """
        :type matrix: List[List[int]]
        :type k: int
        :rtype: int
        """
        import heapq
        n = len(matrix)
        min_heap = []
        
        # Initialize the heap with the first element of each row
        for r in range(min(k, n)):  # No need to push more than k rows
            heapq.heappush(min_heap, (matrix[r][0], r, 0))
        
        # Extract-min k-1 times
        for _ in range(k - 1):
            element, r, c = heapq.heappop(min_heap)
            if c + 1 < n:
                heapq.heappush(min_heap, (matrix[r][c + 1], r, c + 1))
        
        return min_heap[0][0]