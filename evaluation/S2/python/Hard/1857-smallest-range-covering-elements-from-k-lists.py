# Source: https://leetcode.com/problems/smallest-range-covering-elements-from-k-lists/   |   Difficulty: Hard
#
# Problem Description:
# You have k lists of sorted integers in non-decreasing order. Find the smallest range that includes at least one number from each of the k lists.
#
# We define the range [a, b] is smaller than range [c, d] if b - a < d - c or a < c if b - a == d - c.
#
# Example:
# Input: nums = [[4,10,15,24,26],[0,9,12,20],[5,18,22,30]]
# Output: [20,24]
# Explanation: 
# List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
# List 2: [0, 9, 12, 20], 20 is in range [20,24].
# List 3: [5, 18, 22, 30], 22 is in range [20,24].
#
# Constraints:
# nums.length == k
# 	1 <= k <= 3500
# 	1 <= nums[i].length <= 50
# 	-105 <= nums[i][j] <= 105
# 	nums[i] is sorted in non-decreasing order.
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def smallestRange(self, nums):
        """
        :type nums: List[List[int]]
        :rtype: List[int]
        """
        import heapq
        
        # Create a min-heap to store the current elements from each list
        min_heap = []
        max_value = float('-inf')
        
        # Initialize the heap with the first element of each list
        for i in range(len(nums)):
            heapq.heappush(min_heap, (nums[i][0], i, 0))
            max_value = max(max_value, nums[i][0])
        
        best_range = [float('-inf'), float('inf')]
        
        while True:
            min_value, list_index, element_index = heapq.heappop(min_heap)
            
            # Update the best range if the current range is smaller
            if max_value - min_value < best_range[1] - best_range[0] or (max_value - min_value == best_range[1] - best_range[0] and min_value < best_range[0]):
                best_range = [min_value, max_value]
                
            # If we've exhausted one of the lists, break
            if element_index + 1 >= len(nums[list_index]):
                break
                
            # Push the next element from the same list into the heap
            next_value = nums[list_index][element_index + 1]
            heapq.heappush(min_heap, (next_value, list_index, element_index + 1))
            max_value = max(max_value, next_value)

        return best_range